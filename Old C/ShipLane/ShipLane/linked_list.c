#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/*creates a new node and sets its variables*/
node *create(char name[20], double lati, double longi, double direction, double speed){
    node *this_node;
    if(!(this_node = malloc(sizeof(node)))){
        return NULL;
    }
    strcpy(this_node->name, name);
    this_node->latitude = lati;
    this_node->longitude = longi;
    this_node->direction = direction;
    this_node->speed = speed;
    return this_node;
}

/*calls create() with specified variables and adds it after a specified node*/
node *insert_after(node *node_before, char name[20], double lati, double longi, double direction, double speed){
    node *this_node;
    this_node = create(name, lati, longi, direction, speed);
    this_node->next = node_before->next;
    node_before->next = this_node;
    return this_node;
}

/*removes a specified node from the linked list*/
int remove_node(node *this_node, node *removed){
    while (this_node->next && this_node->next != removed){
        this_node = this_node->next;
    }
    if(this_node->next){
        this_node->next = removed->next;
        free(removed);
        return 0;
    }
    else{
        return -1;
    }
}

/*displays the linked list in the standard output*/
void display_all(node *this_node){
    int count = 0;
    //char string[200];
    while (this_node != NULL){
        if (count != 0){
            printf("%s %.3f %.3f %.3f %.3f\n",this_node->name, this_node->latitude, this_node->longitude, this_node->direction, this_node->speed);
            //sprintf(string,"%s %.3f %.3f %.3f %.3f\n",this_node->name, this_node->latitude, this_node->longitude, this_node->direction, this_node->speed);
            //add_to_file(string);
        }
        
        this_node = this_node->next;
        count++;
    }
}

//displays the linked list in the output file
void display_all_to_file(node *this_node){
    int count = 0;
    char string[200];
    while (this_node != NULL){
        if (count != 0){
            //printf("%s %.3f %.3f %.3f %.3f\n",this_node->name, this_node->latitude, this_node->longitude, this_node->direction, this_node->speed);
            sprintf(string,"%s %.3f %.3f %.3f %.3f\n",this_node->name, this_node->latitude, this_node->longitude, this_node->direction, this_node->speed);
            add_to_file(string);
        }
        this_node = this_node->next;
        count++;
    }
}
