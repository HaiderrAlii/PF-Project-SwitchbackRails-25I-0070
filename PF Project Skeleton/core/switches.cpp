#include "switches.h"
#include "simulation_state.h"
#include "grid.h"
#include "io.h"

// ============================================================================
// SWITCHES.CPP - Switch management
// ============================================================================

// ----------------------------------------------------------------------------
// UPDATE SWITCH COUNTERS
// ----------------------------------------------------------------------------
// Increment counters for trains entering switches.
// ----------------------------------------------------------------------------
void updateSwitchCounters(int idx,int dir){
    if(idx<0||idx>=max_switch)return;
    if(dir<0||dir>3)return;
    switch_count[idx][dir]++;
}

// ----------------------------------------------------------------------------
// QUEUE SWITCH FLIPS
// ----------------------------------------------------------------------------
// Queue flips when counters hit K.
// ----------------------------------------------------------------------------
void queueSwitchFlips(){
    for(int i=0;i<max_switch;i++){
        if(switch_exists[i]){
            for(int j=0;j<4;j++){
                int val=switch_count[i][j];
                int limit=0;
                if(switch_mode[i]==0){
                    limit=switch_Kvalue[i][j];
                }
                else{
                    limit=switch_Kvalue[i][0];
                }
                if(limit>0&&val>=limit){
                    switch_waiting[i]=true;
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------
// APPLY DEFERRED FLIPS
// ----------------------------------------------------------------------------
// Apply queued flips after movement.
// ----------------------------------------------------------------------------
void applyDeferredFlips(){
    for(int i=0;i<max_switch;i++){
        if(switch_waiting[i]){
            if(switch_state[i]==0){
                switch_state[i]=1;
            }
            else{
                switch_state[i]=0;
            }
            for(int j=0;j<4;j++){
                switch_count[i][j]=0;
            }
            switch_waiting[i]=false;
        }
    }
}

// ----------------------------------------------------------------------------
// UPDATE SIGNAL LIGHTS
// ----------------------------------------------------------------------------
// Update signal colors for switches.
// ----------------------------------------------------------------------------
void updateSignalLights(){
    
}

// ----------------------------------------------------------------------------
// TOGGLE SWITCH STATE (Manual)
// ----------------------------------------------------------------------------
// Manually toggle a switch state.
// ----------------------------------------------------------------------------
void toggleSwitchState(int idx){
    if(idx>=0&&idx<max_switch){
        if(switch_state[idx]==0){
            switch_state[idx]=1;
        }
        else{
            switch_state[idx]=0;
        }
    }
}

// ----------------------------------------------------------------------------
// GET SWITCH STATE FOR DIRECTION
// ----------------------------------------------------------------------------
// Return the state for a given direction.
// ----------------------------------------------------------------------------
int getSwitchStateForDirection(int idx,int dir){
    if(idx<0||idx>=max_switch)return 0;
    return switch_state[idx];
}
