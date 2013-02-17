//
// metadata.cpp
//
// Copyright 2010 tmkk. All rights reserved.
//

#include "stdafx.h"
#include "common.h"

#define SWAP32(n) ((((n)>>24)&0xff) | (((n)>>8)&0xff00) | (((n)<<8)&0xff0000) | (((n)<<24)&0xff000000))
#define SWAP16(n) ((((n)>>8)&0xff) | (((n)<<8)&0xff00))

#define DEFAULT_UDTA_SIZE 4096

typedef struct
{
	unsigned char *buffer;
	int maxSize;
	int contentSize;
} variableBuffer;

static void appendBytes(variableBuffer *dst, void *src, unsigned char length)
{
	if(dst->contentSize + length > dst->maxSize) {
		dst->maxSize += 4096;
		dst->buffer = (unsigned char *)realloc(dst->buffer,dst->maxSize);
	}
	memcpy(dst->buffer+dst->contentSize,src,length);
	dst->contentSize += length;
}

static void appendTextMetadata(variableBuffer *udtaBuffer, char *str, char *atomID)
{
	int tmp;
	int length = strlen(str);
	tmp = 24 + length;
	tmp = SWAP32(tmp);
	appendBytes(udtaBuffer,&tmp,4);
	appendBytes(udtaBuffer,atomID,4);
	tmp = 16 + length;
	tmp = SWAP32(tmp);
	memcpy(atomID,"data",4);
	appendBytes(udtaBuffer,&tmp,4);
	appendBytes(udtaBuffer,atomID,4);
	tmp = 1;
	tmp = SWAP32(tmp);
	appendBytes(udtaBuffer,&tmp,4);
	tmp = 0;
	appendBytes(udtaBuffer,&tmp,4);
	appendBytes(udtaBuffer,str,length);
}

