/* 
 * File:   main.c
 * Author: alr16
 *
 * Created on 06 December 2011, 15:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


/*displays the current time in both standard output and to the output file*/
void display_time(time *times){
    char string[100];
    printf("Date: %d/%d/%d\nTime: %d:%d:%d:\n", times->day, times->month, times->year,
            times->hour, times->min, times->sec);
    sprintf(string, "Date: %d/%d/%d\nTime: %d:%d:%d:\n", times->day, times->month, times->year,
            times->hour, times->min, times->sec);
    add_to_file(string);
}





/*Requests filename of ships, monitor time and step time and calls run() with
 this information*/
int main(int argc, char** argv) {
    char file_path[50];
    printf("Please enter the file path:\n");
    scanf("%s", &file_path);
    output *my_output = read_file(file_path);
    
    node *first_node = my_output->first;
    time *current_time = my_output->times;
    
    float monitor_time;
    printf("Please enter the total amount of time in hours that you would like to monitor the shipping lane for:\n");
    scanf("%f", &monitor_time);
    
    int step;
    printf("Please enter the step time in minutes (whole numbers only):\n");
    scanf("%d", &step);
    
    run(first_node, current_time, step, monitor_time);
    return (EXIT_SUCCESS);
}

