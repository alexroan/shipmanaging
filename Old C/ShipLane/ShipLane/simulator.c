#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "main.h"


/*steps time and the boats forward according to the step time in minutes*/
void simulate_(node *cur_node, time *the_time, int se){
    while(cur_node != NULL){
        step_forward(cur_node, se);
        cur_node = cur_node->next;    
    }
    step_time_forward(the_time, se);
}

/*iterates through the linked list when stepping forward in time editing the 
 positions of the ships and checking their distances each time*/
void run(node *first_node, time *current_time, int step, float monitor_time){
    write_to_file("BEGINNING OF SIMULATION\n------------------------------------\n");
    printf("\n");
    display_time(current_time);
    display_all_to_file(first_node);
    //add_to_file("\n");
    display_all(first_node);
    check_distances(first_node);
    add_to_file("\n");
    printf("\n");
    
    node *curr_node;
    int s = step;
    
    
    while(s <= (monitor_time * 60)){
        curr_node = first_node->next;
        
        simulate_(curr_node, current_time, step);
        display_time(current_time);
        display_all(first_node);
        
        check_distances(first_node);
        printf("\n");
        add_to_file("\n------------------------------------\n\n");
        s = s + step;
    }
    printf("FINAL POSITIONS\n------------------------------------\n");
    display_all(first_node);
    add_to_file("FINAL POSITIONS\n------------------------------------\n");
    display_all_to_file(first_node);
    printf("Finished simulation!\n");
    add_to_file("Finished simulation!\n");
}

/*checks the distance between the nodes*/
void check_distances(node *first_in_list){
    node *cur_node = first_in_list->next;
    node *compare_node;
    location loc1;
    location loc2;
    double distance_between;   
    char string[100];
    while(cur_node != NULL){
        compare_node = cur_node;
        loc1.lat = cur_node->latitude;
        loc1.lng = cur_node->longitude;
        while(compare_node != NULL){
            if(loc1.lat <= 52.833 || loc1.lng <= -3.833 || loc1.lat >= 51.667 || loc1.lng >= -6.667){
                if(cur_node != compare_node){
                    loc2.lat = compare_node->latitude;
                    loc2.lng = compare_node->longitude;
                    if(loc2.lat <= 52.833 || loc2.lng <= -3.833 || loc2.lat >= 51.667 || loc2.lng >= -6.667){
                        distance_between = great_circle(loc1, loc2);
                        
                        if (distance_between < .25){
                            printf("CRASH: %s and %s have collided and sunk\n", cur_node->name, compare_node->name);
                            sprintf(string, "CRASH: %s and %s have collided and sunk\n", cur_node->name, compare_node->name);
                            add_to_file(string);
                            remove_node(first_in_list, cur_node);
                            remove_node(first_in_list, compare_node);
                        }
                        else if (distance_between < 2){
                            printf("WARNING: %s and %s are in close proximity (%.3fNautical Miles )\n", cur_node->name, compare_node->name,
                                    distance_between);
                            sprintf(string, "WARNING: %s and %s are in close proximity (%.3fNautical Miles )\n", cur_node->name, compare_node->name,
                                    distance_between);
                            add_to_file(string);
                        }
                        
                    }
                }
            }
            compare_node = compare_node->next;
        }
        cur_node = cur_node->next;
    }
}

/*uses M_PI to convert any degree value into radians*/
double convert_to_radians(double value){
    //double degrees = 0.0174532925199432958;
    double deg = value;
    //double radian_angle = deg * degrees;
    double radian_angle = deg * M_PI / 180;
    return radian_angle;
}

/*simulates a boat moving in their specified direction at their specified speed*/
node *step_forward(node *the_node, int step_duration){
    double starting_lat = the_node->latitude;
    double starting_long = the_node->longitude;
    double speed = the_node->speed;
    double direction_in_radians = convert_to_radians(the_node->direction);
    double time_in_mins = step_duration;
    
    double latitude_after = starting_lat + ((speed * cos(direction_in_radians) * time_in_mins) / 3600);
    
    double longitude_after = starting_long + ((speed * sin(direction_in_radians) * time_in_mins 
        / cos(convert_to_radians(starting_lat))) / 3600);
    
    the_node->latitude = latitude_after;
    the_node->longitude = longitude_after;
    char out_string[200];
    if(starting_lat > 51.667 && starting_lat < 52.833 && starting_long > -6.667 && starting_long < -3.833){
        if(latitude_after < 51.667 || latitude_after > 52.833 || longitude_after < -6.667 || longitude_after > -3.833){
            sprintf(out_string, "%s has left the shipping area at\n", the_node->name);
            add_to_file(out_string);
            printf("%s has left the shipping area at\n", the_node->name);
        }
    }
    else if(starting_lat < 51.667 || starting_lat > 52.833 || starting_long < -6.667 || starting_long > -3.833){
        if(latitude_after > 51.667 && latitude_after < 52.833 && longitude_after > -6.667 && longitude_after < -3.833){
            sprintf(out_string, "%s has entered the shipping area at\n", the_node->name);
            add_to_file(out_string);
            printf("%s has entered the shipping area at\n", the_node->name);
        }
    }
    return the_node;
}

/*steps time forward at a specified rate*/
void step_time_forward(time *the_time, int step_duration){
    
    
    the_time->min = the_time->min + step_duration;
     
    while(the_time->min >= 60){
        the_time->hour++;
        the_time->min = the_time->min - 60;
    }
    while(the_time->hour > 23){
        the_time->day++;
        the_time->hour = 0;
    }
    while(the_time->day > 30){
        the_time->month++;
        the_time->day = 1;
    }
    while(the_time->month > 12){
        the_time->year++;
        the_time->month = 1;
    }
}




