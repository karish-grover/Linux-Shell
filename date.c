#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])//Command line arguments to be passed
{
    
    char *days[7][1]={"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    char *month[12][1]= {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct",
    "Nov","Dec"};

    if(argv[0] != NULL && argv[1]!=NULL){
        if(strcmp(argv[1], "-u") == 0 && argv[2]==NULL){
            time_t rt;//Current Time
            struct tm *info;
            time(&rt);
            info=gmtime(&rt);
            int d= info->tm_wday;
            int m= info->tm_mon;
            printf("%s %s %d %d:%d:%d UTC %d\n",
                   *days[d],
                   *month[m],
                   info->tm_mday,info->tm_hour,info->tm_min,info->tm_sec,(info->tm_year)+1900);
        }
        else if(strcmp(argv[1], "--help") == 0 && argv[2]==NULL){
            printf("NAME\n"
            "\tdate -- display or set date and time\n"
             "DESCRIPTION\n"
            "\tWhen invoked without arguments, the date utility displays the current date and time.  Otherwise, depending on the options specified, date will set the date and time or print it in a user-defined way.\n\n"
                   "The options are as follows:\n"

                   "\t-u\tDisplays the time in GMT(Greenwich Mean Time)/UTC(Coordinated Universal Time )time zone.\n"
                   "\t--help\tLays out help for date.\n\n");
        }

        else{
            printf("%s\n", "*INVALID ARGUMENTS TO date*");
        }
    }

    else{
            time_t t0;
            time(&t0);
            printf("%s", ctime(&t0));
    }
    return 0;}

