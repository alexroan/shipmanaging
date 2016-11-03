/* 
 * File:   main.cpp
 * Author: alr16
 *
 * Created on 27 March 2012, 04:46
 */


#include "ship_proximity.h"


/*
 * 
 */
int main(int argc, char** argv) {
    char option = 'a';
    while(option != 'q'){
        cout << "To find ships using position enter 'f', to quit enter 'q'" << endl;
        scanf("%c", &option);
        while(option == 10){
            scanf("%c", &option);
        }
        if(option == 'f'){
            ship_proximity* prox = new ship_proximity();

            cout << "Finding Ships..." << endl;
            prox->find_ships();

            cout << "Loading Ships..." << endl;
            node *ships = prox->load_ships();

            cout << "Enter: latitude<space>longitude in double form to 3 dp" << endl;
            double lat; double lng;
            scanf("%lf %lf", &lat, &lng);
            cout << endl;
            prox->check_positions(ships, lat, lng);

            delete prox;
        }
        else if(option == 'q'){
            break;
        }
        else{
            cout << "Response not recognised" << endl;
        }
    }
    
    return 0;
}

