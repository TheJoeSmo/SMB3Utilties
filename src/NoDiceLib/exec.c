#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "config.h"
#include "exec.h"
#include "stristr.h"

int NoDice_exec_build(void (*buffer_callback)(const char *))
{
	int result = 1;
	static char exec_buffer[EXEC_BUF_LINE_LEN];

	int fd[2];	// Descriptors for the pipe

	// Create the pipe in/out
	int pipe_result = pipe(fd);

	// Need to fork for the child process
	pid_t pid = fork();
	if(pid == 0)
	{
		// Child

		// Redirect both stdout and stderr into same pipe
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd[1], STDERR_FILENO);

		// Don't need the input end
		close(fd[0]);

		// Run process as configured
		execvp(NoDice_config.buildinfo.build_argv[0], NoDice_config.buildinfo.build_argv);

		// You only get here if the process failed to execute...

		// !!NOTE!! DELIBERATE use of the word "error" in case we're
		// doing trip-on-word-error!  Make sure that remains...
		// This will get piped so it will show up on the parent process.
		perror("Error executing");

		// And otherwise, we must return non-zero to trip in that case
		exit(1);
	}
	else
	{
		// Parent

		int status;
		size_t read_amt;

		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);

		while ((read_amt = fread(exec_buffer, 1, EXEC_BUF_LINE_LEN-1, stdin)))
		{
			// Terminate the string
			exec_buffer[read_amt] = '\0';

			// If we're configured to look for error condition via BUILDERR_TEXTERROR,
			// we must look to see if the word "error" appears in the buffer...
			// This isn't a great test, and I personally prefer by error code, but
			// nesasm does not return non-zero, so this is what we do...
			if(
				// Must be configured to do this check...
				(NoDice_config.buildinfo.builderr == BUILDERR_TEXTERROR) &&

				// Must not have already decided an ill status...
				(result == 1) &&

				// ... and finally, check if "error" is present:
				stristr(exec_buffer, "error")	)
				{
					// Error found, return zero!
					result = 0;
				}

			// In any case, call callback with buffer
			if(buffer_callback != NULL)
				buffer_callback(exec_buffer);
		}

		// Wait for child to finish
		waitpid(pid, &status, 0);


		// If configured for return code, check return code for non-zero
		if(NoDice_config.buildinfo.builderr == BUILDERR_RETURNCODE)
			result = WEXITSTATUS(status) == 0;

	}


	return result;
}
