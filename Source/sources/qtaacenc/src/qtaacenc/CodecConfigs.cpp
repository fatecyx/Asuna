//
// CodecConfigs.cpp
//
// Copyright 2010 tmkk. All rights reserved.
//

#include "stdafx.h"
#include "common.h"
#include "CodecConfigs.h"

typedef struct
{
	int min;
	int max;
} bitrateRange;

static int getBitrateIndex(int bitrate, int *table, bitrateRange *range)
{
	int i,ret;
	for(i=range->min;i<=range->max;i++) {
		if(i==range->max) {
			if(bitrate != table[i]) fprintf(stderr,"Warning: actual bitrate used is %d kbps\n",table[i]);
			ret = i;
			break;
		}
		else if(bitrate < table[i]+((table[i+1]-table[i])>>1)) {
			if(bitrate != table[i]) fprintf(stderr,"Warning: actual bitrate used is %d kbps\n",table[i]);
			ret = i;
			break;
		}
	}
	return ret;
}


static void getBitrateRangeForSamplerateAndChannel(bitrateRange *range, int inRate, int outRate, int channels)
{
	if(inRate > 46050) range->max = maxBitrateIndex[channels][8];
	else if(inRate > 38050) range->max = maxBitrateIndex[channels][7];
	else if(inRate > 28000) range->max = maxBitrateIndex[channels][6];
	else if(inRate > 23025) range->max = maxBitrateIndex[channels][5];
	else if(inRate > 19025) range->max = maxBitrateIndex[channels][4];
	else if(inRate > 14000) range->max = maxBitrateIndex[channels][3];
	else if(inRate > 11512) range->max = maxBitrateIndex[channels][2];
	else if(inRate > 9512) range->max = maxBitrateIndex[channels][1];
	else range->max = maxBitrateIndex[channels][0];
	
	switch(outRate) {
		case 48000:
			range->min = minBitrateIndex[channels][8];
			range->max = maxBitrateIndex[channels][8];
			break;
		case 44100:
			range->min = minBitrateIndex[channels][7];
			range->max = maxBitrateIndex[channels][7];
			break;
		case 32000:
			range->min = minBitrateIndex[channels][6];
			range->max = maxBitrateIndex[channels][6];
			break;
		case 24000:
			range->min = minBitrateIndex[channels][5];
			range->max = maxBitrateIndex[channels][5];
			break;
		case 22050:
			range->min = minBitrateIndex[channels][4];
			range->max = maxBitrateIndex[channels][4];
			break;
		case 16000:
			range->min = minBitrateIndex[channels][3];
			range->max = maxBitrateIndex[channels][3];
			break;
		case 12000:
			range->min = minBitrateIndex[channels][2];
			range->max = maxBitrateIndex[channels][2];
			break;
		case 11025:
			range->min = minBitrateIndex[channels][1];
			range->max = maxBitrateIndex[channels][1];
			break;
		case 8000:
			range->min = minBitrateIndex[channels][0];
			range->max = maxBitrateIndex[channels][0];
			break;
		default:
			range->min = 1;
	}
}

static void getBitrateRangeForSamplerateAndChannel_HE(bitrateRange *range, int inRate, int outRate, int channels)
{
	if(inRate > 46050) range->max = maxBitrateIndex_HE[channels][2];
	else if(inRate > 38050) range->max = maxBitrateIndex_HE[channels][1];
	else range->max = maxBitrateIndex_HE[channels][0];
	
	switch(outRate) {
		case 96000:
		case 48000:
			range->min = minBitrateIndex_HE[channels][2];
			range->max = maxBitrateIndex_HE[channels][2];
			break;
		case 44100:
			range->min = minBitrateIndex_HE[channels][1];
			range->max = maxBitrateIndex_HE[channels][1];
			break;
		case 32000:
			range->min = minBitrateIndex_HE[channels][0];
			range->max = maxBitrateIndex_HE[channels][0];
			break;
		default:
			range->min = 1;
	}
}

