/* 
 * File:   node.cpp
 * Author: alr16
 * 
 * Created on 27 March 2012, 12:42
 */

#include "node.h"

node::node() {
}

node::node(const node& orig) {
}

node::~node() {
}

void node::set_mmsi(string new_mmsi){
    mmsi = new_mmsi;
}

string node::get_mmsi(){
    return mmsi;
}

void node::set_lat(double new_lat){
    lat = new_lat;
}

double node::get_lat(){
    return lat;
}

void node::set_lng(double new_lng){
    lng = new_lng;
}

double node::get_lng(){
    return lng;
}


