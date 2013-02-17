//
// qtaacenc.cpp
//
// Copyright 2010 tmkk. All rights reserved.
//
#pragma warning(disable:4819)

#include "stdafx.h"
#include "common.h"
#include "QTAACEncoder.h"
#include "MyLibrary.cpp"

#pragma comment(lib, NT6_LIB(kernel32.lib))

Bool bCtrlC = False;

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        bCtrlC = True;
        return True;
    }
    return False;
}

CFStringRef tCharToCFStr(_TCHAR *tstr)
{
	CFStringRef outStr;
	char *str;
	int len;
#ifdef UNICODE
	len = WideCharToMultiByte(CP_UTF8,0,tstr,-1,NULL,0,NULL,NULL);
	str = new char[len];
	WideCharToMultiByte(CP_UTF8,0,tstr,-1,str,len,NULL,NULL);
	outStr = CFStringCreateWithCString(NULL,str,kCFStringEncodingUTF8);
	delete str;
#else
	wchar_t *wstr;
	len = MultiByteToWideChar(CP_THREAD_ACP,0,tstr,-1,NULL,0);
	wstr = new wchar_t[len];
	MultiByteToWideChar(CP_THREAD_ACP,0,tstr,-1,wstr,len);
	len = WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);
	str = new char[len];
	WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);
	outStr = CFStringCreateWithCString(NULL,str,kCFStringEncodingUTF8);
	delete str;
	delete wstr;
#endif
	return outStr;
}

char *tCharToUTF8Str(_TCHAR *tstr)
{
	char *str;
	int len;
#ifdef UNICODE
	len = WideCharToMultiByte(CP_UTF8,0,tstr,-1,NULL,0,NULL,NULL);
	str = new char[len];
	WideCharToMultiByte(CP_UTF8,0,tstr,-1,str,len,NULL,NULL);
#else
	wchar_t *wstr;
	len = MultiByteToWideChar(CP_THREAD_ACP,0,tstr,-1,NULL,0);
	wstr = new wchar_t[len];
	MultiByteToWideChar(CP_THREAD_ACP,0,tstr,-1,wstr,len);
	len = WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);
	str = new char[len];
	WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);
	delete wstr;
#endif
	return str;
}

void replaceSlashWithBackSlash(_TCHAR *str)
{
	int i;
	for(i=_tcslen(str)-1;i>=0;i--) {
		if(str[i] == _T('/')) str[i] = _T('\\');
	}
}

CFStringRef myCFStringCreateWithFormat(CFAllocatorRef allocator, CFDictionaryRef options, CFStringRef format, ...)
{
	va_list args;
	va_start(args, format);
	CFStringRef str = CFStringCreateWithFormatAndArguments(allocator, options, format, args);
	va_end(args);
	return str;
}

