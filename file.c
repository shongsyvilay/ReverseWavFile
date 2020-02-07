#include "file.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
/**********************************************************************
	Function that is taking in a filename, opening it, finding the
	size of it, and inputting the contents of the file into a buffer 
	@param filename - char pointer to the file
	@param buffer - char pointer to a pointer, starts empty and 
		   is filled with data from file
	@return size_t - size of file
**********************************************************************/ 
size_t read_file(char* filename, char **buffer){
	FILE *file;
	
	/** system struct that is used to store information about files*/
	struct stat st;
	
	if((file = fopen(filename, "rb"))== NULL) {
		printf("Unable to find file.\n");
		exit(-1);
	}
	
	/** function from the stat that gets information about the file
	and writes it to the stat struct*/
	stat(filename, &st);
	/** we can now get the size of the file by reading the fieldin st*/
	long size = st.st_size;
	
	*buffer = (char*) malloc(size * sizeof(char));
	
	fread(*buffer, size, 1, file);
	fclose(file);
	
	return size;
}

/**********************************************************************
	Function that is taking in a filename, opening it, if it does not 
	exist then creates it. The file is then written to with the data
	stored in the buffer with the amount determined by size. 
	@param filename - char pointer to the file
	@param buffer - char pointer, the information that will be written
		   to the file
	@param size - size_t size of what to write in the file
	@return size_t - size of what is written
**********************************************************************/ 
size_t write_file(char* filename, char* buffer, size_t size){
	FILE* file;
	
	file = fopen(filename, "w");
	size_t writtenSize = fwrite(buffer, sizeof(char), size, file);
	fclose(file);
	return writtenSize;
}