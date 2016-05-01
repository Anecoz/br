#include "AudioSource.h"

AudioSource::AudioSource() {
	alGenSources(1, &sourceID);
}

void AudioSource::play(ALuint& buffer) {
	stop();
	alSourcei(sourceID, AL_BUFFER, buffer);
	continuePlaying();
}

void AudioSource::pause() {
	alSourcePause(sourceID);
}

void AudioSource::continuePlaying() {
	alSourcePlay(sourceID);
}

void AudioSource::stop() {
	alSourceStop(sourceID);
}

void AudioSource::setLooping(bool loop) {
	alSourcei(sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}

bool AudioSource::isPlaying() {
	ALint state;
	alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

void AudioSource::setVolume(float volume) {
	alSourcef(sourceID, AL_GAIN, volume);
}

void AudioSource::setPitch(float pitch) {
	alSourcef(sourceID, AL_PITCH, pitch);
}

void AudioSource::setPosition(glm::vec2& position) {
	alSource3f(sourceID, AL_POSITION, position.x, position.y, 0);
}

void AudioSource::setVelocity(glm::vec2& velocity) {
	alSource3f(sourceID, AL_VELOCITY, velocity.x, velocity.y, 0);
}

AudioSource::~AudioSource() {
	stop();
	alDeleteSources(1, &sourceID);
}