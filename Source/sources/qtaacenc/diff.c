diff --git a/src/qtaacenc/CodecConfigs.cpp b/qtaacenc/CodecConfigs.cpp
index 5609d7f..f77b01d 100644
--- a/src/qtaacenc/CodecConfigs.cpp
+++ b/qtaacenc/CodecConfigs.cpp
@@ -182,14 +182,7 @@ static CFArrayRef configureCodecSpecificSettings(CFArrayRef origArr, int modeInd
 {
 	int tmp,i;
 	CFMutableArrayRef configArr = CFArrayCreateMutable(NULL,0,&kCFTypeArrayCallBacks);
-	CFMutableDictionaryRef configDic;
-	for(i=0;i<CFArrayGetCount(origArr);i++) {
-		CFDictionaryRef current = (CFDictionaryRef)CFArrayGetValueAtIndex(origArr,i);
-		if(!CFStringCompare((CFStringRef)CFDictionaryGetValue(current,CFSTR("converter")),CFSTR("CodecConverter"),0)) {
-			configDic = CFDictionaryCreateMutableCopy(NULL,0,current);
-		}
-		else CFArrayAppendValue(configArr,current);
-	}
+	CFMutableDictionaryRef configDic = CFDictionaryCreateMutableCopy(NULL,0,(CFDictionaryRef)CFArrayGetValueAtIndex(origArr,0));
 	CFArrayRef oldParameterArr = (CFArrayRef)CFDictionaryGetValue(configDic,CFSTR("parameters"));
 	CFMutableArrayRef parameterArr = CFArrayCreateMutable(NULL,0,&kCFTypeArrayCallBacks);
 	CFNumberRef num;
diff --git a/src/qtaacenc/QTAACEncoder.cpp b/qtaacenc/QTAACEncoder.cpp
index 098aea3..daedfb5 100644
--- a/src/qtaacenc/QTAACEncoder.cpp
+++ b/qtaacenc/QTAACEncoder.cpp
@@ -12,7 +12,7 @@
 static const unsigned char INTEGER_PCM_GUID[16] = {0x01,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71};
 static const unsigned char FLOAT_PCM_GUID[16]   = {0x03,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71};
 
-static int fseek_stdin(FILE *fp, __int64 offset, char **seekBuf, int *seekBufSize)
+static Int64 fseek_stdin(FILE *fp, __int64 offset, char **seekBuf, int *seekBufSize)
 {
 	if(!offset) return 0;
 	if(fp!=stdin) return fseeko(fp,offset,SEEK_CUR);
@@ -26,15 +26,15 @@ static int fseek_stdin(FILE *fp, __int64 offset, char **seekBuf, int *seekBufSiz
 
 
 static ComponentResult
-pcmInputProc(ComponentInstance ci, 
-			 UInt32 *ioNumberDataPackets, 
-			 AudioBufferList *ioData, 
-			 AudioStreamPacketDescription **outDataPacketDescription, 
+pcmInputProc(ComponentInstance ci,
+			 UInt32 *ioNumberDataPackets,
+			 AudioBufferList *ioData,
+			 AudioStreamPacketDescription **outDataPacketDescription,
 			 void *inRefCon)
 {
 	QTAACEncoder *encoder = (QTAACEncoder *)inRefCon;
 	UInt32 requiredPackets = *ioNumberDataPackets;
-	
+
 	*ioNumberDataPackets = 0;
 
 	if(encoder->totalFrames && encoder->readFrames + requiredPackets > encoder->totalFrames) {
@@ -47,7 +47,7 @@ pcmInputProc(ComponentInstance ci,
 		ioData->mBuffers[0].mDataByteSize = 0;
 		goto last;
 	}
-	
+
 	if(ioData->mBuffers[0].mData == NULL)
 	{
 		UInt32 neededBufSize = requiredPackets * encoder->inAsbd.mBytesPerPacket;
@@ -79,7 +79,7 @@ pcmInputProc(ComponentInstance ci,
 		else if(requiredPackets == 0) encoder->finished = true;
 		//else if(encoder->totalFrames && encoder->readFrames >= encoder->totalFrames) encoder->finished = true;
 	}
-
+/*
 	if(encoder->totalFrames && encoder->showProgress) {
 		static double previousPercent = -1.0;
 		double percent = floor(100.0*(double)encoder->readFrames/encoder->totalFrames+0.5);
@@ -89,8 +89,32 @@ pcmInputProc(ComponentInstance ci,
 			previousPercent = percent;
 		}
 	}
+*/
+    if (encoder->showProgress)
+    {
+        const UInt32 SamplesPerFrame = 1;
+        static double previousPercent = -1.0;
+        double percent;
+        Char buf[50];
+        SInt32 i;
+
+        i = sprintf(buf, "\rProcessed %I64u ", (UInt64)(encoder->readFrames * SamplesPerFrame / encoder->inAsbd.mSampleRate));
+
+        if (encoder->totalFrames)
+        {
+            percent = floor(100.0 * (double)encoder->readFrames / encoder->totalFrames + 0.5);
+            if(percent > previousPercent)
+            {
+                sprintf(buf + i, "/ %I64u (%d%%) ", (UInt64)(encoder->totalFrames * SamplesPerFrame / encoder->inAsbd.mSampleRate), (int)percent);
+//                fprintf(stderr,"/ %I64u (%d%%) ", (UInt64)(encoder->totalFrames * SamplesPerFrame / encoder->inAsbd.mSampleRate), (int)percent);
+                previousPercent = percent;
+            }
+        }
+//        fprintf(stderr, "seconds ...                    ");
+        fprintf(stderr, "%sseconds ...                    ", buf);
+    }
 
-last:	
+last:
 	return noErr;
 }
 
@@ -104,9 +128,9 @@ Track getSoundTrack(Movie theMovie)
         Track    aTrack = NULL;
         Media    aMedia = NULL;
 
-        aTrack = GetMovieIndTrack(theMovie, index); 
+        aTrack = GetMovieIndTrack(theMovie, index);
         aMedia = GetTrackMedia(aTrack);
-        
+
         GetMediaHandlerDescription(aMedia, &aTrackType, 0, 0);
         if(aTrackType == SoundMediaType)
         {
@@ -374,7 +398,7 @@ Boolean QTAACEncoder::openFile(CFStringRef inFile)
 		fprintf(stderr,"MovieAudioExtractionSetProperty error(kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete)\n");
 		goto last;
 	}
-	
+
 	error = MovieAudioExtractionGetProperty(mae,
 											kQTPropertyClass_MovieAudioExtraction_Audio,
 											kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription,
@@ -424,7 +448,7 @@ Boolean QTAACEncoder::openFile(CFStringRef inFile)
 		goto last;
 	}
 	//fprintf(stderr,"%x,%x,%x,%x,%x,%x,%x,%f\n",asbd->mBitsPerChannel,asbd->mBytesPerFrame,asbd->mBytesPerPacket,asbd->mChannelsPerFrame,asbd->mFormatFlags,asbd->mFormatID,asbd->mFramesPerPacket,asbd->mSampleRate);
-	
+
 	if(!unknownChannelMap && noErr == MovieAudioExtractionGetPropertyInfo(mae, kQTPropertyClass_MovieAudioExtraction_Audio,
 													kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout,
 													NULL, &layoutSize, NULL ) )
@@ -605,7 +629,7 @@ SInt64 QTAACEncoder::beginEncode(CFStringRef outFile, encodingParameters *parame
 		fprintf(stderr,"CreateMovieStorage error; can't create the output file\n");
 		goto last;
 	}
-	
+
 	theTrack = NewMovieTrack(theMovie, 0, 0, kFullVolume);
 	if(outAsbd.mFormatID == 'aach')
 		theMedia = NewTrackMedia(theTrack, SoundMediaType, (TimeScale)outAsbd.mSampleRate/2, NULL, 0);
@@ -677,14 +701,15 @@ SInt64 QTAACEncoder::beginEncode(CFStringRef outFile, encodingParameters *parame
 	abl = (AudioBufferList*)calloc(1, offsetof(AudioBufferList, mBuffers[1]));
 	abl->mNumberBuffers = 1;
 
+    extern Bool bCtrlC;
 	// encoding loop
-	while(1) {
+	while(!bCtrlC) {
 		UInt32 i, packetsWritten = PACKETS_PER_LOOP;
 
 		abl->mBuffers[0].mNumberChannels = outAsbd.mChannelsPerFrame;
 		abl->mBuffers[0].mDataByteSize = bufferSize;
 		abl->mBuffers[0].mData = buffer;
-		
+
 		error = SCAudioFillBuffer(movieExporter, pcmInputProc, this, &packetsWritten, abl, aspds);
 		if(error) {
 			fprintf(stderr, "received err %ld from SCAudioFillBuffer\n",error);
@@ -693,7 +718,7 @@ SInt64 QTAACEncoder::beginEncode(CFStringRef outFile, encodingParameters *parame
 		else if(packetsWritten == 0 && abl->mBuffers[0].mDataByteSize == 0) { // EOF
 			break;
 		}
-		
+
 		if(packetsWritten) {
 			if(aspds) {
 				for (i = 0; i < packetsWritten; i++) {
diff --git a/src/qtaacenc/QTMP4Transcoder.cpp b/qtaacenc/QTMP4Transcoder.cpp
index 6a2c345..e29ff81 100644
--- a/src/qtaacenc/QTMP4Transcoder.cpp
+++ b/qtaacenc/QTMP4Transcoder.cpp
@@ -84,7 +84,7 @@ int convertToMP4PathThrough(CFStringRef inFile, CFStringRef outFile)
 	
 	error = ConvertMovieToDataRef(theMovie, 0, outDataRef, outDataRefType, kQTFileTypeMP4, FOUR_CHAR_CODE('TVOD'), createMovieFileDeleteCurFile|createMovieFileDontCreateResFile, movieExporter);
 	if(error) {
-		fprintf(stderr,"ConvertMovieToDataRef error: cannot translate .mov into .m4a (%d)\n",error);
+		fprintf(stderr,"ConvertMovieToDataRef error: cannot convert the input file\n");
 		goto last;
 	}
 
diff --git a/src/qtaacenc/common.h b/qtaacenc/common.h
index fe68bfe..18355f9 100644
--- a/src/qtaacenc/common.h
+++ b/qtaacenc/common.h
@@ -7,11 +7,22 @@
 #ifndef QTAACENC_COMMON_H
 #define QTAACENC_COMMON_H 1
 
-#define VERSION 20110816
+#include "my_common.h"
+#include "my_crt.h"
+#include "my_mem.h"
+
+OVERLOAD_OP_NEW
+
+#define VERSION 20100725
 
 #ifdef _MSC_VER
-#define fseeko _fseeki64
-#define ftello _ftelli64
+#if 1
+    #define fseeko my_fseek64
+    #define ftello my_ftell64
+#else
+    #define fseeko fseek
+    #define ftello ftell
+#endif
 #endif
 
 typedef struct
diff --git a/src/qtaacenc/metadata.cpp b/qtaacenc/metadata.cpp
index c7316d2..1a1c2cf 100644
--- a/src/qtaacenc/metadata.cpp
+++ b/qtaacenc/metadata.cpp
@@ -7,8 +7,18 @@
 #include "stdafx.h"
 #include "common.h"
 
-#define SWAP32(n) ((((n)>>24)&0xff) | (((n)>>8)&0xff00) | (((n)<<8)&0xff0000) | (((n)<<24)&0xff000000))
-#define SWAP16(n) ((((n)>>8)&0xff) | (((n)<<8)&0xff00))
+//#define SWAP32(n) ((((n)>>24)&0xff) | (((n)>>8)&0xff00) | (((n)<<8)&0xff0000) | (((n)<<24)&0xff000000))
+//#define SWAP16(n) ((((n)>>8)&0xff) | (((n)<<8)&0xff00))
+
+#define SWAP32(n) Bswap(n)
+ForceInline USHORT SWAP16(SHORT v)
+{
+    __asm
+    {
+        movzx eax, v;
+        xchg  ah, al;
+    }
+}
 
 #define DEFAULT_UDTA_SIZE 4096
 
@@ -105,26 +115,27 @@ static unsigned char *setupUdta(mp4Metadata_t *metadata, int bitrate, int mode,
 	long version = 0;
 	Gestalt(gestaltQuickTime,&version);
 	attr[0] = 0;
-	if(mode > 3) strcpy_s(attr,128,"High Efficiency, ");
+	if(mode > 3) strcpy(attr,"High Efficiency, ");
 	switch(mode) {
 		case kConfigCBR:
 		case kConfigCBR_HE:
-			sprintf_s(attr,128,"%sCBR %d kbps",attr,modeQuality);
+			sprintf(attr,"%sCBR %d kbps",attr,modeQuality);
 			break;
 		case kConfigABR:
 		case kConfigABR_HE:
-			sprintf_s(attr,128,"%sABR %d kbps",attr,modeQuality);
+			sprintf(attr,"%sABR %d kbps",attr,modeQuality);
 			break;
 		case kConfigConstrainedVBR:
 		case kConfigConstrainedVBR_HE:
-			sprintf_s(attr,128,"%sConstrained VBR %d kbps",attr,modeQuality);
+			sprintf(attr,"%sConstrained VBR %d kbps",attr,modeQuality);
 			break;
 		case kConfigTrueVBR:
-			sprintf_s(attr,128,"%sTrue VBR Quality %d",attr,modeQuality);
+			sprintf(attr,"%sTrue VBR Quality %d",attr,modeQuality);
 			break;
 	}
-	sprintf_s(str,256,"qtaacenc %d, QuickTime %d.%d.%d, %s",VERSION,(version>>24)&0xF,(version>>20)&0xF,(version>>16)&0xF,attr);
+	sprintf(str,"qtaacenc %d, QuickTime %d.%d.%d, %s",VERSION,(version>>24)&0xF,(version>>20)&0xF,(version>>16)&0xF,attr);
 	tmp = 24 + strlen(str);
+//    tmp += sprintf(str,"qtaacenc(modified by Amano) %d, QuickTime %d.%d.%d, %s",VERSION,(version>>24)&0xF,(version>>20)&0xF,(version>>16)&0xF,attr);
 	tmp = SWAP32(tmp);
 	atomID[0] = (char)0xa9;
 	memcpy(atomID+1,"too",3);
@@ -177,7 +188,7 @@ static unsigned char *setupUdta(mp4Metadata_t *metadata, int bitrate, int mode,
 
 	appendBytes(&udtaBuffer," 00000000 00000840 ",19);
 	char gaplessInfo[32];
-	sprintf_s(gaplessInfo,32,"%08X %016llX",(unsigned int)padding,(unsigned long long)frames);
+	sprintf(gaplessInfo,"%08X %016llX",(unsigned int)padding,(unsigned long long)frames);
 	appendBytes(&udtaBuffer,gaplessInfo,25);
 	appendBytes(&udtaBuffer," 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000",72);
 
@@ -502,7 +513,8 @@ void finalizeAtom(_TCHAR *path, int bitrate, int mode, int modeQuality, int samp
 	GetFileAttributesEx(path,GetFileExInfoStandard,&fi);
 	__int64 origSize = ((unsigned __int64)fi.nFileSizeHigh << 32)|fi.nFileSizeLow;
 
-	if(_tfopen_s(&fp, path, _T("r+b"))) return;
+    fp = _tfopen(path, _T("rb+"));
+	if(!fp) return;
 
 	int actualFreq = getM4aFrequency(fp);
 	if(actualFreq && (actualFreq != samplerate)) frame = (int)floor(0.5+(double)frame*actualFreq/samplerate);
diff --git a/src/qtaacenc/qtaacenc.cpp b/qtaacenc/qtaacenc.cpp
index 046dbd5..22a9195 100644
--- a/src/qtaacenc/qtaacenc.cpp
+++ b/qtaacenc/qtaacenc.cpp
@@ -3,11 +3,29 @@
 //
 // Copyright 2010 tmkk. All rights reserved.
 //
+#pragma warning(disable:4819)
 
 #include "stdafx.h"
 #include "common.h"
 #include "QTAACEncoder.h"
 
+Bool bCtrlC = False;
+
+BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
+{
+    switch(dwCtrlType)
+    {
+    case CTRL_C_EVENT:
+    case CTRL_BREAK_EVENT:
+    case CTRL_CLOSE_EVENT:
+    case CTRL_LOGOFF_EVENT:
+    case CTRL_SHUTDOWN_EVENT:
+        bCtrlC = True;
+        return True;
+    }
+    return False;
+}
+
 CFStringRef tCharToCFStr(_TCHAR *tstr)
 {
 	CFStringRef outStr;
@@ -194,22 +212,6 @@ int parseArguments(int argc, _TCHAR* argv[], encodingParameters *params)
 
 void showConfigurations(encodingParameters *params)
 {
-	ComponentDescription cd;
-	cd.componentType = 'aenc';
-	cd.componentSubType = 'aac ';
-	cd.componentManufacturer = kAppleManufacturer;
-	cd.componentFlags = 0;
-	cd.componentFlagsMask = 0;
-	long qtversion = 0;
-	Gestalt(gestaltQuickTime,&qtversion);
-	int lcversion = CallComponentVersion((ComponentInstance)FindNextComponent(NULL, &cd));
-	cd.componentSubType = 'aach';
-	int heversion = CallComponentVersion((ComponentInstance)FindNextComponent(NULL, &cd));
-	if(heversion != badComponentInstance)
-		fprintf(stderr,"Using QuickTime %d.%d.%d (LC-AAC encoder %d.%d.%d, HE-AAC encoder %d.%d.%d)\n",(qtversion>>24)&0xff,(qtversion>>20)&0xf,(qtversion>>16)&0xf,(lcversion>>16)&0xffff,(lcversion>>8)&0xff,lcversion&0xff,(heversion>>16)&0xffff,(heversion>>8)&0xff,heversion&0xff);
-	else
-		fprintf(stderr,"Using QuickTime %d.%d.%d (LC-AAC encoder %d.%d.%d)\n",(qtversion>>24)&0xff,(qtversion>>20)&0xf,(qtversion>>16)&0xf,(lcversion>>16)&0xffff,(lcversion>>8)&0xff,lcversion&0xff);
-
 	char *modeStr,*modeQualityStr,*overallQualityStr;
 	if(params->mode==kConfigCBR || params->mode==kConfigCBR_HE) modeStr = "CBR";
 	else if(params->mode==kConfigABR || params->mode==kConfigABR_HE) modeStr = "ABR";
@@ -276,15 +278,12 @@ void printUsage(void)
 
 int _tmain(int argc, _TCHAR* argv[])
 {
-	_TCHAR currentDir[MAX_PATH+1];
 	_TCHAR tempDir[MAX_PATH+1];
-	_TCHAR tempMovFile[MAX_PATH+1];
-	_TCHAR tempM4aFile[MAX_PATH+1];
-	CFStringRef inFileStr=NULL,outFileStr=NULL,tempMovFileStr=NULL,tempM4aFileStr=NULL;
+	_TCHAR tempFile[MAX_PATH+1];
+	CFStringRef inFileStr=NULL,outFileStr=NULL,tempFileStr=NULL;
 	encodingParameters parameters = {NULL,NULL,kConfigTrueVBR,65,kQualityHigh,0,false,false,false,false,{0}};
 	QTAACEncoder *encoder = NULL;
 	SInt64 frames;
-	Boolean heAvailable = false;
 	parameters.metadata.track = -1;
 	parameters.metadata.totalTrack = -1;
 	parameters.metadata.disc = -1;
@@ -296,17 +295,14 @@ int _tmain(int argc, _TCHAR* argv[])
 		printUsage();
 		return 0;
 	}
-	GetCurrentDirectory(MAX_PATH+1,currentDir);
 
 	InitializeQTML(0);
 	EnterMovies();
 
-	SetCurrentDirectory(currentDir);
-
 	long version = 0;
 	Gestalt(gestaltQuickTime,&version);
-	if(version < 0x07620000) {
-		fprintf(stderr,"Error: Please install the latest version of QuickTime (you have QT %d.%d.%d).\n",(version>>24)&0xff,(version>>20)&0xf,(version>>16)&0xf);
+	if(version < 0x07650000) {
+		fprintf(stderr,"Error: Please install the latest version of QuickTime.\n");
 		return 0;
 	}
 
@@ -320,11 +316,11 @@ int _tmain(int argc, _TCHAR* argv[])
 			RegQueryValueEx(hKey,entry,NULL,NULL,NULL,&size);
 			RegQueryValueEx(hKey,entry,NULL,NULL,(LPBYTE)szPath,&size);
 			RegCloseKey(hKey);
-			_sntprintf_s(szPath,MAX_PATH,_T("%sQuickTimeAudioSupport.qtx"),szPath);
+			_sntprintf(szPath,MAX_PATH,_T("%sQuickTimeAudioSupport.qtx"),szPath);
 		}
 		else {
 			SHGetSpecialFolderPath(NULL,szPath,CSIDL_PROGRAM_FILES,FALSE);
-			_sntprintf_s(szPath,MAX_PATH,_T("%s\\QuickTime\\QTSystem\\QuickTimeAudioSupport.qtx"),szPath);
+			_sntprintf(szPath,MAX_PATH,_T("%s\\QuickTime\\QTSystem\\QuickTimeAudioSupport.qtx"),szPath);
 		}
 		if(GetFileAttributes(szPath) != -1) {
 			ComponentDescription cd;
@@ -336,11 +332,9 @@ int _tmain(int argc, _TCHAR* argv[])
 			ComponentResult (*ComponentRoutine)(ComponentParameters *, Handle);
 			HMODULE h = LoadLibrary(szPath);
 			ComponentRoutine = (ComponentResult(__cdecl *)(ComponentParameters *, Handle))GetProcAddress(h,"ACMP4AACHighEfficiencyEncoderEntry");
-			if(ComponentRoutine) {
-				RegisterComponent(&cd,ComponentRoutine,0,NULL,NULL,NULL);
-				heAvailable = true;
-			}
+			RegisterComponent(&cd,ComponentRoutine,0,NULL,NULL,NULL);
 		}
+		else fprintf(stderr,"Error: HE-AAC encoder is not available in this machine\n");
 	}
 
 	if(parseArguments(argc, argv, &parameters)) {
@@ -348,21 +342,17 @@ int _tmain(int argc, _TCHAR* argv[])
 		printUsage();
 		return 0;
 	}
-	if(parameters.highEfficiency && !heAvailable) {
-		fprintf(stderr,"Error: HE-AAC encoder is only available with QuickTime 7.6.4 or later.\n");
-		return 0;
-	}
 	if(!parameters.quiet) showConfigurations(&parameters);
 
 	GetTempPath(MAX_PATH+1, tempDir);
-	GetTempFileName(tempDir,_T("qta"),0,tempMovFile);
-	GetLongPathName(tempMovFile,tempMovFile,MAX_PATH+1);
+	GetTempFileName(tempDir,_T("qta"),0,tempFile);
+	GetLongPathName(tempFile,tempFile,MAX_PATH+1);
 
-	tempMovFileStr = tCharToCFStr(tempMovFile);
+	tempFileStr = tCharToCFStr(tempFile);
 
 	if(!parameters.readFromStdin) {
 		replaceSlashWithBackSlash(parameters.inFile);
-		if(_tcslen(parameters.inFile) > 2 && !_tcsncmp(parameters.inFile+1,_T(":\\"),2)) {
+		if(_tcslen(parameters.inFile) > 1 && *(parameters.inFile+1)==_T(':')) {
 			inFileStr = tCharToCFStr(parameters.inFile);
 		}
 		else if(_tcslen(parameters.inFile) > 5 && !_tcsncmp(parameters.inFile,_T("\\\\?\\"),4)) {
@@ -380,32 +370,24 @@ int _tmain(int argc, _TCHAR* argv[])
 		_TCHAR *filenamePtr = PathFindFileName(parameters.inFile);
 		int bufSize = _tcslen(filenamePtr)+5;
 		parameters.outFile = new _TCHAR[bufSize];
-		_tcscpy_s(parameters.outFile,bufSize,filenamePtr);
+		_tcscpy(parameters.outFile,filenamePtr);
 		_TCHAR *extPtr = PathFindExtension(parameters.outFile);
-		_tcscpy_s(extPtr,5,_T(".m4a"));
+		_tcscpy(extPtr,_T(".m4a"));
 	}
-	else {
-		replaceSlashWithBackSlash(parameters.outFile);
-	}
-
-#if 0
-	if(_tcslen(parameters.outFile) > 2 && !_tcsncmp(parameters.outFile+1,_T(":\\"),2)) {
+	else replaceSlashWithBackSlash(parameters.outFile);
+	if(_tcslen(parameters.outFile) > 1 && *(parameters.outFile+1)==_T(':')) {
 		outFileStr = tCharToCFStr(parameters.outFile);
 	}
 	else if(_tcslen(parameters.outFile) > 5 && !_tcsncmp(parameters.outFile,_T("\\\\?\\"),4)) {
 		outFileStr = tCharToCFStr(parameters.outFile);
 	}
 	else {
-		_TCHAR *tmp = new _TCHAR[8192];
+//		_TCHAR *tmp = new _TCHAR[8192];
+        _TCHAR *tmp = (_TCHAR *)_alloca(8192 * sizeof(_TCHAR));
 		_tfullpath(tmp,parameters.outFile,8192);
-		_ftprintf(stderr,_T("%s\n"),tmp);
 		outFileStr = tCharToCFStr(tmp);
-		delete tmp;
+//		delete tmp;
 	}
-#endif
-	GetTempFileName(tempDir,_T("qta"),0,tempM4aFile);
-	GetLongPathName(tempM4aFile,tempM4aFile,MAX_PATH+1);
-	tempM4aFileStr = tCharToCFStr(tempM4aFile);
 
 	/* create encoder instance */
 	encoder = new QTAACEncoder();
@@ -438,29 +420,38 @@ int _tmain(int argc, _TCHAR* argv[])
 		}
 	}
 
+    Bool bVisible;
+    HANDLE hStdErr;
+    CONSOLE_CURSOR_INFO cci;
+
+    hStdErr = GetStdHandle(STD_ERROR_HANDLE);
+    GetConsoleCursorInfo(hStdErr, &cci);
+    bVisible = cci.bVisible;
+    cci.bVisible = False;
+    SetConsoleCursorInfo(hStdErr, &cci);
+    SetConsoleCtrlHandler(HandlerRoutine, True);
 	/* encode */
-	frames = encoder->beginEncode(tempMovFileStr,&parameters);
+    fclose(_tfopen(parameters.outFile, _T("wb")));
+	frames = encoder->beginEncode(tempFileStr,&parameters);
+
+    cci.bVisible = bVisible;
+    SetConsoleCursorInfo(hStdErr, &cci);
+
 	if(!frames) goto last;
 
 	/* convert to mp4 */
-	if(convertToMP4PathThrough(tempMovFileStr,tempM4aFileStr)) goto last;
+	if(convertToMP4PathThrough(tempFileStr,outFileStr)) goto last;
 
 	/* add tag */
-	finalizeAtom(tempM4aFile,0,parameters.mode,parameters.modeQuality,(int)encoder->inAsbd.mSampleRate,frames,&encoder->outAsbd,&parameters.metadata);
+	finalizeAtom(parameters.outFile,0,parameters.mode,parameters.modeQuality,(int)encoder->inAsbd.mSampleRate,frames,&encoder->outAsbd,&parameters.metadata);
 	
-	/* move file */
-	SetCurrentDirectory(currentDir);
-	MoveFileEx(tempM4aFile,parameters.outFile,MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH);
-
 last:
 	freeMp4Metadata(&parameters.metadata);
 	if(inFileStr) CFRelease(inFileStr);
 	if(outFileStr) CFRelease(outFileStr);
-	if(tempMovFileStr) CFRelease(tempMovFileStr);
-	if(tempM4aFileStr) CFRelease(tempM4aFileStr);
+	if(tempFileStr) CFRelease(tempFileStr);
 	if(encoder) delete encoder;
-	_tremove(tempMovFile);
-	_tremove(tempM4aFile);
+	_tremove(tempFile);
 	return 0;
 }
 
