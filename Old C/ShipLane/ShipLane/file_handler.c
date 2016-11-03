#include <stdio.h>
#include <stdlib.h>

#include "main.h"


/*reads the specified file and loads in the data. It creates a time struct,
 and calls create() from linked_list to create a new node at the head of the list.
 It then iterates through the rest of the file inserting new nodes for each boat 
 in the file*/
output *read_file(char file_path[40]){
    FILE *file_ptr;
    time *this_time;
    if(!(this_time = malloc(sizeof(time)))){
        printf("Could not create new time structure");
        return NULL;
    }
    char name[20];
    float lati; float longi;
    float dir; float speed;
    
    if(!(file_ptr = fopen(file_path, "r"))){
        printf("could not open file");
        return NULL;
    }
    else{
        int hour;
        int min;
        int sec;
        fscanf(file_ptr, "%d %d %d %d %d %d", &this_time->day, &this_time->month, &this_time->year,
                &this_time->hour, &this_time->min, &this_time->sec);
                
           
        node *first;
        node *current;
        
        first = create("",0,0,0,0);
        current = first;
        
        while(fscanf(file_ptr, "%s %f %f %f %f", &name, &lati, &longi, &dir, &speed) != EOF){
            current = insert_after(current, name, lati, longi, dir, speed);
        }
        
        output *this_output;
        if(!(this_output = malloc(sizeof(output)))){
            printf("could not create output structure in read_file()");
            return NULL;
        }
        else{
            this_output->first = first;
            this_output->times = this_time;
            fclose(file_ptr);
            return this_output;
        }
    }
}

/*Appends the output file by adding text to the end of it*/
int add_to_file(char to_file[200]){
    FILE *file_ptr;
    if(!(file_ptr = fopen("out.txt", "a"))){
        printf("Could not open file for log writing where to_file = %s\n\n", to_file);
        return NULL;
    }
    else{
        fprintf(file_ptr, to_file);
        fclose(file_ptr);
    }  
}

/*writes to the output file initially*/
int write_to_file(char to_file[200]){
    FILE *file_ptr;
    if(!(file_ptr = fopen("out.txt", "w"))){
        printf("Could not open file for log writing where to_file = %s\n\n", to_file);
        return NULL;
    }
    else{
        fprintf(file_ptr, to_file);
        fclose(file_ptr);
    }  
}



