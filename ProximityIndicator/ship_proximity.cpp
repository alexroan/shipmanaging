/* 
 * File:   ship_proximity.cpp
 * Author: alr16
 * 
 * Created on 27 March 2012, 04:48
 */

#include "ship_proximity.h"

ship_proximity::ship_proximity() {
}

ship_proximity::ship_proximity(const ship_proximity& orig) {
}

ship_proximity::~ship_proximity() {
}

//Finds all the mmsis of the ships in the ships folder and stores them
void ship_proximity::find_ships(){
    DIR *current_directory_ptr;
    struct dirent *next_entry_ptr;
    if(!(current_directory_ptr = opendir("../ships"))){
        cout << "could not open ship directory" << endl;
    }
    else{
        while(next_entry_ptr = readdir(current_directory_ptr)){
            if(strcmp(next_entry_ptr->d_name, ".") != 0 && strcmp(next_entry_ptr->d_name, "..") != 0){
                mmsis.push_back(next_entry_ptr->d_name);
            }
        }
    }
}

//Opens each of the ship files and reads in their data to a node array which is
//returned
node *ship_proximity::load_ships(){
    FILE *file_ptr;
    string file_name_string;
    
    node *array = new node[mmsis.size()];
    
    char output[100];
    int fd;
    struct flock *fl;
    for(int i=0; i<mmsis.size(); i++){
        file_name_string = "../ships/" + mmsis[i];
        fd = open(file_name_string.c_str(), O_RDWR);
        if(fd == -1){
            cout << "File Descriptor Error" << endl;
            return NULL;
        }
        else{
            fl = file_lock(F_WRLCK, SEEK_SET);
            if(fcntl(fd, F_SETLK, fl) == -1){
                cout << "lock error" << endl;
            }
            else{
                file_ptr = fdopen(fd, "r");
                fgets(output, 100, file_ptr);
                array[i].set_mmsi(mmsis[i]);
                fgets(output, 100, file_ptr);
                fgets(output, 100, file_ptr);
                istringstream stm(output);
                string word;
                string lat_lng[2];
                int index = 0;
                while(stm >> word){
                    lat_lng[index] = word;
                    index++;
                }
                array[i].set_lat(atof(lat_lng[0].c_str()));
                array[i].set_lng(atof(lat_lng[1].c_str()));
                fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
                fclose(file_ptr);
            }
        } 
    }
    return array;
}

//reads and prints out a single ship file
void ship_proximity::read_file(string file_path){
    FILE *file_ptr;
    int fd;
    string full_file_path = "../ships/" + file_path;
    struct flock *fl;
    fd = open(full_file_path.c_str(), O_RDWR);
    if(fd == -1){
        cout << "File Descriptor Error" << endl;
    }
    else{
        fl = file_lock(F_WRLCK, SEEK_SET);
        if(fcntl(fd, F_SETLK, fl) == -1){
            cout << "lock error" << endl;
        }
        else{
            char output[100];
            file_ptr = fdopen(fd, "r");
            cout << "INFORMATION FOR SHIP: " << file_path << endl;
            for(int k=0; k<6; k++){
                fgets(output, 100, file_ptr);
                cout << output;
            }
            cout << "\n" << endl;
            fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
            fclose(file_ptr);
        }
    }
}

//writes a message about the program viewing a ship to the log file
void ship_proximity::write_to_log(string file_read){
    FILE *file_ptr;
    int fd;
    string full_file_path = "../log/log.txt";
    struct flock *fl;
    fd = open(full_file_path.c_str(), O_RDWR);
    if(fd == -1){
        cout << "File Descriptor Error for log file" << endl;
    }
    else{
        fl = file_lock(F_WRLCK, SEEK_SET);
        if(fcntl(fd, F_SETLK, fl) == -1){
            cout << "lock error" << endl;
        }else{
            file_ptr = fdopen(fd, "a");
            file_read = file_read + " was read by the ship proximity indicator program in C++\n";
            const char *c_output = file_read.c_str();
            fprintf(file_ptr, c_output);
            
            fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
            fclose(file_ptr);
        }
    }
}

//compares the positions of each ship to the lat and long entered 
void ship_proximity::check_positions(node *array, double lat, double lng){
    for(int i=0; i<mmsis.size(); i++){
        double lat_difference = array[i].get_lat() - lat;
        double lng_difference = array[i].get_lng() - lng;
        if((lat_difference <= 0.1001) && (lat_difference >= -0.1001)){
            if((lng_difference <= 0.2001) && (lng_difference >= -0.2001)){
                read_file(array[i].get_mmsi());
                write_to_log(array[i].get_mmsi());
            }
        }
    }
}

//prints all the mmsi's out - mainly used for testing
void ship_proximity::loop_print_ships(node *array){
    for(int i=0; i<mmsis.size(); i++){
        cout << array[i].get_mmsi();
        cout << array[i].get_lat() << endl;
        cout << array[i].get_lng() << endl;
    }
}

//locks a file
flock *ship_proximity::file_lock(short type, short whence){
    static struct flock ret;
    ret.l_type = type;
    ret.l_start = 0;
    ret.l_whence = whence;
    ret.l_len = 0;
    ret.l_pid = getpid();
    return &ret;
}

