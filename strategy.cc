#include "strategy.h"



void Strategy::applyMove (const movement& mv) {
    movement movement1(0,0,0,0);
    if(mv.ox - mv.nx ==2 || mv.oy - mv.oy == 2) {// if the position chosen is
        _blobs.set(mv.ox,mv.oy, -1); //the original blob disappears
    }
        _blobs.set(mv.nx, mv.ny, _current_player);//the new blob appears
    for (movement1.nx = std::max(0, mv.nx-1); movement1.nx < std::min(8, mv.nx +2); movement1.nx++){
        for(movement1.ny = std::max(0, mv.ny-1); movement1.ny < std::min(8, mv.ny +2); movement1.ny++){
            if(_blobs.get(movement1.nx,movement1.ny) != -1 && _blobs.get(movement1.nx,movement1.ny) != _current_player){
                _blobs.set(movement1.nx,movement1.ny, _current_player);
            }
        }
    }
}

Sint32 Strategy::estimateCurrentScore () const {
    Sint32 score = 0;
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
    for (Uint8 i = 0; i<8; i++){
        for (Uint8 j = 0; j<8; j++){
            if (_blobs.get(i,j) == _current_player){
                Uint8 k;
                for(k = std::max(0, i - 2); k < std::min(i + 3, 8); k++){
                    Uint8 l;
                    for(l = std::max(0, j - 2); l < std::min(j + 3, 8); l++){
                        if(!(_blobs.get(k, l) >= 0 || _holes.get(k, l))){
                            valid_moves.push_back(movement(i,j,k,l));
                        }
                    }
                }
            }
        }
    }

    return valid_moves;
}

//algo glouton
void Strategy::computeBestMove () {
    // To be improved...
    movement maxMv(0,0,0,0);
    Sint32 maxScore = 0;
    vector<movement> validMoves;
    validMoves = computeValidMoves(validMoves);
    for (uint i = 0 ; i < validMoves.size(); i++){
        Strategy newStrat = Strategy(*this);
        movement mv = validMoves[i];
        Sint32 score;
        newStrat.applyMove(mv);
        score = newStrat.estimateCurrentScore();
        if (score >= maxScore){
            maxScore = score;
            maxMv = mv;
        }
    }
     _saveBestMove(maxMv);
     return;
}

