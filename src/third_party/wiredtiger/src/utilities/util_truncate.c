/*-
 * Copyright (c) 2014-2016 MongoDB, Inc.
 * Copyright (c) 2008-2014 WiredTiger, Inc.
 *	All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 */

#include "util.h"

static int usage(void);

int
util_truncate(WT_SESSION *session, int argc, char *argv[])
{
	WT_DECL_RET;
	int ch;
	char *name;

	while ((ch = __wt_getopt(progname, argc, argv, "")) != EOF)
		switch (ch) {
		case '?':
		default:
			return (usage());
		}

	argc -= __wt_optind;
	argv += __wt_optind;

	/* The remaining argument is the uri. */
	if (argc != 1)
		return (usage());
	if ((name = util_name(session, *argv, "table")) == NULL)
		return (1);

	if ((ret = session->truncate(session, name, NULL, NULL, NULL)) != 0)
		return (util_err(session, ret, "%s: session.truncate", name));

	free(name);
	return (ret);
}

static int
usage(void)
{
	(void)fprintf(stderr,
	    "usage: %s %s "
	    "truncate uri\n",
	    progname, usage_prefix);
	return (1);
}
