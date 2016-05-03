#include "Application.h"
#include "../../Input/KeyInput.h"
#include "../../Input/MousePosInput.h"
#include "../../Input/MouseButtonInput.h"
#include "../../Audio/AudioMaster.h"
#include "../../Graphics/Shaders/ShaderHandler.h"
#include "../../Font/FontRenderer.h"
#include "../../Graphics/Shadows/ShadowHandler.h"
#include "../../Graphics/Lighting/LightHandler.h"
#include "../../Utils/ResourceHandler.h"

#include <iostream>
#include <chrono>

static void errorCallback(int error, const char* description) {
	std::cerr << description << endl;
}

Application::Application() {
	// Init basic stuff
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
		exit(-1);
}

void Application::run() {
	// Create gl window stuff
	InitWindowHandle();
	// Init Handlers
	InitResources();

	// Build the first state and swap to it
	m_machine.run(StateMachine::build<MainMenu>(m_machine, *m_window, true));

	// Init Main loop stuff
	using namespace chrono;
	long lastTime = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
	double delta = 0.0;
	double ns = 1000000000.0 / 60.0;
	long timer = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
	int updates = 0;
	int frames = 0;
	string ups = " ups ";
	string fps = " fps";

	// Main loop
	while (m_machine.runnning()) {
		long now = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
		delta += (now - lastTime) / ns;
		lastTime = now;

		// Logic Update
		if (delta >= 1.0) {
			glfwPollEvents();
			updates++;
			delta--;

			// Updates for the StateMachine
			m_machine.nextState();
			m_machine.update();

			if (KeyInput::isKeyClicked(GLFW_KEY_ESCAPE))
				m_machine.quit();
		}

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FontRenderer::render();
		// StateMachine Render
		m_machine.render();
		glfwSwapBuffers(m_window);
		// Render stop

		frames++;
		if (duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count() - timer > 1000) {
			timer += 1000;
			glfwSetWindowTitle(m_window, std::string(to_string(updates) + ups + to_string(frames) + fps).c_str());
			updates = 0;
			frames = 0;
		}
	}
	// Cleanup stuff
	FontRenderer::cleanUp();
	ShaderHandler::cleanUp();
}

void Application::InitWindowHandle() {
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(1280, 720, "BR Top", NULL, NULL);

	if (!m_window) {
		cerr << "Failed to open GLFW window lol" << endl;
		glfwTerminate();
		exit(-2);
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

	// Set input callbacks
	glfwSetKeyCallback(m_window, KeyInput::invoke);
	glfwSetCursorPosCallback(m_window, MousePosInput::invoke);
	glfwSetMouseButtonCallback(m_window, MouseButtonInput::invoke);

	// Check for errors
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

}

void Application::InitResources() {
	AudioMaster::init();
	ShaderHandler::init();
	FontRenderer::init(1280, 720);
	LightHandler::init();
	ShadowHandler::init();
	ResourceHandler::init();
}