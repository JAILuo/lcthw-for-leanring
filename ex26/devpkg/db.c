/**
 * Provide access to POSIX operating system APIs, such as access function.
 */
#include <unistd.h>

/**
 * The header file for error code that are define in the Apache Portable Runtime library.
 */
#include <apr_errno.h>

/**
 * The header file for I/O operation are available in the Apache Portable Runtime library.
 */
#include <apr_file_io.h>

#include "db.h"
#include "bstrlib.h"
#include "dbg.h"

/**
 * Open the database file with the specified path and mode.
 */
static FILE *DB_open(const char *path, const char *mode)
{
	return fopen(path, mode);
}

/**
 * Close the database file.
 */
static void DB_close(FILE *db)
{
	fclose(db);
}

/**
 * Load data from the database file and return it as a bstring.
 */
static bstring DB_load()
{
	FILE *db = NULL;
	bstring data = NULL;

	db = DB_open(DB_FILE, "r");
	check(db, "Failed to open database: %s", DB_FILE);

	data = bread((bNread)fread, db);
	check(data, "Failed to read from database file: %s", DB_FILE);

	DB_close(db);
	return data;

error:
	if (db)
	{
		DB_close(db);
	}
	if (data)
	{
		bdestroy(data);
	}
	return NULL;
}

/**
 * Update the database file by appending the specified URL.
 */
int DB_update(const char *url)
{
	if (DB_find(url))
	{
		log_info("Already recorded as installed: %s", url);
	}

	FILE *db = DB_open(DB_FILE, "a+");
	check(db, "Failed to open database file: %s", DB_FILE);

	bstring line = bfromcstr(url);
	bconchar(line, '\n');
	int rc = fwrite(line->data, blength(line), 1, db);
	check(rc == 1, "Failed to append to the database.");

	return 0;

error:
	if (db)
	{
		DB_close(db);
	}
	return -1;
}

/**
 * Find the specified URL in the database file.
 * Returns 1 if found, 0 otherwise.
 */
int DB_find(const char *url)
{
	bstring data = NULL;
	bstring line = bfromcstr(url);
	int res = -1;

	data = DB_load();
	check(data, "Failed to load: %s", DB_FILE);

	if (binstr(data, 0, line) == BSTR_ERR)
	{
		res = 0;
	} else 
	{
		res = 1;
	}

error: // fallthrough
	if (data)
	{
		bdestroy(data);
	}
	if (line)
	{
		bdestroy(line);
	}
	return res;
}

/**
 * Initialize the database by creating the directory 
 * and file if they do not exist.
 */
int DB_init()
{
	apr_pool_t *p = NULL;			 // Declare an APR memory pool pointer
	apr_pool_initialize();			 // Initialize the APR memory pool system
	apr_pool_create(&p, NULL);


	// Check if the directory exists and has write and execute permission
	if (access(DB_DIR, W_OK | X_OK) == -1)
	{
		// Create the directory recursively using APR
		apr_status_t rc = apr_dir_make_recursive(DB_DIR,
				APR_UREAD | APR_UWRITE | APR_UEXECUTE |
				APR_GREAD | APR_GWRITE | APR_GEXECUTE, p);
		check(rc == APR_SUCCESS, "Failed to make database directory: %s", DB_DIR);
	}

	// Check if the file exists and has write permissions
	if (access(DB_FILE, W_OK) == -1) 
	{
		FILE *db = DB_open(DB_FILE, "W");				
		check(db, "Cannot open database: %s", DB_FILE);
		DB_close(db);									
	}
	apr_pool_destroy(p);
	return 0;			 // Success

error:
	apr_pool_destroy(p);
	return -1;			 // Error
}

/**
 * List the contents of the database file.
 */
int DB_list()
{
	bstring data = DB_load();
	check(data, "Failed to read load: %s", DB_FILE);

	printf("%s", bdata(data));
	bdestroy(data);
	return 0;

error:
	return -1;
}


