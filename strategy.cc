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
    for (Uint8 i = 0; i<8; i++) {
        for (Uint8 j = 0; j < 8; j++) {
            if (_blobs.get(i, j) == _current_player) {
                Uint8 k;
                for (k = std::max(0, i - 2); k < std::min(i + 3, 8); k++) {
                    Uint8 l;
                    for (l = std::max(0, j - 2); l < std::min(j + 3, 8); l++) {
                        if (!(_blobs.get(k, l) >= 0 || _holes.get(k, l))) {
                            valid_moves.push_back(movement(i, j, k, l));
                        }
                    }
                }
            }
        }
    }
    return valid_moves;
}

Node Strategy::noeudMax(int depth) const {
    Sint32 val = -1;
    vector<movement> fils;
    fils = computeValidMoves(fils);
    movement mov = fils[0];
    if (depth == 6){                    /*computing from 6 moves ahead*/
        val = estimateCurrentScore();
    } else {
        Sint32 tempVal = 0;
        for (uint i = 0; i < fils.size(); i++) {
            Strategy tempStrat = Strategy(*this);
            mov = fils[i];
            tempStrat.applyMove(mov);
            tempVal = tempStrat.noeudMin(depth+1).getValue();
            if (tempVal > val){
                val = tempVal;
            } else {
                break;
            }
        }
    }
    Node res(val,mov);
    return res;
}

Node Strategy::noeudMin(int depth) const {
    Sint32 val = 65; /*Equivalent to +infinity because each map is 8*8=64 squares*/
    Sint32 tempRes = 0;
    vector<movement> fils;
    fils = computeValidMoves(fils);
    movement mov = fils[0];
    for (uint i = 0;i < fils.size(); i++){
        Strategy tempStrat = Strategy(*this);
        mov = fils[i];
        tempStrat.applyMove(mov);
        tempRes = tempStrat.noeudMax(depth+1).getValue();
        if (tempRes < val) {
            val = tempRes;
        } else {
            break;
        }
    }
    Node res(val, mov);
    return  res;
}


//algo minmax (not anytime)
void Strategy::computeBestMove () {
    movement maxMv = noeudMax(0).getMv();

    _saveBestMove(maxMv);

     return;
}



