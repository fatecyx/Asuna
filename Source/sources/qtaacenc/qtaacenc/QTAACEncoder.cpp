//
// QTAACencoder.cpp
//
// Copyright 2010 tmkk. All rights reserved.
//

#include "stdafx.h"
#include "QTAACEncoder.h"

#define PACKETS_PER_LOOP 128

static const unsigned char INTEGER_PCM_GUID[16] = {0x01,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71};
static const unsigned char FLOAT_PCM_GUID[16]   = {0x03,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71};

static Int64 fseek_stdin(FILE *fp, __int64 offset, char **seekBuf, int *seekBufSize)
{
	if(!offset) return 0;
	if(fp!=stdin) return fseeko(fp,offset,SEEK_CUR);
	if(offset > *seekBufSize) {
		*seekBuf = (char *)realloc(*seekBuf, (size_t)offset);
		*seekBufSize = (size_t)offset;
	}
	if(fread(*seekBuf,1,(size_t)offset,fp) < (size_t)offset) return -1;
	return 0;
}


static ComponentResult
pcmInputProc(ComponentInstance ci,
			 UInt32 *ioNumberDataPackets,
			 AudioBufferList *ioData,
			 AudioStreamPacketDescription **outDataPacketDescription,
			 void *inRefCon)
{
	QTAACEncoder *encoder = (QTAACEncoder *)inRefCon;
	UInt32 requiredPackets = *ioNumberDataPackets;

	*ioNumberDataPackets = 0;

	if(encoder->totalFrames && encoder->readFrames + requiredPackets > encoder->totalFrames) {
		requiredPackets = (int)(encoder->totalFrames - encoder->readFrames);
	}

	if(encoder->finished)
	{
		ioData->mBuffers[0].mData = NULL;
		ioData->mBuffers[0].mDataByteSize = 0;
		goto last;
	}

	if(ioData->mBuffers[0].mData == NULL)
	{
		UInt32 neededBufSize = requiredPackets * encoder->inAsbd.mBytesPerPacket;
		if (encoder->inBufferSize < neededBufSize)
		{
			encoder->inBufferSize = neededBufSize;
			if (encoder->inBuffer) free(encoder->inBuffer);
			encoder->inBuffer = (unsigned char*)malloc(encoder->inBufferSize);
		}
		ioData->mBuffers[0].mDataByteSize = encoder->inBufferSize;
		ioData->mBuffers[0].mData = encoder->inBuffer;
	}

	if(encoder->fp) {
		UInt32 readPackets = fread(encoder->inBuffer,encoder->inAsbd.mBytesPerPacket,requiredPackets,encoder->fp);
		*ioNumberDataPackets = readPackets;
		ioData->mBuffers[0].mDataByteSize = readPackets*encoder->inAsbd.mBytesPerPacket;
		encoder->readFrames += readPackets;
		if(readPackets < requiredPackets) encoder->finished = true;
		else if(encoder->totalFrames && encoder->readFrames >= encoder->totalFrames) encoder->finished = true;
	}
	else {
		UInt32 flags=0;
		MovieAudioExtractionFillBuffer(encoder->mae, &requiredPackets, ioData, &flags);
		*ioNumberDataPackets = requiredPackets;
		ioData->mBuffers[0].mDataByteSize = requiredPackets*encoder->inAsbd.mBytesPerPacket;
		encoder->readFrames += requiredPackets;
		if(flags & kQTMovieAudioExtractionComplete) encoder->finished = true;
		else if(requiredPackets == 0) encoder->finished = true;
		//else if(encoder->totalFrames && encoder->readFrames >= encoder->totalFrames) encoder->finished = true;
	}
/*
	if(encoder->totalFrames && encoder->showProgress) {
		static double previousPercent = -1.0;
		double percent = floor(100.0*(double)encoder->readFrames/encoder->totalFrames+0.5);
		if(percent > previousPercent) {
			fprintf(stderr,"\rProgress:% 4d%%",(int)percent);
			fflush(stderr);
			previousPercent = percent;
		}
	}
*/
    if (encoder->showProgress)
    {
        const UInt32 SamplesPerFrame = 1;
        static double previousPercent = -1.0;
        double percent;
        Char buf[0x100];
        SInt32 i;

        i = sprintf(buf, "\rProcessed %I64u ", (UInt64)(encoder->readFrames * SamplesPerFrame / encoder->inAsbd.mSampleRate));

        if (encoder->totalFrames)
        {
            percent = floor(100.0 * (double)encoder->readFrames / encoder->totalFrames + 0.5);
//            if(percent > previousPercent)
            {
                i += sprintf(buf + i, "/ %I64u (%d%%) ", (UInt64)(encoder->totalFrames * SamplesPerFrame / encoder->inAsbd.mSampleRate), (int)percent);
//                fprintf(stderr,"/ %I64u (%d%%) ", (UInt64)(encoder->totalFrames * SamplesPerFrame / encoder->inAsbd.mSampleRate), (int)percent);
                previousPercent = percent;
            }
        }
//        fprintf(stderr, "seconds ...                    ");
        sprintf(buf + i, "seconds");
        fprintf(stderr, "%s ...                    ", buf);
        buf[i] = 0;
        SetConsoleTitleA(buf + 11);
    }

last:
	return noErr;
}

