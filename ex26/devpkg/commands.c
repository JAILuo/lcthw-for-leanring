#include <apr_uri.h>
#include <apr_fnmatch.h>
#include <stdio.h>
#include <unistd.h>
#include <apr_errno.h>
#include <apr_file_info.h>

#include "commands.h"
#include "shell.h"
#include "dbg.h"
#include "bstrlib.h"
#include "db.h"

/**
 * @brief Processes dependencies for a given path.
 * 
 * @param p Pointer to the memory pool.
 * @param path The path to the dependency file.
 * @return Returns 0 on success, -1 on error.
 */
int Command_depends(apr_pool_t *p, const char *path)
{
	FILE *in = NULL;
	bstring line = NULL;

	in = fopen(path, path);
	check(in != NULL, "Failed to open downloaded depends: %s", path);
	
	for(line = bgets((bNgetc)fgetc, in, '\n');
		line != NULL;
		line = bgets((bNgetc)fgetc, in, '\n'))
	{
			btrimws(line);
			log_info("Processing depends: %s.", bdata(line));
			int rc = Command_install(p, bdata(line), NULL, NULL, NULL);
			check(rc == 0, "Failed to install: %s", bdata(line));
			bdestroy(line);
		}

	fclose(in);
	return 0;

error:
	if(line)
	{
		bdestroy(line);
	}
	if(in)
	{
		fclose(in);
	}
	return -1;

}

/**
 * @brief Fetches source code or dependencies from a URL.
 *
 * @param p Pointer to the memory pool.
 * @param url The URL from which to fetch the source code or dependencies.
 * @param fetch_only Flag indicating whether only fetching is required.
 * @return 1 if an install needs to run, 0 if no install needed,
 *        -1 on error.
 */
int Command_fetch(apr_pool_t *p, const char *url, int fetch_only)
{
	apr_uri_t info = {.port = 0};
	int rc = 0;
	const char *depends_file = NULL;
	apr_status_t rv = apr_uri_parse(p, url, &info);

	check(rv == APR_SUCCESS, "Failed to parse URL: %s", url);

	if(apr_fnmatch(GIT_PAT, info.path, 0) == APR_SUCCESS) 
	{
		rc = Shell_exec(GIT_SH, "URL", url, NULL);
		check(rc == 0, "git failed.");

	} else if(apr_fnmatch(DEPEND_PAT, info.path, 0) == APR_SUCCESS)
	{
		check(!fetch_only, "No point in fetching a DEPENDS file.");
		
		if(info.scheme)
		{
			depends_file = DEPENDS_PATH;
			rc = Shell_exec(CURL_SH, "URL", url, "TARGET", depends_file, NULL);
			check(rc == 0, "curl failed.");
		}else
		{
			depends_file = info.path;
		}

		// recurisvely process the devpkg list
		log_info("Building according to DEPENDS: %s", url);
		rv = Command_depends(p, depends_file);
		check(rv == 0, "Failed to process the DEPENDS: %s", url);

		// this indicates nothing needs to be done.
		return 0;

	} else if(apr_fnmatch(TAR_GZ_PAT, info.path, 0) == APR_SUCCESS)
	{
		if(info.scheme) 
		{
			rc = Shell_exec(CURL_SH,
					"URL", url,
					"TARGET", TAR_GZ_SRC, NULL);
			check(rc == 0, "Failed to curl source: %s", url);
		}

		rv = apr_dir_make(BUILD_DIR,
				APR_UREAD | APR_UWRITE | APR_UEXECUTE, p);
		check(rv = APR_SUCCESS,	"failed to make directory %s.", BUILD_DIR);
		rc = Shell_exec(TAR_SH, "FILE", TAR_BZ2_SRC, NULL);
		check(rc == 0, "Failed to untar: %s", TAR_BZ2_SRC);

	} else 
	{
		sentinel("Don't know how to handle %s", url);
	}

	// indicates that an install needs to actually run
	return 1;

error:
	return -1;
}

/**
 * @brief Configures, builds, and installs a package.
 *
 * @param p Pointer to the memory pool.
 * @param url The URL of the package to build and install.
 * @param configure_opts Options for the configure script.
 * @param make_opts Options for the make command.
 * @param install_opts Options for the install command.
 * @return Returns 0 on success, -1 on error.
 */
int Command_build(apr_pool_t *p, const char *url, const char *configure_opts,
		const char *make_opts, const char *install_opts)
{
	int rc = 0;

	check(access(BUILD_DIR, X_OK | R_OK | W_OK) == 0, 
			"Build directory doesn't exist: %s", BUILD_DIR);

	// actually do an install
	if(access(CONFIG_SCRIPT, X_OK) == 0)
	{
		log_info("Has a configure script, running it.");
		rc = Shell_exec(CONFIGURE_SH, "OPTS", configure_opts,NULL);
		check(rc == 0, "Failed to configure.");
	}

	rc = Shell_exec(MAKE_SH, "OPTS", make_opts, NULL);
	check(rc == 0, "Failed to Build.");

	rc = Shell_exec(INSTALL_SH,
			"TARGET",install_opts ? install_opts : "install",
			NULL);
	check(rc == 0, "Failed to install");

	rc = Shell_exec(CLEANUP_SH, NULL);
	check(rc == 0, "Failed to cleanup after build,");

	rc = DB_update(url);
	check(rc == 0, "Failed to add this package to the database.");

	return 0;

error:
	return -1;
}


/**
 * @brief Installs a package, handling dependencies and building process.
 * 
 * @param p Pointer to the memory pool.
 * @param url The URL of the package to install.
 * @param configure_opts Options for the configure script.
 * @param make_opts Options for the make command.
 * @param install_opts Options for the install command.
 * @return Returns 0 on success, -1 on error.
 */
int Command_install(apr_pool_t *p, const char *url, const char *configure_opts,
		const char *make_opts, const char *install_opts)
{
	int rc = 0;
	check(Shell_exec(CLEANUP_SH, NULL) == 0, 
			"Failed to cleanup before Building.");

	rc = DB_find(url);
	check(rc != -1, "Error checking the install database.");

	if(rc == 1)
	{
		log_info("Package %s already installed.", url);
		return 0;
	}

	rc = Command_fetch(p, url, 0);

	if(rc == 1)
	{
		rc = Command_build(p, url, configure_opts, make_opts, install_opts);
		check(rc == 0, "Failed to build : %s", url);
	} else if(rc == 0)
	{
		// no install needed
		log_info("Depends successfully installed: %s", url);
	} else 
	{
		// had an error
		sentinel("Install failed: %s", url);
	}

	Shell_exec(CLEANUP_SH, NULL);
	return 0;

error:
	Shell_exec(CLEANUP_SH, NULL);
	return -1;
}