static int getAcrualTargetSamplerate(int inRate, int desiredRate)
{
	if(desiredRate == 0) return 0;
	if(desiredRate == 1) desiredRate = inRate;

	if(inRate > 46050 && desiredRate > 46050) {
		if(desiredRate != 48000) fprintf(stderr,"Warning: actual samplerate used is 48000 Hz\n");
		return 48000;
	}
	else if(inRate > 38050 && desiredRate > 38050) {
		if(desiredRate != 44100) fprintf(stderr,"Warning: actual samplerate used is 44100 Hz\n");
		return 44100;
	}
	else if(inRate > 28000 && desiredRate > 28000) {
		if(desiredRate != 32000) fprintf(stderr,"Warning: actual samplerate used is 32000 Hz\n");
		return 32000;
	}
	else if(inRate > 23025 && desiredRate > 23025) {
		if(desiredRate != 24000) fprintf(stderr,"Warning: actual samplerate used is 24000 Hz\n");
		return 24000;
	}
	else if(inRate > 19025 && desiredRate > 19025) {
		if(desiredRate != 22050) fprintf(stderr,"Warning: actual samplerate used is 22050 Hz\n");
		return 22050;
	}
	else if(inRate > 14000 && desiredRate > 14000) {
		if(desiredRate != 16000) fprintf(stderr,"Warning: actual samplerate used is 16000 Hz\n");
		return 16000;
	}
	else if(inRate > 11512 && desiredRate > 11512) {
		if(desiredRate != 12000) fprintf(stderr,"Warning: actual samplerate used is 12000 Hz\n");
		return 12000;
	}
	else if(inRate > 9512 && desiredRate > 9512) {
		if(desiredRate != 11025) fprintf(stderr,"Warning: actual samplerate used is 11025 Hz\n");
		return 11025;
	}
	else {
		if(desiredRate != 8000) fprintf(stderr,"Warning: actual samplerate used is 8000 Hz\n");
		return 8000;
	}
}

static int getSamplerateIndex(int rate) {
	if(rate == 0) return 0;
	if(rate == 8000) return 1;
	if(rate == 11025) return 2;
	if(rate == 12000) return 3;
	if(rate == 16000) return 4;
	if(rate == 22050) return 5;
	if(rate == 24000) return 6;
	if(rate == 32000) return 7;
	if(rate == 44100) return 8;
	if(rate == 48000) return 9;
	return 0;
}

static int getSamplerateIndex_HE(int rate) {
	if(rate == 0) return 0;
	if(rate == 32000) return 1;
	if(rate == 44100) return 2;
	if(rate == 48000) return 3;
	if(rate == 96000) return 4;
	return 0;
}

