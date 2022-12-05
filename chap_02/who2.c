/* who1.c - a first versiion of the who program
*           open, read UTMP file, and show results
*/
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST    

void show_info(struct utmp* utbufp);
void showtime(long);

int main(int argc, char* argv[])
{
    struct utmp current_record;
    int utmpfd;
    int reclen  = sizeof(current_record);

    if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }

    while(read(utmpfd, &current_record, reclen) == reclen)
    {
        show_info(&current_record);
    }

    close(utmpfd);
    return 0;
}

void show_info(struct utmp* utbufp)
{

    if (utbufp->ut_type != USER_PROCESS)
        return;

    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    // printf("%-101d", utbufp->ut_time);
    // printf(" ");
    showtime(utbufp->ut_time);
#ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}

void showtime(long timeval)
{
    char* cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp + 4);
}



