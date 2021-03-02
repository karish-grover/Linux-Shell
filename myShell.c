#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void _cd_(char *stream[10]){
    
    int returnVal = 0;
    char* hdir = getenv("HOME");//Getting home directory using environment variable "HOME"
    
    // Case 0: cd or Case 1: cd ~ -->Home dir
    if(stream[1] == NULL || strcmp(stream[1],"~") == 0)
    {
        returnVal = chdir(hdir);
    }
    // Case 1: cd ..
    else if(strcmp(stream[1], "..") == 0)
    {
        returnVal = chdir("..");
    }
    //Casr 4: cd -L ____ (Directory name)
    else if (strcmp(stream[1], "-P") == 0){
        returnVal = chdir(stream[2]);
        if(returnVal == -1){
            printf("%s is an invalid directory. \n", stream[2]);
        }
    }
        else if(strcmp(stream[1], "--help") == 0){
        
        printf("Change the shell working directory.\n\n"
        
        "Change the current directory to DIR.  The default DIR is the value of the HOME shell variable.\n"
        
        "The variable CDPATH defines the search path for the directory containing DIR.  Alternative directory names in CDPATH are separated by a colon (:). A null directory name is the same as the current directory.  If DIR begins with a slash (/), then CDPATH is not used.\n\n"
        
        "Options:\n"
          "\t-P\tuse the physical directory structure without following symbolic links:\n" "\t\tresolve symbolic links in DIR before processing instances of `..'\n"

          "\t--help\topen help for cd\n"
            
        "The default is to follow symbolic links, as if `-P' were specified. `..' is processed by removing the immediately previous pathname component back to a slash or the beginning of DIR.\n"
               );}
    //Casr 5: cd ____ (Directory name)
    else
    {   returnVal = chdir(stream[1]);
        if(returnVal == -1){
            printf("%s is an invalid directory. \n", stream[1]);
        }
    }
}

void pwdHelp(){
    printf("pwd: pwd[L]\n"
    "\tPrint the name of the current working directory.\n\n"
    "\tOPTIONS:\n"
      "\t  --help\t Get help for pwd\n"
      "\t  -L\t\t Print the value of $PWD if it names the current working directory \n\n"
    "\tBy default, `pwd' behaves as if `-L' were specified.\n\n"
    "\tExit Status:\n"
    "\tReturns 0 unless an invalid option is given or the current directory\n"
    "\tcannot be read.\n");
}//No error handling required, Just printf

void exitHelp(){
    puts("exit: exit \n"
    "Exit the shell.\n\n"
    "Exits the shell with a status of N.  If N is omitted, the exit status\n"
    "is that of the last command executed.\n");
}

int pwdCommand(){
       char *wdir;//Pointer to array storing the working directory
       wdir = getcwd((char*)NULL, 0);
       if (wdir == NULL){//If we get a NULL path
           perror ("getcwd Error");
           return EXIT_FAILURE;
       }//Avoding error
       else{
           puts(wdir);
           free(wdir);
       }
    return EXIT_SUCCESS;
}

void _pwd_(char *input){
    if(input != NULL){
        if(strcmp(input, "-P") == 0){//Option -P
            pwdCommand();
        }
        else if(strcmp(input, "--help") == 0){//Option Help
            pwdHelp();
        }
        else{
            printf("INVALID ARGUMENT TO pwd\n");
        }
    }
    else{//Main PWD Command
        pwdCommand();
        }
}

void _history_(char *input[], char history [500][20] ){
    
    if(input[1]==NULL){
        puts("*HISTORY*");
        FILE* f = fopen("history.txt", "r");
        if(f != NULL){
            char line[500];
            int count = 1;
            while(fgets(line, sizeof(line), f) != NULL){
                printf("\t%d  ", count);
                printf("%s",line);
                count++;
            }
            fclose(f);
        }
    }
    
    else if(strcmp(input[1], "-c")==0){
        fclose(fopen("history.txt", "w"));//Clearing the history content
    }
    
  else if(strcmp(input[1], "-s")==0){

        FILE *f = fopen("history.txt", "a");
        int i=2;
        while(input[i]!=NULL){
            fprintf(f, "%s ", strdup(input[i]));
            i++;
        }
        fprintf(f, "%s", strdup("\n"));
        fclose(f);
    }
}

void echoCommand(char* input[], int i){
        while(input[i] != NULL){
            char *curr = input[i];
            
            for(int k=0; k < strlen(curr); k++){
                if(curr[k]>0 && curr[k] != '\\' && curr[k]!='\''&&curr[k]!= '"'){
                    printf("%c", curr[k]);
                }
            }
            printf(" ");
            i++;
        }
}

void echoE(char* input[]){
    int i=2;
    while(input[i] != NULL){
        char *curr = input[i];
        for(int j=0; j < strlen(curr); j++){
            if(curr[j] == '\\'){
                switch (curr[j+1]) {
                    case 'a':
                        printf("\a");break;
                    case 'b':
                        printf("\b");break;
                    case 'f':
                        printf("\f");break;
                    case 'n':
                        printf("\n");break;
                    case 't':
                        printf("\t");break;
                    case 'v':
                        printf("\v");break;
                    case 'r':
                        printf("\r");break;
                }j++;
            }
            else{
                if(curr[j] != '\''&& curr[j] != '"' ){
                    printf("%c", curr[j]);
                }
            }
        }
        printf(" ");
        i++;
    }
    printf("\n");
}

