#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
int createDirectory(char const *argv[], int i, int mode){
    while(argv[i] != NULL){
        struct stat cd = {0};
        char *wdir;
        wdir= getcwd((char*)NULL, 0);
        
        if(wdir ==NULL){//If you get NULL returned
            perror("Error in fetching directory");
            printf("Error Code: %d\n",errno);
            return 0;
        }
        
        strcat(wdir, "/");
        strcat(wdir, argv[i]);
        if(stat(wdir, &cd) == -1){
            mkdir(wdir, 020);//Giving write permissions for the created directory
            if(mode==0){
                printf("mkdir: Directory created- %s\n",argv[i]);
            }
        }
        else
        {
            printf("%s\n","mkdir: Directory Exists");
        }
        i++;
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    if(argv[2] != NULL){
        if(strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "-verbose") == 0){
            createDirectory(argv,2,0);
        }
        else{
            createDirectory(argv,1,1);}
    }
    
    else{
    if(strcmp(argv[1], "--help") == 0){
            printf("Usage: mkdir [OPTION]... DIRECTORY...\n"
            "Create the DIRECTORY(ies), if they do not already exist.\n\n"

            "Mandatory arguments to long options are mandatory for short options too.\n"
            "\nOPTIONS\n"
              "\t-v, --verbose     print a message for each created directory\n"
            
              "\t--help     display this help and exit"

            "\n\nGNU coreutils online help: <http://www.gnu.org/software/coreutils/>\n"
            "Full documentation at: <http://www.gnu.org/software/coreutils/mkdir>\n"
            "or available locally via: info '(coreutils) mkdir invocation \n");
            }
        else{
        createDirectory(argv,1,1);
    }
    }
    return 0;
}





