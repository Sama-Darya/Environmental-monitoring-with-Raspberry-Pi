/*  ringbuffer.cpp
*   The implimantation of the ringbuffer.h class
*
*   Created by Treasure Nkawu on 08/04/2017.
*   Copyright © 2017 Treasure Nkawu. All rights reserved.
*/

#include <stdio.h>
#include <iostream>

#include <stdlib.h>
#include "ringbuffer.h"

//Error Handling
void QueueStuffed()
{
    std::cout << "Queue structure corrupted\n" << std::endl;
    std::cout << "Read instructions next time" << std::endl;
    exit(1);
}



//Constructor: called when instantiating an object
Queue::Queue()
{
    fp = fg = fcount = 0;
    //fp: input index
    //fg: get index
    //fcount: counter
}

//Destructor: clean-up or free memory used by the objects.




//methods
void Queue::Append(void* newitem)
{
    if(Full())
        QueueStuffed();
    fdata[fp] = newitem;
    fp++;
    if(fp == BUFFER_SIZE)
        fp = 0;
    fcount++;
    return;
}

void *Queue::First(void)
{
    if(Empty())
        QueueStuffed();
    void* temp = fdata[fg];
    fg++;
    if(fg == BUFFER_SIZE)
        fg = 0;
    fcount--;
    return temp;
}
