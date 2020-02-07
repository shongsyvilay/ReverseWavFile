#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**********************************************************************
	Wav header file
**********************************************************************/ 
typedef struct wave_file {
    char riff[4];
    int chunk;
    char wave[4];
    char fmt[4];
    int fmtLength;
    short fmtType;
    short channelNo;
    int sampleRate;
    int byteRate;
    short blockAlign;
    short bps;
    char bds[4];
    int dataSize;
    char* actData;
} wave;

wave* parse(char* contents);
