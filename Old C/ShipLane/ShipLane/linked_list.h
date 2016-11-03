/* 
 * File:   linked_list.h
 * Author: alr16
 *
 * Created on 13 December 2011, 14:31
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H
#include "main.h"
#include "navigation.h"
#include "file_handler.h"

#ifdef	__cplusplus
extern "C" {
#endif

    
    typedef struct ship{
        char name[30];
        double latitude;
        double longitude;
        double direction;
        double speed;
        struct ship *next;
    }node;
    
    node *create(char name[20], double lati, double longi, double direction, double speed);
    node *insert_after(node *node_before, char name[20], double lati, double longi, double direction, double speed);
    int remove_node(node *this_node, node *removed);
    void display_all(node *this_node);
    void display_all_to_file(node *this_node);



#ifdef	__cplusplus
}
#endif

#endif	/* LINKED_LIST_H */

