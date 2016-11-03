/* 
 * File:   file_handler.h
 * Author: alr16
 *
 * Created on 13 December 2011, 14:13
 */

#ifndef FILE_HANDLER_H
#define	FILE_HANDLER_H
#include "main.h"
#include "navigation.h"
#include "linked_list.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct out{
        struct clock *times;
        struct ship *first;
    }output;

    output *read_file(char file_path[40]);
    int add_to_file(char to_file[200]);


#ifdef	__cplusplus
}
#endif

#endif	/* FILE_HANDLER_H */