int parseArguments(int argc, _TCHAR* argv[], encodingParameters *params)
{
	int i;
	for(i=1;i<argc;i++) {
		if(!_tcscmp(argv[i],_T("--fastest"))) params->overallQuality = kQualityFastest;
		else if(!_tcscmp(argv[i],_T("--fast"))) params->overallQuality = kQualityFast;
		else if(!_tcscmp(argv[i],_T("--normal"))) params->overallQuality = kQualityNormal;
		else if(!_tcscmp(argv[i],_T("--high"))) params->overallQuality = kQualityHigh;
		else if(!_tcscmp(argv[i],_T("--highest"))) params->overallQuality = kQualityHighest;
		else if(!_tcscmp(argv[i],_T("--quiet"))) params->quiet = true;
		else if(!_tcscmp(argv[i],_T("--cbr"))) {
			params->mode = kConfigCBR;
			if(++i<argc) {
				params->modeQuality = _tstoi(argv[i]);
				if(params->modeQuality < 8) params->modeQuality = 8;
				else if(params->modeQuality > 1280) params->modeQuality = 1280;
			}
		}
		else if(!_tcscmp(argv[i],_T("--abr"))) {
			params->mode = kConfigABR;
			if(++i<argc) {
				params->modeQuality = _tstoi(argv[i]);
				if(params->modeQuality < 8) params->modeQuality = 8;
				else if(params->modeQuality > 1280) params->modeQuality = 1280;
			}
		}
		else if(!_tcscmp(argv[i],_T("--cvbr"))) {
			params->mode = kConfigConstrainedVBR;
			if(++i<argc) {
				params->modeQuality = _tstoi(argv[i]);
				if(params->modeQuality < 8) params->modeQuality = 8;
				else if(params->modeQuality > 1280) params->modeQuality = 1280;
			}
		}
		else if(!_tcscmp(argv[i],_T("--tvbr"))) {
			params->mode = kConfigTrueVBR;
			if(++i<argc) {
				params->modeQuality = _tstoi(argv[i]);
				if(params->modeQuality < 0) params->modeQuality = 0;
				else if(params->modeQuality > 127) params->modeQuality = 127;
			}
		}
		else if(!_tcscmp(argv[i],_T("--samplerate"))) {
			if(++i<argc) {
				if(!_tcscmp(argv[i],_T("auto"))) params->outSamplerate = 0;
				else if(!_tcscmp(argv[i],_T("keep"))) params->outSamplerate = 1;
				else params->outSamplerate = _tstoi(argv[i]);
				if(params->outSamplerate < 0) params->outSamplerate = 0;
			}
		}
		else if(!_tcscmp(argv[i],_T("--title"))) {
			if(++i<argc) params->metadata.title = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--album"))) {
			if(++i<argc) params->metadata.album = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--artist"))) {
			if(++i<argc) params->metadata.artist = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--albumartist"))) {
			if(++i<argc) params->metadata.albumArtist = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--composer"))) {
			if(++i<argc) params->metadata.composer = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--grouping"))) {
			if(++i<argc) params->metadata.group = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--genre"))) {
			if(++i<argc) params->metadata.genre = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--date"))) {
			if(++i<argc) params->metadata.date = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--comment"))) {
			if(++i<argc) params->metadata.comment = tCharToUTF8Str(argv[i]);
		}
		else if(!_tcscmp(argv[i],_T("--track"))) {
			if(++i<argc) {
				_TCHAR *ptr;
				params->metadata.track = _tcstol(argv[i],&ptr,10);
				if(*ptr == _T('/')) params->metadata.totalTrack = _tcstol(ptr+1,&ptr,10);
			}
		}
		else if(!_tcscmp(argv[i],_T("--disc"))) {
			if(++i<argc) {
				_TCHAR *ptr;
				params->metadata.disc = _tcstol(argv[i],&ptr,10);
				if(*ptr == _T('/')) params->metadata.totalDisc = _tcstol(ptr+1,&ptr,10);
			}
		}
		else if(!_tcscmp(argv[i],_T("--compilation"))) {
			params->metadata.compilation = true;
		}
		else if(!_tcscmp(argv[i],_T("--ignorelength"))) {
			params->ignoreLength = true;
		}
		else if(!_tcscmp(argv[i],_T("--he"))) {
			params->highEfficiency = true;
		}
		else if(!_tcsncmp(argv[i],_T("--"),2)) {}
		else {
			if(!params->inFile) {
				params->inFile = argv[i];
				if(!_tcscmp(argv[i],_T("-"))) params->readFromStdin = true;
			}
			else if(!params->outFile) params->outFile = argv[i];
		}
	}
	if(!params->inFile) return -1;
	if(params->highEfficiency) {
		if(params->mode < 3) params->mode = (codecConfig)(params->mode + 4);
		else {
			fprintf(stderr,"Warning: HE-AAC encoder cannot be used with true VBR mode - disabled.\n");
			params->highEfficiency = false;
		}
	}
	return 0;
}

