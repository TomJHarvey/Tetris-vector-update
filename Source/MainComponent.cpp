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
    setSize (608, 798);
   
    holdLabel.setText("Hold", sendNotification);
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
    
    threadCounter.startCounter();   // Starts the counter// in the future select the level to chnage the speed
    threadCounter.setSpeed(100); // Sets the speed for the first level
    threadCounter.setListener(this);

    addAndMakeVisible(tetrimino);
    
    setWantsKeyboardFocus(true);
    addKeyListener(this);
    getTopLevelComponent()->addKeyListener(this);
    

    for (int count = 0; count < 10; count ++)   // Set each height of each collum to the maxinum height
    {
        currentHeightOfColumn[count] = 798;
    }
    
    addAndMakeVisible(drawTetrimino);           // Make the tetrimino piece visible
    
}

MainContentComponent::~MainContentComponent()
{
   
    
}

void MainContentComponent::counterChanged (int counterValue_)
{
  
    if (isPieceFalling == false)
    {
        isPieceFalling = true;
        pieceHasLanded = false;
        numberOfSquaresFallen = 0;                                      // How many squares the piece has fallen is reset each time its a new piece
        tetriminoType = randomTetrimino.nextInt(7);                     //  a random tetrimino is created
        rotationCounter = 0;
        
        tetriminoType = 0;
        
        if (tetriminoType != 0 || tetriminoType != 1)                   // Checks to see if the component has the correct width and height
        {
            if (tetriminoSizes[tetriminoType][0] == 76)                 // If they are incorrect they are swapped back to the default width and height
            {
                int sizeCopy = tetriminoSizes[tetriminoType][0];
                tetriminoSizes[tetriminoType][0] = tetriminoSizes[tetriminoType][1];
                tetriminoSizes[tetriminoType][1] = sizeCopy;
            }
        }
        
        tetrimino.setBounds(304, 0, tetriminoSizes[tetriminoType][0], tetriminoSizes[tetriminoType][1]);
        tetrimino.setType(tetriminoType);
        currentTetriminoPosition = 304; // default to the middle
        updateRows();
        
        // reset fallcount
    }
    
   else if (isPieceFalling == true) // If there is room for it to fall
    {
        numberOfSquaresFallen ++;
        tetrimino.setBounds(currentTetriminoPosition, numberOfSquaresFallen * 38, tetriminoSizes[tetriminoType][0], tetriminoSizes[tetriminoType][1]);
        updateRows();
    }

    
    checkAvailableSpaceForTetrimino(); // each time it falls check to see if it has made the limit.
    
    if (pieceHasLanded == true)
    {
        isPieceFalling = false;
    }

}


bool MainContentComponent::keyPressed(const KeyPress &key, Component* originatingComponent )
{
    
    //DBG(key.getKeyCode());
    // Move the tetrimino to the left
    if (key.getKeyCode() == 63234)
    {
        if (currentTetriminoPosition >= 152)
        {
            currentTetriminoPosition -= 38;
            tetrimino.setBounds(currentTetriminoPosition, numberOfSquaresFallen * 38, tetriminoSizes[tetriminoType][0], tetriminoSizes[tetriminoType][1]);
        }
        
        updateRows();
    }
    
    // Move the tetrimino to the right
    else if (key.getKeyCode() == 63235)
    {
        if (currentTetriminoPosition + tetriminoSizes[tetriminoType][0] <= 456)
        {
            currentTetriminoPosition += 38;
            tetrimino.setBounds(currentTetriminoPosition, numberOfSquaresFallen * 38, tetriminoSizes[tetriminoType][0], tetriminoSizes[tetriminoType][1]);
        }
        updateRows();
    }
    
    else if (key.getKeyCode() == 63233 && tetrimino.getY() + tetrimino.getHeight() <= 7 )
    {
        if (currentTetriminoPosition + tetriminoSizes[tetriminoType][0] <= 456)
        {
            numberOfSquaresFallen ++;
            tetrimino.setBounds(currentTetriminoPosition, numberOfSquaresFallen * 38, tetriminoSizes[tetriminoType][0], tetriminoSizes[tetriminoType][1]);
        }
        updateRows();
    }
    
    // Rotate the shape
    else if (key.getKeyCode() == 63232)
    {
        if (tetriminoType != 1)
        {
            int xOffset = 0;
            int yOffset = 0;
            rotationCounter ++;
            
            if (rotationCounter == 4)
            {
                rotationCounter = 0;
            }
            
            else if (rotationCounter == 1)
            {
                xOffset = 38;
            }
            
            if (rotationCounter == 1 || rotationCounter == 3)
            {
                yOffset = - 38;
            }
            
            int sizeCopy = tetriminoSizes[tetriminoType][0];                        // this swaps the width and the height values around
            tetriminoSizes[tetriminoType][0] = tetriminoSizes[tetriminoType][1];
            tetriminoSizes[tetriminoType][1] = sizeCopy;
            
            // Then the position is updated
            tetrimino.setBounds(currentTetriminoPosition + xOffset, (numberOfSquaresFallen * 38) + yOffset, tetriminoSizes[tetriminoType][0], tetriminoSizes[tetriminoType][1]);
            tetrimino.rotateShape(tetriminoType);         // re draws the shape
            updateRows();
        }
        
    }

}

