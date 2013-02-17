//
// QTAACencoder.h
//
// Copyright 2010 tmkk. All rights reserved.
//

#include "common.h"

class QTAACEncoder
{
public:
	FILE *fp;
	MovieAudioExtractionRef mae;
	AudioStreamBasicDescription inAsbd;
	AudioStreamBasicDescription outAsbd;
	AudioChannelLayout *layout;
	unsigned char *inBuffer;
	unsigned int inBufferSize;
	Boolean finished;
	SInt64 totalFrames;
	SInt64 readFrames;
	Boolean showProgress;

	QTAACEncoder();
	~QTAACEncoder();
	Boolean openFile(CFStringRef inFile);
	Boolean openStream(FILE *stream);
	SInt64 beginEncode(CFStringRef outFile, encodingParameters *parameters);
};
