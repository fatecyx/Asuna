//
// QTMP4Transcoder.cpp
//
// Copyright 2010 tmkk. All rights reserved.
//

#include "stdafx.h"
#include "common.h"

int convertToMP4PathThrough(CFStringRef inFile, CFStringRef outFile)
{
	OSStatus error;
	MovieExportComponent movieExporter = NULL;
	Handle inDataRef=0, outDataRef=0;
	OSType inDataRefType, outDataRefType;
	short inResID = 0;
	Movie theMovie=0;
	int ret = -1;

	error = OpenADefaultComponent(MovieExportType, kQTFileTypeMP4, &movieExporter);
	if(error) {
		fprintf(stderr,"OpenADefaultComponent error: cannot find the QuickTime conponent\n");
		goto last;
	}
	error = QTNewDataReferenceFromFullPathCFString(inFile, kQTNativeDefaultPathStyle, 0, &inDataRef, &inDataRefType);
	if(error) {
		fprintf(stderr,"QTNewDataReferenceFromFullPathCFString error: input file path is invalid\n");
		goto last;
	}
	error = QTNewDataReferenceFromFullPathCFString(outFile, kQTNativeDefaultPathStyle, 0, &outDataRef, &outDataRefType);
	if(error) {
		fprintf(stderr,"QTNewDataReferenceFromFullPathCFString error: output file path is invalid\n");
		goto last;
	}
	error = NewMovieFromDataRef(&theMovie, newMovieActive, &inResID, inDataRef, inDataRefType);
	if(error) {
		fprintf(stderr,"NewMovieFromDataRef error: cannot open the input file\n");
		goto last;
	}

	Track theTrack = getSoundTrack(theMovie);
	Media theMedia = GetTrackMedia(theTrack);
	DeleteTrackSegment(theTrack, 0, GetTrackDuration(theTrack));
	SetMovieTimeScale(theMovie, GetMediaTimeScale(theMedia));
	InsertMediaIntoTrack(theTrack, 0, 0, GetMediaDuration(theMedia), fixed1);

	Boolean useHighResolutionAudio = true;
	QTSetComponentProperty(
		movieExporter,
		kQTPropertyClass_MovieExporter,
		kQTMovieExporterPropertyID_EnableHighResolutionAudioFeatures,
		sizeof(Boolean),
		&useHighResolutionAudio
	);

	UInt32 ftyp = 'mp42';
	QTSetComponentProperty(
		movieExporter,
		kQTPropertyClass_MovieExporter,
		'ftyp',
		4,
		&ftyp
	);

	QTAtomContainer ac;
	MovieExportGetSettingsAsAtomContainer(movieExporter, &ac);
	QTAtom ensoAtom = QTFindChildByID(ac, kParentAtomIsContainer, kQTSettingsMovieExportEnableSound, 1, NULL);
	if(ensoAtom) {
		long size, *data;
		QTGetAtomDataPtr(ac,ensoAtom,&size,(Ptr *)&data);
		data[0] = EndianS32_NtoB('past');
		QTSetAtomData(ac, ensoAtom, size, data);
		MovieExportSetSettingsFromAtomContainer(movieExporter, ac);
	}
	DisposeHandle(ac);
	
	/*Boolean cancelled;
	error = MovieExportDoUserDialog(movieExporter, theMovie, NULL, 0, GetMovieDuration(theMovie), &cancelled);
	if(cancelled) goto last;
	if(error) {
		printf("MovieExportDoUserDialog error\n");
		goto last;
	}*/
	
	error = ConvertMovieToDataRef(theMovie, 0, outDataRef, outDataRefType, kQTFileTypeMP4, FOUR_CHAR_CODE('TVOD'), createMovieFileDeleteCurFile|createMovieFileDontCreateResFile, movieExporter);
	if(error) {
        fprintf(stderr,"ConvertMovieToDataRef error: cannot translate .mov into .m4a (%d)\n",error);
		goto last;
	}

	ret = 0;
	
last:
	if(movieExporter) CloseComponent(movieExporter);
	if(theMovie) DisposeMovie(theMovie);
	if(inDataRef) DisposeHandle(inDataRef);
	if(outDataRef) DisposeHandle(outDataRef);

	return ret;
}
