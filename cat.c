#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int catFile(const char *argv[],int i, int mode){
    int count=1;//Line count for mode 1
           while(argv[i] != NULL){
               struct stat cd = {0};
               char *wdir;
               wdir =getcwd((char*)NULL, 0);
               
               if(wdir ==NULL){//If you get NULL returned
                   perror("Error in fetching directory");
                   printf("Error Code: %d\n",errno);
                   return 0;}
            
               
               strcat(wdir, "/");
               strcat(wdir, argv[i]);
               if(stat(wdir, &cd) == -1){//If file not found
                   printf("%s\n", "No such file exists!");
               }
               FILE* f = fopen(wdir, "r");//Open to read the file
               if(f != NULL){
                   char line[1000];
                   while(fgets(line, sizeof(line), f) != NULL){
                       if(mode ==2){
                        long len = strlen(line);
                        line[len-1] = '$';
                        fputs(line,stdout);
                        printf("\n");
                       }
                       else if(mode ==1){
                        printf("\t%d ", count);
                        fputs(line,stdout);
                        count++;
                       }
                       else{
                       fputs(line,stdout);
                       }
                   }
                   fclose(f);
               }
               else
               {
                   perror("File not found");
                   printf("%s\n", "Error in opening file.");
                   return 0;
               }
               i++;
           }
    return 1;
}

int main(int argc, char const *argv[])
{
    if(strcmp(argv[1], "-n") == 0){ return catFile(argv,2,1); }
   
    else if(strcmp(argv[1], "-E") == 0){ return catFile(argv,2,2); }
    
    else if(argv[1]==NULL){
        printf("Add a file name!");
    }
    
    else { return catFile(argv,1,3);}
    
    return 0;
}