static CFArrayRef configureCodecSpecificSettings(CFArrayRef origArr, int modeIndex, int samplerateIndex, int modeQualityIndex, int overallQualityIndex, Boolean heFlag)
{
	int tmp,i;
	CFMutableArrayRef configArr = CFArrayCreateMutable(NULL,0,&kCFTypeArrayCallBacks);
	CFMutableDictionaryRef configDic;
	for(i=0;i<CFArrayGetCount(origArr);i++) {
		CFDictionaryRef current = (CFDictionaryRef)CFArrayGetValueAtIndex(origArr,i);
		if(!CFStringCompare((CFStringRef)CFDictionaryGetValue(current,CFSTR("converter")),CFSTR("CodecConverter"),0)) {
			configDic = CFDictionaryCreateMutableCopy(NULL,0,current);
		}
		else CFArrayAppendValue(configArr,current);
	}
	CFArrayRef oldParameterArr = (CFArrayRef)CFDictionaryGetValue(configDic,CFSTR("parameters"));
	CFMutableArrayRef parameterArr = CFArrayCreateMutable(NULL,0,&kCFTypeArrayCallBacks);
	CFNumberRef num;
	for(i=0;i<CFArrayGetCount(oldParameterArr);i++) {
		CFDictionaryRef dic = (CFDictionaryRef)CFArrayGetValueAtIndex(oldParameterArr,i);
		/*if(!CFStringCompare((CFStringRef)CFDictionaryGetValue(dic,CFSTR("key")),CFSTR("Channel Configuration"),0)) {
			tmp=1;
			CFMutableDictionaryRef newDic = CFDictionaryCreateMutableCopy(NULL,0,dic);
			num = CFNumberCreate(NULL,kCFNumberSInt32Type,&tmp);
			CFDictionarySetValue(newDic,CFSTR("current value"),num);
			CFRelease(num);
			CFArrayAppendValue(parameterArr,newDic);
			CFRelease(newDic);
		}
		else */if(!CFStringCompare((CFStringRef)CFDictionaryGetValue(dic,CFSTR("key")),CFSTR("Sample Rate"),0)) {
			CFMutableDictionaryRef newDic = CFDictionaryCreateMutableCopy(NULL,0,dic);
			num = CFNumberCreate(NULL,kCFNumberSInt32Type,&samplerateIndex);
			CFDictionarySetValue(newDic,CFSTR("current value"),num);
			CFRelease(num);
			CFArrayAppendValue(parameterArr,newDic);
			CFRelease(newDic);
		}
		else if(!CFStringCompare((CFStringRef)CFDictionaryGetValue(dic,CFSTR("key")),CFSTR("Target Format"),0)) {
			CFMutableDictionaryRef newDic = CFDictionaryCreateMutableCopy(NULL,0,dic);
			num = CFNumberCreate(NULL,kCFNumberSInt32Type,&modeIndex);
			CFDictionarySetValue(newDic,CFSTR("current value"),num);
			CFRelease(num);
			CFArrayAppendValue(parameterArr,newDic);
			CFRelease(newDic);
		}
		else if(!CFStringCompare((CFStringRef)CFDictionaryGetValue(dic,CFSTR("key")),CFSTR("Bit Rate"),0)) {
			CFMutableDictionaryRef newDic = CFDictionaryCreateMutableCopy(NULL,0,dic);
			if(heFlag || modeIndex != 1) {
				num = CFNumberCreate(NULL,kCFNumberSInt32Type,&modeQualityIndex);
				CFDictionarySetValue(newDic,CFSTR("current value"),num);
				CFRelease(num);
			}
			else {
				tmp=0;
				num = CFNumberCreate(NULL,kCFNumberSInt32Type,&tmp);
				CFDictionarySetValue(newDic,CFSTR("current value"),num);
				CFRelease(num);
				num = CFNumberCreate(NULL,kCFNumberSInt32Type,&modeQualityIndex);
				CFDictionarySetValue(newDic,CFSTR("slider value"),num);
				CFRelease(num);
			}
			CFArrayAppendValue(parameterArr,newDic);
			CFRelease(newDic);
		}
		else if(!CFStringCompare((CFStringRef)CFDictionaryGetValue(dic,CFSTR("key")),CFSTR("Quality"),0)) {
			CFMutableDictionaryRef newDic = CFDictionaryCreateMutableCopy(NULL,0,dic);
			num = CFNumberCreate(NULL,kCFNumberSInt32Type,&overallQualityIndex);
			CFDictionarySetValue(newDic,CFSTR("current value"),num);
			CFRelease(num);
			CFArrayAppendValue(parameterArr,newDic);
			CFRelease(newDic);
		}
		else {
			CFArrayAppendValue(parameterArr,dic);
		}
	}

	CFDictionarySetValue(configDic,CFSTR("parameters"),parameterArr);
	CFRelease(parameterArr);
	CFArrayAppendValue(configArr,configDic);
	CFRelease(configDic);
	return (CFArrayRef)configArr;
}