void showConfigurations(encodingParameters *params)
{
	ComponentDescription cd;
	cd.componentType = 'aenc';
	cd.componentSubType = 'aac ';
	cd.componentManufacturer = kAppleManufacturer;
	cd.componentFlags = 0;
	cd.componentFlagsMask = 0;
	long qtversion = 0;
	Gestalt(gestaltQuickTime,&qtversion);
	int lcversion = CallComponentVersion((ComponentInstance)FindNextComponent(NULL, &cd));
	cd.componentSubType = 'aach';
	int heversion = CallComponentVersion((ComponentInstance)FindNextComponent(NULL, &cd));
	if(heversion != badComponentInstance)
		fprintf(stderr,"Using QuickTime %d.%d.%d (LC-AAC encoder %d.%d.%d, HE-AAC encoder %d.%d.%d)\n",(qtversion>>24)&0xff,(qtversion>>20)&0xf,(qtversion>>16)&0xf,(lcversion>>16)&0xffff,(lcversion>>8)&0xff,lcversion&0xff,(heversion>>16)&0xffff,(heversion>>8)&0xff,heversion&0xff);
	else
		fprintf(stderr,"Using QuickTime %d.%d.%d (LC-AAC encoder %d.%d.%d)\n",(qtversion>>24)&0xff,(qtversion>>20)&0xf,(qtversion>>16)&0xf,(lcversion>>16)&0xffff,(lcversion>>8)&0xff,lcversion&0xff);

	char *modeStr,*modeQualityStr,*overallQualityStr;
	if(params->mode==kConfigCBR || params->mode==kConfigCBR_HE) modeStr = "CBR";
	else if(params->mode==kConfigABR || params->mode==kConfigABR_HE) modeStr = "ABR";
	else if(params->mode==kConfigConstrainedVBR || params->mode==kConfigConstrainedVBR_HE) modeStr = "Constrained VBR";
	else if(params->mode==kConfigTrueVBR) modeStr = "True VBR quality";
	if(params->mode!=kConfigTrueVBR) modeQualityStr = " kbps";
	else modeQualityStr = "";
	if(params->overallQuality==kQualityFastest) overallQualityStr = "Fastest speed";
	else if(params->overallQuality==kQualityFast) overallQualityStr = "Fast speed";
	else if(params->overallQuality==kQualityNormal) overallQualityStr = "Normal";
	else if(params->overallQuality==kQualityHigh) overallQualityStr = "High quality";
	else if(params->overallQuality==kQualityHighest) overallQualityStr = "Highest quality";
	fprintf(stderr,"Configurations: %s %d%s, ",modeStr,params->modeQuality,modeQualityStr);
	if(params->highEfficiency) fprintf(stderr,"High efficiency, ");
	fprintf(stderr,"%s profile, ",overallQualityStr);
	if(params->outSamplerate == 0) fprintf(stderr,"auto Hz\n");
	else if(params->outSamplerate == 1) fprintf(stderr,"keep Hz\n");
	else fprintf(stderr,"%d Hz\n",params->outSamplerate);
	fflush(stderr);
}

void printUsage(void)
{
	fprintf(stderr,"qtaacenc version %d by tmkk\n",VERSION);
	fprintf(stderr,"Usage: qtaacenc.exe [options] infile [outfile]\n");
	fprintf(stderr,"  Note: pass - as infile to encode from stdin.\n\n");
	fprintf(stderr,"  General encoding options\n");
	fprintf(stderr,"\t--cbr <bitrate>  : encode in CBR mode, bitrate=8..1280\n");
	fprintf(stderr,"\t--abr <bitrate>  : encode in ABR mode, bitrate=8..1280\n");
	fprintf(stderr,"\t--cvbr <bitrate> : encode in Constrained VBR mode, bitrate=8..1280\n");
	fprintf(stderr,"\t--tvbr <quality> : encode in True VBR mode, quality=0..127 [default]\n");
	fprintf(stderr,"\t--he             : enable high efficiency (HE-AAC) encoder\n");
	fprintf(stderr,"\t                   (cannot be used with True VBR mode)\n");
	fprintf(stderr,"\t--samplerate <auto|keep|value> : control the output samplerate\n");
	fprintf(stderr,"\t    auto  : automatically choose the optimum samplerate\n");
	fprintf(stderr,"\t            according to the bitrate and quality [default]\n");
	fprintf(stderr,"\t    keep  : keep the original samplerate (if possible)\n");
	fprintf(stderr,"\t    value : specify samplerate in Hz; allowed values are\n");
	fprintf(stderr,"\t            8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000\n");
	fprintf(stderr,"  Quality and speed options\n");
	fprintf(stderr,"\t--fastest : fastest encoding speed, but lowest quality\n");
	fprintf(stderr,"\t--fast    : fast encoding speed, but low quality\n");
	fprintf(stderr,"\t--normal  : moderate speed and quality\n");
	fprintf(stderr,"\t--high    : high quality, but slow encoding speed [default]\n");
	fprintf(stderr,"\t--highest : highest quality, but slowest encoding speed\n");
	fprintf(stderr,"  Metadata options\n");
	fprintf(stderr,"\t--title       <string>      : set the title tag\n");
	fprintf(stderr,"\t--artist      <string>      : set the artist tag\n");
	fprintf(stderr,"\t--album       <string>      : set the album title tag\n");
	fprintf(stderr,"\t--albumartist <string>      : set the album artist tag\n");
	fprintf(stderr,"\t--genre       <string>      : set the genre tag\n");
	fprintf(stderr,"\t--date        <string>      : set the release date tag\n");
	fprintf(stderr,"\t--composer    <string>      : set the composer tag\n");
	fprintf(stderr,"\t--grouping    <string>      : set the grouping tag\n");
	fprintf(stderr,"\t--comment     <string>      : set the comment tag\n");
	fprintf(stderr,"\t--track       <num>[/total] : set the track number tag\n");
	fprintf(stderr,"\t--disc        <num>[/total] : set the disc number tag\n");
	fprintf(stderr,"\t--compilation               : set the compilation flag\n");
	fprintf(stderr,"  Other options \n");
	fprintf(stderr,"\t--ignorelength : ignore the size of data chunk when encoding from pipe\n");
	fprintf(stderr,"\t--quiet        : don't print the progress\n");
}

