/* 
 * File:   node.h
 * Author: User
 *
 * Created on 27 March 2012, 12:42
 */

#ifndef NODE_H
#define	NODE_H
#include <dirent.h>
#include <string>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sstream>
#include <stdlib.h>

using namespace std;

class node {
public:
    node();
    node(const node& orig);
    virtual ~node();
    void set_mmsi(string new_mmsi);
    string get_mmsi();
    void set_lat(double new_lat);
    double get_lat();
    void set_lng(double new_lng);
    double get_lng();
private:
    string mmsi;
    double lat;
    double lng;
};

#endif	/* NODE_H */

