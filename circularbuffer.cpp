//
//  circularbuffer.cpp
//  Circularbuffer
//
//  Created by Treasure Nkawu on 16/04/2017.
//  Copyright © 2017 Treasure Nkawu. All rights reserved.
//


#include "circularbuffer.h"

//Constructor
Circularbuffer::Circularbuffer(int s) {
        cap= s; //capacity
        queue = new double[cap];
        head = 0; tail = 0;
        buffer_counter = 0;
}
//Destructor
Circularbuffer::~Circularbuffer() { delete [] queue; }
void Circularbuffer::Insert(double v) {
        /* Add data into the buffer. */
        queue[tail] = v;
        tail = (tail+1) % cap;
        buffer_counter++;
    }
//change the return from int to double
double Circularbuffer::Remove() {
    /* Return data before removing it from the buffer. */
        //int t = queue[head]; // changed this from int to double, see line below.
        double t = queue[head];
        head = (head + 1) % cap;
        return t;
    }
int Circularbuffer::Empty() {return (head == tail ); } //Check if the buffer is empty
int Circularbuffer::Full() {return (head==(tail+1)%cap);} //Check if the buffer is full
int Circularbuffer::Length(void) const { return buffer_counter; } //Check buffer length
