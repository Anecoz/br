#pragma once

#include <al\al.h>
#include <glm\glm.hpp>

class AudioSource {
public:
	AudioSource();
	~AudioSource();

	void play(ALuint& buffer);
	void pause();
	void continuePlaying();
	void stop();
	void setLooping(bool loop);
	bool isPlaying();
	void setVolume(float volume);
	void setPitch(float pitch);
	void setPosition(glm::vec2& position);
	void setVelocity(glm::vec2& velocity);
private:
	ALuint sourceID;
};