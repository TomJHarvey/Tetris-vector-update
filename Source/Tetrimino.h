/*
  ==============================================================================

    Tetrimino.h
    Created: 23 Oct 2017 1:20:09pm
    Author:  Thomas Harvey

  ==============================================================================
*/

#ifndef TETRIMINO_H_INCLUDED
#define TETRIMINO_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


class Tetrimino: public Component
{
public:
    
    Tetrimino();
    ~Tetrimino();
    
    void setType(int type);
    void paint (Graphics&) override;
    void rotateShape(int type);
    int returnBlankSpace(int xAxisValue, int topOrbottom);
    Array<int> returnXpositions(int tetriminoYposition, int width);
    Array<int> returnYpositions(int tetriminoXposition, int width);
    std::vector <int> returnYposition(int tetriminoYposition, int width);
    std::vector <int> returnXposition(int tetriminoXposition, int width);
   
private:
    
    int typeSelect = 0;                         // Selects what tetrimino is used
    int rotateCounter = 0;                      // Counts how many times the piece has been rotated
    int xPosition[6] = {0};                     // The x position of each of the 6 sqaures for all shapes apart from i and 0
    int yPosition[6] = {0};                     // The y position "...... "
    int rowSelect[8] = {0,38,38,0,38,0,0,38};   // The cordinates of the staring position for the current rotation
    int xOrYcordintates[3] = {0,38,76};         // The cordinates for the row or collum
    int xOrYdirection[4] = {1,1,-1,-1};         // The direction that the above x or y cordiates are drawn
    int xOrYstartPos[4] = {0,0,2,2};            // If it starts at the highest or lowest value for the x or y
    
    int iXdimensionsFlat[4] = {0,38,76,114};
    int iYdimensionsFlat[4] = {0,0,0,0};
    int iXdimensionsStanding[4] = {0,0,0,0};
    int iYdimensionsStanding[4] = {0,38,76,114};
   
    
    
    int oXdimensions[4] = {0,38,0,38};
    int oYdimensions[4] = {0,0,38,38};
    
    Colour tetriminoColorus[7] =
    {
        Colours::lightskyblue,
        Colours::yellow,
        Colours::pink,
        Colours::navy,
        Colours::orange,
        Colours::green,
        Colours::red
    };
    
    
    int tetriminoSquaresChecker[7][6] =         // 1 is if a square should be present, 0 is if its a blank space
    {
        {0},                // I
        {0},                // O
        {1,1,1,0,1,0},      // T
        {1,0,0,1,1,1},      // J
        {0,0,1,1,1,1},      // L
        {0,1,1,1,1,0},      // S
        {1,1,0,0,1,1}       // Z
        
    };
    
    
};




#endif  // TETRIMINO_H_INCLUDED
