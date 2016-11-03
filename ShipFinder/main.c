/* 
 * File:   main.c
 * Author: alr16
 *
 * Created on 19 March 2012, 18:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "main.h"
/*
 * 
 */
int main(int argc, char** argv) {
    char option = 'a';
    while(option != 'q'){
        printf("To find a ship enter 'f', to quit enter 'q'\n");
        scanf("%c", &option);
        while(option == 10){
            scanf("%c", &option);
        }
        
        if(option == 'f'){
            char choice;

            printf("To find a ship using its MMSI number enter 'm'\n");
            printf("To find a ship using its name enter 'n'\n");
            scanf("%c", &choice);
            while(choice == 10){
                scanf("%c", &choice);
            }


            if(choice == 'm'){
                char mmsi[9];
                printf("Please enter the MMSI number of the ship you'd like info on\n");
                scanf("%s", &mmsi);
                read_file(mmsi);
            }
            else if(choice == 'n'){
                node *first_ship = get_ships();
                char name[40];
                printf("Please enter the name of the ship you'd like info on\n");
                scanf("%s", &name);

                
                int j=0;
                int length = get_length(first_ship);
                for(;j<length;j++){
                    check_file(get(first_ship, j)->mmsi, name);
                }
            }
            else{
                printf("I'm sorry, response not recognised\n");
            }
            
        }else if(option == 'q'){
            break;
        }
        else{
            printf("I'm sorry, response not recognised");
        }
    
    }
    
    printf("Program closing");
    return (EXIT_SUCCESS);
}

//Checks if the name contains the char[] input
int check_file(char file_path[9], char possible_name[40]){
    FILE *file_ptr;
    char file[18];
    sprintf(file, "../ships/%s", file_path);
    if(!(file_ptr = fopen(file, "r"))){
        printf("could not open file/file doesn't exist");
        return -1;
    }
    else{
        char mmsi[10];
        char name[40];
        fgets(mmsi, sizeof mmsi, file_ptr);
        fgets(name, sizeof name, file_ptr);
        fgets(name, sizeof name, file_ptr);
        if(strstr(name, possible_name)){
            read_file(file_path);
            return 1;
        }
        else{
            return -1;
        }
    }
}

//gets all ships from the ship folder and stores them in the linked list
node *get_ships(){
    DIR *current_directory_ptr;
    struct dirent *next_entry_ptr;
    if(!(current_directory_ptr = opendir("../ships"))){
        printf("could not open ship directory");
        return;
    }
    else{
        node *first_node;
        node *current_node;
        int count_var = 0;
        while(next_entry_ptr = readdir(current_directory_ptr)){
            if(strcmp(next_entry_ptr->d_name, ".") != 0 && strcmp(next_entry_ptr->d_name, "..") != 0){
                if(count_var == 0){
                    first_node = create(next_entry_ptr->d_name);
                    current_node = first_node;
                }
                else{
                    current_node = insert_after(current_node, next_entry_ptr->d_name);
                }
                count_var++;
            }
        }
        closedir(current_directory_ptr);

        return first_node;
    }    
}

//reads and prints the data from a file
void read_file(char file_path[9]){
    FILE *file_ptr;
    char file[18];
    sprintf(file, "../ships/%s", file_path);
    if(!(file_ptr = fopen(file, "r"))){
        printf("could not open file/file doesn't exist");
        return;
    }
    else{
        printf("INFORMATION FOR SHIP %s:\n\n", file_path);
        char line[60];
        while(fgets(line, sizeof line, file_ptr) != NULL){
            fputs(line, stdout);
        }
        printf("\n\n");
        fclose(file_ptr);
        char to_file[200];
        sprintf(to_file, "%s was read by the Ship Finder program in C\n", file_path);
        add_to_log_file(to_file);
    }
}

//writes a message to the log file
int add_to_log_file(char to_file[200]){
    FILE *file_ptr;
    if(!(file_ptr = fopen("../log/log.txt", "a"))){
        printf("Could not open log file and write %s to it\n", to_file);
        return -1;
    }
    else{
        fprintf(file_ptr, to_file);
        fclose(file_ptr);
        return 1;
    }
}

