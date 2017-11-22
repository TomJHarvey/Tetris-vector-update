/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"



//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (608, 798);                             // The grid consists of sqaures 38 X 38
   
    holdLabel.setText("Hold", sendNotification);    // drawn all lables and text
    addAndMakeVisible(holdLabel);
    nextLabel.setText("Next", sendNotification);
    addAndMakeVisible(nextLabel);
    levelLabel.setText("Level", sendNotification);
    addAndMakeVisible(levelLabel);
    goalLabel.setText("Goal", sendNotification);
    addAndMakeVisible(goalLabel);
    levelNumber.setText("1", sendNotification);
    addAndMakeVisible(levelNumber);
    goalNumber.setText("10", sendNotification);
    addAndMakeVisible(goalNumber);
    
    addAndMakeVisible(tetrimino);               // add the objects
    addAndMakeVisible(drawTetrimino);
    threadCounter.startCounter();               // Starts the counter in the future select the level to chnage the speed
    threadCounter.setSpeed(200);                // Sets the speed for the first level
    threadCounter.setListener(this);
    setWantsKeyboardFocus(true);                // Enable use of the keyboard
    addKeyListener(this);

    currentXpositions.resize(4);                // resize vectors
    currentYpositions.resize(4);
    gridValues.resize(21);                      // Make it hold 21 different vectors, which is one for each line
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        gridValues[i].resize(10);               // Make each of the 21 gridValues vectors have 10 items which makes each line 10 across.
    }
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        for (int j = 0; j < gridValues[i].size(); j ++)
        {
            gridValues[i][j] = -1;              // Sets each piece of the grid equal to -1 so it has no 'tetrimino type'
        }
    }
}

MainContentComponent::~MainContentComponent()
{
   
    
}

void MainContentComponent::counterChanged (int counterValue_)
{
    if (canPieceFallFurther == false) // if the piece can't fall further
    {
        drawTetriminoOnGrid();  // draw the tetrimino
    }
    
    if (isPieceFalling == false)    // if the piece has fallen and been drawn
    {
       createNewPiece();    // create a new piece
    }
    
    else if (isPieceFalling == true) // if there is room for it to fall
    {
        if (tetrimino.getY() + tetrimino.getHeight() <= 760) // If the piece isn't below the grid
        {
            moveTetrimino(38, 0);   // Move the piece down
        }
        else
        {
            canPieceFallFurther = false; // set the piece to unable to fall further
        }
    }

    if (pieceHasLanded == true){
        isPieceFalling = false;
    }
}

void MainContentComponent::createNewPiece()
{
    isPieceFalling = true;                                          // Set the piece to be falling
    pieceHasLanded = false;                                         // Reset the piece to not have landed
    numberOfSquaresFallen = 0;                                      // How many squares the piece has fallen is reset each time its a new piece
    tetriminoType = randomTetrimino.nextInt(7);                     // A random tetrimino is selected
    rotationCounter = 0;                                            // Reset the rotation counter
    currentTetriminoXposition = 304;                                // Reset the piece to the middle
    //tetriminoType = 4;                                            // Set type for testing purposes
    
    if (tetriminoType != 0 || tetriminoType != 1)                   // Checks to see if the component has the correct default width and height
    {
        if (tetriminoWidthAndHeight[tetriminoType][0] == 76)        // If they are incorrect they are swapped back to the default width and height
        {
            int sizeCopy = tetriminoWidthAndHeight[tetriminoType][0];
            tetriminoWidthAndHeight[tetriminoType][0] = tetriminoWidthAndHeight[tetriminoType][1];
            tetriminoWidthAndHeight[tetriminoType][1] = sizeCopy;
        }
    }
    
    tetrimino.setBounds(currentTetriminoXposition, 0, tetriminoWidthAndHeight[tetriminoType][0], tetriminoWidthAndHeight[tetriminoType][1]);  // The tetrimino piece's position is set to the default
    tetrimino.setType(tetriminoType);                                                      // The type is selected and in tetriminos paint function the piece is drawn.
    currentXpositions = tetrimino.returnXposition(tetrimino.getX(), tetrimino.getWidth()); // When a piece is created the 4 sqaures need to be added to the array in the position they are at relative to the main screen.
    currentYpositions = tetrimino.returnYposition(tetrimino.getY(), tetrimino.getWidth());
}


