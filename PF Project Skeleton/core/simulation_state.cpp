#include "simulation_state.h"
#include <cstring>

// ============================================================================
// SIMULATION_STATE.CPP - Global state definitions
// ============================================================================

// ----------------------------------------------------------------------------
// GRID
// ----------------------------------------------------------------------------
char grid[max_rows][max_cols];
int rows = 0;
int cols = 0;

// ----------------------------------------------------------------------------
// TRAINS
// ----------------------------------------------------------------------------
int id[max_trains];
int spawnTick[max_trains];
int direction[max_trains];
int color[max_trains];
int x[max_trains];
int y[max_trains];

bool Active[max_trains];
bool Finished[max_trains];
bool Crashed[max_trains];

int traincount = 0;

// ----------------------------------------------------------------------------
// SWITCHES
// ----------------------------------------------------------------------------
int switch_state[max_switch];
int switch_mode[max_switch];
int switch_signal[max_switch];
bool switch_exists[max_switch];
bool switch_waiting[max_switch];

int switch_count[max_switch][4];
int switch_Kvalue[max_switch][4];
// ----------------------------------------------------------------------------
// SPAWN AND DESTINATION POINTS
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SIMULATION PARAMETERS
// ----------------------------------------------------------------------------
int seed=0;
int weather=0;
int currentTick=0;
// ----------------------------------------------------------------------------
// METRICS
// ----------------------------------------------------------------------------
int total_trains_finished=0;
int total_trains_crashed=0;
// ----------------------------------------------------------------------------
// EMERGENCY HALT
// ----------------------------------------------------------------------------
bool emergency_halt_active=false;
int emergency_halt_timer=0;
// ============================================================================
// INITIALIZE SIMULATION STATE
// ============================================================================
// ----------------------------------------------------------------------------
// Resets all global simulation state.
// ----------------------------------------------------------------------------
// Called before loading a new level.
// ----------------------------------------------------------------------------
void initializeSimulationState() {
    rows=0;
    cols=0;
    traincount=0;
    seed=0;
    weather=weather_normal;
    currentTick=0;
    total_trains_crashed=0;
    total_trains_finished=0;
    emergency_halt_active=false;
    emergency_halt_timer=0;

    for(int i=0;i<max_rows;i++){
        for(int j=0;j<max_cols;j++){
            grid[i][j]=' ';
        }
    }
    for(int i=0;i<max_trains;i++){
        id[i]=-1;
        spawnTick[i]=0;
        color[i]=0;
        direction[i]=0;
        x[i]=-1;
        y[i]=-1;
        Active[i]=false;
        Finished[i]=false;
        Crashed[i]=false;
    }
    for(int i=0;i<max_switch;i++){
        switch_exists[i]=false;
        switch_state[i]=0;
        switch_mode[i]=0;
        switch_signal[i]=green;
        switch_waiting[i]=false;
        for(int j=0;j<4;j++){
            switch_count[i][j]=0;
            switch_Kvalue[i][j]=0;
        }
    }
}
