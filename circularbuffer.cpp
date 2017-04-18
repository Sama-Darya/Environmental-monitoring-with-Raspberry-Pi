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
Circularbuffer::~Circularbuffer() { delete [] queue; }
void Circularbuffer::Insert(int v) {
        queue[tail] = v;
        tail = (tail+1) % cap;
        buffer_counter++;
    }
int Circularbuffer::Remove() {
    /* Return data before removing it from the buffer. */
        int t = queue[head];
        head = (head + 1) % cap;
        return t;
    }
int Circularbuffer::Empty() {return (head == tail ); }
int Circularbuffer::Full() {return (head==(tail+1)%cap);}
int Circularbuffer::Length(void) const { return buffer_counter; }