void MainContentComponent::moveTetrimino(int downIncrement, int leftOrRightIncrement)
{
    int yValue = 0;
    int xValue = 0;
    bool tetriminoCanMove = true;
    
    for (int i = 0; i < 4; i ++)
    {
        xValue = ((currentXpositions[i] / 38) - 3) + (leftOrRightIncrement/38);
        yValue = (currentYpositions[i] / 38) + (downIncrement/38);
        
        if (yValue == 21) {
            tetriminoCanMove = false;                       // this means that the value has exceeded the grid so it can't move any further
            break;
        }
        
        if (gridValues[yValue][xValue] != -1){              // if there is a sqaure in the same position the whole piece can't move
            tetriminoCanMove = false;
        }
    }
    
    if (tetriminoCanMove == true)
    {
        currentTetriminoXposition += leftOrRightIncrement;  // move the piece left or right
        numberOfSquaresFallen += downIncrement;             // increase number of sqaures fallen.
        canPieceFallFurther = true;                         // update the piece to be falling because the piece may not have been able to fall before it was moved (left or right)
        tetrimino.setBounds(currentTetriminoXposition, numberOfSquaresFallen, tetriminoWidthAndHeight[tetriminoType][0], tetriminoWidthAndHeight[tetriminoType][1]);// Apply the updated x or y position
    }

    else
    {
        canPieceFallFurther = false;
    }
    
    currentXpositions = tetrimino.returnXposition(tetrimino.getX(), tetrimino.getWidth());  // Update the x and y positions each time a move has taken place
    currentYpositions = tetrimino.returnYposition(tetrimino.getY(), tetrimino.getWidth());
}

void MainContentComponent::drawTetriminoOnGrid()
{
    bool haveLinesBeenCleared = drawTetrimino.updateDimensions(currentXpositions, currentYpositions, tetriminoType);    // Draws the new sqaures that have just been added
    
    if (haveLinesBeenCleared == false)                      // If no lines were cleared
    {
        int xValue = 0;
        int yValue = 0;
        
        for (int i = 0 ; i < 4 ; i ++)
        {
            xValue = ((currentXpositions[i] / 38) - 3);     // The x position is scaled into a number from 0 - 9
            yValue = (currentYpositions[i] / 38);           // The y position is scaled into a number between 0 - 21
            gridValues[yValue][xValue] = tetriminoType;     // The grid values for these positions are now updated so a block is in this position. The type determines the colour.
        }
    }
    
    else
    {
        drawTetrimino.updateGrid(gridValues);               // If a 1 or more lines have been cleared the new positions in the grid are updated and moved in the vector.
    }
    
    isPieceFalling = false;                                 // A new piece can now be created once it has been drawn
    canPieceFallFurther = true;
}

bool MainContentComponent::keyPressed(const KeyPress &key, Component* originatingComponent )
{
    DBG(key.getKeyCode());
    
    if (key.getKeyCode() == 63234)                              // Move tetrimino to the left
    {
        if (currentTetriminoXposition >= 152){
            moveTetrimino(0, -38);
        }
    }
    
    else if (key.getKeyCode() == 63235)                         // Move the tetrimino to the right
    {
        if (currentTetriminoXposition + tetriminoWidthAndHeight[tetriminoType][0] <= 456){
            moveTetrimino(0, 38);
        }
    }
    
    else if (key.getKeyCode() == 63233)                         // Move tetrimino down
    {
        if (tetrimino.getY() + tetrimino.getHeight() <= 760){   // If the piece is not outside of the grid
            moveTetrimino(38, 0);
        }
        
        else
            canPieceFallFurther = false;
        
    }
    
    else if (key.getKeyCode() == 32)                            // Hard drop
    {
        while (canPieceFallFurther == true){
            moveTetrimino(38, 0);
        }
    }
    
    else if (key.getKeyCode() == 63232)
    {
        if (tetriminoType != 1) {
            rotateTetrimino();
        }
    }
}