Track getSoundTrack(Movie theMovie)
{
	int index;
	int trackCount = GetMovieTrackCount(theMovie);
    for(index = 1; index <= trackCount; index++)
    {
        OSType     aTrackType;
        Track    aTrack = NULL;
        Media    aMedia = NULL;

        aTrack = GetMovieIndTrack(theMovie, index);
        aMedia = GetTrackMedia(aTrack);

        GetMediaHandlerDescription(aMedia, &aTrackType, 0, 0);
        if(aTrackType == SoundMediaType)
        {
            return aTrack;
        }
    }
	return NULL;
}

QTAACEncoder::QTAACEncoder()
{
	fp = NULL;
	mae = NULL;
	inBufferSize = 0;
	inBuffer = NULL;
	finished = false;
	readFrames = 0;
	totalFrames = 0;
	showProgress = true;
	memset(&inAsbd,0,sizeof(AudioStreamBasicDescription));
	memset(&outAsbd,0,sizeof(AudioStreamBasicDescription));
	layout = NULL;
}

QTAACEncoder::~QTAACEncoder()
{
	if(inBuffer) free(inBuffer);
	if(mae) MovieAudioExtractionEnd(mae);
	if(layout) free(layout);
}

Boolean QTAACEncoder::openStream(FILE *stream)
{
	char chunk[4];
	char *seekBuf = (char *)malloc(256);
	int seekBufSize = 256;
	unsigned int tmp, chunkSize;
	unsigned short tmp2;
	unsigned int channelBitmap;
	Boolean extensible = false;
	Boolean ret = false;

	fp = stream;

	if(fread(chunk,1,4,fp) < 4) goto last;
	if(memcmp(chunk,"RIFF",4)) {
		fprintf(stderr,"Error: input stream is not a RIFF WAVE file\n");
		goto last;
	}
	if(fseek_stdin(fp,4,&seekBuf,&seekBufSize)) goto last;
	if(fread(chunk,1,4,fp) < 4) goto last;
	if(memcmp(chunk,"WAVE",4)) {
		fprintf(stderr,"Error: input stream is not a RIFF WAVE file\n");
		goto last;
	}
	while(1) { // find fmt chunk
		if(fread(chunk,1,4,fp) < 4) goto last;
		if(fread(&chunkSize,4,1,fp) < 1) goto last;
		if(!memcmp(chunk,"fmt ",4)) break;
		if(fseek_stdin(fp,chunkSize,&seekBuf,&seekBufSize)) goto last;
	}

	inAsbd.mFramesPerPacket = 1;

	if(fread(&tmp2,2,1,fp) < 1) goto last;
	if(tmp2 == 0x1) {
		inAsbd.mFormatID = kAudioFormatLinearPCM;
		inAsbd.mFormatFlags |= kAudioFormatFlagIsSignedInteger|kAudioFormatFlagIsPacked;
	}
	else if(tmp2 == 0x3) {
		inAsbd.mFormatID = kAudioFormatLinearPCM;
		inAsbd.mFormatFlags |= kAudioFormatFlagIsFloat|kAudioFormatFlagIsPacked;
	}
	else if(tmp2 == 0xFFFE) {
		extensible = true;
	}
	else {
		fprintf(stderr,"Error: unsupported format\n");
		goto last;
	}
	if(fread(&tmp2,2,1,fp) < 1) goto last;
	inAsbd.mChannelsPerFrame = tmp2;
	if(fread(&tmp,4,1,fp) < 1) goto last;
	inAsbd.mSampleRate = (Float64)tmp;
	if(fseek_stdin(fp,4,&seekBuf,&seekBufSize)) goto last;
	if(fread(&tmp2,2,1,stream) < 1) goto last;
	inAsbd.mBytesPerFrame = tmp2;
	inAsbd.mBytesPerPacket = tmp2;
	if(fread(&tmp2,2,1,fp) < 1) goto last;
	inAsbd.mBitsPerChannel = tmp2;
	if(tmp2 == 8) inAsbd.mFormatFlags &= ~kAudioFormatFlagIsSignedInteger;

	if(extensible && (chunkSize-16) == 24) {
		if(fread(&tmp2,2,1,fp) < 1) goto last;
		chunkSize = tmp2;
		if(fseek_stdin(fp,2,&seekBuf,&seekBufSize)) goto last;
		if(fread(&channelBitmap,4,1,fp) < 1) goto last;
		unsigned char guid[16];
		if(fread(guid,1,16,fp) < 16) goto last;
		if(!memcmp(guid,INTEGER_PCM_GUID,16)) {
			inAsbd.mFormatID = kAudioFormatLinearPCM;
			if(inAsbd.mBitsPerChannel == 8)
				inAsbd.mFormatFlags |= kAudioFormatFlagIsPacked;
			else inAsbd.mFormatFlags |= kAudioFormatFlagIsSignedInteger|kAudioFormatFlagIsPacked;
		}
		else if(!memcmp(guid,FLOAT_PCM_GUID,16)) {
			inAsbd.mFormatID = kAudioFormatLinearPCM;
			inAsbd.mFormatFlags |= kAudioFormatFlagIsFloat|kAudioFormatFlagIsPacked;
		}
		else {
			fprintf(stderr,"Error: unsupported format\n");
			goto last;
		}
		layout = (AudioChannelLayout *)calloc(1,sizeof(AudioChannelLayout)+sizeof(AudioChannelDescription)*(inAsbd.mChannelsPerFrame-1));
		layout->mChannelLayoutTag = kAudioChannelLayoutTag_UseChannelDescriptions;
		int i;
		for(i=0;i<18;i++) {
			if(channelBitmap&(1<<i)) layout->mChannelDescriptions[layout->mNumberChannelDescriptions++].mChannelLabel = i+1;
		}
		switch(channelBitmap) {
			case 0x07:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_3_0_A;
				break;
			case 0x33:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_Quadraphonic;
				break;
			case 0x107:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_4_0_A;
				break;
			case 0x37:
			case 0x607:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_5_0_A;
				break;
			case 0x3f:
			case 0x60f:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_5_1_A;
				break;
			case 0x13f:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_6_1_A;
				break;
			case 0x70f:
				layout->mChannelDescriptions[5].mChannelLabel = kAudioChannelLabel_LeftSurround;
				layout->mChannelDescriptions[6].mChannelLabel = kAudioChannelLabel_RightSurround;
				break;
			case 0xff:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_7_1_A;
				break;
			case 0x6cf:
				layout->mChannelDescriptions[6].mChannelLabel = kAudioChannelLabel_LeftSurround;
				layout->mChannelDescriptions[7].mChannelLabel = kAudioChannelLabel_RightSurround;
				break;
			case 0x63f:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_7_1_A;
				break;
		}
	}
	else if(extensible) {
		fprintf(stderr,"Error: unsupported format\n");
		goto last;
	}
	else if(fseek_stdin(fp,chunkSize-16,&seekBuf,&seekBufSize)) goto last;

	if(!layout && inAsbd.mChannelsPerFrame>2) {
		layout = (AudioChannelLayout *)calloc(1,sizeof(AudioChannelLayout));
		switch(inAsbd.mChannelsPerFrame) {
			case 3:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_3_0_A;
				break;
			case 4:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_4_0_A;
				break;
			case 5:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_5_0_A;
				break;
			case 6:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_5_1_A;
				break;
			case 7:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_6_1_A;
				break;
			case 8:
				layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_7_1_A;
				break;
		}
	}

	while(1) { // find data chunk
		if(fread(chunk,1,4,fp) < 4) goto last;
		if(fread(&chunkSize,4,1,fp) < 1) goto last;
		if(!memcmp(chunk,"data",4)) break;
		if(fseek_stdin(fp,chunkSize,&seekBuf,&seekBufSize)) goto last;
	}

	totalFrames = chunkSize / inAsbd.mBytesPerFrame;
	ret = true;
last:
	free(seekBuf);
	return ret;
}

