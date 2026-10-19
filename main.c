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

#define get_current_dir getcwd

char* check_mgit_repo(char* mgit_dir_buff, size_t m_size, char* work_dir_buff, size_t w_size);
void make_dir(const char *path);


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
    //list the status info like branch(assume main for now), list of uncommited files
    char work_dir_buff[128];
    char mgit_dir_buff[256];

    if(!check_mgit_repo(mgit_dir_buff, sizeof(mgit_dir_buff), work_dir_buff, sizeof(work_dir_buff)))
    {
        printf("Not a mgit repo\n");
        return;
    }

    printf("On branch main\n");



}

void make_dir(const char *path)
{
    if(mkdir(path, 0777))
    {
        
        if(errno == EEXIST)
        {
            printf("\nThis is path already exists\n");
        }
        else
        {
            printf("\nFailed to create path\n");
        }

    }
}


char* check_mgit_repo(char* mgit_dir_buff, size_t m_size, char* work_dir_buff, size_t w_size)
{

    if(get_current_dir(work_dir_buff, w_size) == NULL)
    {
        perror("Failed to get current working directory");
        return NULL;
    }
    
    snprintf(mgit_dir_buff, m_size, "%s/.mgit", work_dir_buff);

    struct stat info;

    if(stat(mgit_dir_buff, &info) != 0){
        return NULL;
    }

    if(S_ISDIR(info.st_mode)){
        return mgit_dir_buff;
    }
    
    return NULL;
}

void init()
{
    //make a .mgit dir.
    //output, initialized an empty git repo <the absolute path of the repo>
    //get working dir and create a .mgit dir in it.

    char working_dir[128];

    if(get_current_dir(working_dir, sizeof(working_dir)) == NULL)
    {
        perror("Failed to get current working directory");
    }else
    {
        char mgit_dir[200];
        char objects_dir[256];
        char hooks_dir[256];

        snprintf(mgit_dir, sizeof(mgit_dir), "%s/.mgit", working_dir);
        make_dir(mgit_dir);

        snprintf(objects_dir, sizeof(objects_dir), "%s/objects", mgit_dir);
        make_dir(objects_dir);

        snprintf(hooks_dir, sizeof(hooks_dir), "%s/hooks", mgit_dir);
        make_dir(hooks_dir);

        printf("Initialized an empty mgit repository in %s\n", mgit_dir);

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