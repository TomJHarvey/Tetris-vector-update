/*
 ==============================================================================
 
 Counter.cpp
 Created: 5 Jan 2017 12:43:28pm
 Author:  Thomas Harvey
 
 ==============================================================================
 */

#include "Counter.h"

Counter::Counter(): Thread ("CounterThread")
{
    
    listener = nullptr;
}


Counter::~Counter()
{
    stopThread(500);
    count.set(0);
    
}

void Counter::run()
{
    
    while (!threadShouldExit())
    {
        
        
        uint32 time = Time::getMillisecondCounter();
        
        // calls main component with the updated counter position
        
        if (listener != nullptr)
        {
            const MessageManagerLock mmLock;
            listener->counterChanged (count.get());
        }
        
        isThreadRunning();
        
        // increments the counter based on the current speed
        
        if (count.get() == 0)
        {
            Time::waitForMillisecondCounter (time + 0);
        }
        
        else
        {
            Time::waitForMillisecondCounter (time + counterSpeed.get());
        }
        count.set(count.get() + 1);
  
    }
}



void Counter::startCounter()
{
    // toggles between pausing and starting the thread
    
    if (isThreadRunning() == false)
    {
        startThread();
    }
    
    else
    {
        stopThread(250);
        listener -> resetSequence(0);
    }
}

void Counter::stopCounter()
{
    
    // stops and resets the thread
    
    stopThread(250);
    count.set(0);
    listener -> resetSequence(1);
    
}

int Counter::returnCounter()
{
    return  count.get();
}

void Counter::setCounter(int counterValue_)
{
    count.set(counterValue_);
}

void Counter::setSpeed(int speed)
{
    counterSpeed.set(speed);
}

void Counter::setListener (Listener* newListener)
{
    listener = newListener;
}



