/* 
 * File:   main.h
 * Author: alr16
 *
 * Created on 19 March 2012, 22:23
 */

#ifndef MAIN_H
#define	MAIN_H
#include "linked_list.h"

#ifdef	__cplusplus
extern "C" {
#endif

        int add_to_log_file(char to_file[200]);
        void read_file(char file_path[9]);
        node *get_ships();


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