#define HOOK_FUCKING_QUICK_TIME_OUTPUT L"C:\\COM_OutputM4aFileNameHack.m4a"
#define STUPID_QUICK_TIME   TAG4('SPQT')

struct FUCK_ : public TEB_ACTIVE_FRAME
{
    PWSTR Output;
    PWSTR TrueOutput;
};

TYPE_OF(CreateFileW)*		StubCreateFileW;
TYPE_OF(MoveFileW)*			StubMoveFileW;

HANDLE
WINAPI
HookCreateFileW(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
)
{
    FUCK_ *fuck;

    fuck = (FUCK_ *)Nt_FindThreadFrameByContext(STUPID_QUICK_TIME);
    if (fuck != NULL && !StrICompareW(lpFileName, fuck->Output))
    {
//        CreateSymbolicLink(fuck->Output, fuck->TrueOutput, NULL);
//        dwCreationDisposition = OPEN_EXISTING;
//        dwShareMode = FILE_SHARE_READ;
//		dwDesiredAccess = GENERIC_ALL;
		lpFileName = fuck->TrueOutput;
    }

    return StubCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL WINAPI HookMoveFileW(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName)
{
    FUCK_ *fuck;

    fuck = (FUCK_ *)Nt_FindThreadFrameByContext(STUPID_QUICK_TIME);
    if (fuck != NULL && !StrICompareW(lpNewFileName, fuck->Output))
    {
		lpNewFileName = fuck->TrueOutput;
		DeleteFileW(lpNewFileName);
    }

    return StubMoveFileW(lpExistingFileName, lpNewFileName);
}

int _tmain(int argc, _TCHAR* argv[])
{
    FUCK_ fuck;
    _TCHAR currentDir[MAX_PATH+1];
	_TCHAR tempDir[MAX_PATH+1];
//	_TCHAR tempFile[MAX_PATH+1];
//	CFStringRef inFileStr=NULL,outFileStr=NULL,tempFileStr=NULL;
	_TCHAR tempMovFile[MAX_PATH+1];
	_TCHAR tempM4aFile[MAX_PATH+1];
	CFStringRef inFileStr=NULL,outFileStr=NULL,tempMovFileStr=NULL,tempM4aFileStr=NULL;
	encodingParameters parameters = {NULL,NULL,kConfigTrueVBR,65,kQualityHigh,0,false,false,false,false,{0}};
	QTAACEncoder *encoder = NULL;
    SInt64 frames;
    Boolean heAvailable = false;
	parameters.metadata.track = -1;
	parameters.metadata.totalTrack = -1;
	parameters.metadata.disc = -1;
	parameters.metadata.totalDisc = -1;

	setlocale(LC_ALL, ".936");

	if(argc==1) {
		printUsage();
		return 0;
	}

	InitializeQTML(0);
	EnterMovies();

	long version = 0;
	Gestalt(gestaltQuickTime,&version);
	if(version < 0x07620000) {
		fprintf(stderr,"Error: Please install the QuickTime 7.6.2 (you have QT %d.%d.%d).\n",(version>>24)&0xff,(version>>20)&0xf,(version>>16)&0xf);
		return 0;
	}

	{
		HKEY hKey;
		TCHAR *subKey = _T("SOFTWARE\\Apple Computer, Inc.\\QuickTime");
		TCHAR *entry = _T("QTSysDir");
		DWORD size;
		TCHAR szPath[MAX_PATH+1];
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,subKey,0,KEY_READ,&hKey) == ERROR_SUCCESS) {
			RegQueryValueEx(hKey,entry,NULL,NULL,NULL,&size);
			RegQueryValueEx(hKey,entry,NULL,NULL,(LPBYTE)szPath,&size);
			RegCloseKey(hKey);
			_sntprintf(szPath,MAX_PATH,_T("%sQuickTimeAudioSupport.qtx"),szPath);
		}
		else {
			SHGetSpecialFolderPath(NULL,szPath,CSIDL_PROGRAM_FILES,FALSE);
			_sntprintf(szPath,MAX_PATH,_T("%s\\QuickTime\\QTSystem\\QuickTimeAudioSupport.qtx"),szPath);
		}
		if(GetFileAttributes(szPath) != -1) {
			ComponentDescription cd;
			cd.componentType = 'aenc';
			cd.componentSubType = kAudioFormatMPEG4AAC_HE;
			cd.componentManufacturer = kAppleManufacturer;
			cd.componentFlags = 0;
			cd.componentFlagsMask = 0;
			ComponentResult (*ComponentRoutine)(ComponentParameters *, Handle);
			HMODULE h = LoadLibrary(szPath);
			ComponentRoutine = (ComponentResult(__cdecl *)(ComponentParameters *, Handle))GetProcAddress(h,"ACMP4AACHighEfficiencyEncoderEntry");
			if(ComponentRoutine) {
				RegisterComponent(&cd,ComponentRoutine,0,NULL,NULL,NULL);
				heAvailable = true;
			}
		}
	}

	if(parseArguments(argc, argv, &parameters)) {
		if(argc>1)fprintf(stderr,"Error while parsing arguments\n");
		printUsage();
		return 0;
	}
	if(parameters.highEfficiency && !heAvailable) {
		fprintf(stderr,"Error: HE-AAC encoder is only available with QuickTime 7.6.4 or later.\n");
		return 0;
	}
	if(!parameters.quiet) showConfigurations(&parameters);

	GetTempPath(MAX_PATH+1, tempDir);