void MainContentComponent::updateRows()
{
    int blankSpace = 0;
    int blankSpaceIncrement[4] = {0,38,76,114};

    // This is the position of each block relative to the 10x10 grid.
    // The first value starts from the left.
    
    currentPositionOfTetrimino[0] = (tetrimino.getX() - 114) / 38;
    currentPositionOfTetrimino[1] = currentPositionOfTetrimino[0] + 1;
    currentPositionOfTetrimino[2] = currentPositionOfTetrimino[1] + 1;
    currentPositionOfTetrimino[3] = currentPositionOfTetrimino[2] + 1;
    
    if (tetriminoType != 1 && tetriminoType != 0)
    {
        for (int blankSpaceCounter = 0; blankSpaceCounter < tetrimino.getWidth()/38 ; blankSpaceCounter ++ ) // check each bottom square on the x axis
        {
            blankSpace = tetrimino.returnBlankSpace(blankSpaceIncrement[blankSpaceCounter],0);                  // 0 is second argument for the top
            currentTetriminoLimit[blankSpaceCounter] = tetrimino.getY() + tetrimino.getHeight() - blankSpace;
             //std::cout << blankSpaceCounter << ": tetrimino limit = " << currentTetriminoLimit[blankSpaceCounter] << std::endl;
        }
    }
    
    else    // if its i or o
    {
        for (int count = 0; count < tetrimino.getWidth()/38; count ++)
        {
            currentTetriminoLimit[count] = tetrimino.getY() + tetrimino.getHeight();
           // std::cout << count << ": tetrimino limit = " << currentTetriminoLimit[count] << std::endl;
        }
    }
}

void MainContentComponent::updateHeightOfColumns()
{
    int numberOflinesCleared = 0;
    int blankSpace = 0;
    
    if (tetriminoType != 1 && tetriminoType != 0)
    {
        for (int count = 0; count < tetrimino.getWidth()/38; count ++)
        {
            blankSpace = tetrimino.returnBlankSpace(blankSpaceIncrement[count],1);
            //std::cout << "Previous height = " << currentHeightOfColumn[currentPositionOfTetrimino[count]] << std::endl;
            currentHeightOfColumn[currentPositionOfTetrimino[count]] = tetrimino.getY() + blankSpace;
            //std::cout << "Current height = " << currentHeightOfColumn[currentPositionOfTetrimino[count]] << std::endl;
        }
    }
    
    else
    {
        for (int count = 0; count < tetrimino.getWidth()/38; count ++)
        {
             currentHeightOfColumn[currentPositionOfTetrimino[count]] = tetrimino.getY();
        }
    }
    
   numberOflinesCleared = drawTetrimino.getNumberOflinesCleared();
    
    if (numberOflinesCleared > 0)
    {
        for (int count = 0; count < 10; count ++)
        {
            currentHeightOfColumn[count] += (numberOflinesCleared * 38);                            ////////////// ////////////// ////////////// ////////////// ////////////// ////////////// ////////////// ////////////// //////////////
        }
    }
 
}

void MainContentComponent::checkAvailableSpaceForTetrimino()
{
        for (int count = 0; count < tetrimino.getWidth()/38; count ++)
        {
            //std::cout << count << ": current limit =" << currentTetriminoLimit[count] << " Current height of collum = " << currentHeightOfColumn[currentPositionOfTetrimino[count]] << std::endl;
            if (currentTetriminoLimit[count] == currentHeightOfColumn[currentPositionOfTetrimino[count]])
            {
                pieceHasLanded = true;
               // drawTetrimino.getDimensions(tetrimino.returnXpositions(tetrimino.getX(), tetrimino.getWidth()), tetrimino.returnYpositions(tetrimino.getY(), tetrimino.getWidth()), tetriminoType);
                drawTetrimino.updateDimensions(tetrimino.returnXposition(tetrimino.getX(), tetrimino.getWidth()), tetrimino.returnYposition(tetrimino.getY(), tetrimino.getWidth()), tetriminoType);
                updateHeightOfColumns();
                drawTetrimino.repaint();
                
                for (int count = 0; count < 4; count ++)
                {
                    currentTetriminoLimit[count] = 0;
                }
            }
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
