#include "app.h"
#include "../core/simulation_state.h"
#include "../core/simulation.h"
#include "../core/io.h"
#include <iostream>
using namespace std;
// ============================================================================
// MAIN.CPP - Entry point of the application (NO CLASSES)
// ============================================================================

// ----------------------------------------------------------------------------
// MAIN ENTRY POINT
// ----------------------------------------------------------------------------
// This function is the main entry point of the application. It handles command
// line arguments to specify the level file to load, loads the level file using
// loadLevelFile, initializes the simulation system, initializes the SFML
// application window, prints control instructions to the console, runs the
// main application loop, cleans up resources, and prints final simulation
// statistics. Returns 0 on success, 1 on error (e.g., failed to load level
// file or initialize application).
// ----------------------------------------------------------------------------
int main(int argc, char* argv[]){
    if(argc<2){
        cout<<"Error..... no file provided"<<endl;
        cout<<"Usage: ./switchback_rails data/levels/easy_level.lvl"<<endl;
        return 1;
    }
    bool loaded=loadLevelFile(argv[1]);
    if(loaded==false){
        cout<<"Errorrrrrrrr the level file did not loaddddd."<<endl;
        return 1;
    }
    initializeSimulation();
    // bool windowReady=initializeApp();
    // if(windowReady==false){
    //     cout<<"Error...."<<endl;
    //     return 1;
    // }
    cout<<"Simulation Started!"<<endl;
    // cout<<"Controls: SPACE=Pause, . = Step, ESC=Exit"<<endl;
    // runApp();
    // cleanupApp();
    char input=' ';
    while(input!='q'){
        simulateOneTick();
        cout<<"Step > ";
        input=cin.get();
    }
    return 0;
}
