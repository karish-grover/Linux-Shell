#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
int removeFile(char const* argv[], int i, int mode){

         while(argv[i] != NULL){
                    char *wdir=NULL;
                    wdir= getcwd((char*)NULL, 0);
             
             if(wdir ==NULL){//If you get NULL returned
                 perror("Error in fetching directory");
                 printf("Error Code: %d\n",errno);
                 return 0;
             }
                    strcat(wdir, "/");
                    strcat(wdir, argv[i]);
                    if(remove(wdir) == 0){
                        if(mode ==1)
                        printf("%s deleted successfully.\n",argv[i]);
                    }else{
                        printf("File could not be deleted.\n");
                    }
                
                i++;
        }
    return 1;
    }

int main(int argc, char const *argv[])
{

    if(argv[2] != NULL){
        if(strcmp(argv[1], "-v") == 0) {return removeFile(argv, 2, 1);}
        
        else if(strcmp(argv[1], "-f") == 0) {return removeFile(argv,2,0);
            
        }
        else{ return removeFile(argv,1,0);}
    }
    
    else{ return removeFile(argv,1,0);}

    return 0;
}


