/*
  ==============================================================================

    DrawTetriminos.cpp
    Created: 7 Nov 2017 2:38:08pm
    Author:  Thomas Harvey

  ==============================================================================
*/

#include "DrawTetriminos.h"
#include "../JuceLibraryCode/JuceHeader.h"


DrawTetrimino::DrawTetrimino()
{
    
    gridValues.resize(21);                      // Make it hold 21 different vectors, which is one for each line
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        gridValues[i].resize(10);               // Make each of the vectors have 10 items which makes each line 10 across.
    }
    
    for (int i = 0; i < gridValues.size(); i ++)
    {
        for (int j = 0; j < gridValues[i].size(); j ++)
        {
            gridValues[i][j] = -1;           // Sets each piece of the grid equal to 0
        }
    }

}
DrawTetrimino::~DrawTetrimino()
{

}


void DrawTetrimino::updateGrid(vector<vector <int>> &gridValuesReference)
{
    for (int i = 0; i < 21; i ++)
    {
        for (int j = 0; j < 10; j ++)
        {
            gridValuesReference[i][j] = gridValues[i][j];
        }
    }
}

bool DrawTetrimino::updateDimensions(std::vector <int> xDimensions,std::vector<int> yDimensions, int type) // THIS DOESN'T NEED TO BE A VECTOR.
{
    
    bool linesHaveBeenCleared = false;
    
    for (int i = 0; i < 4; i ++)
    {
        int xValue = (xDimensions[i] / 38) - 3;
        int yValue = yDimensions[i]/38;
        
        gridValues[yValue][xValue] = type;
        numberOfsquaresPerLine[yValue] ++;
    }
    
    for (int i = 0; i < 21; i ++)
    {
        
        std::cout << i << ": Number of sqaures per line = " << numberOfsquaresPerLine[i] << std::endl;
        
        if (numberOfsquaresPerLine[i] == 10)
        {
            std::cout << i << ": Number of sqaures per line = " << numberOfsquaresPerLine[i] << std::endl;
            
            numberOfsquaresPerLine[i] = 0;
            for (int j = 0; j < 10; j ++)
            {
                gridValues[i][j] = -1;
            }
            
            for (int k = i; k > 0; k --)
            {
                
                numberOfsquaresPerLine[k] = numberOfsquaresPerLine[k-1];
                for (int l = 0; l < 10; l ++)
                {
                  gridValues[k][l] = gridValues[k - 1][l];
                }
            }
            repaint();
            linesHaveBeenCleared = true;
            
            
            
            
        }
        
    }
    
    
//    for (int i = 0; i < 21; i ++)
//    {
//        std::cout << "LINE = : " << i << std::endl << std::endl;
//        
//        for (int j = 0; j < 10; j ++)
//        {
//            std::cout << "GRID VALUES = " << gridValues[i][j] << std::endl;
//        }
//        
//    }
   
    repaint();
    
    if (linesHaveBeenCleared == false)
    {
        return false;
    }
    else
    {
        return true;
    }

}

void DrawTetrimino::paint(Graphics& g)
{
    for (int i = 0; i < 21; i ++)
    {
        for (int j = 0; j < 10; j ++)
        {
            if (gridValues[i][j] != -1)
            {
                g.setColour(tetriminoColorus[gridValues[i][j]]);
                g.drawRect((j + 3) * 38, i*38, 38, 38);
                g.fillRect((j + 3) * 38, i*38, 38, 38);
            }
        }
    }
}


