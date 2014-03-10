/*
 * Copyright (C) 2007, Sébastien Le Ray
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * passwd.c : Functions handling passwd entries retrieval.
 */

#include "nss-sqlite.h"
#include "utils.h"
#include "conf.h"

#include <errno.h>
#include <grp.h>
#include <malloc.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>


/**
 * Setup everything needed to retrieve passwd entries.
 */
enum nss_status _nss_sqlite_setpwent(void)
{
    NSS_DEBUG("Initializing pw functions\n");
    return NSS_STATUS_SUCCESS;
}


/*
 * Free getpwent resources.
 */
enum nss_status _nss_sqlite_endpwent(void)
{
    NSS_DEBUG("Finishing pw functions\n");
    return NSS_STATUS_SUCCESS;
}


/*
 * Return next passwd entry.
 * Not implemeted yet.
 */
enum nss_status _nss_sqlite_getpwent_r(struct passwd *pwbuf, char *buf,
                                       size_t buflen, int *errnop)
{
    NSS_DEBUG("Getting next pw entry\n");
    return NSS_STATUS_UNAVAIL;
}


/**
 * Get user info by username.
 * Open database connection, fetch the user by name, close the connection.
 */
enum nss_status _nss_sqlite_getpwnam_r(const char* name, struct passwd *pwbuf,
                                       char *buf, size_t buflen, int *errnop)
{
    sqlite3 *pDb;
    struct sqlite3_stmt* pSt;
    int res;
    uid_t uid;
    gid_t gid;
    const char* shell;
    const char* homedir;
    char query[MAXBUF];
    CFG *cfg = NULL;

    NSS_DEBUG("NSS performing (passwd) lookup for for username [%s]\n", name);

    /* get config parameters from the .conf file */
    get_config(&cfg);

    /*
     * compose the query to fetch uid, gid, shell and homedir
     * for the incoming user
     */
    sprintf(query, "SELECT u.%s, urm.%s, u.%s, u.%s FROM %s u " \
            "INNER JOIN %s urm on u.%s == urm.%s AND u.%s = '%s';",
            cfg->user_table_uid_column, cfg->user_group_map_groupid_column,
            cfg->user_table_shell_column, cfg->user_table_homedir_column,
            cfg->user_table, cfg->user_group_map_table,
            cfg->user_table_uid_column, cfg->user_group_map_userid_column,
            cfg->user_table_userid_column, name);

    if(!open_and_prepare(&pDb, &pSt, query, cfg->database))
        return NSS_STATUS_UNAVAIL;

    res = fetch_first(pDb, pSt);
    if(res != NSS_STATUS_SUCCESS)
        return res;

    /* SQLITE_ROW was returned, fetch data */
    uid = sqlite3_column_int(pSt, 0);
    gid = sqlite3_column_int(pSt, 1);
    shell = sqlite3_column_text(pSt, 2);
    homedir = sqlite3_column_text(pSt, 3);

    /* fill the passwd struct */
    res = fill_passwd(pwbuf, buf, buflen, name, "x", uid,
                      gid, "", shell, homedir, errnop);

    sqlite3_finalize(pSt);
    sqlite3_close(pDb);

    NSS_DEBUG("NSS (passwd) lookup for username [%s] successful!\n", name);
    return res;
}

/*
 * Get user by UID.
 */

enum nss_status _nss_sqlite_getpwuid_r(uid_t uid, struct passwd *pwbuf,
               char *buf, size_t buflen, int *errnop) {
    sqlite3 *pDb;
    struct sqlite3_stmt* pSt;
    int res;
    gid_t gid;
    const unsigned char *name;
    const unsigned char *shell;
    const unsigned char *homedir;
    char query[MAXBUF];
    CFG *cfg = NULL;

    NSS_DEBUG("NSS performing (passwd) lookup for user id [%d]\n", uid);

    /* get config parameters from the .conf file */
    get_config(&cfg);

    /*
     * compose the query to fetch userid, name, shell and homedir
     * for the incoming user id
     */
    sprintf(query, "SELECT u.%s, urm.%s, u.%s, u.%s FROM %s u " \
            "INNER JOIN %s urm on u.%s == urm.%s AND u.%s = %d;",
            cfg->user_table_userid_column, cfg->user_group_map_groupid_column,
            cfg->user_table_shell_column, cfg->user_table_homedir_column,
            cfg->user_table, cfg->user_group_map_table,
            cfg->user_table_uid_column, cfg->user_group_map_userid_column,
            cfg->user_table_uid_column, uid);

    if(!open_and_prepare(&pDb, &pSt, query, cfg->database))
        return NSS_STATUS_UNAVAIL;

    res = fetch_first(pDb, pSt);
    if(res != NSS_STATUS_SUCCESS)
        return res;

    name = sqlite3_column_text(pSt, 0);
    gid = sqlite3_column_int(pSt, 1);
    shell = sqlite3_column_text(pSt, 2);
    homedir = sqlite3_column_text(pSt, 3);

    fill_passwd(pwbuf, buf, buflen, name, "*", uid, gid, "",
            shell, homedir, errnop);

    sqlite3_finalize(pSt);
    sqlite3_close(pDb);

    NSS_DEBUG("NSS (passwd) lookup for user id [%d] successful!\n", uid);
    return NSS_STATUS_SUCCESS;
}

