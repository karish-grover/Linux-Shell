#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char const *argv[]){

    struct dirent **dir;
    int k= scandir(".", &dir, 0, alphasort);
    
    if(k==-1){
        printf("Error code: %d\n",errno);
        perror("Error occured");
        exit(EXIT_FAILURE);
    }
    
    if(argv[1] != NULL){
        if(strcmp(argv[1], "-i") == 0){
            for(int i=0; i < k; i++){
                //Change this to %lu for linux
                printf("%llu %s\n",dir[i]->d_ino, dir[i]->d_name);
                free(dir[i]);
            }
        }
        
        else if (strcmp(argv[1], "-X") == 0){
        for(int i=0; i < k; i++){
            printf("%s\n", dir[i]->d_name);
            free(dir[i]);
        }
    }
        else{
            printf("INVALID ARGUMENT FOR ls");
        }
    }

    else{
        for(int i=0; i < k; i++){
            printf("%s\n", dir[i]->d_name);
            free(dir[i]);
        }
    }
    free(dir);
    return(0);
}


