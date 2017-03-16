#include "strategy.h"



void Strategy::applyMove (const movement& mv) {
    if(mv.ox - mv.nx == 1 || mv.ox - mv.nx == -1){
        _blobs.set(mv.nx, mv.ny, _current_player);//spawns a new blob
    } else {
        _blobs.set(mv.ox,mv.oy, -1); //the original blob disappears
        _blobs.set(mv.nx, mv.ny, _current_player);//the new blob appears
    }
    for (int i = std::max(mv.nx-1, 0); i < std::min(mv.nx +2, 8); i++){
        for(int j = std::max(mv.ny, 0); j < std::min(mv.ny +2, 8); j++){
            if(_blobs.get(i,j) == _current_player%2){
                _blobs.set(i,j, _current_player);
            }
        }
    }
}

Sint32 Strategy::estimateCurrentScore () const {
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (_blobs.get(i, j) == _current_player) {
                score++;
            }
        }
    }
    return score;
}

vector<movement>& Strategy::computeValidMoves (vector<movement>& valid_moves) const {
        // To be completed...
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (_blobs.get(i,j) == _current_player){
                int k;
                for(k = std::max(0, i - 2); k < std::min(i + 3, 8); k++){
                    int l;
                    for(l = std::max(0, j - 2); l < std::min(j + 3, 8); l++){
                        if(!(_blobs.get(k, l) > 0 || _holes.get(k, l))){
                            valid_moves.push_back(movement(i,j,k,l));
                        }
                    }
                }
            }
        }
    }

    return valid_moves;
}

void Strategy::computeBestMove () {
    // To be improved...

    //The following code find a valid move.
    movement mv(0,0,0,0);
    //iterate on starting position
    for(mv.ox = 0 ; mv.ox < 8 ; mv.ox++) {
        for(mv.oy = 0 ; mv.oy < 8 ; mv.oy++) {
            if (_blobs.get(mv.ox, mv.oy) == (int) _current_player) {
                //iterate on possible destinations
                for(mv.nx = std::max(0,mv.ox-2) ; mv.nx <= std::min(7,mv.ox+2) ; mv.nx++) {
                    for(mv.ny = std::max(0,mv.oy-2) ; mv.ny <= std::min(7,mv.oy+2) ; mv.ny++) {
                        if (_holes.get(mv.nx, mv.ny)) continue;
                        if (_blobs.get(mv.nx, mv.ny) == -1) goto end_choice;
                    }
                }
            }
        }
    }

end_choice:
     _saveBestMove(mv);
     return;
}

