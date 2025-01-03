#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void log_message(FILE* logfile, const char* format, ...) {
	if(logfile) {
		va_list args;
		va_start(args, format);
		vfprintf(logfile, format, args);
		//fprintf(logfile, format, args);
		fflush(logfile); //Writes to the file inmediately
		va_end(args);
	}
}