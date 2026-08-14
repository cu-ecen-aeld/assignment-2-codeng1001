#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // LOG_PID is useful if there are multiple instance, LOG_CONS is useful if SYSLOG is fails 
    // so its not silently dropped, I thould be directed to console.
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: %d (expected 2)", argc - 1);
        fprintf(stderr, "Usage: %s writefile writestr\n", argv[0]);
        closelog();
        exit(1);
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    FILE *fp = fopen(writefile, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Could not open %s for writing: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: could not create file %s: %s\n", writefile, strerror(errno));
        closelog();
        exit(1);
    }

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    if (fprintf(fp, "%s\n", writestr) < 0) {
        syslog(LOG_ERR, "Failed to write to %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: failed to write to %s\n", writefile);
        fclose(fp);
        closelog();
        exit(1);
    }

    if (fclose(fp) != 0) {
        syslog(LOG_ERR, "Failed to close %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: failed to close %s\n", writefile);
        closelog();
        exit(1);
    }

    closelog();
    return 0;
}
