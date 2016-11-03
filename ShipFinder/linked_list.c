/* 
 * File:   main.c
 * Author: alr16
 *
 * Created on 19 March 2012, 18:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

//inserts a node after the previous one
node *insert_after(node *node_before, char mmsi[9]){
    node *this_node;
    this_node = create(mmsi);
    this_node->next = node_before->next;
    node_before->next = this_node;
    return this_node;
}

//creates memory for a new node
node *create(char mmsi[9]){
    node *this_node;
    if(!(this_node = malloc(sizeof(node)))){
        return NULL;
    }
    strcpy(this_node->mmsi, mmsi);
    return this_node;
}

//gets the current length of the list
int get_length(node *first_node){
    node *current_node = first_node;
    int length;
    if(current_node != NULL){
        length = 1;
    }
    else{
        length = 0;
    }
    while(current_node->next != NULL){
        current_node = current_node->next;
        length++;
    }
    return length;
}

//gets a specific node
node *get(node *first_node, int node_number){
    node *current_node = first_node;
    int i = 0;
    for(; i<node_number; i++){
        if(current_node->next != NULL){
            current_node = current_node->next;
        }
    }
    return current_node;
}