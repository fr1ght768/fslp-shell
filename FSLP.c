#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <stdbool.h> 
#include <dirent.h>
#include <windows.h>

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char cwd[1024];
    char *arg;
    char command[50];

    printf("FSLP\n");
    printf("Fr1ght's Shell Like Program\n\n");

    while (true){
        if (_getcwd(cwd, sizeof(cwd)) != NULL){
            printf("%s> ", cwd);
        }
        else{
            perror("getcwd error");
            printf("> ");
        }
        fgets(command, sizeof(command), stdin);
        if (strlen(command) > 0){
            command[strlen(command) - 1] = '\0';
        }

        char *cmd_name = strtok(command, " ");
        arg = strtok(NULL, "");

        if (cmd_name == NULL) continue;


        if (strcmp(cmd_name, "mkdir") == 0){
            if(arg == NULL){
                printf("Error: mkdir requires a folder name\n");
            }
            else if(_mkdir(arg) == 0){
                continue;
            }
            else{
                perror("Error");
            }
        }
        else if(strcmp(cmd_name, "ls") == 0){
            struct dirent *de;

            char *target = (arg == NULL) ? "." : arg;
            DIR *dr = opendir(target);

            if (dr == NULL){
                perror("Error opening directory");
            }
            else{
                while((de = readdir(dr)) != NULL){
                    printf("%s\n", de->d_name);
                }
                closedir(dr);
            }
        }
        
        else if(strcmp(cmd_name,"rmdir") == 0){
            if (arg == NULL){
                printf("Error: rmdir requires a folder\n");
            }
            else if (_rmdir(arg) == 0){
                continue;
            }
            else{
                perror("Error");
            }
        }

        else if(strcmp(cmd_name, "clear") == 0){
                clear_screen();
            }
        
        else if(strcmp(cmd_name, "cd") == 0){
            if (arg == NULL){
                printf("Error: you must write a path\n");
            }
            else if(_chdir(arg) == 0){
                continue;
            }
            else{
                perror("Error\n");
            }
        }

        else if (strcmp(cmd_name, "quit") == 0){
            break;
        }


        else{
            printf("The command %s is not defined!\n", command);
        }
    }

    return 0;
}