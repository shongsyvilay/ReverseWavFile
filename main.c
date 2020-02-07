#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "wav.h"

int main(int argc, char** argv){
    char* content;
	
    size_t size = read_file(argv[1], &content);
    
    wave* wav_file = parse(content);
	
	if(argc != 3){
		printf("Not enough inputs. Please rerun program with an input \
			file and output file\n");
		return -1;
	}
	
    int dataSize = wav_file->dataSize;
    char reverseIt[dataSize];
    memcpy(reverseIt, wav_file->actData, dataSize);

	/** For loop that is reversing the file two bytes at a time. 
	The loop is only going through half the data size since we are 
	moving two bytes. */
    for(int i = 0; i <= dataSize/2; i = i + 2) {
        char temp0 = reverseIt[i];
		char temp1 = reverseIt[i + 1];
		reverseIt[i] = reverseIt[dataSize - i - 2];
		reverseIt[i + 1] = reverseIt[dataSize - i - 1];
		reverseIt[dataSize - i - 2] = temp0;
		reverseIt[dataSize - i - 1] = temp1;
    }
    
	/** Here the reverse data that was created is being replaced as
		the data in content with the same size.*/
    memcpy(content + 44, reverseIt, dataSize);
	
	/** The content is then being written into the file specified
		by the filename. It returns a size, but return is not used. */
    write_file(argv[2], content, size);

	/** Print statements that confirms that we get all the correct 
		header data. */
    printf("\nFile: %s \n", argv[1]);
    printf("====================\n");
    printf("- File size is %zu. Read %d bytes. \n", size, 
		   wav_file->chunk);
    printf("- Format is %s with format data length %d. \n", 
		   wav_file->fmt, wav_file->fmtLength);
    printf("- Format type is %hd. \n", wav_file->fmtType);
    printf("- %d channels with a sample rate of %d. \n", 
		   wav_file->channelNo, wav_file->sampleRate);
    printf("- %d byte rate, %d alignment, %d bits per sample. \n", 
		   wav_file->byteRate, wav_file->blockAlign, wav_file->bps);
    printf("- Data is %c%c%c%c and data size is %d. \n", 
		   wav_file->bds[0], wav_file->bds[1], wav_file->bds[2], 
		   wav_file->bds[3], dataSize);

    free(content);
	free(wav_file);
}