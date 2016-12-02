#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <malloc.h>


//g++ -O2 bitbyte.cpp -o bitbyte

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

int main(){ //bitbyte intense
    cout << "Starting task type 1" << endl;
    volatile int x = 0x1ff;
    volatile int y;
    while (1) {
#if(ARCH == ARM)
        asm volatile (
        "ubfx   r0, r1, #3, #4\n"
        "ubfx   r0, r1, #2, #6\n"
        "ubfx   r0, r1, #0, #15\n"
        "ubfx   r1, r0, #6, #4\n"
        "ubfx   r1, r0, #8, #10\n"
        "ubfx   r0, r1, #3, #4\n"
        "ubfx   r0, r1, #2, #6\n"
        "ubfx   r0, r1, #0, #15\n"
        "ubfx   r1, r0, #6, #4\n"
        "ubfx   r1, r0, #8, #10\n"
        "ubfx   r0, r1, #3, #4\n"
        "ubfx   r0, r1, #2, #6\n"
        "ubfx   r0, r1, #0, #15\n"
        "ubfx   r1, r0, #6, #4\n"
        "ubfx   r1, r0, #8, #10\n"
        "ubfx   r0, r1, #3, #4\n"
        "ubfx   r0, r1, #2, #6\n"
        "ubfx   r0, r1, #0, #15\n"
        "ubfx   r1, r0, #6, #4\n"
        "ubfx   r1, r0, #8, #10\n"
        : // no output
        :  // no input
        : "memory", "r0", "r1" //clobber
        );
#elif(ARCH == INTEL)
        y = x & 0xf;
        y = x & 0xff;
        y = x & 0x1;
        y = x & 0x1ff;
        y = x & 0x6;
        y = x & 0xf;
        y = x & 0xff;
        y = x & 0x1;
        y = x & 0x1ff;
        y = x & 0x6;
        y = x & 0xf;
        y = x & 0xff;
        y = x & 0x1;
        y = x & 0x1ff;
        y = x & 0x6;
        y = x & 0xf;
        y = x & 0xff;
        y = x & 0x1;
        y = x & 0x1ff;
        y = x & 0x6;
#endif
    }
    cout << "Task type1 done!" << endl;
    return 0;
}