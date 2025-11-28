#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

// ============================================================================
// SIMULATION_STATE.H - Global constants and state
// ============================================================================
// Global constants and arrays used by the game.
// ============================================================================
const int dir_up=0;
const int dir_right=1;
const int dir_down=2;
const int dir_left=3;
// ----------------------------------------------------------------------------
// GRID CONSTANTS
// ----------------------------------------------------------------------------
const int max_rows=128;
const int max_cols=128;

// ----------------------------------------------------------------------------
// TRAIN CONSTANTS
// ----------------------------------------------------------------------------
const int max_trains=200;

// ----------------------------------------------------------------------------
// SWITCH CONSTANTS
// ----------------------------------------------------------------------------
const int max_switch=26;

// ----------------------------------------------------------------------------
// WEATHER CONSTANTS
// ----------------------------------------------------------------------------
const int weather_normal=0;
const int weather_fog=1;
const int weather_rain=2;

// ----------------------------------------------------------------------------
// SIGNAL CONSTANTS
// ----------------------------------------------------------------------------
const int green=0;
const int yellow=1;
const int red=2;

// ----------------------------------------------------------------------------
// GLOBAL STATE: GRID
// ----------------------------------------------------------------------------
extern char grid[max_rows][max_cols];
extern int rows;
extern int cols;

// ----------------------------------------------------------------------------
// GLOBAL STATE: TRAINS
// ----------------------------------------------------------------------------
extern int id[max_trains];
extern int spawnTick[max_trains];
extern int direction[max_trains];
extern int color[max_trains];
extern int x[max_trains];
extern int y[max_trains];

extern bool Active[max_trains];
extern bool Finished[max_trains];
extern bool Crashed[max_trains];

extern int traincount;
// ----------------------------------------------------------------------------
// GLOBAL STATE: SWITCHES (A-Z mapped to 0-25)
// ----------------------------------------------------------------------------
extern int switch_state[max_switch];
extern int switch_mode[max_switch];
extern int switch_signal[max_switch];
extern bool switch_exists[max_switch];
extern bool switch_waiting[max_switch];
extern int switch_count[max_switch][4];
extern int switch_Kvalue[max_switch][4];

// ----------------------------------------------------------------------------
// GLOBAL STATE: SPAWN POINTS
// ----------------------------------------------------------------------------
const char TILE_SPAWN = 'S';

// ----------------------------------------------------------------------------
// GLOBAL STATE: DESTINATION POINTS
// ----------------------------------------------------------------------------
const char TILE_DESTINATION = 'D';

// ----------------------------------------------------------------------------
// GLOBAL STATE: SIMULATION PARAMETERS
// ----------------------------------------------------------------------------
extern int seed;          
extern int weather;       
extern int currentTick;

// ----------------------------------------------------------------------------
// GLOBAL STATE: METRICS
// ----------------------------------------------------------------------------
extern int total_trains_finished;
extern int total_trains_crashed;

// ----------------------------------------------------------------------------
// GLOBAL STATE: EMERGENCY HALT
// ----------------------------------------------------------------------------
extern bool emergency_halt_active;
extern int emergency_halt_timer;
// ----------------------------------------------------------------------------
// INITIALIZATION FUNCTION
// ----------------------------------------------------------------------------
// Resets all state before loading a new level.
void initializeSimulationState();

#endif
