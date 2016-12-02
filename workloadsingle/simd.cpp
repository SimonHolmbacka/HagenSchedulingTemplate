#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <malloc.h>


//g++ -O2 simd.cpp -o simd

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
int main(){ //SIMD mult intense
    cout << "Starting task type 7" << endl;
    while (1) {
        asm volatile (
            "vmul.f64    d0, d1, d2\n"
            "vmul.f64    d0, d1, d2\n"
            "vmul.f64    d0, d1, d2\n"
            "vmul.f64    d0, d1, d2\n"
            "vmul.f64    d0, d1, d2\n"
            "vmul.f64    d0, d1, d2\n"
            "vmul.f64    d0, d1, d2\n"

            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"
            "vmla.f64    d0, d1, d2\n"

            : // no output
            :  // no input
            : "memory", "d0", "d1" //clobber
            );
    }
    cout << "Task type7 done!" << endl;
    return 0;
}
#elif(ARCH == INTEL)
int main(){
    cout << "Starting task type 7" << endl;
    volatile __m128d vec1;
    volatile __m128d vec2;
    volatile __m128d vec3;
    while (1) {
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
       vec3 = _mm_mul_pd(vec1, vec2);
    }
    cout << "Task type7 done!" << endl;
    return 0;
}
#endif