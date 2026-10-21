#include <stdio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

//LOCAL FIRST
//run git init -> we initialize a repo. create a .mgit folder
//run status -> we check uncommitted files and list them 
//run add -> we stage the files in the working dir
//run commit -> we create a local snapshot of the files in the object store

#define get_current_dir getcwd

char* check_mgit_repo(char* mgit_dir_buff, size_t m_size, char* work_dir_buff, size_t w_size);
void make_dir(const char *path);
void clean_up();

struct Split_Parts {
    char filename[256];
    char hash[256];
};

void commit() 
{
    //check if we are in a mgit repo already!!

}

void add(const char *file_path)
{
    //check if we are in a mgit repo already!!
    char work_dir_buff[128];
    char mgit_dir_buff[256];

    if(!check_mgit_repo(mgit_dir_buff, sizeof(mgit_dir_buff), work_dir_buff, sizeof(work_dir_buff)))
    {
        printf("Not a mgit repo\n");
        return;
    }

  
    //Check if we have the files in the index first
    //This should hash the files and store the hashes, filename and permissions in the index

    FILE *f_stream;
    f_stream = fopen("./.mgit/index", "r");

    if(f_stream == NULL){
        perror("Error opening file");
        return;
    }

    char buffer[256];

    while(fgets(buffer, sizeof(buffer), f_stream) != NULL){
        //Check  need to grab the file name
        struct Split_Parts parts;
        char part[128];
                        
        int i = 0;
        int part_idx = 0;
        
        while(buffer[i] != '\n'){
            if(buffer[i] == '\t'){
                snprintf(parts.filename, sizeof(parts.filename), "%s", part);
                part_idx = 0;
            }else{
                part[part_idx] = buffer[i];
                part_idx++;
                part[part_idx] = '\0';
            }
            
            i++;
        }

        snprintf(parts.hash, sizeof(parts.hash), "%s", part);

        printf("name: %s\n", parts.filename);
        printf("hash: %s\n", parts.hash);
    }

    fclose(f_stream);
    //want to read this line by line
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

void make_file(const char *path, const char *content){

        FILE *fptr;
        fptr = fopen(path, "w");

        if(fptr == NULL){
            printf("Error opening the file\n");
            clean_up();
            return;
        }

        fprintf(fptr, "%s", content);
        fclose(fptr);

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

void clean_up(){


}

void init()
{
    //make a .mgit dir.
    //output, initialized an empty git repo <the absolute path of the repo>
    //get working dir and create a .mgit dir in it.
    //create objects/ and HEAD file in .mgit

    char work_dir[128];
    char mgit_dir[150];

    if(check_mgit_repo(mgit_dir, sizeof(mgit_dir), work_dir, sizeof(work_dir)))
    {
        printf("This is a mgit repo. Try this in a different directory\n");
        return;
    }
    
    char objects_dir[180];
    char refs_dir[180];
    char heads_dir[200];
    char HEAD_path[250];
    char index_path[250];
    char main_path[250];

    snprintf(mgit_dir, sizeof(mgit_dir), "%s/.mgit", work_dir);
    make_dir(mgit_dir);

    snprintf(objects_dir, sizeof(objects_dir), "%s/objects", mgit_dir);
    make_dir(objects_dir);

    snprintf(refs_dir, sizeof(refs_dir), "%s/refs", mgit_dir);
    make_dir(refs_dir);

    snprintf(index_path, sizeof(index_path), "%s/%s", mgit_dir, "index");
    make_file(index_path, "");

    snprintf(HEAD_path, sizeof(HEAD_path), "%s/%s", mgit_dir, "HEAD");
    make_file(HEAD_path, "ref: refs/heads/main");

    snprintf(heads_dir, sizeof(heads_dir), "%s/heads", refs_dir);
    make_dir(heads_dir);

    snprintf(main_path, sizeof(main_path), "%s/%s", heads_dir, "main");
    
    make_file(main_path, "no commit yet");

    printf("Initialized an empty mgit repository in %s\n", mgit_dir);

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

void parse_args(const char *command, const char* sub_command){

    if(strcmp(command, "init") == 0){
        init();
    }else if(strcmp(command, "add") == 0){
        add(sub_command);
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
        parse_args(argv[1], argv[2]);
    }
    
}