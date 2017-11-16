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
    heightsForEachCollum.resize(10);
    
    for (int i = 0; i < 10; i ++)
    {
        heightsForEachCollum[i].push_back(498);
    }
    
    
    
    /*
        For the collums that are being used which will be the first set of vectors. Add what the heights are into the heightsforeachcollum[]
        When it goes to delete it searcches through each collum. If one of the values is on the same line it removes it. 
        It then updates the heights of the collums with the largest one in the vector.
     
     
     */

}
DrawTetrimino::~DrawTetrimino()
{

}

void DrawTetrimino::getDimensions(Array <int> xDimensions, Array <int> yDimensions, int type)
{
    
}



void DrawTetrimino::updateDimensions(std::vector <int> xDimensions,std::vector<int> yDimensions, int type) // THIS DOESN'T NEED TO BE A VECTOR.
{
    
    numberOfLinesCleared = 0;
    
    for (int count = 0; count < xDimensions.size(); count ++)
    {
        
        int numberOfLine = (yDimensions[count]/38) - 1;
        xpositionsVector.push_back(xDimensions[count]);
        ypositionsVector.push_back(yDimensions[count]);
        coloursVector.push_back(type);
        lineNumbers.push_back(numberOfLine);    // This number of line will corespond to each the y, x and colour.
                                                // So when a line is deleted all x,y and colours of that same index will be deleted.
        
        numberOfsquaresPerLine[numberOfLine] ++; // increment the counter for the line that each new square is on
        
        
        std::cout << "X positions = " << xpositionsVector[count] << std::endl;
        std::cout << "Y positions = " << ypositionsVector[count] << std::endl;
        
    }
    
    
    for (int i = 0 ; i < 20; i ++)
    {
        std::cout << i << " :Number of sqaures per line = " << numberOfsquaresPerLine[i] << std::endl;
    }
    
    // std::cout << "Number of total squares before = " << xPositions.size() << std::endl;
    
    for (int count = 0; count < 20; count ++) // remove line
    {
        if (numberOfsquaresPerLine[count] == 10)
        {
 
            numberOfLinesCleared ++;
            std::cout << "Line deleted" << std::endl;
            
            int lineCounter = 0;
            
            for (int i = 0; i < xpositionsVector.size() ; i ++) // look through every element
            {
                
                if (lineNumbers[i] == count)    // if the sqaure is on this line
                {
                    
                    xpositionsVector[i] = -1;
                    ypositionsVector[i] = -1;
                    coloursVector[i] = -1;
                    lineNumbers[i] = -1;
                    repaint();
                    lineCounter ++;
                }
            }
            
            std::cout << lineCounter << " :Lines deleted"  << std::endl;
            
            for (int i = xpositionsVector.size() - 1; i >=0 ; i --) // look through every element
            {
                if (lineNumbers[i] == -1)    // if the sqaure is on this line
                    {
            
                    xpositionsVector[i] = xpositionsVector.back();
                    xpositionsVector.pop_back();
                    ypositionsVector[i] = ypositionsVector.back();
                    ypositionsVector.pop_back();
                    coloursVector[i] = coloursVector.back();
                    coloursVector.pop_back();
                    lineNumbers[i] = lineNumbers.back();
                    lineNumbers.pop_back();
                    repaint();
                                
                    }
                }
            
            
            
            
            
//            for (int i = xpositionsVector.size() - 1; i >=0 ; i --) // look through every element
//            {
//                if (lineNumbers[i] == count)    // if the sqaure is on this line
//                {
//
//                    xpositionsVector[i] = xpositionsVector.back();
//                    xpositionsVector.pop_back();
//                    ypositionsVector[i] = ypositionsVector.back();
//                    ypositionsVector.pop_back();
//                    coloursVector[i] = coloursVector.back();
//                    coloursVector.pop_back();
//                    lineNumbers[i] = lineNumbers.back();
//                    lineNumbers.pop_back();
//                    repaint();
//                    
//                }
//            }

            
            for (int counter = count; counter > 0; counter --)    // count is the line that has just been removed
            {
                numberOfsquaresPerLine[counter] = numberOfsquaresPerLine[counter - 1];  // This makes each line equal to the line below it starting from the line that has been removed
            }
            
            numberOfsquaresPerLine[0] = 0; // the top one will always = 0 if a line has been removed.
            
            for (int i = 0; i < ypositionsVector.size(); i ++)
            {
                
                if (ypositionsVector[i] <= count * 38 )
                {
                    ypositionsVector[i] +=38;
                    lineNumbers[i] +=1;
                    repaint();
                }
            }
            
            //std::cout << "Y size after = " <<  yPositions.size() << std::endl;
        }
        
    }
    
//    for (int counter = 0; counter < xPositions.size(); counter ++)
//    {
//        std::cout << counter << ": Y positions = " << yPositions[counter]/38 << std::endl;
//        std::cout << counter << ": X positions = " << xPositions[counter]/38 << std::endl;
//    }
    
    
    
    //  std::cout << "Number of total squares after = " << xPositions.size() << std::endl;
}

int DrawTetrimino::getNumberOflinesCleared()
{
    std::cout << "Number of liens cleared: " << numberOfLinesCleared << std::endl;
    return numberOfLinesCleared;
}

void DrawTetrimino::paint(Graphics& g)
{
       // std::cout << "X SIZE = " << xPositions.size() << std::endl;

//    if (drawNew == 1)
//    {
//        std::cout << "DRAW " << std::endl;
    
        for (int count = 0; count < xpositionsVector.size(); count ++)
        {
            g.setColour(tetriminoColorus[coloursVector[count]]);
            g.drawRect(xpositionsVector[count], ypositionsVector[count], 38, 38);
            g.fillRect(xpositionsVector[count], ypositionsVector[count], 38, 38);
            
//         
//            std::cout << "Y positions = " << yPositions[count] << std::endl;
//            std::cout << "X positions = " << xPositions[count] << std::endl;
        }

 
}


