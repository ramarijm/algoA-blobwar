#ifndef __STRATEGY_H
#define __STRATEGY_H

#include "common.h"
#include "bidiarray.h"
#include "movement.h"


class Node;
class Strategy {

private:
    //! array containing all blobs on the board
    bidiarray<Sint16> _blobs;
    //! an array of booleans indicating for each cell whether it is a hole or not.
    const bidiarray<bool>& _holes;
    //! Current player
    Sint16 _current_player;
    
    //! Call this function to save your best move.
    //! Multiple call can be done each turn,
    //! Only the last move saved will be used.
    void (*_saveBestMove)(movement&);

public:
        // Constructor from a current situation
    Strategy (bidiarray<Sint16>& blobs,
              const bidiarray<bool>& holes,
              const Sint16 current_player,
              void (*saveBestMove)(movement&))
            : _blobs(blobs),_holes(holes), _current_player(current_player), _saveBestMove(saveBestMove)
        {
        }
    
              
    
        // Copy constructor
    Strategy (const Strategy& St)
            : _blobs(St._blobs), _holes(St._holes),_current_player(St._current_player) 
        {}
    
        // Destructor
    ~Strategy() {}
    
        /** 
         * Apply a move to the current state of blobs
         * Assumes that the move is valid
         */
    void applyMove (const movement& movement1);

        /**
         * Compute the vector containing every possible moves
         */
    vector<movement>& computeValidMoves (vector<movement>& valid_moves) const;

        /**
         * Estimate the score of the current state of the game
         */
    Sint32 estimateCurrentScore () const;

    Node noeudMin(int depth) const ;

    Node noeudMax(int depth) const ;

        /**
         * Find the best move.
         */
    void computeBestMove ();
    
    
};

class Node{
    Sint32 value;
    movement mv;

public:
    Node (Sint32 val,
          movement mov): value(val), mv(mov)
    {}

    Sint32 getValue(){ return  value;}
    movement getMv(){ return mv;}
};
#endif
