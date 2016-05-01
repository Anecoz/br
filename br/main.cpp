#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <chrono>
#include <string>

#include "Logic\Level.h"
#include "Graphics\Camera.h"

#include "Input\KeyInput.h"
#include "Input\MousePosInput.h"
#include "Input\MouseButtonInput.h"

#include "Audio\AudioMaster.h"
#include "Audio\AudioSource.h"

#include "Font\FontRenderer.h"
#include "Font\Text.h"
#include "Graphics\GUI\Button.h"

#include "Graphics\Shaders\ShaderHandler.h"

using namespace std;
using namespace glm;

static void errorCallback(int error, const char* description) {
	cerr << description << endl;
}

int main() {	

	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
		exit(-1);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window;

	window = glfwCreateWindow(1280, 720, "BR Top", NULL, NULL);

	if (!window) {
		cerr << "Failed to open GLFW window lol" << endl;
		glfwTerminate();
		exit(-2);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, KeyInput::invoke);
	glfwSetCursorPosCallback(window, MousePosInput::invoke);
	glfwSetMouseButtonCallback(window, MouseButtonInput::invoke);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cerr << "Error: " << glewGetErrorString(err) << endl;
		exit(-3);
	}

	glClearColor(0.2, 0.2, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST);
	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
	cout << "Supported OpenGL version: " << glGetString(GL_VERSION) << endl;

	AudioMaster::init();
	AudioMaster::setListenerData(vec2(0), vec2(0));
	ALuint buffer = AudioMaster::loadSound("Resource/ambience_bird.wav");
	AudioSource source;
	source.setLooping(true);
	source.setVolume(1.0f);
	source.play(buffer);

	Level* level = new Level("Resource/maps/map_01.tmx");
	Camera* camera = new Camera(1280, 720);
	ShaderHandler::init();
	FontRenderer::init(1280, 720);

	// TESTING
	Text* text = new Text("Welcome to Kapperino Kapperoni", 0, 0, 64);
	Button* button = new Button("BUTTON", 30, glm::vec2(0.5f));
	button->setCallback([] {cout << "CALBBACK TRIGGERD" << endl; });

	using namespace chrono;
	long lastTime = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
	double delta = 0.0;
	double ns = 1000000000.0 / 60.0;
	long timer = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
	int updates = 0;
	int frames = 0;
	string ups = " ups ";
	string fps = " fps";

	while (!glfwWindowShouldClose(window)) {
		long now = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
		delta += (now - lastTime) / ns;
		lastTime = now;
		
		// Logic Update
		if (delta >= 1.0) {
			glfwPollEvents();			
			button->update();
			updates++;
			delta--;


			if (KeyInput::isKeyClicked(GLFW_KEY_ESCAPE))
				glfwSetWindowShouldClose(window, GL_TRUE);
		}

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		level->render(camera->getProjection());
		FontRenderer::render();
		glfwSwapBuffers(window);
		// Render stop
		
		frames++;
		if (duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count() - timer > 1000) {
			timer += 1000;
			glfwSetWindowTitle(window, std::string(to_string(updates) + ups + to_string(frames) + fps).c_str());
			updates = 0;
			frames = 0;
		}
	}

	delete level;
	level = nullptr;
	delete button;
	button = nullptr;
	delete text;
	text = nullptr;
	ShaderHandler::cleanUp();
	FontRenderer::cleanUp();
}