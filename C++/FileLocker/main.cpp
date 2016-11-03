/* 
 * File:   main.cpp
 * Author: alr16
 *
 * Created on 13 March 2012, 17:37
 */

#include <cstdlib>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include <string>
#include <fstream>
#include <vector>

#include <iostream>
using namespace std;

/*
 * 
 */

struct flock* file_lock(short type, short whence){
    static struct flock ret;
    ret.l_type = type;
    ret.l_start = 0;
    ret.l_whence = whence;
    ret.l_len = 0;
    ret.l_pid = getpid();
    return &ret;
}

int main(int argc, char** argv) {
        char st[100];

    cout << "C file locking test" << endl;
    
    int fd = open("../../log/log.txt", O_RDWR);
    if (fd == -1) {
        printf("File descriptor error");
        exit(1);
    }
    
    

    struct flock* fl = file_lock(F_WRLCK, SEEK_SET);

    if (fcntl(fd, F_SETLK, fl) == -1) {
        if (errno == EACCES || errno == EAGAIN) {
            printf("Already locked by another process... bad luck\n");
            exit(1);
        } else {
            /* Handle unexpected error */;
        }
    } else {
        cout << "OK we have the lock\n\n";
        FILE* text = fdopen(fd, "r");
        while (!feof(text)) {
            fgets(st, 100, text);
            cout << st;
        }
        
        //fprintf(text, "edited by c++");
        
        /*
        ifstream ifs("test.txt");
        string temp;
        while (getline(ifs, temp)) {
            cout << temp << '\n';
        }
        */
        cout << "\n\nHit the end of file\n";

        cout << "Press <RETURN> to unlock the file\n";
        getchar();

        // unlock the file descriptor
        fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
        cout << "File unlocked\n";

        cout << "Press <RETURN> to close the file\n";
        getchar();
        fclose(text);
    }
    return 0;
}

