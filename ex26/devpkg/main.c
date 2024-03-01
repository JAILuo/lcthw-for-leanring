#include <stdio.h>
#include <apr_general.h>
#include <apr_getopt.h>
#include <apr_strings.h>
#include <apr_lib.h>

#include "apr_errno.h"
#include "apr_pools.h"
#include "dbg.h"
#include "db.h"
#include "commands.h"

/**
 * Execute a command line operation based on user input.
 *
 * The main function parses command line arguments and determines the action 
 * to be taken based on the input. 
 * It supports various operations like 
 * installing software, listing software,
 * fetching software, building software, and initializing the database.
 *
 * @param argc: The number of command line arguments.
 * @param argv: An array of command line arguments.
 * @return: 0 if the operation was successful, 1 if an error occurred.
 *
 * @Note
 * The function uses the Apache Portable Runtime (APR) library
 * for handling command line arguments and memory management.
 * It switches between different operation types based on the provided 
 * command line options, then calls corresponding functions to perform the actions.
 *
 */
int main(int argc, const char *argv[])
{
	// Initialize APR memory pool
	apr_pool_t *p = NULL;
	apr_pool_initialize();
	apr_pool_create(&p, NULL);

	apr_getopt_t *opt;
	apr_status_t rv;

	char ch = '\0';
	const char *optarg = NULL;
	const char *config_opts = NULL;
	const char *install_opts = NULL;
	const char *make_opts = NULL;
	const char *url = NULL;
	enum CommandType request = COMMAND_NONE;

	// Initialize APR getopt with command line arguments
	rv = apr_getopt_init(&opt, p, argc, argv);

	while(apr_getopt(opt, "I:Lc:m:i:d;SF:B:", &ch, &optarg) == APR_SUCCESS)
	{
		switch (ch) {
			case 'I':
				request = COMMAND_INSTALL;
				url = optarg;
				break;

			case 'L':
				request = COMMAND_LIST;
				break;

			case 'c':
				config_opts = optarg;
				break;

			case 'm':
				make_opts = optarg;
				break;

			case 'i':
				install_opts = optarg;
				break;

			case 'S':
				request = COMMAND_INIT;
				break;

			case 'F':
				request = COMMAND_FETCH;
				url = optarg;
				break;

			case 'B':
				request = COMMAND_BUILD;
				url = optarg;
				break;

			default: break;
		}
	}

	switch (request) {
		case COMMAND_INSTALL:
			check(url, "You must at least give a URL.");
			Command_install(p, url, config_opts, make_opts, install_opts);
			break;;

		case COMMAND_LIST:
			DB_list();
			break;

		case COMMAND_FETCH:
			check(url != NULL, "You must give a URL.");
			Command_fetch(p, url, 1);
			log_info("Downloaded to %s and in /tmp/", BUILD_DIR);
			break;

		case COMMAND_BUILD:
			check(url, "You must at least give a URL.");
			Command_build(p, url, config_opts, make_opts, install_opts);
			break;

		case COMMAND_INIT:
			rv = DB_init();
			check(rv == 0, "Failed to make database.");
			break;

		default:
			sentinel("Invalid command given.");
	}

	return 0;

error:
	return 1;
}
