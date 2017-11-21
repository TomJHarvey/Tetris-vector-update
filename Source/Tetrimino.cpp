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
    rotateShape(typeSelect);
    
}

void Tetrimino::rotateShape(int type)
{

    // In each rotation either X or Y is static or moving.
    // Static is if it has only two different values
    // Moving is if it has three different values

    int rowIncrement = 0;
    int increment = xOrYstartPos[rotateCounter];
    int* xOrYpointerStatic = nullptr;
    int* xOrYpointerMoving = nullptr;
    
    if (rotateCounter == 0 || rotateCounter == 2)
    {
        xOrYpointerStatic = yPosition;
        xOrYpointerMoving = xPosition;
    }
    else
    {
        xOrYpointerStatic = xPosition;
        xOrYpointerMoving = yPosition;
    }

    for (int count = 0; count < 6; count ++ )   // Writes the cordiantes for each sqaure
    {
        
                if (count == 3 )                                    // Re sets the row or collum
                {
                    rowIncrement = (rotateCounter + 1);             // Choses the next value for the row select array
                    increment = xOrYstartPos[rotateCounter];
                }
                
                xOrYpointerStatic[count] = rowSelect[rotateCounter + rowIncrement];
                xOrYpointerMoving[count] = xOrYcordintates[increment];
                increment += xOrYdirection[rotateCounter];
    }

    rotateCounter ++;
    
    if (rotateCounter == 4) // If all rotations are complete this is reset
    {
        rotateCounter = 0;
    }

}

int Tetrimino::returnBlankSpace(int xAxisValue, int topOrbottom)
{
    int firstYvalue[2] =    {getHeight() - 38,0};
    int secondYvalue[2] =   {getHeight() - 76,38};

        for (int count = 0; count < 6; count ++)
        {
            if (xPosition[count] == xAxisValue && yPosition[count] == firstYvalue[topOrbottom]) // check each x position to see if its the bottom one starting from the left
            {
                if (tetriminoSquaresChecker[typeSelect][count] == 0)        // if it is, check to see if there is a blank space
                {
                    
                    for (int counter = 0; counter < 6; counter ++)
                    {
                        if (xPosition[counter] == xAxisValue && yPosition[counter]  == secondYvalue[topOrbottom])// checks to see if there is an extra blank space above or below (only for L and J pieces this applies)
                        {
                            if (tetriminoSquaresChecker[typeSelect][counter] == 0)        // if it is, check to see if there is a blank space
                            {
                                return 76;
                            }
                        }
 
                    }
    
                    return 38; // if it doesn't find an space return just one space
                }
            }
        }
    
    return 0;
    
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
