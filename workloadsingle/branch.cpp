#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <malloc.h>


//g++ -O2 branch.cpp -o branch

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
int main(){ //Branch heavy
    cout << "Starting task type 3" << endl;
    while (1) {
    asm volatile (
                "b    l1\n"
                "l1: b l2\n"
                "l2: b l3\n"
                "l3: b l4\n"
                "l4: b l5\n"
                "l5: b l6\n"
                "l6: b l7\n"
                "l7: b l8\n"
                "l8: b l9\n"
                "l9: b l10\n"
                "l10: b l11\n"
                "l11: b l12\n"
                "l12: b l13\n"
                "l13: b l14\n"
                "l14: b l15\n"
                "l15: b l16\n"
                "l16: b l17\n"
                "l17: b l18\n"
                "l18: b l19\n"
                "l19: b l20\n"
                "l20:\n"
                : // no output
                :  // no input
                : // "memory", "q0", "q1" //clobber
                );
    }
    cout << "Task type3 done!" << endl;
    return 0;
}
#elif(ARCH == INTEL)
int __attribute__((optimize("O0"))) main(){
    cout << "Starting task type 3" << endl;
    while (1) {
            l1: goto l20;
            l2: goto l19;
            l3: goto l18;
            l4: goto l17;
            l5: goto l16;
            l6: goto l15;
            l7: goto l14;
            l8: goto l13;
            l9: goto l12;
            l10: goto l11;
            l11: goto ende;
            l12: goto l10;
            l13: goto l9;
            l14: goto l8;
            l15: goto l7;
            l16: goto l6;
            l17: goto l5;
            l18: goto l4;
            l19: goto l3;
            l20: goto l2;
            ende:;
    }
    cout << "Task type3 done!" << endl;
    return 0;  
}
#endif