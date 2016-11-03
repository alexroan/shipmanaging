/* 
 * File:   linked_list.h
 * Author: alr16
 *
 * Created on 24 March 2012, 19:20
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct ship{
        char mmsi[9];
        struct ship *next;
    }node;

    node *insert_after(node *node_before, char mmsi[9]);
    node *create(char mmsi[9]);
    int get_length(node *first_node);
    node *get(node *first_node, int node_number);

#ifdef	__cplusplus
}
#endif

#endif	/* LINKED_LIST_H */

