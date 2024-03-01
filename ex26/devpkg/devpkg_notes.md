## Brief description
​	Apache Portable Runtime (APR) project is a sub-project of the Apache Software Foundation, providing a cross-platform library to support the development of Apache HTTP Server and other related projects.
​	The goal of APR is to offer a universal, portable programming interface that allows developers to easily **write cross-platform applications.**

####  Features and Usage of APR:

1. Cross-platform:
APR offers a cross-platform API,
enabling developers to write code with the same functionality on
different operating systems without worrying about
platform-specific details.

2. Low-level functionality support:
APR encapsulates many low-level functionalities such as memory management,
file operations, network operations, making it easier for
developers to access these functionalities.

3. Thread support:
APR provides a thread library, allowing developers to use multithreading
in their applications for concurrent processing.

4. Memory pool:
APR provides a memory pool mechanism for more efficient memory allocation
and deallocation, avoiding memory leaks and fragmentation.

5. Network programming:
APR offers network programming-related functionalities like socket operations,
network address handling, facilitating the development
of network applications.

6. File operations:
APR provides file operation functionalities such as file read/write,
file attribute operations, making it convenient for developing file
handling applications.

## Some header files in devpkg

- `#include "apr_errno.h"`
- `#include "apr_pools.h"`
- `#include "apr_thread_proc.h"`
- `#include <apr_errno.h>`
- `#include <apr_file_io.h>`



## Funtions in APR library
>Some functions and marcos from the Apache Portable Runtime (APR) library are used in the devpkg.
>Make simple introduction

####  db.c
1. `apr_pool_t *p = NULL;`
   
   - **Purpose**: Declare a pointer to the APR memory pool.
   - **Features**: A memory pool is a mechanism in APR for allocating and managing memory, which can improve the efficiency and management of memory allocation.
   
   
   
2. `apr_pool_initialize();`
   - **Purpose**: Initialize the memory pool system in the APR library.
   - **Function**: This function needs to be called for initialization before using the APR memory pool.
   
   
   
3. `apr_pool_create(&p, NULL);`
   
   - **Purpose**: Create a new APR memory pool.
   - **Feature**: Used to create a new memory pool that can be used to allocate memory and manage resources.
   
   
   
4. `apr_status_t rc = apr_dir_make_recursive(DB_DIR, APR_UREAD | APR_UWRITE | APR_UEXECUTE | APR_GREAD | APR_GWRITE | APR_GEXECUTE, p);`
   - **Purpose**: Create a directory recursively.
   - **Function**: Create directories with specified permissions, including read, write, and execute permissions for users and groups.
   
   
   
5. `apr_status_t`
   
   - **Function**: The return type of the function in the APR library, which indicates the status of the function execution result.





#### shell.c

1. `apr_procattr_create();`
   
    ```c
    /**
     * Create and initialize a new procattr variable
     * @param new_attr The newly created procattr. 
     * @param cont The pool to use
     */
    APR_DECLARE(apr_status_t) apr_procattr_create(apr_procattr_t **new_attr,
                                                      apr_pool_t *cont);
    ```
    
    - **Purpose**: Prepare the environment for launching a new child process. 
    
        The function initializes a structure to specify the attributes of the child process, such as the starting directory, input/output streams, etc.



2. `apr_procattr_io_set();`

    ```c
    /**
     * Determine if any of stdin, stdout, or stderr should be linked to pipes 
     * when starting a child process.
     * @param attr The procattr we care about. 
     * @param in Should stdin be a pipe back to the parent?
     * @param out Should stdout be a pipe back to the parent?
     * @param err Should stderr be a pipe back to the parent?
     * @note If APR_NO_PIPE, there will be no special channel, the child
     * inherits the parent's corresponding stdio stream.  If APR_NO_FILE is 
     * specified, that corresponding stream is closed in the child (and will
     * be INVALID_HANDLE_VALUE when inspected on Win32). This can have ugly 
     * side effects, as the next file opened in the child on Unix will fall
     * into the stdio stream fd slot!
     */
    APR_DECLARE(apr_status_t) apr_procattr_io_set(apr_procattr_t *attr, 
                                                 apr_int32_t in, apr_int32_t out,
                                                 apr_int32_t err);
    ```

    - **Purpose**: This function is used to set the handling of the standard input, output, and error streams of the child process. By controlling these pipe connections, inter-process communication and redirection can be achieved.



3. `apr_procattr_dir_set:`

    ```c
    /**
     * Set which directory the child process should start executing in.
     * @param attr The procattr we care about. 
     * @param dir Which dir to start in.  By default, this is the same dir as
     *            the parent currently resides in, when the createprocess call
     *            is made.                            
     */
    APR_DECLARE(apr_status_t) apr_procattr_dir_set(apr_procattr_t *attr,
    												const char *dir);
    ```

    - **Purpose**: This function specifies the starting directory of the child process. When the child process is launched, it will switch to the specified directory to execute subsequent operations.



4. `apr_procattr_cmdtype_set:`

    ```c
        /**
     * Set what type of command the child process will call.
     * @param attr The procattr we care about. 
     * @param cmd The type of command.  One of:
     * <PRE>
     *            APR_SHELLCMD     --  Anything that the shell can handle
     *            APR_PROGRAM      --  Executable program   (default) 
     *            APR_PROGRAM_ENV  --  Executable program, copy environment
     *            APR_PROGRAM_PATH --  Executable program on PATH, copy env
     * </PRE>
     */
    APR_DECLARE(apr_status_t) apr_procattr_cmdtype_set(apr_procattr_t *attr,
                                                      apr_cmdtype_e cmd);
    ```

    - **Purpose**: By setting the command type, you can specify the type of command the child process will execute, such as executable program, shell command, etc.



