#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <malloc.h>


//g++ -O2 intadd.cpp -o intadd

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
int main(){ //Integer add intense
    while (1) {
        asm volatile (
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                "add	r3, r2, #1\n"
                : // no output
                :  // no input
                : "memory", "r2", "r3" //clobber
                );
    }
    cout << "Task type5 done!" << endl;
    return 0;
 }
#elif(ARCH == INTEL)
int main(){
    cout << "Starting task type 5" << endl;
        volatile int x = 0, y = 1, z = 3;
    while (1) {
            x+=1;
            y+=2;
            z+=3;
            x+=4;
            y+=5;
            z+=6;
            x+=7;
            y+=8;
            z+=9;
            x+=10;
            y+=1;
            z+=2;
            x+=3;
            y+=4;
            z+=5;
            x+=6;
            y+=7;
            z+=8;
            x+=9;
            y+=10;
    }
    cout << "Task type5 done!" << endl;
    return 0;
}
#endif