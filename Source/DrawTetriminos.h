/*
  ==============================================================================

    DrawTetriminos.h
    Created: 7 Nov 2017 2:38:08pm
    Author:  Thomas Harvey

  ==============================================================================
*/

#ifndef DRAWTETRIMINOS_H_INCLUDED
#define DRAWTETRIMINOS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
using std::vector;
using std::cout;

class DrawTetrimino: public Component
{
public:
    
    DrawTetrimino();
    ~DrawTetrimino();
    bool updateDimensions(std::vector <int> xDimensions,std::vector<int> yDimensions, int type);
    void updateGrid(vector<vector <int>> &gridValuesReference);
    void paint (Graphics&) override;
    
private:
    
//    Array<int> xPositions;
//    Array<int> yPositions;
//    Array<int> colour;
    
    std::vector <int> xpositionsVector;
    std::vector <int> ypositionsVector;
    std::vector <int> coloursVector;
    std::vector <int> lineNumbers;
    
    
    vector<vector <int>> gridValues;
    
    std::vector<std::vector <int>> heightsForEachCollum;

    
    int numberOfsquaresPerLine[20] = {0};   // This is how many blocks are per line. Once this is full a line will be cleared and this will be reset.
    int valueOfSquaresPerLine[20][10] = {0};
    int numberOfLinesCleared = 0;
    
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
    
    int drawNew = 0;
    
    
};

#endif  // DRAWTETRIMINOS_H_INCLUDED
