#include "grid.h"
#include "simulation_state.h"

// ============================================================================
// GRID.CPP - Grid utilities
// ============================================================================

// ----------------------------------------------------------------------------
// Check if a position is inside the grid.
// ----------------------------------------------------------------------------
// Returns true if x,y are within bounds.
// ----------------------------------------------------------------------------
bool isInBounds(int r,int c){
    return(r>=0&&r<rows&&c>=0&&c<cols);
}


// ----------------------------------------------------------------------------
// Check if a tile is a track tile.
// ----------------------------------------------------------------------------
// Returns true if the tile can be traversed by trains.
// ----------------------------------------------------------------------------
bool isTrackTile(char tile){
    if(tile=='-'||tile=='|'||tile=='/'||tile=='\\'||tile=='+'||tile=='='){
        return true;
    }
    if(tile>='A'&&tile<='Z'){
        return true;
    }
    else return false;
}

// ----------------------------------------------------------------------------
// Check if a tile is a switch.
// ----------------------------------------------------------------------------
// Returns true if the tile is 'A'..'Z'.
// ----------------------------------------------------------------------------
bool isSwitchTile(char tile){
    return(tile>='A'&&tile<='Z');
}

// ----------------------------------------------------------------------------
// Get switch index from character.
// ----------------------------------------------------------------------------
// Maps 'A'..'Z' to 0..25, else -1.
// ----------------------------------------------------------------------------
int getSwitchIndex(char tile){
    if(tile>='A'&&tile<='Z'){
        return(tile-'A');
    }
    else return -1;
}

// ----------------------------------------------------------------------------
// Check if a position is a spawn point.
// ----------------------------------------------------------------------------
// Returns true if x,y is a spawn.
// ----------------------------------------------------------------------------
bool isSpawnPoint(char tile){
    return(tile==TILE_SPAWN);
}

// ----------------------------------------------------------------------------
// Check if a position is a destination.
// ----------------------------------------------------------------------------
// Returns true if x,y is a destination.
// ----------------------------------------------------------------------------
bool isDestinationPoint(char tile){
    return(tile==TILE_DESTINATION);
}

// ----------------------------------------------------------------------------
// Toggle a safety tile.
// ----------------------------------------------------------------------------
// Returns true if toggled successfully.
// ----------------------------------------------------------------------------
bool toggleSafetyTile(int r,int c){
    if(!isInBounds(r,c)) return false;
    char present=grid[r][c];
    if(present=='='){
        grid[r][c]='-';
        return true;
    }
    else if(isTrackTile(present)){
        if(present=='-'||present=='|'||present=='/'||present=='\\'){
            grid[r][c]='=';
            return true;
        }
    }
    else return false;
}
