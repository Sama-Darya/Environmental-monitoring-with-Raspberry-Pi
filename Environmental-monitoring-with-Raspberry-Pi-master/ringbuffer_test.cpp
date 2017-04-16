// This is program is to test the ringbuffer.h / ringbuffer.cpp
// class Test is used inside main() to instantiate object for testing.
//  Ringbuffer_cpp
//
//  Created by Treasure Nkawu on 08/04/2017.
//  Copyright © 2017 Treasure Nkawu. All rights reserved.
//  This code was tested running on Xcode (Macbook) with ringbuffer.h and ringbuffer.cpp in
// the same directory.

#include <iostream>

#include <stdlib.h>

#include "ringbuffer.h"

class Test {
  public:
      Test(int num, char sym);
      void PrintOn(std::ostream& out);
  private:
      int fN;
      char fC;

};

Test::Test(int num, char sym)
{
    fN = num; fC = sym;
}
void Test::PrintOn(std::ostream& out)
{
    out << "Job #" << fN << ", activity " << fC << std::endl;
}



int main(void)
{
  int n = 0;
    Test *j = NULL;
    Test *current = NULL;
    Queue theQ;
    for(int done = 0; !done ;) {
        char command;
        std::cout << ">";
        std::cin >> command;
        switch(command) {
            case 'q': done = 1;
                break;
            case 'l' : std::cout << "Queue length now " <<
                theQ.Length() << std::endl;
                break;
            case 'a' :
                j = new Test(++n, (rand() % 25) + 'A');
                std::cout << "Made new job "; j->PrintOn(std::cout);
                if(theQ.Full()) {
                    std::cout << "But couldn't add it to queue"
                    " so got rid of it";
                    std::cout << std::endl;
                    delete j;
                }
                else {
                    theQ.Append(j);
                    std::cout << "Queued" << std::endl;
                }
                j = NULL;
                break;
            case 'g':
                if(theQ.Empty())
                    std::cout << "Silly, the queue is empty"
                    << std::endl;
                else {
                    if(current != NULL)
                        delete current;
                    current = (Test*) theQ.First();
                    std::cout << "Got ";
                    current->PrintOn(std::cout);
                }
                break;
            case 'c':
                if(current != NULL) {
                    std::cout << "Current job is ";
                    current->PrintOn(std::cout);
                }
                else std::cout << "No current job" << std::endl;
                break;
            case '?':
                std::cout << "Commands are:" << std::endl;
                std::cout << "\tq Quit\n\ta Add to queue\t" << std::endl;
                std::cout << "\tc show Current job\n"\
                "tg Get job at front of queue" << std::endl;
                std::cout << "\tl Length of queue\n" << std::endl;
                break;
            default:
                ;
        }
    }

  return EXIT_SUCCESS;
}