void MainContentComponent::rotateTetrimino()
{
        int xOffset = 0;
        int yOffset = 0;
        rotationCounter ++;
        
        if (rotationCounter == 4)
        {
            rotationCounter = 0;
        }
        
        else if (rotationCounter == 1)  // When a piece rotates it has a different x position for both of the horizontal instances of the rotation, these if loops set this.
        {
            xOffset = 38;
        }
        
        if (rotationCounter == 1 || rotationCounter == 3)
        {
            yOffset = - 38;
        }
        
        tetrimino.getGridInformation(gridValues, tetrimino.getX(), tetrimino.getY());
        
        if (tetrimino.rotateShape(tetriminoType) == true)
        {
            int sizeCopy0 = tetriminoWidthAndHeight[tetriminoType][0];                        // this swaps the width and the height values around
            int sizeCopy1 = tetriminoWidthAndHeight[tetriminoType][1];
            tetriminoWidthAndHeight[tetriminoType][0] = sizeCopy1;
            tetriminoWidthAndHeight[tetriminoType][1] = sizeCopy0;
            tetrimino.setBounds(currentTetriminoXposition + xOffset, (numberOfSquaresFallen) + yOffset, tetriminoWidthAndHeight[tetriminoType][0], tetriminoWidthAndHeight[tetriminoType][1]);
            currentXpositions = tetrimino.returnXposition(tetrimino.getX(), tetrimino.getWidth());  // Update the x and y positions each time a move has taken place
            currentYpositions = tetrimino.returnYposition(tetrimino.getY(), tetrimino.getWidth());
        }
}


void MainContentComponent::resetSequence(int buttonType_)
{
    // this is called when the counter needs to start again, so when the game is over, or if its paused it will start from where it left off
    
    // change the arugments for both counter ones
    
}


void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    g.setColour(Colours::grey);
    
    // The grid
    for (int count = 0; count < 16; count ++)
    {
        g.drawLine(0 + (count * 38), 0 , 0 + (count * 38), getHeight());
    }
    
    for (int count = 0; count < 22; count ++)
    {
        g.drawLine(0, 0 + (count * 38) ,getWidth(),  0 + (count * 38));
    }
    
    // Left side bar
    g.setColour (Colours::aliceblue);
    g.drawRect (0, 0, 114, getHeight());
    g.fillRect (0, 0, 114, getHeight());
    
    // Right side bar
    g.setColour (Colours::aliceblue);
    g.drawRect (getWidth() - 114, 0, 114, getHeight());
    g.fillRect (getWidth() - 114, 0, 114, getHeight());
    
    
    // Thin top bar
    g.setColour(Colours::slategrey);
    g.drawRect (114, 0, 380, 38);
    g.fillRect (114, 0, 380, 38);
    
    // Hold
    g.setColour(Colours::black);
    g.drawRect(17, 40, 80, 80);
    g.fillRect(17, 40, 80, 80);
    
    // Next
    g.drawRect(511, 40, 80, 80);    // Box 1
    g.fillRect(511, 40, 80, 80);
    g.drawRect(522, 140, 60, 60);   // Box 2
    g.fillRect(522, 140, 60, 60);
    g.drawRect(522, 210, 60, 60);   // Box 3
    g.fillRect(522, 210, 60, 60);
    g.drawRect(522, 280, 60, 60);   // Box 4
    g.fillRect(522, 280, 60, 60);
    g.drawRect(522, 350, 60, 60);   // Box 5
    g.fillRect(522, 350, 60, 60);
    
}

void MainContentComponent::resized()
{
    holdLabel.setBounds(38, 25, 80, 10);
    nextLabel.setBounds(532, 25, 80, 10);
    levelLabel.setBounds(19, 550, 80, 10);
    levelNumber.setBounds(19, 565, 100, 60);
    goalLabel.setBounds(19, 630, 80, 10);
    goalNumber.setBounds(19, 645, 100, 60);
    drawTetrimino.setBounds(0, 0, getWidth(), getHeight());

}
