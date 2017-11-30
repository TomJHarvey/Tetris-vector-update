/*
 ==============================================================================
 
 Tetrimino.cpp
 Created: 23 Oct 2017 1:20:09pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "Tetrimino.h"

Tetrimino::Tetrimino()
{
    
    

}

Tetrimino::~Tetrimino()
{
    
    
}

void Tetrimino::setType(int type, int size)
{
    typeSelect = type;          // set the type
    squareSize = size;          // the square size can vary depending on if its a playing piece or as a hold or next piece
    rotateCounter = 0;
    
    if (typeSelect == 0 || typeSelect == 1)
    {
        typeOfTetriminoForLoopSize = 4;
    }
    else
    {
        typeOfTetriminoForLoopSize = 6;
    }
    
    if (typeSelect != 1)        // if this is not an o piece
    {
        rotateCounter = 0;
        firstRotation = true;
        rotateShape(typeSelect);    // the first time rotate shape is called, it draws the shape
    }
    
    else                            // This sets the positions for the o piece as it will never change.
    {
        for (int i = 0; i < 4; i ++)
        {
            xPosition[i] = oXdimensions[i];
            yPosition[i] = oYdimensions[i];
        }
    }

}
void Tetrimino::getGridInformation(std::vector<std::vector <int >> gridValues, int tetriminoXposition, int tetriminoYposition)
{
    gridValuesCopy = gridValues;                    // This copy contains all the infromtation for where sqauares are and what type they are
    firstRotation = false;
    tetriminoXpositionCopy = tetriminoXposition;    // The current X and Y position of the tetrimino is copied in
    tetriminoYpositionCopy = tetriminoYposition;
}

bool Tetrimino::rotateShape(int type)
{
    setPositionOfRotatedSqaures();          // The x and y positions of each sqaure in the rotated piece are set into temporary variables.
    
    if (firstRotation == true)              // if this the first time
    {
        addCordinatesForThreeByTwoShapes(); // The temporary variables are then copied into the permentant x and y cordiantes for each of the 4 sqaures that make up a shape
        rotateCounter ++;
    }
    
    else                                    // if this is not the first time
    {
        if (checkForRotatedShapeHittingOtherSqaures() == false) // if the shape is rotated will it hit a square, this is caclulated using the temporary values calculated in setPositionOfRotatedSqaures()?
        {
            return false;
        }
        
        addCordinatesForThreeByTwoShapes(); // The temporary variables are then copied into the permentant x and y cordiantes for each of the 4 sqaures that make up a shape
        rotateCounter ++;
    }
    
    if (rotateCounter == 4) // If all rotations are complete this is reset
    {
        rotateCounter = 0;
    }
    
    repaint();
    return true;
}


void Tetrimino::setPositionOfRotatedSqaures()
{
    /*
      
     For all shapes apart from the i block and the o block they are made up of a 3 x 2 grid.
     Each shape is only four squares, so this leaves two blank.
     This function sets the cordinates for each of the 6 squares once a rotation has taken place.
     The static pointer means that this axis is the smaller (the 2) from the 3 X 2 grid.
     When calculating the shape the axis that is static remains at the same position for the first three squares calculated then moves to a consecutive second position for the next three squares.
     The moving pointer means that this axis is the bigger (the 3) from the 3 X 2 grid.
     When caclculating the shape the moving axis is at three different consecutive positions for the first three squsres.
     Then for the next three squares it resets and repeats itself and does the same three positions.
     These two working together draws a 3X2 grid.
     
     The i block doesn't follow this pattern however the pointers are called static and moving so it can match up with the naming for the other shapes.
     
     */
    
    
    int rowIncrement = 0;
    int increment = xOrYstartPos[rotateCounter];
    int* xOrYpointerStatic = nullptr;
    int* xOrYpointerMoving = nullptr;
    
    if (rotateCounter == 0 || rotateCounter == 2)   // if its flat/ a wider piece
    {
        xOrYpointerStatic = yPositionCopy;
        xOrYpointerMoving = xPositionCopy;
        
    }
    else                                            // if its a taller rotation
    {
        xOrYpointerStatic = xPositionCopy;
        xOrYpointerMoving = yPositionCopy;

    }
    
    if (typeSelect != 0)
    {
        for (int count = 0; count < 6; count ++ )   // Writes the cordiantes for each sqaure
        {
            
            if (count == 3)                                    // Re sets the row or collum that it is counting through
            {
                rowIncrement = (rotateCounter + 1);             // Choses the next value for the row select array
                increment = xOrYstartPos[rotateCounter];
            }
            
            xOrYpointerStatic[count] = rowSelect[rotateCounter + rowIncrement];
            xOrYpointerMoving[count] = xOrYcordintates[increment];
            increment += xOrYdirection[rotateCounter];
        }
    }
    
    else
    {

            for (int i = 0; i < 4; i ++)                     
            {
                if (rotateCounter == 0 || rotateCounter == 2)
                {
                    xOrYpointerMoving[i] = iXdimensionsFlat[i];
                    xOrYpointerStatic[i] = iYdimensionsFlat[i];
                }
                else
                {
                    xOrYpointerMoving[i] = iYdimensionsStanding[i];
                    xOrYpointerStatic[i] = iXdimensionsStanding[i];
                }
            }
    }
    
    xOrYpointerStatic = nullptr;
    xOrYpointerMoving = nullptr;
}
bool Tetrimino::checkForRotatedShapeHittingOtherSqaures()
{
    int yValue = 0;
    int xValue = 0;
    
    for (int i = 0; i < typeOfTetriminoForLoopSize ; i ++)
    {
        if (tetriminoSquaresChecker[typeSelect][i] == 1) // If there is a sqaure at this position
        {
            yValue = (yPositionCopy[i] + tetriminoYpositionCopy) / 38;
            xValue = ((xPositionCopy[i] + tetriminoXpositionCopy) / 38 ) - 3;
            
            if (yValue >= 21 || yValue <= -1 || gridValuesCopy[yValue][xValue] != -1 || xValue >= 10 || (xPositionCopy[i] + tetriminoXpositionCopy) >= 494 )  // fix this and find the problem earlier for the yvalues == to 21 and -1
            {
                return false; // piece wont rotate
            }
        }
    }
    
    return true;
}

