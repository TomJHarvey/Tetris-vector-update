/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Counter.h"
#include "Tetrimino.h"
#include "DrawTetriminos.h"




//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, public KeyListener, public Counter::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
    void updateRows();
    void updateHeightOfColumns();
    void checkAvailableSpaceForTetrimino();
    void moveTetrimino(int downIncrement, int leftOrRightIncrement);
    
    /** Updates the sequence based on the main thread counter position.*/
    void counterChanged (int counterValue_) override;
    
    /** Resets the sequence when the stop button is pressed.*/
    void resetSequence(int buttonType_) override;
    bool keyPressed(const KeyPress &key, Component* originatingComponent ) override;
    
private:
    
    int lineSpace = 38;
    Path horizontalLines[16];
    Path verticalLines[21];
    
    Label holdLabel;
    Label nextLabel;
    Label levelLabel;
    Label goalLabel;
    Label levelNumber;
    Label goalNumber;
    
    Counter threadCounter;
    Tetrimino tetrimino;
    DrawTetrimino drawTetrimino;

    int tetriminoWidthAndHeight[7][2] = {
        
        {152,38},   // i
        {76,76},    // o
        {114,76},   // t
        {114,76},   // j
        {114,76},   // l
        {114,76},   // s
        {114,76}    // z
    };
    
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
    
    
    

    std::vector <int> currentXpositions;
    std::vector <int> currentYpositions;
    
    int tetriminoCounter = 0;   // the number of the current tetrimino
    int fallingCounter = 0;     // how many sqaures the current tetrimino has fallen
    Random randomTetrimino;     // generates the random tetrimino type
    int tetriminoType = 0;
    int numberOfSquaresFallen = 0;
    int currentTetriminoXposition = 0;
    int rotationCounter = 0; // This is used to offset the tetrimino if it on its 4th rotation.
    
    bool isPieceFalling = false;    // keeps track if a piece is falling
    bool pieceHasLanded = false;    // is true when a piece has landed which resets and creates a new piece.
    bool canPieceFallFurther = true;
    
    int testCounter = 0;
    
    int currentHeightOfColumn[10] = {0};     // For each collum the current height
    int currentPositionOfTetrimino[4] = {0};
    int currentTetriminoLimit[4] = {0};
    int blankSquaresX[2] = {0};
    int blankSquaresY[2] = {0};
    int blankSpaceIncrement[4] = {0,38,76,114};
    
    
    vector<vector <int>> gridValues;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
