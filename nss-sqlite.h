#ifndef NSS_SQLITE_H
#define NSS_SQLITE_H

#define _GNU_SOURCE

#ifdef HAVE_CONFIG_H
#include <config.h>
#else
#error You must use autotools to build this!
#endif

#include <nss.h>
#include <syslog.h>
#include <stdio.h>
#include <unistd.h>

/* Some syslog shortcuts */
#ifdef DEBUG
#define NSS_DEBUG(msg, ...) syslog(LOG_DEBUG, ("[%s] [%s] [%d] -> " msg), __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__)
#else
#define NSS_DEBUG(msg, ...)
#endif

#define NSS_ERROR(msg, ...) syslog(LOG_ERR, ("[%s] [%s] [%d] -> " msg), __FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__)

#define FALSE 0
#define TRUE !FALSE

#endif
