/*  ringbuffer.h
*   A ring buffer or circular buffer is required to temporary store
*   incoming data from the MCP3424 ADC. The old data is overwritten by new data
*   when the buffer is full.
*   Created by Treasure Nkawu on 08/04/2017.
*   Copyright © 2017 Treasure Nkawu. All rights reserved.
*/

#ifndef ringbuffer_h
#define ringbuffer_h
#define BUFFER_SIZE 512
/*buffer class defination begins below: */ 
class Queue {
public:
    Queue();
    void Append(void* newitem);
    void *First(void);
    int Length(void) const;
    int Full(void) const;
    int Empty(void) const;
private:
    void *fdata[BUFFER_SIZE];
    int fp;
    int fg;
    int fcount;
};
inline int Queue::Length(void) const { return fcount; }
inline int Queue::Full(void) const { return fcount == BUFFER_SIZE; }
inline int Queue::Empty(void) const { return fcount == 0; }



#endif /* end ringbuffer_h */
