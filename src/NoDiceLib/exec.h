
#ifndef NODICE_EXEC_H
#define NODICE_EXEC_H

// Process execution
#define EXEC_BUF_LINE_LEN	512	// Length of a single line of output from the process execution buffer
int NoDice_exec_build(void (*buffer_callback)(const char *));	// FIXME: Probably not necessary to expose this

#endif
