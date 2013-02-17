//
// common.h
//
// Copyright 2010 tmkk. All rights reserved.
//

#ifndef QTAACENC_COMMON_H
#define QTAACENC_COMMON_H 1

#define VERSION 20110816

#ifdef _MSC_VER
#define fseeko _fseeki64
#define ftello _ftelli64
#endif

typedef struct
{
	char *title;
	char *artist;
	char *album;
	char *albumArtist;
	char *composer;
	char *group;
	char *genre;
	char *date;
	char *comment;
	int track;
	int totalTrack;
	int disc;
	int totalDisc;
	Boolean compilation;
} mp4Metadata_t;

typedef enum
{
	kConfigCBR = 0,
	kConfigABR,
	kConfigConstrainedVBR,
	kConfigTrueVBR,
	kConfigCBR_HE,
	kConfigABR_HE,
	kConfigConstrainedVBR_HE,
	kConfigMP4PathThrough
} codecConfig;

typedef enum
{
	kQualityFastest = 0x0,
	kQualityFast = 0x20,
	kQualityNormal = 0x40,
	kQualityHigh = 0x60,
	kQualityHighest = 0x7f
} codecQuality;

typedef struct
{
	_TCHAR *inFile;
	_TCHAR *outFile;
	codecConfig mode;
	int modeQuality;
	codecQuality overallQuality;
	int outSamplerate;
	Boolean highEfficiency;
	Boolean quiet;
	Boolean readFromStdin;
	Boolean ignoreLength;
	mp4Metadata_t metadata;
} encodingParameters;

int convertToMP4PathThrough(CFStringRef inFile, CFStringRef outFile);
void finalizeAtom(_TCHAR *path, int bitrate, int mode, int modeQuality, int samplerate, SInt64 frame, AudioStreamBasicDescription *asbd, mp4Metadata_t *metadata);
void freeMp4Metadata(mp4Metadata_t *metadata);
OSStatus configureComponent(ComponentInstance ci, encodingParameters *parameters, AudioStreamBasicDescription *inAsbd, AudioStreamBasicDescription *outAsbd, AudioChannelLayout *layout);
Track getSoundTrack(Movie theMovie);

#endif
