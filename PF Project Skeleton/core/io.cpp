#include "io.h"
#include "simulation_state.h"
#include "grid.h"
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

// ============================================================================
// IO.CPP - Level I/O and logging
// ============================================================================

// ----------------------------------------------------------------------------
// LOAD LEVEL FILE
// ----------------------------------------------------------------------------
// Load a .lvl file into global state.
// ----------------------------------------------------------------------------
bool loadLevelFile() {
    initializeSimulationState();
    ifstream file(filename);
    if(!file.is_open()){
        cout<<"Error: Could not open level file "<<endl;
        return false;
    }
    string line;
    string currentsection="";
    int mapRow;
    while(getline(file,line)){
        if(!line.empty()&&line[line.length()-1]=='\r'){
            line.erase(line.length()-1);
        }
        if(line.empty()) continue;
        if(line=="ROWS:"){
            currentsection="ROWS";
            continue;
        }
        if(line=="COLS:"){
            currentsection="COLS";
            continue;
        }
        if(line=="SEED:"){
            currentsection="SEED";
            continue;
        }
        if(line=="WEATHER:"){
            currentsection="WEATHER";
            continue;
        }
        if(line=="MAP:"){
            currentsection="MAP";
            mapRow=0;
            continue;
        }
        if(line=="SWITCHES:"){
            currentsection="SWITCHES";
            continue;
        }
        if(line=="TRAINS:"){
            currentsection="TRAINS";
            continue;
        }
    }

}

// ----------------------------------------------------------------------------
// INITIALIZE LOG FILES
// ----------------------------------------------------------------------------
// Create/clear CSV logs with headers.
// ----------------------------------------------------------------------------
void initializeLogFiles() {
}

// ----------------------------------------------------------------------------
// LOG TRAIN TRACE
// ----------------------------------------------------------------------------
// Append tick, train id, position, direction, state to trace.csv.
// ----------------------------------------------------------------------------
void logTrainTrace() {
}

// ----------------------------------------------------------------------------
// LOG SWITCH STATE
// ----------------------------------------------------------------------------
// Append tick, switch id/mode/state to switches.csv.
// ----------------------------------------------------------------------------
void logSwitchState() {
}

// ----------------------------------------------------------------------------
// LOG SIGNAL STATE
// ----------------------------------------------------------------------------
// Append tick, switch id, signal color to signals.csv.
// ----------------------------------------------------------------------------
void logSignalState() {
}

// ----------------------------------------------------------------------------
// WRITE FINAL METRICS
// ----------------------------------------------------------------------------
// Write summary metrics to metrics.txt.
// ----------------------------------------------------------------------------
void writeMetrics() {
}
