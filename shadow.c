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
 * shadow.c : Functions handling passwd entries retrieval.
 */

#include "nss-sqlite.h"
#include "utils.h"
#include "conf.h"

#include <errno.h>
#include <grp.h>
#include <malloc.h>
#include <pwd.h>
#include <shadow.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


/*
 * Get shadow information using username.
 */
enum nss_status _nss_sqlite_getspnam_r(const char* name, struct spwd *spbuf,
                                       char *buf, size_t buflen, int *errnop)
{
    sqlite3 *pDb;
    int name_length;
    int pw_length;
    const unsigned char* pw;
    struct sqlite3_stmt* pSt;
    int res;
    char query[MAXBUF];
    CFG *cfg = NULL;

    NSS_DEBUG("NSS performing (shadow) lookup for username [%s]\n", name);

    /* get config parameters from the .conf file */
    get_config(&cfg);

    /* compose the query */
    sprintf(query, "SELECT %s FROM %s WHERE %s = '%s';",
            cfg->user_table_passwd_column, cfg->user_table,
            cfg->user_table_userid_column, name);

    if(!open_and_prepare(&pDb, &pSt, query, cfg->database))
        return NSS_STATUS_UNAVAIL;

    res = fetch_first(pDb, pSt);
    if(res != NSS_STATUS_SUCCESS)
        return res;

    /* SQLITE_ROW was returned, fetch data */
    pw = sqlite3_column_text(pSt, 0);
    name_length = strlen(name) + 1;
    pw_length = strlen(pw) + 1;
    if(buflen < name_length + pw_length) {
        *errnop = ERANGE;
        return NSS_STATUS_TRYAGAIN;
    }
    strcpy(buf, name);
    spbuf->sp_namp = buf;
    buf += name_length;
    strcpy(buf, pw);
    spbuf->sp_pwdp = buf;
    spbuf->sp_lstchg = -1;
    spbuf->sp_min = -1;
    spbuf->sp_max = -1;
    spbuf->sp_warn = -1;
    spbuf->sp_inact = -1;
    spbuf->sp_expire = -1;
    sqlite3_finalize(pSt);
    sqlite3_close(pDb);

    NSS_DEBUG("NSS (shadow) lookup for username [%s] successful\n", name);
    return NSS_STATUS_SUCCESS;
}