void Tetrimino::addCordinatesForThreeByTwoShapes()
{
    int j = 0;
    for (int i = 0 ; i < typeOfTetriminoForLoopSize; i ++)
    {
        if (tetriminoSquaresChecker[typeSelect][i] == 1) // If there is a sqaure at this position set the position of the sqaures.
        {
            xPosition[j] = xPositionCopy[i];
            yPosition[j] = yPositionCopy[i];
            j++;
        }
    }
}

std::vector <int> Tetrimino::returnXorYPositions(int tetriminoXorYPosition, int widthOrHeight, int type)
{
    int* XorYpositionsPointer = nullptr;
    std::vector<int> XorYpositions;
    
    if (type == 0)
    {
        XorYpositionsPointer = xPosition;
    }
    else
    {
        XorYpositionsPointer = yPosition;
    }
    
    for (int count = 0; count < 4; count ++)
    {
        XorYpositions.push_back(XorYpositionsPointer[count] + tetriminoXorYPosition);
    }
    
    XorYpositionsPointer = nullptr;
    return XorYpositions;
}


void Tetrimino::paint(Graphics& g)
{
    g.setColour(tetriminoColorus[typeSelect]);

    for (int i = 0; i < 4; i ++)
    {
        g.drawRect(xPosition[i]/squareSize, yPosition[i]/squareSize, 38/squareSize, 38/squareSize);
        g.fillRect(xPosition[i]/squareSize, yPosition[i]/squareSize, 38/squareSize, 38/squareSize);
    }
    
}