//	GetTempFileName(tempDir,_T("qta"),0,tempFile);
//	GetLongPathName(tempFile,tempFile,MAX_PATH+1);
	GetTempFileName(tempDir,_T("qta"),0,tempMovFile);
	GetLongPathName(tempMovFile,tempMovFile,MAX_PATH+1);

//	tempFileStr = tCharToCFStr(tempFile);
	tempMovFileStr = tCharToCFStr(tempMovFile);

	if(!parameters.readFromStdin) {
		replaceSlashWithBackSlash(parameters.inFile);
        if (parameters.inFile[0] != 0 && parameters.inFile[1] == ':' && parameters.inFile[2] == '\\') {
			inFileStr = tCharToCFStr(parameters.inFile);
		}
		else if(_tcslen(parameters.inFile) > 5 && !_tcsncmp(parameters.inFile,_T("\\\\?\\"),4)) {
			inFileStr = tCharToCFStr(parameters.inFile);
		}
		else {
			_TCHAR *tmp = new _TCHAR[8192];
			_tfullpath(tmp,parameters.inFile,8192);
			inFileStr = tCharToCFStr(tmp);
			delete tmp;
		}
	}
	
	if(!parameters.outFile) {
		_TCHAR *filenamePtr = PathFindFileName(parameters.inFile);
		int bufSize = _tcslen(filenamePtr)+5;
		parameters.outFile = new _TCHAR[bufSize];
		_tcscpy(parameters.outFile,filenamePtr);
		_TCHAR *extPtr = PathFindExtension(parameters.outFile);
		_tcscpy(extPtr,_T(".m4a"));
	}
	else {
		replaceSlashWithBackSlash(parameters.outFile);
	}

#if 0
    if (parameters.outFile[0] != 0 && parameters.outFile[1] == ':' && parameters.outFile[2] == '\\') {
		outFileStr = tCharToCFStr(parameters.outFile);
	}
	else if(_tcslen(parameters.outFile) > 5 && !_tcsncmp(parameters.outFile,_T("\\\\?\\"),4)) {
		outFileStr = tCharToCFStr(parameters.outFile);
	}
	else {
//		_TCHAR *tmp = new _TCHAR[8192];
        _TCHAR *tmp = (_TCHAR *)_alloca(8192 * sizeof(_TCHAR));
		_tfullpath(tmp,parameters.outFile,8192);
		outFileStr = tCharToCFStr(tmp);
		delete tmp;
	}
