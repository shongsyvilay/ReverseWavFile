#include "wav.h"
#include <string.h>
/**********************************************************************
	Parse takes in a pointer of information which will then copy the
	first 44 bytes as a wav file's header. The rest of the data will 
	be stored in the wav file's actData. Lastly, returning the 
	pointer to a wav file. 
	@param contents - char pointer
	@return wav pointer - a pointer to parsed data
**********************************************************************/
wave* parse(char* contents){
    
    wave* w = malloc(sizeof(wave));
    memcpy(w, contents, 44);
    w->actData = contents + 44;
    return w;
}
