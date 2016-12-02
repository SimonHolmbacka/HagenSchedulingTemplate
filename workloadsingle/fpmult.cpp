#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <malloc.h>


//g++ -O2 fpmult.cpp -o fpmult

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
int main(){ //Floating point mul intense
    while (1) {
        asm volatile (
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            "fmuld	d24, d26, d23\n"
            : // no output
            :  // no input
            : "memory", "d26", "d23", "d24" //clobber
            );
    }
    cout << "Task type6 done!" << endl;  
    return 0;
}
#elif(ARCH == INTEL)
int main(){ //Floating point mul intense
    cout << "Starting task type 6" << endl;
    volatile double x = 1.123, y = 0.23, z = 6.32;
    while (1) {
        x*=1.121;
        y*=1.122;
        z*=1.123;
        x*=1.124;
        y*=1.125;
        z*=1.126;
        x*=1.127;
        y*=1.128;
        z*=1.129;
        x*=1.120;
        y*=1.121;
        z*=1.122;
        x*=1.123;
        y*=1.124;
        z*=1.125;
        x*=1.126;
        y*=1.127;
        z*=1.128;
        x*=1.129;
        y*=1.120;
    }
    cout << "Task type6 done!" << endl;
    return 0;
}
#endif