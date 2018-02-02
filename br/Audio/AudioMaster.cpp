#include <GL\glew.h>
#include <iostream>

#include "AudioMaster.h"

vector<ALuint> AudioMaster::buffers;
ALCdevice *AudioMaster::device;
ALCcontext *AudioMaster::context;

void AudioMaster::init() {
	device = alcOpenDevice(NULL); // select the "preferred device"

	if (device) {
		context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);
	}
	// Generate Buffers
	alGetError(); // clear error code 
}

void AudioMaster::setListenerData(const glm::vec2& position, const glm::vec2& velocity) {
	alListener3f(AL_POSITION, position.x, position.y, 0);
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, 0);
}

int AudioMaster::loadSound(string filename) {
	//Local Declarations
	ALuint buffer = -1;
	FILE* soundFile = NULL;
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	unsigned char* data;
	ALsizei size = -1;
	ALsizei frequency = -1;
	ALenum format;

	try {
		fopen_s(&soundFile, filename.c_str(), "rb");
		//soundFile = fopen(filename.c_str, "rb");
		if (!soundFile)
			throw (filename);

		// Read in the first chunk into the struct
		fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

		//check for RIFF and WAVE tag in memeory
		if ((riff_header.chunkID[0] != 'R' ||
			riff_header.chunkID[1] != 'I' ||
			riff_header.chunkID[2] != 'F' ||
			riff_header.chunkID[3] != 'F') ||
			(riff_header.format[0] != 'W' ||
				riff_header.format[1] != 'A' ||
				riff_header.format[2] != 'V' ||
				riff_header.format[3] != 'E'))
			throw ("Invalid RIFF or WAVE Header");

		//Read in the 2nd chunk for the wave info
		fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
		//check for fmt tag in memory
		if (wave_format.subChunkID[0] != 'f' ||
			wave_format.subChunkID[1] != 'm' ||
			wave_format.subChunkID[2] != 't' ||
			wave_format.subChunkID[3] != ' ')
			throw ("Invalid Wave Format");

		//check for extra parameters;
		if (wave_format.subChunkSize > 16)
			fseek(soundFile, sizeof(short), SEEK_CUR);

		//Read in the the last byte of data before the sound file
		fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
		//check for data tag in memory
		if (wave_data.subChunkID[0] != 'd' ||
			wave_data.subChunkID[1] != 'a' ||
			wave_data.subChunkID[2] != 't' ||
			wave_data.subChunkID[3] != 'a')
			throw ("Invalid data header");

		//Allocate memory for data
		data = new unsigned char[wave_data.subChunk2Size];

		// Read in the sound data into the soundData variable
		if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
			throw ("error loading WAVE data into struct!");

		//Now we set the variables that we passed in with the
		//data from the structs
		try {
			size = wave_data.subChunk2Size;
		}
		catch (exception e) {
			cerr << e.what() << endl;
		}
		frequency = wave_format.sampleRate;
		//The format is worked out by looking at the number of
		//channels and the bits per sample.
		if (wave_format.numChannels == 1) {
			if (wave_format.bitsPerSample == 8)
				format = AL_FORMAT_MONO8;
			else if (wave_format.bitsPerSample == 16)
				format = AL_FORMAT_MONO16;
		}
		else if (wave_format.numChannels == 2) {
			if (wave_format.bitsPerSample == 8)
				format = AL_FORMAT_STEREO8;
			else if (wave_format.bitsPerSample == 16)
				format = AL_FORMAT_STEREO16;
		}

		// Create the buffers
		alGenBuffers(1, &buffer);
		buffers.push_back(buffer);
		alGetError();
		//now we put our data into the openAL buffer and
		//check for success
		alBufferData(buffer, format, (void*)data,
			size, frequency);
		alGetError();
		//clean up and return true if successful
		fclose(soundFile);
		return buffer;
	}
	catch (string error) {
		//our catch statement for if we throw a string
		cerr << error << " : trying to load "
			<< filename << endl;
		//clean up memory if wave loading fails
		if (soundFile != NULL)
			fclose(soundFile);
		//return false to indicate the failure to load wave
		return -1;
	}

	return buffer;
}

AudioMaster::~AudioMaster() {
	static vector<ALuint>* buffers;

	for (ALuint &entry : *buffers) {
		alDeleteBuffers(1, &entry);
	}

	alcCloseDevice(device);
	alcDestroyContext(context);

	device = nullptr;
	context = nullptr;
}