5. `apr_proc_create:`

    ```c
    /**
     * Create a new process and execute a new program within that process.
     * @param new_proc The resulting process handle.
     * @param progname The program to run 
     * @param args the arguments to pass to the new program.  The first 
     *             one should be the program name.
     * @param env The new environment table for the new process.  This 
     *            should be a list of NULL-terminated strings. This argument
     *            is ignored for APR_PROGRAM_ENV, APR_PROGRAM_PATH, and                                                                                               
     *            APR_SHELLCMD_ENV types of commands.
     * @param attr the procattr we should use to determine how to create the new
     *         process
     * @param pool The pool to use.
     * @note This function returns without waiting for the new process to terminate;
     * use apr_proc_wait for that.
     */
    APR_DECLARE(apr_status_t) apr_proc_create(apr_proc_t *new_proc,
                                              const char *progname,
                                              const char * const *args,
                                              const char * const *env,
                                              apr_procattr_t *attr,
                                              apr_pool_t *pool);
    ```

    - **Purpose**: This function actually creates a new process based on the current process and executes the specified program within it. It uses the previously set `apr_procattr_t` structure to determine the attributes of the new process.

> **==Some thoughts while coding==**
>
> The answer from GPT：
>
> The function `Shell_run` initializes many attributes of the new process before creating the process for several reasons:
>
> 1. **Granular Control**: By setting attributes before creating the process, the function can have granular control over various aspects of the new process, such as I/O settings, root directory, command type, etc. This allows for customization and fine-tuning of the process's behavior and environment.
> 2. **Error Handling**: Setting attributes individually allows for better error handling. If any attribute setting fails, the function can catch the error and handle it appropriately. This approach helps in ensuring that the process creation is successful and provides detailed error messages in case of failures.
> 3. **Modularity and Readability**: Initializing attributes separately makes the code modular and easier to read and maintain. Each step in the process is clearly defined and can be easily understood, making the code more organized and structured.
>
> Regarding passing all related information when using `apr_proc_create` directly, it is a matter of design choice and flexibility. By setting attributes individually, the function can have more control over each aspect of the process creation. This approach also allows for better error checking and handling at each step.



6. `apr_proc_wait:`

    ```c
    /**
     * Wait for a child process to die
     * @param proc The process handle that corresponds to the desired child process 
     * @param exitcode The returned exit status of the child, if a child process 
     *                 dies, or the signal that caused the child to die.
     *                 On platforms that don't support obtaining this information, 
     *                 the status parameter will be returned as APR_ENOTIMPL.
     * @param exitwhy Why the child died, the bitwise or of:
     * <PRE>
     *            APR_PROC_EXIT         -- process terminated normally
     *            APR_PROC_SIGNAL       -- process was killed by a signal
     *            APR_PROC_SIGNAL_CORE  -- process was killed by a signal, and
     *                                     generated a core dump.
     * </PRE>
     * @param waithow How should we wait.  One of:
     * <PRE>
     *            APR_WAIT   -- block until the child process dies.
     *            APR_NOWAIT -- return immediately regardless of if the 
     *                          child is dead or not.
     * </PRE>
     * @remark The child's status is in the return code to this process.  It is one of:
     * <PRE>
     *            APR_CHILD_DONE     -- child is no longer running.
     *            APR_CHILD_NOTDONE  -- child is still running.
     * </PRE>
     */
    APR_DECLARE(apr_status_t) apr_proc_wait(apr_proc_t *proc,
                                            int *exitcode, apr_exit_why_e *exitwhy,
                                            apr_wait_how_e waithow);
    ```

    - **Purpose**: This function waits for the specified child process to exit and retrieves its exit status and exit reason. This function can be used to achieve inter-process synchronization and handle the exit status of child processes.



7. `apr_procattr_t *attr`:

    - **Type**: Pointer to the `apr_procattr_t` structure.

    - **Purpose**: This variable is used to store attributes for process creation.

        In the Apache Portable Runtime (APR) library, the `apr_procattr_t` structure is used to set and control the attributes of a new process, such as environment variables, file descriptors, signal handling, etc. 

        By configuring the `apr_procattr_t` structure, the behavior and execution environment of the new process can be influenced.

        

8. `apr_status_t rv`:

    - **Type**: `apr_status_t`, typically used to represent the return value of a function.

    - **Purpose**: This variable is used to store the return value of a function call. 

        In the APR library, most function return types are `apr_status_t`, which indicates the result of the function execution, such as success, failure, error codes, etc. 

        Programmers can use the value of `rv` to determine the success of a function call and perform subsequent handling as needed.



9. `apr_proc_t newproc`:

    - **Type**: `apr_proc_t` structure.

    - **Purpose**: This variable represents the newly created process. 

        After calling a function to create a process, the `newproc` variable can be used to access information about the new process, such as the process ID, input/output streams, etc. 

        The `apr_proc_t` structure typically contains basic attributes and status information of the process.



- `apr_procattr_t *attr` is used to set attributes for the new process.
- `apr_status_t rv` is used to store the return value of function calls for error handling.
- `apr_proc_t newproc` represents the newly created process and provides access to its related information.



10. `Some basic marcos`

    The use of macro definitions such as `APR_SUCCESS`, `APR_CHILD_DONE`, `APR_WAIT`, `APR_PROC_EXIT` helps in handling different states and events during process-related operations. 


















