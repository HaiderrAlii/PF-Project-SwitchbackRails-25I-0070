#include "trains.h"
#include "simulation_state.h"
#include "grid.h"
#include "switches.h"
#include <cstdlib>
#include <iostream>
using namespace std;

// ============================================================================
// TRAINS.CPP - Train logic
// ============================================================================

// Storage for planned moves (for collisions).
int next_x[max_trains];
int next_y[max_trains];
int next_dir[max_trains];
bool can_move[max_trains];
// Previous positions (to detect switch entry).

// ----------------------------------------------------------------------------
// SPAWN TRAINS FOR CURRENT TICK
// ----------------------------------------------------------------------------
// Activate trains scheduled for this tick.
// ----------------------------------------------------------------------------
void spawnTrainsForTick(){
    for(int i=0;i<traincount;i++){
        if(Active[i]==false&&Finished[i]==false&&Crashed[i]==false){
            if(currentTick>=spawnTick[i]){
                bool blocked=false;
                for(int j=0;j<traincount;j++){
                    if(Active[j]==true){
                        if(x[j]==x[i]&&y[j]==y[i]){
                            blocked=true;
                            break;
                        }
                    }
                }
                if(blocked==false){
                    Active[i]=true;
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------
// DETERMINE NEXT POSITION for a train
// ----------------------------------------------------------------------------
// Compute next position/direction from current tile and rules.
// ----------------------------------------------------------------------------
bool determineNextPosition(int idx){
    int r=y[idx];
    int c=x[idx];
    int d=direction[idx];
    char tile=grid[r][c];
    
    int nd=getNextDirection(d,tile);
    int nr=r;
    int nc=c;
    
    if(nd==0)
    nr=r-1;
    if(nd==1)
    nc=c+1;
    if(nd==2)
    nr=r+1;
    if(nd==3)
    nc=c-1;
    
    next_x[idx]=nc;
    next_y[idx]=nr;
    next_dir[idx]=nd;
    
    if(isInBounds(nr,nc)==false){
        next_x[idx]=c;
        next_y[idx]=r;
        return false;
    }
    if(isTrackTile(grid[nr][nc])==false){
        next_x[idx]=c;
        next_y[idx]=r;
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------------
// GET NEXT DIRECTION based on current tile and direction
// ----------------------------------------------------------------------------
// Return new direction after entering the tile.
// ----------------------------------------------------------------------------
int getNextDirection(int currentDir,char currentTile){
    if(currentTile=='-'||currentTile=='|'||currentTile=='+'||currentTile=='='||currentTile=='S'){
        return currentDir;
    }
    if(currentTile=='/'){
        if(currentDir==0) return 1;
        if(currentDir==1) return 0;
        if(currentDir==2) return 3;
        if(currentDir==3) return 2;
    }
    if(currentTile=='\\'){
        if(currentDir==0) return 3;
        if(currentDir==1) return 2;
        if(currentDir==2) return 1;
        if(currentDir==3) return 0;
    }
    if(currentTile>='A'&&currentTile<='Z'){
        int idx=currentTile-'A';
        int state=switch_state[idx];
        if(state==0){
            return currentDir;
        }
        else{
            if(currentDir==0) return 1;
            if(currentDir==1) return 2;
            if(currentDir==2) return 3;
            if(currentDir==3) return 0;
        }
    }
    return currentDir;
}

// ----------------------------------------------------------------------------
// SMART ROUTING AT CROSSING - Route train to its matched destination
// ----------------------------------------------------------------------------
// Choose best direction at '+' toward destination.
// ----------------------------------------------------------------------------
int getSmartDirectionAtCrossing(int t_idx,int r,int c,int current_dir){
    return current_dir;
}

// ----------------------------------------------------------------------------
// DETERMINE ALL ROUTES (PHASE 2)
// ----------------------------------------------------------------------------
// Fill next positions/directions for all trains.
// ----------------------------------------------------------------------------
void determineAllRoutes(){
    for(int i=0;i<traincount;i++){
        can_move[i]=false;
        if(Active[i]==true){
        can_move[i]=determineNextPosition(i);
        }
    }
}

// ----------------------------------------------------------------------------
// MOVE ALL TRAINS (PHASE 5)
// ----------------------------------------------------------------------------
// Move trains; resolve collisions and apply effects.
// ----------------------------------------------------------------------------
void moveAllTrains(){
    determineAllRoutes();
    detectCollisions(); 
    for(int i=0;i<traincount;i++){
        if (Active[i] && !can_move[i] && !Crashed[i]) {
            cout<<"Train "<<i<<" WAITING at "<<x[i]<<","<<y[i]<<endl;
        }
        if(Active[i]==true&&Crashed[i]==false&&can_move[i]==true){
            char nextTile=grid[next_y[i]][next_x[i]];
            if(nextTile>='A'&&nextTile<='Z'){
                bool trainMoved=false;
                if(next_x[i]!=x[i]||next_y[i]!=y[i]){
                    trainMoved=true;
                }
                if(trainMoved==true){
                    int switchIndex=nextTile-'A';
                    updateSwitchCounters(switchIndex,direction[i]);
                }
            }
            x[i]=next_x[i];
            y[i]=next_y[i];
            direction[i]=next_dir[i];
        }
    }
}


// ----------------------------------------------------------------------------
// DETECT COLLISIONS WITH PRIORITY SYSTEM
// ----------------------------------------------------------------------------
// Resolve same-tile, swap, and crossing conflicts.
// ----------------------------------------------------------------------------
void detectCollisions(){
    for(int i=0;i<traincount;i++){
        if(Active[i]==false) continue;
        if(can_move[i]==false) continue;
        for(int j=0;j<traincount;j++){
            if(i==j) continue;
            if(Active[j]==false) continue;
            bool sameSpot=false;
            if(next_x[i]==next_x[j]&&next_y[i]==next_y[j]){
                sameSpot=true;
            }
            bool headOn=false;
            if(next_x[i]==x[j]&&next_y[i]==y[j]){
                if(next_x[j]==x[i]&&next_y[j]==y[i]){
                    headOn=true;
                }
            }
            if(sameSpot==true||headOn==true){
                int dist_i=10000;
                for(int r=0;r<rows;r++){
                    for(int c=0;c<cols;c++){
                        if(grid[r][c]=='D'){
                            int d=abs(y[i]-r)+abs(x[i]-c);
                            if(d<dist_i){
                                dist_i=d;
                            }
                        }
                    }
                }
                int dist_j=10000;
                for(int r=0;r<rows;r++){
                    for(int c=0;c<cols;c++){
                        if(grid[r][c]=='D'){
                            int d=abs(y[j]-r)+abs(x[j]-c);
                            if(d<dist_j){
                                dist_j=d;
                            }
                        }
                    }
                }
                if(dist_i>dist_j){
                    can_move[j]=false;
                }
                else if(dist_j>dist_i){
                    can_move[i]=false;
                }
                else{
                    Crashed[i]=true;
                    Crashed[j]=true;
                    can_move[i]=false;
                    can_move[j]=false;
                    total_trains_crashed=total_trains_crashed+2;
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------
// CHECK ARRIVALS
// ----------------------------------------------------------------------------
// Mark trains that reached destinations.
// ----------------------------------------------------------------------------
void checkArrivals(){
    for(int i=0;i<traincount;i++){
        if(Active[i]==true&&Crashed[i]==false){
            if(grid[y[i]][x[i]]=='D'){
                Active[i]=false;
                Finished[i]=true;
                total_trains_finished=total_trains_finished+1;
            }
        }
    }
}

// ----------------------------------------------------------------------------
// APPLY EMERGENCY HALT
// ----------------------------------------------------------------------------
// Apply halt to trains in the active zone.
// ----------------------------------------------------------------------------
void applyEmergencyHalt(){
    
}

// ----------------------------------------------------------------------------
// UPDATE EMERGENCY HALT
// ----------------------------------------------------------------------------
// Decrement timer and disable when done.
// ----------------------------------------------------------------------------
void updateEmergencyHalt() {
}
