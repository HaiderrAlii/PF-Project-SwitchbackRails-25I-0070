#include "io.h"
#include "simulation_state.h"
#include "grid.h"
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
// ============================================================================
// IO.CPP - Level I/O and logging
// ============================================================================

// ----------------------------------------------------------------------------
// LOAD LEVEL FILE
// ----------------------------------------------------------------------------
// Load a .lvl file into global state.
// ----------------------------------------------------------------------------
bool loadLevelFile(const char* filename) {
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
        if(line.empty() && currentsection != "MAP") continue;
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
        if(currentsection=="ROWS"){
            rows=stoi(line);
        }
        else if(currentsection=="COLS"){
            cols=stoi(line);
        }
        else if(currentsection=="SEED"){
            seed=stoi(line);
        }
        else if(currentsection=="WEATHER"){
            if(line=="RAIN") weather=weather_rain;
            else if(line=="FOG") weather=weather_fog;
            else weather=weather_normal;
        }
        else if(currentsection=="MAP"){
            if(mapRow<max_rows){
                for(int i=0;i<(int)line.length()&&i<max_cols;i++){
                    grid[mapRow][i]=line[i];
                }
                mapRow++;
            }
        }
        else if(currentsection=="SWITCHES"){
    char letter;
    char modeStr[20];
    int first,k0,k1,k2,k3;  
    int items=sscanf(line.c_str(),"%c %s %d %d %d %d %d",&letter,modeStr,&first,&k0,&k1,&k2,&k3);
    if(items==7){
        int idx=letter-'A';  
        if(idx>=0 && idx<max_switch){
            switch_exists[idx]=true;
            switch_state[idx]=first; 
            string m=modeStr;
            if(m=="GLOBAL") switch_mode[idx]=1;
            else switch_mode[idx]=0;
            switch_Kvalue[idx][0]=k0;
            switch_Kvalue[idx][1]=k1;
            switch_Kvalue[idx][2]=k2;
            switch_Kvalue[idx][3]=k3;
            for(int dir=0;dir<4;dir++){
                switch_count[idx][dir]=0;
            }
        }
    }
}
    else if(currentsection=="TRAINS"){
    int t,tx,ty,tdir,tcol;
    int items=sscanf(line.c_str(),"%d %d %d %d %d",&t,&tx,&ty,&tdir,&tcol);
    if(items==5&&traincount<max_trains){
        id[traincount]=traincount;
        spawnTick[traincount]=t;
        x[traincount]=tx;
        y[traincount]=ty;
        direction[traincount]=tdir;
        color[traincount]=tcol;
        Active[traincount]=false;
        Finished[traincount]=false;
        Crashed[traincount]=false;
        traincount++;
    }
}
}
    file.close();
    for(int i=0;i<traincount;i++){
        int cx=x[i];
        int cy=y[i];
        if(grid[cy][cx] != 'S'){
            for(int r=0; r<rows; r++){
                if(grid[r][cx]=='S'){
                    y[i]=r; 
                    break;
                }
            }
        }
    }
    cout<<"Loaded level file "<<filename<<": "<<rows<<" rows, "<<cols<<" cols, "<<traincount<<" trains."<<endl; 
    return true;
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