Boolean QTAACEncoder::openFile(CFStringRef inFile)
{
	OSStatus error;
	Handle inDataRef=0;
	OSType inDataRefType;
	short inResID = 0;
	Movie theMovie=0;
	Track theTrack=0;
	Media theMedia=0;
	UInt32 layoutSize;
	Boolean allChansDiscrete;
	Boolean unknownChannelMap = false;
	int descreteNumChannels;
	Boolean ret = false;

	error = QTNewDataReferenceFromFullPathCFString(inFile, kQTNativeDefaultPathStyle, 0, &inDataRef, &inDataRefType);
	if(error) {
		fprintf(stderr,"QTNewDataReferenceFromFullPathCFString error: input file path is invalid\n");
		goto last;
	}
	error = NewMovieFromDataRef(&theMovie, newMovieActive, &inResID, inDataRef, inDataRefType);
	if(error) {
		fprintf(stderr,"NewMovieFromDataRef error: cannot open the input file\n");
		goto last;
	}
	theTrack = getSoundTrack(theMovie);
	if(NULL == theTrack) {
		fprintf(stderr,"error: cannot find the audio track\n");
		goto last;
	}
	theMedia = GetTrackMedia(theTrack);
	DeleteTrackSegment(theTrack, 0, GetTrackDuration(theTrack));
	SetMovieTimeScale(theMovie, GetMediaTimeScale(theMedia));
	InsertMediaIntoTrack(theTrack, 0, 0, GetMediaDuration(theMedia), fixed1);

	error = MovieAudioExtractionBegin(theMovie, 0, &mae);
	if(error) {
		fprintf(stderr,"MovieAudioExtractionBegin error: cannot begin session\n");
		goto last;
	}
	allChansDiscrete = true;
	error = MovieAudioExtractionSetProperty(mae,
											kQTPropertyClass_MovieAudioExtraction_Movie,
											kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete,
											sizeof(allChansDiscrete), &allChansDiscrete);
	if(error) {
		fprintf(stderr,"MovieAudioExtractionSetProperty error(kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete)\n");
		goto last;
	}
	error = MovieAudioExtractionGetProperty(mae,
											kQTPropertyClass_MovieAudioExtraction_Audio,
											kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
											sizeof(AudioStreamBasicDescription), &inAsbd, NULL);
	if(error) {
		fprintf(stderr,"MovieAudioExtractionGetProperty error: cannot get the file property\n");
		goto last;
	}
	descreteNumChannels = inAsbd.mChannelsPerFrame;
	allChansDiscrete = false;
	error = MovieAudioExtractionSetProperty(mae,
											kQTPropertyClass_MovieAudioExtraction_Movie,
											kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete,
											sizeof(allChansDiscrete), &allChansDiscrete);
	if(error) {
		fprintf(stderr,"MovieAudioExtractionSetProperty error(kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete)\n");
		goto last;
	}

	error = MovieAudioExtractionGetProperty(mae,
											kQTPropertyClass_MovieAudioExtraction_Audio,
											kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
											sizeof(AudioStreamBasicDescription), &inAsbd, NULL);
	if(error) {
		fprintf(stderr,"MovieAudioExtractionGetProperty error: cannot get the file property\n");
		goto last;
	}
	if(descreteNumChannels != inAsbd.mChannelsPerFrame) {
		unknownChannelMap = true;
		allChansDiscrete = true;
		error = MovieAudioExtractionSetProperty(mae,
												kQTPropertyClass_MovieAudioExtraction_Movie,
												kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete,
												sizeof(allChansDiscrete), &allChansDiscrete);
		if(error) {
			fprintf(stderr,"MovieAudioExtractionSetProperty error(kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete)\n");
			goto last;
		}
		error = MovieAudioExtractionGetProperty(mae,
												kQTPropertyClass_MovieAudioExtraction_Audio,
												kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
												sizeof(AudioStreamBasicDescription), &inAsbd, NULL);
		if(error) {
			fprintf(stderr,"MovieAudioExtractionGetProperty error: cannot get the file property\n");
			goto last;
		}
	}
	inAsbd.mFormatFlags &= ~kLinearPCMFormatFlagIsNonInterleaved;
	inAsbd.mChannelsPerFrame = descreteNumChannels;
	inAsbd.mBytesPerFrame *= inAsbd.mChannelsPerFrame;
	inAsbd.mBytesPerPacket = inAsbd.mBytesPerFrame;
	error = MovieAudioExtractionSetProperty(mae,
											kQTPropertyClass_MovieAudioExtraction_Audio,
											kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
											sizeof(AudioStreamBasicDescription), &inAsbd);
	if(error) {
		fprintf(stderr,"MovieAudioExtractionSetProperty error\n");
		goto last;
	}
	error = MovieAudioExtractionGetProperty(mae,
											kQTPropertyClass_MovieAudioExtraction_Audio,
											kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
											sizeof(AudioStreamBasicDescription), &inAsbd, NULL);
	if(error) {
		fprintf(stderr,"MovieAudioExtractionGetProperty error: cannot get the file property\n");
		goto last;
	}
	//fprintf(stderr,"%x,%x,%x,%x,%x,%x,%x,%f\n",asbd->mBitsPerChannel,asbd->mBytesPerFrame,asbd->mBytesPerPacket,asbd->mChannelsPerFrame,asbd->mFormatFlags,asbd->mFormatID,asbd->mFramesPerPacket,asbd->mSampleRate);

	if(!unknownChannelMap && noErr == MovieAudioExtractionGetPropertyInfo(mae, kQTPropertyClass_MovieAudioExtraction_Audio,
													kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout,
													NULL, &layoutSize, NULL ) )
	{
		if (layoutSize) {
			layout = (AudioChannelLayout*)calloc(1, layoutSize);
			if (noErr == MovieAudioExtractionGetProperty(mae, kQTPropertyClass_MovieAudioExtraction_Audio,
														kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout,
														layoutSize, layout, &layoutSize))
			{
				if(layout->mChannelLayoutTag == kAudioChannelLayoutTag_UseChannelDescriptions) {
					unsigned int channelBitmap = 0,i;
					unsigned int channelOrder = 0;
					Boolean shouldUpdateLayout = false;
					for(i=0;i<layout->mNumberChannelDescriptions;i++) {
						channelBitmap |= 1 << (layout->mChannelDescriptions[i].mChannelLabel-1);
						channelOrder |= ((layout->mChannelDescriptions[i].mChannelLabel)&0xf)<<(4*i);
					}
					if(channelBitmap == 0x607 && channelOrder == 0xba321 && inAsbd.mChannelsPerFrame == 5) {
						layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_5_0_A;
						shouldUpdateLayout = true;
					}
					else if(channelBitmap == 0x60f && channelOrder == 0xba4321 && inAsbd.mChannelsPerFrame == 6) {
						layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_5_1_A;
						shouldUpdateLayout = true;
					}
					else if(channelBitmap == 0x70f && channelOrder == 0xba94321 && inAsbd.mChannelsPerFrame == 7) {
						layout->mChannelDescriptions[5].mChannelLabel = kAudioChannelLabel_LeftSurround;
						layout->mChannelDescriptions[6].mChannelLabel = kAudioChannelLabel_RightSurround;
						shouldUpdateLayout = true;
					}
					else if(channelBitmap == 0x6cf && channelOrder == 0xba874321 && inAsbd.mChannelsPerFrame == 8) {
						layout->mChannelDescriptions[6].mChannelLabel = kAudioChannelLabel_LeftSurround;
						layout->mChannelDescriptions[7].mChannelLabel = kAudioChannelLabel_RightSurround;
						shouldUpdateLayout = true;
					}
					else if(channelBitmap == 0x63f && channelOrder == 0xba654321 && inAsbd.mChannelsPerFrame == 8) {
						layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_7_1_A;
						shouldUpdateLayout = true;
					}
					if(shouldUpdateLayout)
						MovieAudioExtractionSetProperty(mae,
														kQTPropertyClass_MovieAudioExtraction_Audio,
														kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout,
														layoutSize, layout);
					//fprintf(stderr,"%x\n",channelBitmap);
				}
			}
			else {
				free(layout);
				layout = NULL;
			}
		}
		else if(inAsbd.mChannelsPerFrame > 2) {
			unknownChannelMap = true;
		}
	}
	if(unknownChannelMap && inAsbd.mChannelsPerFrame > 2) {
		layout = (AudioChannelLayout *)calloc(1,sizeof(AudioChannelLayout));
		switch(inAsbd.mChannelsPerFrame) {
				case 3:
					layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_3_0_A;
					break;
				case 4:
					layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_4_0_A;
					break;
				case 5:
					layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_5_0_A;
					break;
				case 6:
					layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_5_1_A;
					break;
				case 7:
					layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_6_1_A;
					break;
				case 8:
					layout->mChannelLayoutTag = kAudioChannelLayoutTag_MPEG_7_1_A;
					break;
		}
		error = MovieAudioExtractionSetProperty(mae,
												kQTPropertyClass_MovieAudioExtraction_Audio,
												kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout,
												sizeof(AudioChannelLayout), layout);
		if(error) {
			fprintf(stderr,"MovieAudioExtractionSetProperty error\n");
			goto last;
		}
	}

	totalFrames = (SInt64)(GetMediaDuration(theMedia)*inAsbd.mSampleRate/GetMediaTimeScale(theMedia));
	ret = true;

last:
	return ret;
}


