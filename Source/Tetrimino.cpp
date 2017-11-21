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

void Tetrimino::setType(int type)
{
    typeSelect = type;
    rotateCounter = 0;
    firstRotation = true;
    rotateShape(typeSelect);
    
}
void Tetrimino::getGridInformation(std::vector<std::vector <int >> gridValues, int tetriminoXposition, int tetriminoYposition)
{
    gridValuesCopy = gridValues;
    firstRotation = false;
    tetriminoXpositionCopy = tetriminoXposition;
    tetriminoYpositionCopy = tetriminoYposition;
}

bool Tetrimino::rotateShape(int type)
{

    // Every shape apart from i and o are made up of 4 squares and two blank squares.
    // This function keeps the order of the squares and makes it so each square keeps its value when it is rotated.
    
    // In each rotation either X or Y is static or moving.
    // Static is if it has only two different values
    // Moving is if it has three different values
    // For example  X was static and Y was moving, this would mean the same x axis is used for three different y values. Then the next x value along the axis is used for the same three y values.

    int rowIncrement = 0;
    int increment = xOrYstartPos[rotateCounter];
    int* xOrYpointerStatic = nullptr;
    int* xOrYpointerMoving = nullptr;
    
    int xPositionCopy[6] = {0};
    int yPositionCopy[6] = {0};
    
   
    if (rotateCounter == 0 || rotateCounter == 2)
    {
        xOrYpointerStatic = yPositionCopy;
        xOrYpointerMoving = xPositionCopy;
    }
    else
    {
        xOrYpointerStatic = xPositionCopy;
        xOrYpointerMoving = yPositionCopy;
    }

    for (int count = 0; count < 6; count ++ )   // Writes the cordiantes for each sqaure
    {
        
                if (count == 3 )                                    // Re sets the row or collum that it is counting through
                {
                    rowIncrement = (rotateCounter + 1);             // Choses the next value for the row select array
                    increment = xOrYstartPos[rotateCounter];
                }
                
                xOrYpointerStatic[count] = rowSelect[rotateCounter + rowIncrement];
                xOrYpointerMoving[count] = xOrYcordintates[increment];
                increment += xOrYdirection[rotateCounter];
    }

    if (firstRotation == false) // if this is not the first time
    {

        int yValue = 0;
        int xValue = 0;
        
        for (int i = 0; i < 6 ; i ++)
        {
            if (tetriminoSquaresChecker[typeSelect][i] == 1) // If there is a sqaure at this position
            {
                yValue = (yPositionCopy[i] + tetriminoYpositionCopy) / 38;
                xValue = ((xPositionCopy[i] + tetriminoXpositionCopy) / 38 ) - 3;
                
                if (gridValuesCopy[yValue][xValue] != -1 || xPositionCopy[i] + tetriminoXpositionCopy >= 494)
                {
                    return false; // piece wont rotate
                }
                
            }
        }
        
        for (int i = 0 ; i < 6; i ++)
        {
            xPosition[i] = xPositionCopy[i];
            yPosition[i] = yPositionCopy[i];
        }
        
        rotateCounter ++;
        
    }
    
    else
    {
        for (int i = 0 ; i < 6; i ++)
        {
            xPosition[i] = xPositionCopy[i];
            yPosition[i] = yPositionCopy[i];
        }
        rotateCounter ++;
    }

    if (rotateCounter == 4) // If all rotations are complete this is reset
    {
        rotateCounter = 0;
    }
    // delete pointers
    return true;
   
}





std::vector <int> Tetrimino::returnXposition(int tetriminoXposition, int width) // THIS DOESN'T NEED TO BE A VECTOR.
{
    
    std::vector<int> xPositions;
    //int *positions = new int[4];

    if (typeSelect != 0 && typeSelect != 1)
    {
        for (int count = 0; count < 6; count ++)
        {
            if (tetriminoSquaresChecker[typeSelect][count] == 1) // If there is a sqaure at this position
            {
                xPositions.push_back(xPosition[count] + tetriminoXposition);
            }
        }
    }
    
    else
    {
        for (int count = 0; count < 4 ; count ++)
        {
            if (typeSelect == 0)
            {
                if (width == 152 )
                {
                    xPositions.push_back(iXdimensionsFlat[count] + tetriminoXposition);      // sort out i block
                }
                else
                {
                    xPositions.push_back(iXdimensionsStanding[count] + tetriminoXposition);
                }
            }
            else if (typeSelect == 1)
            {
                xPositions.push_back(oXdimensions[count] + tetriminoXposition);
            }
        }
    }
    
    
    return xPositions;
}



std::vector <int> Tetrimino::returnYposition(int tetriminoYposition, int width)
{
    std::vector<int> yPositions;
    
    if (typeSelect != 0 && typeSelect != 1)
    {
        for (int count = 0; count < 6; count ++)
        {
            if (tetriminoSquaresChecker[typeSelect][count] == 1) // If there is a sqaure at this position
            {
                yPositions.push_back(yPosition[count] + tetriminoYposition);
            }
        }
    }
    
    else
    {
        for (int count = 0; count < 4 ; count ++)
        {
            if (typeSelect == 0)
            {
                if (width == 152 )
                {
                    yPositions.push_back(iYdimensionsFlat[count] + tetriminoYposition);      // sort out i block
                }
                else
                {
                    yPositions.push_back(iYdimensionsStanding[count] + tetriminoYposition);
                }
            }
            else if (typeSelect == 1)
            {
                yPositions.push_back(oYdimensions[count] + tetriminoYposition);
            }
        }
    }
    
    
    return yPositions;
    
    
    
}







void Tetrimino::paint(Graphics& g)
{
    
    if (typeSelect == 0 || typeSelect == 1 )
    {
        g.fillAll(tetriminoColorus[typeSelect]); // i or o tetrimino require no shaping here
    }
    
    else // the remaining tetriminos are shaped
    {
        g.setColour(tetriminoColorus[typeSelect]);
        
        for (int count = 0; count < 6; count ++ )
        {
            if (tetriminoSquaresChecker[typeSelect][count] == 1) // If there is a sqaure at this position
            {
                g.setColour(tetriminoColorus[typeSelect]);
                g.drawRect(xPosition[count], yPosition[count], 38, 38);
                g.fillRect(xPosition[count], yPosition[count], 38, 38);
            }
        }
    }
    
    
}
