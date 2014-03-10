#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "nss-sqlite.h"
#include "conf.h"


static void set_option(const char *option,
                       const char *value,
                       CFG *cfg)
{
    if (!cfg) {
        NSS_DEBUG("No configuration data to set to!\n");
        return;
    }
    if (!strcmp(option, "database"))
        cfg->database = strdup(value);
    if (!strcmp(option, "user_table"))
        cfg->user_table = strdup(value);
    if (!strcmp(option, "user_table_uid_column"))
        cfg->user_table_uid_column = strdup(value);
    if (!strcmp(option, "user_table_userid_column"))
        cfg->user_table_userid_column = strdup(value);
    if (!strcmp(option, "user_table_passwd_column"))
        cfg->user_table_passwd_column = strdup(value);
    if (!strcmp(option, "user_table_name_column"))
        cfg->user_table_name_column = strdup(value);
    if (!strcmp(option, "user_table_expired_column"))
        cfg->user_table_expired_column = strdup(value);
    if (!strcmp(option, "user_table_newtok_column"))
        cfg->user_table_newtok_column = strdup(value);
    if (!strcmp(option, "user_table_email_column"))
        cfg->user_table_email_column = strdup(value);
    if (!strcmp(option, "user_table_shell_column"))
        cfg->user_table_shell_column = strdup(value);
    if (!strcmp(option, "user_table_homedir_column"))
        cfg->user_table_homedir_column = strdup(value);
    if (!strcmp(option, "group_table"))
        cfg->group_table = strdup(value);
    if (!strcmp(option, "group_table_gid_column"))
        cfg->group_table_gid_column = strdup(value);
    if (!strcmp(option, "group_table_groupid_colum "))
        cfg->group_table_groupid_colum  = strdup(value);
    if (!strcmp(option, "user_group_map_table"))
        cfg->user_group_map_table = strdup(value);
    if (!strcmp(option, "user_group_map_groupid_column"))
        cfg->user_group_map_groupid_column = strdup(value);
    if (!strcmp(option, "user_group_map_userid_column"))
        cfg->user_group_map_userid_column = strdup(value);
    if (!strcmp(option, "pw_type"))
        cfg->pw_type = strdup(value);
    if (!strcmp(option, "debug"))
        cfg->debug = strdup(value);
    return;
}


void free_config(CFG *cfg)
{
    if (cfg->database)
        free(cfg->database);
    if (cfg->user_table)
        free(cfg->user_table);
    if (cfg->user_table_uid_column)
        free(cfg->user_table_uid_column);
    if (cfg->user_table_userid_column)
        free(cfg->user_table_userid_column);
    if (cfg->user_table_passwd_column)
        free(cfg->user_table_passwd_column);
    if (cfg->user_table_name_column)
        free(cfg->user_table_name_column);
    if (cfg->user_table_expired_column)
        free(cfg->user_table_expired_column);
    if (cfg->user_table_newtok_column)
        free(cfg->user_table_newtok_column);
    if (cfg->user_table_email_column)
        free(cfg->user_table_email_column);
    if (cfg->user_table_shell_column)
        free(cfg->user_table_shell_column);
    if (cfg->user_table_homedir_column)
        free(cfg->user_table_homedir_column);
    if (cfg->group_table)
        free(cfg->group_table);
    if (cfg->group_table_gid_column)
        free(cfg->group_table_gid_column);
    if (cfg->group_table_groupid_colum )
        free(cfg->group_table_groupid_colum );
    if (cfg->user_group_map_table)
        free(cfg->user_group_map_table);
    if (cfg->user_group_map_groupid_column)
        free(cfg->user_group_map_groupid_column);
    if (cfg->user_group_map_userid_column)
        free(cfg->user_group_map_userid_column);
    if (cfg->pw_type)
        free(cfg->pw_type);
    if (cfg->debug)
        free(cfg->debug);
    if (cfg)
        free(cfg);
    NSS_DEBUG("Free successful!\n");
    return;
}


void print_config(CFG *cfg)
{
    if (!cfg) {
        NSS_DEBUG("No configuration data to print!\n");
        return;
    }
    if (cfg->database)
        NSS_DEBUG("%30s -> %s\n", "database", cfg->database);
    if (cfg->user_table)
        NSS_DEBUG("%30s -> %s\n", "user_table",cfg->user_table);
    if (cfg->user_table_uid_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_uid_column", cfg->user_table_uid_column);
    if (cfg->user_table_userid_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_userid_column", cfg->user_table_userid_column);
    if (cfg->user_table_passwd_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_userid_column", cfg->user_table_passwd_column);
    if (cfg->user_table_name_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_name_column", cfg->user_table_name_column);
    if (cfg->user_table_expired_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_expired_column", cfg->user_table_expired_column);
    if (cfg->user_table_newtok_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_newtok_column", cfg->user_table_newtok_column);
    if (cfg->user_table_email_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_email_column", cfg->user_table_email_column);
    if (cfg->user_table_shell_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_shell_column", cfg->user_table_shell_column);
    if (cfg->user_table_homedir_column)
        NSS_DEBUG("%30s -> %s\n", "user_table_homedir_column", cfg->user_table_homedir_column);
    if (cfg->group_table)
        NSS_DEBUG("%30s -> %s\n", "group_table", cfg->group_table);
    if (cfg->group_table_gid_column)
        NSS_DEBUG("%30s -> %s\n", "group_table_gid_column", cfg->group_table_gid_column);
    if (cfg->group_table_groupid_colum )
        NSS_DEBUG("%30s -> %s\n", "group_table_groupid_colum", cfg->group_table_groupid_colum );
    if (cfg->user_group_map_table)
        NSS_DEBUG("%30s -> %s\n", "group_table_groupid_colum", cfg->user_group_map_table);
    if (cfg->user_group_map_groupid_column)
        NSS_DEBUG("%30s -> %s\n", "user_group_map_groupid_column", cfg->user_group_map_groupid_column);
    if (cfg->user_group_map_userid_column)
        NSS_DEBUG("%30s -> %s\n", "user_group_map_userid_column", cfg->user_group_map_userid_column);
    if (cfg->pw_type)
        NSS_DEBUG("%30s -> %s\n", "pw_type", cfg->pw_type);
    if (cfg->debug)
        NSS_DEBUG("%30s -> %s\n", "pw_type", cfg->debug);
    return;
}



char * trim(char *str)
{
    char *end;

    /* remove leading whitespaces */
    while(isspace(*str))
        str++;

    /* incoming string is all spaces */
    if(*str == 0)
        return str;

    /* remove leading whitespaces */
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end))
        end--;
    *(end+1) = 0;

    return str;
}


void get_config(CFG **cfg)
{
    CFG *config;
    FILE *file = fopen (FILENAME, "r");
    char line[MAXBUF];
    char *a, *b, *delim = "=";

    if ((config = (CFG *)calloc(sizeof(CFG), 1)) == NULL) {
        NSS_DEBUG("Unable to allocate memory to read conf file [%s]! \n",
                  FILENAME);
        return;
    }

    if (file == NULL) {
        NSS_DEBUG("Unable to open conf file [%s]\n", FILENAME);
        return;
    }

    while(fgets(line, sizeof(line), file) != NULL) {
        a = strtok(line, delim);
        if (!a) {
            NSS_DEBUG("Unable to find the option!\n");
            return;
        }
        a = trim(a);
        b = strtok(NULL, delim);
        if (!b) {
            NSS_DEBUG("Unable to find the value for [option=%s]!\n", a);
            return;
        }
        b = trim(b);
        set_option(a, b, config);
    }
    fclose(file);
    *cfg = config;
    return;
}