SInt64 QTAACEncoder::beginEncode(CFStringRef outFile, encodingParameters *parameters)
{
	OSStatus error;
	ComponentInstance movieExporter = NULL;
	Handle outDataRef=0;
	OSType outDataRefType;
	Movie theMovie=0;
	Track theTrack=0;
	Media theMedia=0;
	SoundDescriptionHandle sdh=0;
	DataHandler dataHandler=0;
	UInt32 size;
	Boolean requiresPackets = false;
	AudioStreamPacketDescription* aspds = NULL;
	UInt32 maxBytesPerPacket = 0;
	AudioBufferList* abl = NULL;
	void* buffer = NULL;
	UInt32 bufferSize = 0;
	SInt64 ret = 0;

	showProgress = !parameters->quiet;
	if(fp && parameters->ignoreLength) totalFrames = 0;

	error = OpenADefaultComponent(StandardCompressionType, StandardCompressionSubTypeAudio, &movieExporter);
	if(error) {
		fprintf(stderr,"OpenADefaultComponent error: cannot find the QuickTime conponent\n");
		goto last;
	}

	//fprintf(stderr,"%x,%x,%x,%x,%x,%x,%x,%f\n",inAsbd.mBitsPerChannel,inAsbd.mBytesPerFrame,inAsbd.mBytesPerPacket,inAsbd.mChannelsPerFrame,inAsbd.mFormatFlags,inAsbd.mFormatID,inAsbd.mFramesPerPacket,inAsbd.mSampleRate);
	error = QTSetComponentProperty(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_InputBasicDescription, sizeof(AudioStreamBasicDescription), &inAsbd);
	if(error) {
		fprintf(stderr,"QTSetComponentProperty error: cannot set input ASBD\n");
		goto last;
	}
	if(inAsbd.mChannelsPerFrame > 2 && layout) {
		//fprintf(stderr,"%x,%x,%x,%x\n",layout->mChannelBitmap,layout->mChannelLayoutTag,layout->mNumberChannelDescriptions,layout->mChannelDescriptions[0].mChannelLabel);
		error = QTSetComponentProperty(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_InputChannelLayout, sizeof(AudioChannelLayout)+sizeof(AudioChannelDescription)*(layout->mNumberChannelDescriptions ? (layout->mNumberChannelDescriptions-1) : 0), layout);
		if(error) {
			fprintf(stderr,"QTSetComponentProperty error: cannot set AudioChannelLayout; maybe unsupported channel layout\n");
			goto last;
		}
	}

	error = configureComponent(movieExporter,parameters,&inAsbd,&outAsbd,layout);
	if(error) {
		fprintf(stderr,"Error occured while configuring AAC encoder.\n");
		goto last;
	}

	if(mae) {
		MovieAudioExtractionSetProperty(mae,
										kQTPropertyClass_MovieAudioExtraction_Audio,
										kQTMovieAudioExtractionAudioPropertyID_RenderQuality,
										4, &parameters->overallQuality);
	}

	//SCSetSettingsFromAtomContainer(movieExporter, currentSettings);

	/*error = SCRequestImageSettings(movieExporter);
	if(error == userCanceledErr) goto last;
	else if(error)
	{
		fprintf(stderr, "SCRequestImageSettings error\n");
		goto last;
	}*/

	error = QTGetComponentProperty(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_BasicDescription, sizeof(outAsbd), &outAsbd, NULL);
	if(error) {
		fprintf(stderr, "QTGetComponentProperty(kQTSCAudioPropertyID_BasicDescription) error\n");
		goto last;
	}
	error = QTNewDataReferenceFromFullPathCFString(outFile, kQTNativeDefaultPathStyle, 0, &outDataRef, &outDataRefType);
	if(error) {
		fprintf(stderr,"QTNewDataReferenceFromFullPathCFString error: output file path is invalid\n");
		goto last;
	}
	error = CreateMovieStorage(outDataRef, outDataRefType, 'TVOD', 0, createMovieFileDeleteCurFile|createMovieFileDontCreateResFile, &dataHandler, &theMovie);
	DisposeHandle(outDataRef);
	if(error) {
		fprintf(stderr,"CreateMovieStorage error; can't create the output file\n");
		goto last;
	}

	theTrack = NewMovieTrack(theMovie, 0, 0, kFullVolume);
	if(outAsbd.mFormatID == 'aach')
		theMedia = NewTrackMedia(theTrack, SoundMediaType, (TimeScale)outAsbd.mSampleRate/2, NULL, 0);
	else
		theMedia = NewTrackMedia(theTrack, SoundMediaType, (TimeScale)outAsbd.mSampleRate, NULL, 0);
	error = BeginMediaEdits(theMedia);
	if(error) {
		fprintf(stderr,"BeginMediaEdits error\n");
		goto last;
	}
	error = QTSoundDescriptionCreate(&outAsbd, NULL, 0, NULL, 0, kQTSoundDescriptionKind_Movie_LowestPossibleVersion, &sdh);
	if(error) {
		fprintf(stderr,"QTSoundDescriptionCreate error\n");
		goto last;
	}

	if (noErr == QTGetComponentPropertyInfo(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_ChannelLayout, NULL, &size, NULL))
	{
		if (size) {
			AudioChannelLayout * pLayout = (AudioChannelLayout*)calloc(1, size);
			if (noErr == QTGetComponentProperty(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_ChannelLayout, size, pLayout, &size))
			{
				error = QTSoundDescriptionSetProperty(sdh, kQTPropertyClass_SoundDescription, kQTSoundDescriptionPropertyID_AudioChannelLayout, size, pLayout);
				if(error) fprintf(stderr, "QTSoundDescriptionSetProperty(ChannelLayout) error");
			}
			free(pLayout);
			if (error) goto last;
		}
	}
	if (noErr == QTGetComponentPropertyInfo(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_MagicCookie, NULL, &size, NULL))
	{
		if (size) {
			void * magicCookie = calloc(1, size);
			if (noErr == QTGetComponentProperty(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_MagicCookie, size, magicCookie, &size))
			{
				error = QTSoundDescriptionSetProperty(sdh, kQTPropertyClass_SoundDescription, kQTSoundDescriptionPropertyID_MagicCookie, size, magicCookie);
				if(error) fprintf(stderr, "QTSoundDescriptionSetProperty(MagicCookie) error\n");
			}
			free(magicCookie);
			if(error) goto last;
		}
	}

	error = QTGetComponentProperty(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_OutputFormatIsExternallyFramed, sizeof(requiresPackets), &requiresPackets, NULL);
	if(error) {
		fprintf(stderr,"QTGetComponentProperty(kQTSCAudioPropertyID_OutputFormatIsExternallyFramed) error\n");
		goto last;
	}
	if(requiresPackets) {
		aspds = (AudioStreamPacketDescription*)calloc(PACKETS_PER_LOOP, sizeof(AudioStreamPacketDescription));
	}

	if(outAsbd.mBytesPerPacket) {
		maxBytesPerPacket = outAsbd.mBytesPerPacket;
	}
	else {
		error = QTGetComponentProperty(movieExporter, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_MaximumOutputPacketSize, sizeof(maxBytesPerPacket), &maxBytesPerPacket, NULL);
		if(error) {
			fprintf(stderr, "QTGetComponentProperty(kQTSCAudioPropertyID_MaximumOutputPacketSize) error\n");
			goto last;
		}
	}
	bufferSize = maxBytesPerPacket * PACKETS_PER_LOOP;
	if(bufferSize == 0) {
		fprintf(stderr, "invalid buffer size.\n");
		goto last;
	}
	buffer = malloc(bufferSize);
	abl = (AudioBufferList*)calloc(1, offsetof(AudioBufferList, mBuffers[1]));
	abl->mNumberBuffers = 1;

    extern Bool bCtrlC;
	// encoding loop
	while(!bCtrlC) {
		UInt32 i, packetsWritten = PACKETS_PER_LOOP;

		abl->mBuffers[0].mNumberChannels = outAsbd.mChannelsPerFrame;
		abl->mBuffers[0].mDataByteSize = bufferSize;
		abl->mBuffers[0].mData = buffer;

		error = SCAudioFillBuffer(movieExporter, pcmInputProc, this, &packetsWritten, abl, aspds);
		if(error) {
			fprintf(stderr, "received err %ld from SCAudioFillBuffer\n",error);
			goto last;
		}
		else if(packetsWritten == 0 && abl->mBuffers[0].mDataByteSize == 0) { // EOF
			break;
		}

		if(packetsWritten) {
			if(aspds) {
				for (i = 0; i < packetsWritten; i++) {
					TimeValue64 duration = (aspds[i].mVariableFramesInPacket ? aspds[i].mVariableFramesInPacket : outAsbd.mFramesPerPacket);
					if(outAsbd.mFormatID == 'aach') duration /= 2;
					error = AddMediaSample2(theMedia,
						(UInt8*)abl->mBuffers[0].mData + aspds[i].mStartOffset,
						aspds[i].mDataByteSize,
						duration,
						0,
						(SampleDescriptionHandle)sdh,
						1,
						0,
						NULL);
					if(error) {
						fprintf(stderr, "AddMediaSample2 error\n");
						goto last;
					}
				}
			}
			else {
				ItemCount numSamples = packetsWritten * outAsbd.mFramesPerPacket;
				error = AddMediaSample2(theMedia,
					(UInt8*)abl->mBuffers[0].mData,
					abl->mBuffers[0].mDataByteSize,
					1,
					0,
					(SampleDescriptionHandle)sdh,
					numSamples,
					0,
					NULL);
				if(error) {
					fprintf(stderr, "AddMediaSample2 error\n");
					goto last;
				}
			}
		}
	}
	if(showProgress) fprintf(stderr,"\n");

	ret = readFrames;

last:
	if(aspds) free(aspds);
	if(buffer) free(buffer);
	if(abl) free(abl);
	if(movieExporter) CloseComponent(movieExporter);
	if(theMovie) {
		if(theMedia) {
			EndMediaEdits(theMedia);
			InsertMediaIntoTrack(theTrack, 0, 0, GetMediaDuration(theMedia), fixed1);
		}
		if(dataHandler) {
			AddMovieToStorage(theMovie,dataHandler);
			CloseMovieStorage(dataHandler);
		}
		DisposeMovie(theMovie);
	}
	if(sdh) DisposeHandle((Handle)sdh);

	return ret;
}
