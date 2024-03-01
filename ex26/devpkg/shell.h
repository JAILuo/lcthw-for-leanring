#ifndef _shell_h
#define _shell_h

#define MAX_COMMAND_ARGS 100

#include <apr_thread_proc.h>

typedef struct Shell
{
    const char *dir;		// The directory in which the command will be executed
    const char *exe;		// The executable command

    apr_procattr_t *attr;	// The attribute of the process
    apr_proc_t proc;		// The process information 
    apr_exit_why_e exit_why;// The reason for process exit
    int exit_code;			// The exit code of the process

    const char *args[MAX_COMMAND_ARGS];// The arguments for the commmand
	int num_args;			// The count of arguments that need to replace.
} Shell;

int Shell_run(apr_pool_t *p, Shell *cmd, int num_replace_args);
int Shell_exec(Shell cmd, ...);

extern Shell CLEANUP_SH;	// Shell instance for cleanup command
extern Shell GIT_SH;		// Shell instance for git command
extern Shell TAR_SH;		// Shell instance for tar command
extern Shell CURL_SH;		// Shell instance for curl command
extern Shell CONFIGURE_SH;  // Shell instance for configure command
extern Shell MAKE_SH;		// Shell instance for make command
extern Shell INSTALL_SH;	// Shell instance for install command
#endif

