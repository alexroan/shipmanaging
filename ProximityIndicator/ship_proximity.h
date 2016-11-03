/* 
 * File:   ship_proximity.h
 * Author: alr16
 *
 * Created on 27 March 2012, 04:48
 */

#ifndef SHIP_PROXIMITY_H
#define	SHIP_PROXIMITY_H

#include "node.h"

class ship_proximity {
public:
    
    ship_proximity();
    ship_proximity(const ship_proximity& orig);
    virtual ~ship_proximity();
    void find_ships();
    void loop_print_ships(node *array);
    node *load_ships();
    struct flock *file_lock(short type, short whence);
    void check_positions(node *array, double lat, double lng);
    void read_file(string file_path);
    void write_to_log(string file_read);
    
    
private:
    vector<string> mmsis;
};

#endif	/* SHIP_PROXIMITY_H */