void _echo_(char *arr[]){
    if(arr[1] == NULL){// Case: echo -- print new line
        printf("\n");
    }
    else{
        if(strcmp(arr[1], "-e") == 0){
            echoE(arr);
        }
        else if(strcmp(arr[1], "-n") == 0){
            echoCommand(arr,2);
        }
        else{
            echoCommand(arr,1);
            printf("\n");
        }
    }
}

int external(char *stream[10]){
    int PID;
    PID = fork();
    
    if(PID < 0)
    {
        perror("ERROR IN FORKING: ");
    }
    else if(PID == 0)
    {
        //child process
        if(strcmp(stream[0], "date") == 0 && stream[1] == NULL){
            execlp("date", "date", NULL);
            return 0;
        }
        
        else if(strcmp(stream[0], "date") == 0 && stream[1] != NULL){
            execl("date", "date", stream[1],stream[2], NULL);
            return 0;
        }
        
        else if(strcmp(stream[0], "mkdir") == 0 && stream[1] == NULL){
            printf( "%s\n", "Add a directory name!");
            return 0;
        }
        
        else if(strcmp(stream[0], "mkdir") == 0 && stream[1] != NULL)
        {
            execv("mkdir", stream);
            return 0;
        }
        
        else if(strcmp(stream[0], "ls") == 0 && stream[1] != NULL){
            execl("ls", "ls", stream[1], NULL);
            return 0;
        }
        
        else if(strcmp(stream[0], "ls") == 0){
            execl("ls", "ls", NULL);
            return 0;
        }
        
        else if(strcmp(stream[0], "rm") == 0 && stream[1] == NULL){
            printf("%s\n", "Add an argument to remove!" );
            return 0;
        }
        
        else if(strcmp(stream[0], "rm") == 0 && stream[1] != NULL){
            execv("rm", stream);
            return 0;
        }
        
        else if(strcmp(stream[0], "cat") == 0 && stream[1] == NULL){
            printf("%s\n", "Add a file name to open." );
            return 0;
        }
        
        else if(strcmp(stream[0], "cat") == 0 && stream[1] != NULL){
            execv("cat", stream);
            return 0;
        }
        exit(0);
    }
    
    else
    {
        wait(NULL);//Wait
    }
    return 0;
}

void start(){
    
    printf("\n*********   WELCOME TO myShell  ********** \n\n");
    
    char history[500][20]={{0}};//Store history-500 last commands are stored
    int count=0;//Count of commands in history
    
    while(1)//Run untill exitted
    {
        char input[30]={0};//User input
        printf(">>> ");
        
        
        scanf ("%[^\n]%*c", input);//"%[^\n]%*c"
        
        int p = 0;
        int found=0;
        int c=0;
        while(input[p] != '\0')//Getting between special character
        {
            if(input[p] == '*' && c%2==0){ found =1;
                c++;
                }
            else if(input[p]=='*' && c%2!=0){
                found=0;
                c++;
            }
            else if(input[p]==' '&& found==1){
                input[p]='_';
            }
            p++;
        }
        

        strcpy(history[count],input);  //Adding to history
        strcat(history[count],"\n"); //Inserting new line character to help in printing the history
        count++;
        
        FILE *f = fopen("history.txt", "a");
        if(f!=NULL){
            fprintf(f, "%s\n", strdup(input));
            fclose(f);
        }
    
        char *stream[10];
        int i=0;
        
        stream[i] = strtok(input, " *");
        while(stream[i] != NULL){
            stream[++i] = strtok(NULL, " *");}
        

        if((int)input[0]==76){ //Blank character or just enter then exit
            break;
        }

        //Internal Commands - exit, cd, pwd, history, echo
        else if(strcmp(stream[0], "exit") == 0){
            if(stream[1]!=NULL && strcmp(stream[1], "--help") == 0) exitHelp();
            else break;
        }
        
        else if(strcmp(stream[0], "cd") == 0){
            _cd_(stream);
        }
        
        else if(strcmp(stream[0], "pwd") == 0){
            _pwd_(stream[1]);
        }
        
        else if(strcmp(stream[0], "history") == 0){
            _history_(stream,history);
        }
        
        else if(strcmp(stream[0], "echo") == 0){
            _echo_(stream);
        }
        
        else if (strcmp(stream[0], "cat")==0 || strcmp(stream[0], "mkdir")==0 ||strcmp(stream[0], "date")==0||strcmp(stream[0], "ls")==0||strcmp(stream[0], "rm")==0){
            external(stream); //External - cat, ls, date, mkdir, rm
    }
        else{//If there is any command other than these 10 commands
                printf("%s\n", "*INVALID COMMAND*");
        }
    }
}

int main(){
    start();//Start the program
    return 0;
}