static unsigned char *setupUdta(mp4Metadata_t *metadata, int bitrate, int mode, int modeQuality, int padding, SInt64 frames, int codecVersion, int *udtaSize)
{
	int tmp;
	short tmp2;
	char atomID[4];

	variableBuffer udtaBuffer;
	udtaBuffer.maxSize = DEFAULT_UDTA_SIZE;
	udtaBuffer.contentSize = 0;
	udtaBuffer.buffer = (unsigned char *)malloc(DEFAULT_UDTA_SIZE);

	/* udta atom */
	tmp = 0;
	memcpy(atomID,"udta",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);

	/* meta atom */
	tmp = 0;
	memcpy(atomID,"meta",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	appendBytes(&udtaBuffer,&tmp,4);

	/* hdlr atom */
	tmp = 0x22;
	tmp = SWAP32(tmp);
	memcpy(atomID,"hdlr",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 0;
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,&tmp,4);
	memcpy(atomID,"mdir",4);
	appendBytes(&udtaBuffer,atomID,4);
	memcpy(atomID,"appl",4);
	appendBytes(&udtaBuffer,atomID,4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,&tmp,4);
	tmp2 = 0;
	tmp2 = SWAP16(tmp2);
	appendBytes(&udtaBuffer,&tmp2,2);

	/* ilst atom */
	tmp = 0;
	memcpy(atomID,"ilst",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);

	/* encoder info */
	char attr[128];
	char str[256];
	long version = 0;
	Gestalt(gestaltQuickTime,&version);
	attr[0] = 0;
	if(mode > 3) strcpy_s(attr,128,"High Efficiency, ");
	switch(mode) {
		case kConfigCBR:
		case kConfigCBR_HE:
			sprintf_s(attr,128,"%sCBR %d kbps",attr,modeQuality);
			break;
		case kConfigABR:
		case kConfigABR_HE:
			sprintf_s(attr,128,"%sABR %d kbps",attr,modeQuality);
			break;
		case kConfigConstrainedVBR:
		case kConfigConstrainedVBR_HE:
			sprintf_s(attr,128,"%sConstrained VBR %d kbps",attr,modeQuality);
			break;
		case kConfigTrueVBR:
			sprintf_s(attr,128,"%sTrue VBR Quality %d",attr,modeQuality);
			break;
	}
	sprintf_s(str,256,"qtaacenc %d, QuickTime %d.%d.%d, %s",VERSION,(version>>24)&0xF,(version>>20)&0xF,(version>>16)&0xF,attr);
	tmp = 24 + strlen(str);
	tmp = SWAP32(tmp);
	atomID[0] = (char)0xa9;
	memcpy(atomID+1,"too",3);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 16 + strlen(str);
	tmp = SWAP32(tmp);
	memcpy(atomID,"data",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 1;
	tmp = SWAP32(tmp);
	appendBytes(&udtaBuffer,&tmp,4);
	tmp = 0;
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,str,strlen(str));

	/* gapless info */
	tmp = 0xBC;
	tmp = SWAP32(tmp);
	memcpy(atomID,"----",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 0x1C;
	tmp = SWAP32(tmp);
	memcpy(atomID,"mean",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 0;
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,"com.apple.iTunes",16);
	tmp = 0x14;
	tmp = SWAP32(tmp);
	memcpy(atomID,"name",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 0;
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,"iTunSMPB",8);
	tmp = 0x84;
	tmp = SWAP32(tmp);
	memcpy(atomID,"data",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 1;
	tmp = SWAP32(tmp);
	appendBytes(&udtaBuffer,&tmp,4);
	tmp = 0;
	appendBytes(&udtaBuffer,&tmp,4);

	appendBytes(&udtaBuffer," 00000000 00000840 ",19);
	char gaplessInfo[32];
	sprintf_s(gaplessInfo,32,"%08X %016llX",(unsigned int)padding,(unsigned long long)frames);
	appendBytes(&udtaBuffer,gaplessInfo,25);
	appendBytes(&udtaBuffer," 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000",72);

	/* bitrate info */
	tmp = 0x6f;
	tmp = SWAP32(tmp);
	memcpy(atomID,"----",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 0x1C;
	tmp = SWAP32(tmp);
	memcpy(atomID,"mean",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 0;
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,"com.apple.iTunes",16);
	tmp = 0x1B;
	tmp = SWAP32(tmp);
	memcpy(atomID,"name",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 0;
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,"Encoding Params",15);
	tmp = 0x30;
	tmp = SWAP32(tmp);
	memcpy(atomID,"data",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);
	tmp = 0;
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,&tmp,4);

	tmp = 1;
	tmp = SWAP32(tmp);
	appendBytes(&udtaBuffer,"vers",4);
	appendBytes(&udtaBuffer,&tmp,4);

	mode = (mode<4) ? mode : mode-4;
	tmp = SWAP32(mode);
	appendBytes(&udtaBuffer,"acbf",4);
	appendBytes(&udtaBuffer,&tmp,4);

	tmp = SWAP32(bitrate);
	appendBytes(&udtaBuffer,"brat",4);
	appendBytes(&udtaBuffer,&tmp,4);

	tmp = SWAP32(codecVersion);
	appendBytes(&udtaBuffer,"cdcv",4);
	appendBytes(&udtaBuffer,&tmp,4);
	
	/* title */
	if(metadata->title) {
		atomID[0] = (char)0xa9;
		memcpy(atomID+1,"nam",3);
		appendTextMetadata(&udtaBuffer,metadata->title,atomID);
	}
	/* artist */
	if(metadata->artist) {
		atomID[0] = (char)0xa9;
		memcpy(atomID+1,"ART",3);
		appendTextMetadata(&udtaBuffer,metadata->artist,atomID);
	}
	/* album */
	if(metadata->album) {
		atomID[0] = (char)0xa9;
		memcpy(atomID+1,"alb",3);
		appendTextMetadata(&udtaBuffer,metadata->album,atomID);
	}
	/* album artist */
	if(metadata->albumArtist) {
		memcpy(atomID,"aART",4);
		appendTextMetadata(&udtaBuffer,metadata->albumArtist,atomID);
	}
	/* composer */
	if(metadata->composer) {
		atomID[0] = (char)0xa9;
		memcpy(atomID+1,"wrt",3);
		appendTextMetadata(&udtaBuffer,metadata->composer,atomID);
	}
	/* group */
	if(metadata->group) {
		atomID[0] = (char)0xa9;
		memcpy(atomID+1,"grp",3);
		appendTextMetadata(&udtaBuffer,metadata->group,atomID);
	}
	/* genre */
	if(metadata->genre) {
		atomID[0] = (char)0xa9;
		memcpy(atomID+1,"gen",3);
		appendTextMetadata(&udtaBuffer,metadata->genre,atomID);
	}
	/* date */
	if(metadata->date) {
		atomID[0] = (char)0xa9;
		memcpy(atomID+1,"day",3);
		appendTextMetadata(&udtaBuffer,metadata->date,atomID);
	}
	/* comment */
	if(metadata->comment) {
		atomID[0] = (char)0xa9;
		memcpy(atomID+1,"cmt",3);
		appendTextMetadata(&udtaBuffer,metadata->comment,atomID);
	}
	/* track */
	if(metadata->track > 0 || metadata->totalTrack > 0) {
		tmp = 0x20;
		tmp = SWAP32(tmp);
		memcpy(atomID,"trkn",4);
		appendBytes(&udtaBuffer,&tmp,4);
		appendBytes(&udtaBuffer,atomID,4);
		tmp = 0x18;
		tmp = SWAP32(tmp);
		memcpy(atomID,"data",4);
		appendBytes(&udtaBuffer,&tmp,4);
		appendBytes(&udtaBuffer,atomID,4);
		tmp = 0;
		appendBytes(&udtaBuffer,&tmp,4);
		appendBytes(&udtaBuffer,&tmp,4);
		tmp2 = 0;
		appendBytes(&udtaBuffer,&tmp2,2);
		if(metadata->track > 0) {
			tmp2 = metadata->track;
			tmp2 = SWAP16(tmp2);
		}
		appendBytes(&udtaBuffer,&tmp2,2);
		tmp2 = 0;
		if(metadata->totalTrack > 0) {
			tmp2 = metadata->totalTrack;
			tmp2 = SWAP16(tmp2);
		}
		appendBytes(&udtaBuffer,&tmp2,2);
		tmp2 = 0;
		appendBytes(&udtaBuffer,&tmp2,2);
	}
	/* disc */
	if(metadata->disc > 0 || metadata->totalDisc > 0) {
		tmp = 0x20;
		tmp = SWAP32(tmp);
		memcpy(atomID,"disk",4);
		appendBytes(&udtaBuffer,&tmp,4);
		appendBytes(&udtaBuffer,atomID,4);
		tmp = 0x18;
		tmp = SWAP32(tmp);
		memcpy(atomID,"data",4);
		appendBytes(&udtaBuffer,&tmp,4);
		appendBytes(&udtaBuffer,atomID,4);
		tmp = 0;
		appendBytes(&udtaBuffer,&tmp,4);
		appendBytes(&udtaBuffer,&tmp,4);
		tmp2 = 0;
		appendBytes(&udtaBuffer,&tmp2,2);
		if(metadata->disc > 0) {
			tmp2 = metadata->disc;
			tmp2 = SWAP16(tmp2);
		}
		appendBytes(&udtaBuffer,&tmp2,2);
		tmp2 = 0;
		if(metadata->totalDisc > 0) {
			tmp2 = metadata->totalDisc;
			tmp2 = SWAP16(tmp2);
		}
		appendBytes(&udtaBuffer,&tmp2,2);
		tmp2 = 0;
		appendBytes(&udtaBuffer,&tmp2,2);
	}

	/* compilation */
	if(metadata->compilation) {
		tmp = 0x19;
		tmp = SWAP32(tmp);
		memcpy(atomID,"cpil",4);
		appendBytes(&udtaBuffer,&tmp,4);
		appendBytes(&udtaBuffer,atomID,4);
		tmp = 0x11;
		tmp = SWAP32(tmp);
		memcpy(atomID,"data",4);
		appendBytes(&udtaBuffer,&tmp,4);
		appendBytes(&udtaBuffer,atomID,4);
		tmp = 0x15;
		tmp = SWAP32(tmp);
		appendBytes(&udtaBuffer,&tmp,4);
		tmp = 0;
		appendBytes(&udtaBuffer,&tmp,4);
		char tmp3 = 1;
		appendBytes(&udtaBuffer,&tmp3,1);
	}
	
	/* update length of ilst atom */
	tmp = SWAP32(udtaBuffer.contentSize-54);
	memcpy(udtaBuffer.buffer+54,&tmp,4);

	/* padding */
	memset(udtaBuffer.buffer+udtaBuffer.contentSize,0,udtaBuffer.maxSize-udtaBuffer.contentSize);

	tmp = SWAP32(udtaBuffer.maxSize-udtaBuffer.contentSize);
	memcpy(atomID,"free",4);
	appendBytes(&udtaBuffer,&tmp,4);
	appendBytes(&udtaBuffer,atomID,4);

	/* update length of udta atom */
	tmp = SWAP32(udtaBuffer.maxSize);
	memcpy(udtaBuffer.buffer,&tmp,4);

	/* update length of meta atom */
	tmp = SWAP32(udtaBuffer.maxSize-8);
	memcpy(udtaBuffer.buffer+8,&tmp,4);

	*udtaSize = udtaBuffer.maxSize;

	return udtaBuffer.buffer;
}

static const unsigned int srTable[16]= {96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11025,  8000,  7350,     0,     0,     0,};

static int getM4aFrequency(FILE *fp)
{
	char atom[4];
	int tmp,i;
	__int64 initPos = ftello(fp);
	int freq = 0;
	
	if(fseeko(fp,0,SEEK_SET) != 0) goto end;
	
	while(1) { //skip until moov;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"moov",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}
	
	while(1) { //skip until trak;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"trak",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}
	
	while(1) { //skip until mdia;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"mdia",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}
	
	while(1) { //skip until minf;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"minf",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}
	
	while(1) { //skip until stbl;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"stbl",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}
	
	while(1) { //skip until esds;
		if(fread(atom,1,4,fp) < 4) goto end;
		if(!memcmp(atom,"esds",4)) break;
		if(fseeko(fp,-3,SEEK_CUR) != 0) goto end;
	}
	
	if(fseeko(fp,5,SEEK_CUR) != 0) goto end;
	for(i=0;i<3;i++) {
		if(fread(atom,1,1,fp) < 1) goto end;
		if((unsigned char)atom[0] != 0x80) {
			if(fseeko(fp,-1,SEEK_CUR) != 0) goto end;
			break;
		}
	}
	if(fseeko(fp,5,SEEK_CUR) != 0) goto end;
	for(i=0;i<3;i++) {
		if(fread(atom,1,1,fp) < 1) goto end;
		if((unsigned char)atom[0] != 0x80) {
			if(fseeko(fp,-1,SEEK_CUR) != 0) goto end;
			break;
		}
	}
	if(fseeko(fp,15,SEEK_CUR) != 0) goto end;
	for(i=0;i<3;i++) {
		if(fread(atom,1,1,fp) < 1) goto end;
		if((unsigned char)atom[0] != 0x80) {
			if(fseeko(fp,-1,SEEK_CUR) != 0) goto end;
			break;
		}
	}
	if(fseeko(fp,1,SEEK_CUR) != 0) goto end;
	if(fread(atom,1,2,fp) < 2) goto end;
	tmp = (atom[0]<<1)&0xe;
	tmp |= (atom[1]>>7)&0x1;
	freq = srTable[tmp];
	
end:
	fseeko(fp,initPos,SEEK_SET);
	return freq;
}

void finalizeAtom(_TCHAR *path, int bitrate, int mode, int modeQuality, int samplerate, SInt64 frame, AudioStreamBasicDescription *asbd, mp4Metadata_t *metadata)
{
	unsigned int tmp;
	char atom[4];
	int udtaSize = 0;
	int bufferSize = 1024*1024;
	char *tmpbuf = (char *)malloc(bufferSize);
	char *tmpbuf2 = (char *)malloc(bufferSize);
	char *read = tmpbuf;
	char *write = tmpbuf2;
	char *swap;
	FILE *fp;
	unsigned char *udta = NULL;
	WIN32_FILE_ATTRIBUTE_DATA fi;

	GetFileAttributesEx(path,GetFileExInfoStandard,&fi);
	__int64 origSize = ((unsigned __int64)fi.nFileSizeHigh << 32)|fi.nFileSizeLow;

	if(_tfopen_s(&fp, path, _T("r+b"))) return;

	int actualFreq = getM4aFrequency(fp);
	if(actualFreq && (actualFreq != samplerate)) frame = (int)floor(0.5+(double)frame*actualFreq/samplerate);
	int padding = (int)((SInt64)ceil((frame + 2112)/1024.0)*1024 - (frame + 2112));

	ComponentDescription cd;
	cd.componentType = 'aenc';
	cd.componentSubType = asbd->mFormatID;
	cd.componentManufacturer = kAppleManufacturer;
	cd.componentFlags = 0;
	cd.componentFlagsMask = 0;
	int version = GetComponentVersion((ComponentInstance)FindNextComponent(NULL, &cd));

	if(!bitrate) {
		while(1) { //skip until mdat;
			if(fread(&tmp,4,1,fp) < 1) goto end;
			if(fread(atom,1,4,fp) < 4) goto end;
			tmp = SWAP32(tmp);
			if(!memcmp(atom,"mdat",4)) break;
			if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
		}
		bitrate = (int)ceil(0.5+(tmp-8)/((double)frame/actualFreq)*8) ;
		rewind(fp);
	}

	udta = setupUdta(metadata,bitrate,mode,modeQuality,padding,frame,version,&udtaSize);
	int i;

	while(1) { //skip until moov;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"moov",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}

	if(fseeko(fp,-8,SEEK_CUR) != 0) goto end;

	/* update moov atom size */
	__int64 pos_moov = ftello(fp);
	if(fread(&tmp,4,1,fp) < 1) goto end;
	int moovSize = SWAP32(tmp);
	if(fseeko(fp,-4,SEEK_CUR) != 0) goto end;
	tmp = SWAP32(moovSize + udtaSize);
	if(fwrite(&tmp,4,1,fp) < 1) goto end;

	if(fseeko(fp,4,SEEK_CUR) != 0) goto end;

	while(1) { //skip until trak;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"trak",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}

	while(1) { //skip until mdia;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"mdia",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}

	while(1) { //skip until minf;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"minf",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}

	while(1) { //skip until stbl;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"stbl",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}
	
	__int64 nextAtom = ftello(fp);

	while(1) { //skip until stsz;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"stsz",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}

	if(fseeko(fp,4,SEEK_CUR) != 0) goto end;
	
	/* estimate maximum bitrate */
	int maxBitrate = 0;
	if(fread(&tmp,4,1,fp) < 1) goto end;
	tmp = SWAP32(tmp);
	if(tmp) maxBitrate = tmp * 8 * actualFreq / 1024;
	else {
		if(fread(&tmp,4,1,fp) < 1) goto end;
		int frameNum = SWAP32(tmp);
		int frameSize;
		int sample;
		for(i=0,sample=0,frameSize=0;i<frameNum;i++) {
			if(fread(&tmp,4,1,fp) < 1) goto end;
			tmp = SWAP32(tmp);
			if(sample + 1024 >= actualFreq) {
				frameSize += (int)((actualFreq - sample)/1024.0 * tmp);
				if(frameSize*8 > maxBitrate) maxBitrate = frameSize*8;
				sample = 1024 - (actualFreq - sample);
				frameSize = (int)(sample/1024.0 * tmp);
				continue;
			}
			frameSize += tmp;
			sample += 1024;
		}
	}

	if(fseeko(fp,nextAtom,SEEK_SET) != 0) goto end;

	/* write bitrate info */
	while(1) { //skip until esds;
		if(fread(atom,1,4,fp) < 4) goto end;
		if(!memcmp(atom,"esds",4)) break;
		if(fseeko(fp,-3,SEEK_CUR) != 0) goto end;
	}

	if(fseeko(fp,5,SEEK_CUR) != 0) goto end;
	for(i=0;i<3;i++) {
		if(fread(atom,1,1,fp) < 1) goto end;
		if((unsigned char)atom[0] != 0x80) {
			if(fseeko(fp,-1,SEEK_CUR) != 0) goto end;
			break;
		}
	}
	if(fseeko(fp,5,SEEK_CUR) != 0) goto end;
	for(i=0;i<3;i++) {
		if(fread(atom,1,1,fp) < 1) goto end;
		if((unsigned char)atom[0] != 0x80) {
			if(fseeko(fp,-1,SEEK_CUR) != 0) goto end;
			break;
		}
	}
	if(fseeko(fp,6,SEEK_CUR) != 0) goto end;
	tmp = SWAP32(maxBitrate);
	if(fwrite(&tmp,4,1,fp) < 1) goto end;
	tmp = SWAP32(bitrate);
	if(fwrite(&tmp,4,1,fp) < 1) goto end;

	if(fseeko(fp,nextAtom,SEEK_SET) != 0) goto end;

	while(1) { //skip until stco;
		if(fread(&tmp,4,1,fp) < 1) goto end;
		if(fread(atom,1,4,fp) < 4) goto end;
		tmp = SWAP32(tmp);
		if(!memcmp(atom,"stco",4)) break;
		if(fseeko(fp,tmp-8,SEEK_CUR) != 0) goto end;
	}

	int *stco = (int *)malloc(tmp-8);
	if(fread(stco,1,tmp-8,fp) < tmp-8) goto end;
	int nElement = SWAP32(stco[1]);

	/* update stco atom */

	for(i=0;i<nElement;i++) {
		stco[2+i] = SWAP32(SWAP32(stco[2+i])+udtaSize);
	}
	if(fseeko(fp,8-(int)tmp,SEEK_CUR) != 0) goto end;
	if(fwrite(stco,1,tmp-8,fp) < tmp-8) goto end;

	free(stco);

	/* write tags */
	if(fseeko(fp,pos_moov,SEEK_SET) != 0) goto end;
	if(fseeko(fp,moovSize,SEEK_CUR) != 0) goto end;

	__int64 pos_tag = ftello(fp);
	__int64 bytesToMove = origSize-pos_tag;

	if(bytesToMove < udtaSize) {
		if(bufferSize < udtaSize) {
			tmpbuf = (char *)realloc(tmpbuf,udtaSize);
			read = tmpbuf;
		}
		if((int)fread(read,1,(size_t)bytesToMove,fp) < bytesToMove) goto end;
		if(fseeko(fp,0,SEEK_END) != 0) goto end;
		if((int)fwrite(read,1,(size_t)(udtaSize-bytesToMove),fp) < (udtaSize-bytesToMove)) goto end;
		if((int)fwrite(read,1,(size_t)bytesToMove,fp) < bytesToMove) goto end;
	}
	else if(bytesToMove > bufferSize) {
		if(bufferSize < udtaSize) {
			tmpbuf = (char *)realloc(tmpbuf,udtaSize);
			tmpbuf2 = (char *)realloc(tmpbuf2,udtaSize);
			read = tmpbuf;
			write = tmpbuf2;
			bufferSize = udtaSize;
			if(bytesToMove <= bufferSize) goto moveBlock_is_smaller_than_buffer;
		}
		if((int)fread(write,1,bufferSize,fp) < bufferSize) goto end;
		bytesToMove -= bufferSize;
		while(bytesToMove > bufferSize) {
			if((int)fread(read,1,bufferSize,fp) < bufferSize) goto end;
			if(fseeko(fp,udtaSize-2*bufferSize,SEEK_CUR) != 0) goto end;
			if((int)fwrite(write,1,bufferSize,fp) < bufferSize) goto end;
			if(fseeko(fp,bufferSize-udtaSize,SEEK_CUR) != 0) goto end;
			swap = read;
			read = write;
			write = swap;
			bytesToMove -= bufferSize;
		}
		if((int)fread(read,1,(size_t)bytesToMove,fp) < bytesToMove) goto end;
		if(fseeko(fp,udtaSize-bufferSize-bytesToMove,SEEK_CUR) != 0) goto end;
		if((int)fwrite(write,1,bufferSize,fp) < bufferSize) goto end;
		if((int)fwrite(read,1,(size_t)bytesToMove,fp) < bytesToMove) goto end;
	}
	else {
moveBlock_is_smaller_than_buffer:
		if((int)fread(read,1,(size_t)bytesToMove,fp) < bytesToMove) goto end;
		if(udtaSize < bytesToMove) {
			if(fseeko(fp,udtaSize-bytesToMove,SEEK_CUR) != 0) goto end;
		}
		else {
			if(fseeko(fp,0-bytesToMove,SEEK_CUR) != 0) goto end;
			if((int)fwrite(udta,1,udtaSize,fp) < udtaSize) goto end;
		}
		if((int)fwrite(read,1,(size_t)bytesToMove,fp) < bytesToMove) goto end;
	}

	if(fseeko(fp,pos_tag,SEEK_SET) != 0) goto end;
	
	if((int)fwrite(udta,1,udtaSize,fp) < udtaSize) goto end;

end:
	fclose(fp);
	if(udta) free(udta);
	free(tmpbuf);
	free(tmpbuf2);
}

void freeMp4Metadata(mp4Metadata_t *metadata)
{
	if(metadata->title) free(metadata->title);
	if(metadata->artist) free(metadata->artist);
	if(metadata->album) free(metadata->album);
	if(metadata->albumArtist) free(metadata->albumArtist);
	if(metadata->composer) free(metadata->composer);
	if(metadata->group) free(metadata->group);
	if(metadata->genre) free(metadata->genre);
	if(metadata->date) free(metadata->date);
	if(metadata->comment) free(metadata->comment);
}
