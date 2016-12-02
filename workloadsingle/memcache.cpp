#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <malloc.h>


//g++ -O2 memcache.cpp -o memcache

#define ARM 0
#define INTEL 1

#define ARCH INTEL

#define MEM_SIZE 1000000

#if(ARCH==INTEL)
#include <xmmintrin.h>
#endif

#if(ARCH==ARM)
#include <arm_neon.h>
#endif

using namespace std;
volatile double dmemBuf[MEM_SIZE];
int main(){ //bitbyte intense
    cout << "Starting task type 2" << endl;
    int index = 0;
    while (1) {

        index = (index + 14564) % MEM_SIZE;
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];
        dmemBuf[index] = dmemBuf[index];

    }
    cout << "Task type2 done!" << endl;
    return 0;
}