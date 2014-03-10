#ifndef NSS_SQLITE_CONFIG_H
#define NSS_SQLITE_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "/home/vagrant/devel/libnss-sqlite/nss_sqlite.conf"
#define MAXBUF 1024

typedef struct config {
    char *database;
    char *user_table;
    char *user_table_uid_column;
    char *user_table_userid_column;
    char *user_table_passwd_column;
    char *user_table_name_column;
    char *user_table_expired_column;
    char *user_table_newtok_column;
    char *user_table_email_column;
    char *user_table_shell_column;
    char *user_table_homedir_column;
    char *group_table;
    char *group_table_gid_column;
    char *group_table_groupid_colum ;
    char *user_group_map_table;
    char *user_group_map_groupid_column;
    char *user_group_map_userid_column;
    char *pw_type;
    char *debug;
} CFG;


void free_config(CFG *);
void print_config(CFG *);
void get_config(CFG **);

#endif
