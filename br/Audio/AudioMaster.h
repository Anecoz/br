#pragma once

#include <al\al.h>
#include <al\alc.h>
#include <glm\glm.hpp>
#include <vector>
#include <string>

using namespace std;

/*
* Struct that holds the RIFF data of the Wave file.
* The RIFF data is the meta data information that holds,
* the ID, size and format of the wave file
*/
struct RIFF_Header {
	char chunkID[4];
	long chunkSize;//size not including chunkSize or chunkID
	char format[4];
};
/*
* Struct to hold fmt subchunk data for WAVE files.
*/
struct WAVE_Format {
	char subChunkID[4];
	long subChunkSize;
	short audioFormat;
	short numChannels;
	long sampleRate;
	long byteRate;
	short blockAlign;
	short bitsPerSample;
};
/*
* Struct to hold the data of the wave file
*/
struct WAVE_Data {
	char subChunkID[4]; //should contain the word data
	long subChunk2Size; //Stores the size of the data block
};

class AudioMaster {
public:
	AudioMaster() = default;
	~AudioMaster();

	static void init();
	static void setListenerData(const glm::vec2& position, const glm::vec2& velocity);
	static int loadSound(string file);

private:
	static vector<ALuint> buffers;
	static ALCdevice* device;
	static ALCcontext* context;
};