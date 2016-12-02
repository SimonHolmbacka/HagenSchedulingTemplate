#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <malloc.h>


//g++ -O2 logic.cpp -o logic

#define ARM 0
#define INTEL 1

#define ARCH INTEL

#if(ARCH==INTEL)
#include <xmmintrin.h>
#endif

#if(ARCH==ARM)
#include <arm_neon.h>
#endif

using namespace std;

#if(ARCH==ARM)
int main(){ //Logic intense
    cout << "Starting task type 4" << endl;
    while (1) {
        asm volatile (
            "and	r4, r3, #1\n"
            "orr	r4, r3, #4\n"
            "and	r4, r3, #15\n"
            "orr	r4, r3, #255\n"
            "and	r4, r3, #1\n"
            "orr	r4, r3, #4\n"
            "and	r4, r3, #15\n"
            "orr	r4, r3, #255\n"
            "and	r4, r3, #1\n"
            "orr	r4, r3, #4\n"
            "and	r4, r3, #15\n"
            "orr	r4, r3, #255\n"
            "and	r4, r3, #1\n"
            "orr	r4, r3, #4\n"
            "and	r4, r3, #15\n"
            "orr	r4, r3, #255\n"
            "and	r4, r3, #1\n"
            "orr	r4, r3, #4\n"
            "and	r4, r3, #15\n"
            "orr	r4, r3, #255\n"
            : // no output
            :  // no input
            : "memory", "r3", "r4" //clobber
            );
    }
    out << "Task type4 done!" << endl;
    return 0;
}
#elif(ARCH == INTEL)
int main(){
    cout << "Starting task type 4" << endl;
    volatile int x;
    while (1) {
        x = x & 1;
        x = x | 4;
        x = x & 0xf;
        x = x & 0xffff;
        x = x | 0xff;
        x = x & 1;
        x = x | 4;
        x = x & 0xf;
        x = x & 0xffff;
        x = x | 0xff;
        x = x & 1;
        x = x | 4;
        x = x & 0xf;
        x = x & 0xffff;
        x = x | 0xff;
        x = x & 1;
        x = x | 4;
        x = x & 0xf;
        x = x & 0xffff;
        x = x | 0xff;
    }
    cout << "Task type4 done!" << endl;
  return 0;
}
#endif