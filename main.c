#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//LOCAL FIRST
//run git init -> we initialize a repo. create a .mgit folder
//run status -> we check uncommitted files and list them 
//run add -> we stage the files in the working dir
//run commit -> we create a local snapshot of the files in the object store

#define MAX_PATH_SIZE 1024
#define get_current_dir getcwd


void commit() 
{
    //check if we are in a mgit repo already!!

}

void add()
{
    //check if we are in a mgit repo already!!
}
void status()
{
    //check if we are in a mgit repo already!!

}

void init()
{
    //make a .mgit dir.
    //output, initialized an empty git repo <the absolute path of the repo>
    //get working dir and create a .mgit dir in it.
    printf("we are initing vro\n");

    char working_dir[MAX_PATH_SIZE];

    if(get_current_dir(working_dir, sizeof(working_dir)) == NULL)
    {
        perror("Failed to get current working directory");
    }
    
    if(mkdir(".mgit", 0777) == 0)
    {
        printf("Initialized an empty mgit repository in ");
        printf("%s/.mgit\n", working_dir);
    }
    else
    {
        
        if(errno == EEXIST)
        {
            printf("\nThis is already an mgit repository\n");
        }
        else
        {
            printf("\nFailed to initialize the repository\n");
        }

    }
        
}

/*
Calling this func ex
    struct stat info ;

    get_file_info("./index.txt", &info);
*/

int get_file_info(const char *path, struct stat *info)
{

    if(stat(path, info)){
        perror("stat() error");
        return 1;
    }

    return 0;
}

void default_message(){

    printf("=================================\n");
    printf("USAGE:\n");
    printf("=================================\n");
    

}

void parse_args(const char *command){

    if(strcmp(command, "init") == 0){
        init();
    }else if(strcmp(command, "add") == 0){
        add();
    }else if(strcmp(command, "commit") == 0){
        commit();
    }else if(strcmp(command, "status") == 0){
        status();
    }else {
        default_message();
    }
    
}

int main(int argc, char *argv[]){

   
    if(argc > 1){
        parse_args(argv[1]);
    }
    
}