#endif

	WCHAR FullOutFile[MAX_NTPATH];

	GetTempFileName(tempDir,_T("qta"),0,tempM4aFile);
	GetLongPathName(tempM4aFile,tempM4aFile,MAX_PATH+1);
//    _tcscpy(tempM4aFile, parameters.outFile);
	tempM4aFileStr = tCharToCFStr(tempM4aFile);

	RtlGetFullPathName_U(parameters.outFile, sizeof(FullOutFile), FullOutFile, NULL);

    fuck.Context = STUPID_QUICK_TIME;
    fuck.Output = tempM4aFile;
    fuck.TrueOutput = FullOutFile;
	RtlPushFrame(&fuck);

    MEMORY_FUNCTION_PATCH f[] =
    {
		INLINE_HOOK_JUMP(CreateFileW,	HookCreateFileW,	StubCreateFileW),
		INLINE_HOOK_JUMP(MoveFileW,		HookMoveFileW,		StubMoveFileW),
    };

    Nt_PatchMemory(0, 0, f, countof(f), 0);

	/* create encoder instance */
	encoder = new QTAACEncoder();
	
	/* open file or stream */
	if(parameters.readFromStdin) {
		_setmode(_fileno(stdin), _O_BINARY);
		if(!encoder->openStream(stdin)) goto last;
	}
	else {
		if(GetFileAttributes(parameters.inFile) == -1) {
			fprintf(stderr,"Error: input file does not exist.\n");
			goto last;
		}
		if(!encoder->openFile(inFileStr)) goto last;
	}
	
	if(encoder->inAsbd.mChannelsPerFrame>8) {
		fprintf(stderr,"Error: max #channels supported is 8\n");
		goto last;
	}
	if(parameters.highEfficiency) {
		if(encoder->inAsbd.mSampleRate > 72000 || encoder->inAsbd.mSampleRate <= 28000) {
			fprintf(stderr,"Error: the input samplerate is not supported in HE-AAC encoder\n");
			goto last;
		}
		if(parameters.outSamplerate > 1 && parameters.outSamplerate < 32000) {
			fprintf(stderr,"Error: the output samplerate is not supported in HE-AAC encoder\n");
			goto last;
		}
	}

    Bool bVisible;
    HANDLE hStdErr;
    CONSOLE_CURSOR_INFO cci;

    hStdErr = GetStdHandle(STD_ERROR_HANDLE);
    GetConsoleCursorInfo(hStdErr, &cci);
    bVisible = cci.bVisible;
    cci.bVisible = False;
    SetConsoleCursorInfo(hStdErr, &cci);
    SetConsoleCtrlHandler(HandlerRoutine, True);
	/* encode */
    fclose(_tfopen(parameters.outFile, _T("wb")));
    // DeleteFileW(tempM4aFile);

//	frames = encoder->beginEncode(tempFileStr,&parameters);
	frames = encoder->beginEncode(tempMovFileStr,&parameters);

    cci.bVisible = bVisible;
    SetConsoleCursorInfo(hStdErr, &cci);

	if(!frames) goto last;

	/* convert to mp4 */
//	if(convertToMP4PathThrough(tempFileStr,outFileStr)) goto last;
	if(convertToMP4PathThrough(tempMovFileStr,tempM4aFileStr)) goto last;

	/* add tag */
    finalizeAtom(parameters.outFile,0,parameters.mode,parameters.modeQuality,(int)encoder->inAsbd.mSampleRate,frames,&encoder->outAsbd,&parameters.metadata);
//	finalizeAtom(tempM4aFile,0,parameters.mode,parameters.modeQuality,(int)encoder->inAsbd.mSampleRate,frames,&encoder->outAsbd,&parameters.metadata);

last:
	freeMp4Metadata(&parameters.metadata);
	if(inFileStr) CFRelease(inFileStr);
	if(outFileStr) CFRelease(outFileStr);
//	if(tempFileStr) CFRelease(tempFileStr);
	if(tempMovFileStr) CFRelease(tempMovFileStr);
	if(tempM4aFileStr) CFRelease(tempM4aFileStr);
	if(encoder) delete encoder;
//	_tremove(tempFile);
	DeleteFileW(tempMovFile);
	DeleteFileW(tempM4aFile);
	return 0;
}