OSStatus configureComponent(ComponentInstance ci, encodingParameters *parameters, AudioStreamBasicDescription *inAsbd, AudioStreamBasicDescription *outAsbd, AudioChannelLayout *layout)
{
	codecConfig config = parameters->mode;
	int modeQuality = parameters->modeQuality;
	int overallQuality = parameters->overallQuality;
	int inRate = (int)inAsbd->mSampleRate;
	int outRate = parameters->outSamplerate;
	int channels = inAsbd->mChannelsPerFrame;
	int overallQualityIndex;
	int modeQualityIndex;
	int samplerateIndex;
	int modeIndex;
	CFArrayRef oldConfigArray=NULL, newConfigArray=NULL;
	int ret = -1;
	OSStatus error;

	if(overallQuality < 0) overallQuality = 0;
	else if(overallQuality > 127) overallQuality = 127;

	if(overallQuality < 43) overallQualityIndex = 0;
	else if(overallQuality < 86) overallQualityIndex = 1;
	else overallQualityIndex = 2;

	if(config == kConfigABR || config == kConfigCBR_HE) modeIndex = 0;
	else if(config == kConfigTrueVBR || config == kConfigABR_HE) modeIndex = 1;
	else if(config == kConfigConstrainedVBR || config == kConfigConstrainedVBR_HE) modeIndex = 2;
	else modeIndex = 3;

	outRate = getAcrualTargetSamplerate(inRate, outRate);

	if(config != 3) {
		bitrateRange range;
		int virtualChannelNum = channels;
		if(channels>2 && layout) {
			if(layout->mNumberChannelDescriptions) {
				unsigned int i;
				for(i=0;i<layout->mNumberChannelDescriptions;i++) {
					if(layout->mChannelDescriptions[i].mChannelLabel == kAudioChannelLabel_LFEScreen) virtualChannelNum--;
					else if(layout->mChannelDescriptions[i].mChannelLabel == kAudioChannelLabel_LFE2) virtualChannelNum--;
				}
			}
			else {
				switch(layout->mChannelLayoutTag) {
					case kAudioChannelLayoutTag_MPEG_5_1_A:
					case kAudioChannelLayoutTag_MPEG_5_1_B:
					case kAudioChannelLayoutTag_MPEG_5_1_C:
					case kAudioChannelLayoutTag_MPEG_5_1_D:
					case kAudioChannelLayoutTag_MPEG_6_1_A:
					case kAudioChannelLayoutTag_AAC_6_1:
					case kAudioChannelLayoutTag_MPEG_7_1_A:
					case kAudioChannelLayoutTag_MPEG_7_1_B:
					case kAudioChannelLayoutTag_MPEG_7_1_C:
					case kAudioChannelLayoutTag_Emagic_Default_7_1:
					case kAudioChannelLayoutTag_SMPTE_DTV:
						virtualChannelNum--;
				}
			}
		}
		if(config < 4) {
			getBitrateRangeForSamplerateAndChannel(&range,inRate,outRate,virtualChannelNum);
			modeQualityIndex = getBitrateIndex(modeQuality,bitrateTable[virtualChannelNum-1],&range);
			samplerateIndex = getSamplerateIndex(outRate);
			modeQuality = bitrateTable[virtualChannelNum-1][modeQualityIndex];
		}
		else {
			getBitrateRangeForSamplerateAndChannel_HE(&range,inRate,outRate,virtualChannelNum);
			modeQualityIndex = getBitrateIndex(modeQuality,bitrateTable_HE[virtualChannelNum-1],&range);
			samplerateIndex = getSamplerateIndex_HE(outRate);
			modeQuality = bitrateTable_HE[virtualChannelNum-1][modeQualityIndex];
		}
	}
	else {
		if(modeQuality < 0) {
			modeQuality = 0;
			fprintf(stderr,"Warning: actual VBR quality used is 0\n");
		}
		else if(modeQuality > 127) {
			modeQuality = 127;
			fprintf(stderr,"Warning: actual VBR quality used is 127\n");
		}
		modeQualityIndex = modeQuality;
		samplerateIndex = getSamplerateIndex(outRate);
	}

	memset(outAsbd,0,sizeof(AudioStreamBasicDescription));
	outAsbd->mFormatID = (config < 4) ? kAudioFormatMPEG4AAC : kAudioFormatMPEG4AAC_HE;
	outAsbd->mChannelsPerFrame = inAsbd->mChannelsPerFrame;
	
	error = QTSetComponentProperty(ci, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_BasicDescription, sizeof(AudioStreamBasicDescription), outAsbd);
	if(error) {
		fprintf(stderr,"QTSetComponentProperty error: cannot set output ASBD\n");
		goto last;
	}

	error = QTSetComponentProperty(ci, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_RenderQuality, 4, &overallQuality);
	if(error) {
		fprintf(stderr,"QTSetComponentProperty error: cannot set RenderQuality\n");
		goto last;
	}

	error = QTGetComponentProperty(ci, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_CodecSpecificSettingsArray, sizeof(CFArrayRef), &oldConfigArray,NULL);
	if(error) {
		fprintf(stderr,"QTGetComponentProperty error (kQTSCAudioPropertyID_CodecSpecificSettingsArray)\n");
		goto last;
	}

	newConfigArray = configureCodecSpecificSettings(oldConfigArray,modeIndex,samplerateIndex,modeQualityIndex,overallQualityIndex,parameters->highEfficiency);
	error = QTSetComponentProperty(ci, kQTPropertyClass_SCAudio, kQTSCAudioPropertyID_CodecSpecificSettingsArray, sizeof(CFArrayRef), &newConfigArray);
	if(error) {
		fprintf(stderr,"QTSetComponentProperty error (kQTSCAudioPropertyID_CodecSpecificSettingsArray)\n");
		goto last;
	}

	ret = 0;
	
last:
	parameters->modeQuality = modeQuality;
	if(oldConfigArray) CFRelease(oldConfigArray);
	if(newConfigArray) CFRelease(newConfigArray);
	return ret;
}
