/**
 * Components to help log into the console.
 *
 */

#include <stdarg.h>
#include <stdio.h>

#ifndef _CORE_LOGGING_H
#define _CORE_LOGGING_H

#define ERROR_MESSAGE_LENGTH 8192

void generate_error_to_buffer(char *buffer, int buffer_size, char *message);
char *generate_error(char *message);
void write_error(FILE *file, char *message);
void fwrite_error(FILE *file, char *message,...);

void generate_warning_to_buffer(char *buffer, int buffer_size, char *message);
char *generate_warning(char *message);
void write_warning(FILE *file, char *message);
void fwrite_warning(FILE *file, char *message,...);

#endif
