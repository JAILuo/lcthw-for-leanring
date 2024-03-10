#include "shell.h"
#include "apr_errno.h"
#include "apr_pools.h"
#include "apr_thread_proc.h" 
#include "bstrlib.h"
#include "dbg.h"
#include <stdarg.h>

/** 
 * Execute a shell command with variable arguments.
 *
 * @param template: The Shell struct containing the template command to run.
 * @param ...: Variable arguments to be substituted into the template command. 
 *             Each key-value pair consists of a key (template argument)
 *             and its corresponding value.
 *             The variable argument list must be terminated with a NULL value.
 * @return: 0 if the command was executed successfully,
 *         -1 if there was an error.
 * 
 * @Note 
 * The keys are represented by the template arguments,
 * and the values are the new arguments to substitute.
 * If a key in the template.args array matches the current key,
 * the corresponding value is replaced with the new argument.
 * 
 * @Note: The two key-value pair
 *			key <--> args[i] 
 *			arg <--> *args[i]
 *
 */
int Shell_exec(Shell template, ...)
{
    apr_pool_t *p = NULL;
    int rc = -1;
    apr_status_t rv = APR_SUCCESS;
    va_list argp;
	const char *key = NULL;		//The key in a key-value pairs
	const char *arg = NULL;		//The value in a key-value pairs       
    int i = 0;
	int num_replace_args = 1;
    
    rv = apr_pool_create(&p, NULL);
    check(rv == APR_SUCCESS, "Failed to create pool.");
    
    va_start(argp, template);
    
	// Update the template arguments
    for(key = va_arg(argp, const char *);
        key != NULL;
        key = va_arg(argp, const char *))
    {
        arg = va_arg(argp, const char *);
        
        for(i = 0; template.args[i] != NULL; i++)
		{
            if(strcmp(template.args[i], key) == 0)
			{
                template.args[i] = arg;
				num_replace_args++;
                break;
            }
        }
    }

	// Run the command and found corresponding parameter
    rc = Shell_run(p, &template, num_replace_args);
    check(rc == 0, "the command '%s' was executed unsuccessfully", template.exe); 

    apr_pool_destroy(p);
    va_end(argp);
    return rc;
 
error:
    if(p)
	{
        apr_pool_destroy(p);
    }
    return rc;
}


/**
 * Set up and execute a new shell command process.
 *
 * @param p: The memory pool to use for the process.
 * @param cmd: The Shell struct containing information about the command to run.
 * @Returns: 0 if the command was executed successfully,
 *          -1 if there was an error.
 */
int Shell_run(apr_pool_t *p, Shell *cmd, int num_replace_args)
{
	check(num_replace_args == cmd->num_args, "Incorrect numder of arguments provided for command.");

    apr_procattr_t *attr;	 // Set attributes for new process creation
    apr_status_t rv;		 // The return value of function calls for error handling.
    apr_proc_t newproc;		 // New process and its related information.	

    rv = apr_procattr_create(&attr, p); // Create process attribute
    check(rv == APR_SUCCESS, "Failed to create proc attr.");

    rv = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE); // Set IO for the command
    check(rv == APR_SUCCESS, "Failed to set IO of command.");

    rv = apr_procattr_dir_set(attr, cmd->dir); // Set root directory for the command
    check(rv == APR_SUCCESS, "Failed to set root to %s.", cmd->dir);

    rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH); // Set command type
    check(rv == APR_SUCCESS, "Failed to set cmd type.");

    rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, attr, p); // Create new process
    check(rv == APR_SUCCESS, "Failed to run command.");

    rv = apr_proc_wait(&newproc, &cmd->exit_code, &cmd->exit_why, APR_WAIT); // Wait for the process to finish
    check(rv == APR_CHILD_DONE, "Failed to wait.");
    check(cmd->exit_code == 0, "%s exited badly.", cmd->exe); // Check if the process exited successfully
    check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crashed.", cmd->exe); // Check exit reason

    return 0;
error:
    return -1;
}

Shell CLEANUP_SH =
{
    .exe = "rm",
    .dir = "/tmp",
    .args = {"rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz",
        "/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL},
    .num_args = 4
};

Shell GIT_SH =
{
    .dir = "/tmp",
    .exe = "git",
    .args = {"git", "clone", "URL", "pkg-build", NULL},
    .num_args = 2
};

Shell TAR_SH =
{
    .dir = "/tmp/pkg-build",
    .exe = "tar",
    .args = {"tar", "-xzf", "FILE", "--strip-components", "1", NULL},
    .num_args = 1
};

Shell CURL_SH =
{
    .dir = "/tmp",
    .exe = "curl",
    .args = {"curl", "-L", "-o", "TARGET", "URL", NULL},
    .num_args = 2
};

Shell CONFIGURE_SH =
{
    .exe = "./configure",
    .dir = "/tmp/pkg-build",
    .args = {"configure", "OPTS", NULL},
    .num_args = 1
};

Shell MAKE_SH =
{
    .exe = "make",
    .dir = "/tmp/pkg-build",
    .args = {"make", "OPTS", NULL},
    .num_args = 1
};

Shell INSTALL_SH =
{
    .exe = "sudo",
    .dir = "/tmp/pkg-build",
    .args = {"sudo", "make", "TARGET", NULL},
    .num_args = 1
};
