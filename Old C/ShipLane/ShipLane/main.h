/* 
 * File:   main.h
 * Author: alr16
 *
 * Created on 13 December 2011, 13:22
 */

#ifndef MAIN_H
#define	MAIN_H
#include "navigation.h"
#include "file_handler.h"
#include "linked_list.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct clock{
        int year;
        int month;
        int day;
        int hour;
        int min;
        int sec;
        
    }time; 
    
    void simulate_(node *cur_node, time *the_time, int se);
    void run(node *first_node, time *current_time, int step, float monitor_time);
    void check_distances(node *first_in_list);
    double convert_to_radians(double value);
    node *step_forward(node *the_node, int step_duration);
    void step_time_forward(time *the_time, int step_duration);
    
    void display_time(time *times);
    int main(int argc, char** argv);
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

