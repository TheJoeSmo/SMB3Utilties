#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "logging.h"

/**
 * Generates a error into `buffer` from `message`.
 *
 * Parameters
 * ----------
 * buffer: *char
 *     The buffer to write the error to.
 * buffer_size: int
 *     The size of the buffer to write.
 * message: *char
 *     The error message.
 *
 */
void generate_error_to_buffer(char *buffer, int buffer_size, char *message) {
    snprintf(buffer, buffer_size, "%sError: %s%s\n", START_COLOR_YELLOW, END_COLORING, message);
}

/**
 * Generates a error message from `message`.
 *
 * Parameters
 * ----------
 * message: *char
 *     The error message.
 *
 * Returns
 * -------
 * char*
 *     The error message generated.
 *
 */
char *generate_error(char *message) {
    char *buffer = calloc(ERROR_MESSAGE_LENGTH, sizeof(char));

    // Handle if we do not have memory.
    if (buffer == NULL) {
        fwrite_error(stdout, "Failed to allocate memory for error: '%s'\n", message);
    }

    generate_error_to_buffer(buffer, ERROR_MESSAGE_LENGTH, message);

    return buffer;
}

/**
 * Writes a error message from `message` to `file`.
 *
 * Parameters
 * ----------
 * file: *FILE
 *     The file to write the error message to.
 * message: *char
 *     The error message.
 *
 */
void write_error(FILE *file, char *message) {
    char *error_message = generate_error(message);

    fputs(error_message, file);

    free(error_message);
}

/**
 * Writes a error message from `message` to `file` with formatting.
 *
 * Parameters
 * ----------
 * file: *FILE
 *     The file to write the error message to.
 * message: *char
 *     The error message to be formatted.
 * ...: va_list
 *     Variables arguments to be formatted inside the message.
 *
 */
void fwrite_error(FILE *file, char *message,...) {
    char formatted_message[ERROR_MESSAGE_LENGTH];
    va_list argp;

    // Reset the errno
    errno = 0;

    // Format the message provided from the user.
    va_start(argp, message);
    vsnprintf(formatted_message, sizeof(formatted_message), message, argp);
    if (errno != 0) {
        perror(formatted_message);
    }
    va_end(argp);

    write_error(file, formatted_message);
}

/**
 * Generates a warning into `buffer` from `message`.
 *
 * Parameters
 * ----------
 * buffer: *char
 *     The buffer to write the warning to.
 * buffer_size: int
 *     The size of the buffer to write.
 * message: *char
 *     The warning message.
 *
 */
void generate_warning_to_buffer(char *buffer, int buffer_size, char *message) {
    snprintf(buffer, buffer_size, "%sWarning: %s%s\n", START_COLOR_YELLOW, END_COLORING, message);
}

/**
 * Generates a warning message from `message`.
 *
 * Parameters
 * ----------
 * message: *char
 *     The warning message.
 *
 * Returns
 * -------
 * char*
 *     The warning message generated.
 *
 */
char *generate_warning(char *message) {
    char *buffer = calloc(ERROR_MESSAGE_LENGTH, sizeof(char));

    // Handle if we do not have memory.
    if (buffer == NULL) {
        fwrite_error(stdout, "Failed to allocate memory for warning: '%s'\n", message);
    }

    generate_warning_to_buffer(buffer, ERROR_MESSAGE_LENGTH, message);

    return buffer;
}

/**
 * Writes a warning message from `message` to `file`.
 *
 * Parameters
 * ----------
 * file: *FILE
 *     The file to write the warning message to.
 * message: *char
 *     The warning message.
 *
 */
void write_warning(FILE *file, char *message) {
    char *warning_message = generate_warning(message);

    fputs(warning_message, file);

    free(warning_message);
}

/**
 * Writes a warning message from `message` to `file` with formatting.
 *
 * Parameters
 * ----------
 * file: *FILE
 *     The file to write the warning message to.
 * message: *char
 *     The warning message to be formatted.
 * ...: va_list
 *     Variables arguments to be formatted inside the message.
 *
 */
void fwrite_warning(FILE *file, char *message,...) {
    char formatted_message[ERROR_MESSAGE_LENGTH];
    va_list argp;

    // Reset the errno
    errno = 0;

    // Format the message provided from the user.
    va_start(argp, message);
    vsnprintf(formatted_message, sizeof(formatted_message), message, argp);
    if (errno != 0) {
        perror(formatted_message);
    }
    va_end(argp);

    write_warning(file, formatted_message);
}
