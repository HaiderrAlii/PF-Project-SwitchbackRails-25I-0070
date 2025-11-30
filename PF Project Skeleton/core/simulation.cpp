#include "simulation.h"
#include "simulation_state.h"
#include "trains.h"
#include "switches.h"
#include "io.h"
#include <cstdlib>
#include <ctime>
#include<iostream>
using namespace std;
// ============================================================================
// SIMULATION.CPP - Implementation of main simulation logic
// ============================================================================

// ----------------------------------------------------------------------------
// INITIALIZE SIMULATION
// ----------------------------------------------------------------------------

void initializeSimulation() {
}

// ----------------------------------------------------------------------------
// SIMULATE ONE TICK
// ----------------------------------------------------------------------------

void simulateOneTick(){
    spawnTrainsForTick();
    moveAllTrains();
    queueSwitchFlips();
    applyDeferredFlips();
    checkArrivals();
    currentTick++;
    logTrainTrace();
    logSwitchState();
    logSignalState();
    char displayMap[max_rows][max_cols];
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            displayMap[r][c]=grid[r][c];
        }
    }
    for(int i=0;i<traincount;i++){
        if(Active[i]==true){
            int r=y[i];
            int c=x[i];
            displayMap[r][c]='0'+(id[i]%10); 
        }
    }
    cout<<"Tick: "<<currentTick<<" | Finished: "<<total_trains_finished<<" | Crashed: "<<total_trains_crashed<<endl;
    
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            cout<<displayMap[r][c];
        }
        cout<<endl;
    }
    cout<<"--------------------------------"<<endl;
}

// ----------------------------------------------------------------------------
// CHECK IF SIMULATION IS COMPLETE
// ----------------------------------------------------------------------------

bool isSimulationComplete(){
    if(traincount==0) return false;
    for(int i=0;i<traincount;i++){
        if(Finished[i]==false&&Crashed[i]==false){
            return false;
        }
    }
    return true;
}
