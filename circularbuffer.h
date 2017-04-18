//
//  circularbuffer.h
//  Circularbuffer
//
//  Created by Treasure Nkawu on 16/04/2017.
//  Copyright © 2017 Treasure Nkawu. All rights reserved.
//

#ifndef circularbuffer_h
#define circularbuffer_h
#define BUFFERSIZE 256

class Circularbuffer{
    private:
        double *queue;
        int cap,head,tail;
    public:
    int buffer_counter;
    Circularbuffer(int s=BUFFERSIZE);
    ~Circularbuffer();
    void Insert(int v);
    int Remove();
    int Empty();
    int Full();
    int Length(void) const;
};

#endif /* circularbuffer_h */
