#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <malloc.h>
#include "settings.h"


#if(ARCH==INTEL)
#include <xmmintrin.h>
#endif

#if(ARCH==ARM)
#include <arm_neon.h>
#endif


#include "schedule.h"
#include "core.h"
#include "LinkedList.h"

using namespace std;

volatile int done[MAXCORES] = {0,0,0,0,0,0,0,0};

/* Task types*
 * 1: -Bitbyte (bit manipulation)
 * 2: -Memory+cache
 * 3: -Branch
 * 4: -Logic (and, or)
 * 5: -Integer add
 * 6: -Floating point mult.
 * 7: -SIMD double precision mult.
 * 8: -Reserved
 * 9: -Reserved
 * 10: -Reserved
 * 11: -Reserved
 */

volatile double dmemBuf[MEM_SIZE];

void *TimerTask(void* arg) { //Arguments: "ID", "Time"
    int *info = (int*)arg;
    //cout << "TIMER: id " << info[0] << " time " << info[1] << endl;
    done[info[0]] = 0;
    //cout << "TIMER: done is now " << done[info[0]] << endl;
    usleep(1000*info[1]);
    done[info[0]] = 1;
    //cout << "TIMER: done is now " << done[info[0]] << endl;
//    return NULL;
}

void IdleTask(int d){
#if(VERBOSE >=1)
    cout << "Starting task type 0" << endl;
#elif(VERBOSE == 0)
    cout << "0" << endl;
#endif
    //cout << "delay " << d << endl;
    while(--d >= 0){
        usleep(1000); //Sleep one millisecond
    }
#if(VERBOSE >= 2)
    cout << "Task type 0 done!" << endl;
#endif
}

void TaskType1(int _core){ //bitbyte intense
#if(VERBOSE >= 1)
    cout << "Starting task type 1 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "1" << endl;
#endif
    volatile int x = 0x1ff;
    volatile int y;
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type1 done!" << endl;
#endif
}

void TaskType2(int _core){ //memory and cache intense
#if(VERBOSE >= 1)
    cout << "Starting task type 2 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "2" << endl;
#endif
    int index = 0;
    while (done[_core]==0) {

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
#if(VERBOSE >= 2)
    cout << "Task type 2 done!" << endl;
#endif
}

#if(ARCH==ARM)
void TaskType3(int _core){ //Branch heavy
#if(VERBOSE >= 1)
    cout << "Starting task type 3 on core "<< _core << endl;
#elif(VERBOSE == 0)
    cout << "3" << endl;
#endif
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 3 done!" << endl;
#endif
}
#elif(ARCH == INTEL)
void* __attribute__((optimize("O0"))) TaskType3(int _core){
#if(VERBOSE >= 1)
    cout << "Starting task type 3 on core "<< _core << endl;
#elif(VERBOSE == 0)
    cout << "3" << endl;
#endif
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 3 done!" << endl;
#endif
}
#endif

#if(ARCH==ARM)
void TaskType4(int _core){ //Logic intense
#if(VERBOSE >= 1)
    cout << "Starting task type 4 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "4" << endl;
#endif
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 4 done!" << endl;
#endif

}
#elif(ARCH == INTEL)
//foo 16 ok
void TaskType4(int _core){
#if(VERBOSE >= 1)
    cout << "Starting task type 4 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "4" << endl;
#endif
    volatile int x;
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 4 done!" << endl;
#endif
}
#endif


#if(ARCH==ARM)
void TaskType5(int _core){ //Integer add intense
#if(VERBOSE >= 1)
    cout << "Starting task type 5 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "5" << endl;
#endif
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 5 done!" << endl;
#endif
 }
#elif(ARCH == INTEL)
void TaskType5(int _core){
#if(VERBOSE >= 1)
    cout << "Starting task type 5 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "5" << endl;
#endif
        volatile int x = 0, y = 1, z = 3;
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 5 done!" << endl;
#endif
}
#endif
#if(ARCH==ARM)
void TaskType6(int _core){ //Floating point mul intense
#if(VERBOSE >= 1)
    cout << "Starting task type 6 on core "<< _core << endl;
#elif(VERBOSE == 0)
    cout << "6" << endl;
#endif
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 6 done!" << endl;
#endif
}
#elif(ARCH == INTEL)
void TaskType6(int _core){ //Floating point mul intense
#if(VERBOSE >= 1)
    cout << "Starting task type 6 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "6" << endl;
#endif
    volatile double x = 1.123, y = 0.23, z = 6.32;
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 6 done!" << endl;
#endif
}
#endif

#if(ARCH==ARM)
void TaskType7(int _core){ //SIMD mult intense
#if(VERBOSE >= 1)
    cout << "Starting task type 7 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "7" << endl;
#endif
    while (done[_core]==0) {
        asm volatile (
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            "vrsqrtsq.f32    q2, q3, q0\n"
            : // no output
            :  // no input
            : "memory", "d0", "d1" //clobber
            );
    }
#if(VERBOSE == 2)
    cout << "Task type 7 done!" << endl;
#endif
}
#elif(ARCH == INTEL)
void TaskType7(int _core){
#if(VERBOSE >= 1)
    cout << "Starting task type 7 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "7" << endl;
#endif
    volatile __m128d vec1;
    volatile __m128d vec2;
    volatile __m128d vec3;
    while (done[_core]==0) {
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
#if(VERBOSE >= 2)
    cout << "Task type 7 done!" << endl;
#endif
}
#endif
void* __attribute__((optimize("O0"))) TaskType8(int _core){

register float32x4_t fr;
register float32x4_t fr2;
register float32x4_t fr3;
register float32x4_t fr4;
register float32x4_t fr5;
register float32x4_t fr6;
register float32x4_t fr7;
register float32x4_t fr8;
register float32x4_t fr9;
register float32x4_t fr10;
register float32x4_t fr1;
register float32x4_t fr12;
register float32x4_t fr13;
register float32x4_t fr14;
register float32x4_t fr15;
register float32x4_t fr16;
register float32x4_t fr17;
register float32x4_t fr18;
register float32x4_t fr19;
register float32x4_t fr20;
static float32x4_t fa;
static float32x4_t fb;
static float32x4_t fa2;
static float32x4_t fb2;
static float32x4_t fa3;
static float32x4_t fb3;
static float32x4_t fa4;
static float32x4_t fb4;
static float32x4_t fa5;
static float32x4_t fb5;
static float32x4_t fa6;
static float32x4_t fb6;
static float32x4_t fa7;
static float32x4_t fb7;
static float32x4_t fa8;
static float32x4_t fb8;
static float32x4_t fa9;
static float32x4_t fb9;
static float32x4_t fa10;
static float32x4_t fb10;
static float32x4_t fa11;
static float32x4_t fb11;
static float32x4_t fa12;
static float32x4_t fb12;
static float32x4_t fa13;
static float32x4_t fb13;
static float32x4_t fa14;
static float32x4_t fb14;
static float32x4_t fa15;
static float32x4_t fb15;
static float32x4_t fa16;
static float32x4_t fb16;
static float32x4_t fa17;
static float32x4_t fb17;
static float32x4_t fa18;
static float32x4_t fb18;
static float32x4_t fa19;
static float32x4_t fb19;
static float32x4_t fa20;
static float32x4_t fb20;
fa = vdupq_n_f32(1.0);
fb = vdupq_n_f32(2.0);
fa2 = vdupq_n_f32(3.0);
fb2 = vdupq_n_f32(4.0);
fa3 = vdupq_n_f32(5.0);
fb3 = vdupq_n_f32(6.0);
fa4 = vdupq_n_f32(7.0);
fb4 = vdupq_n_f32(8.0);
fa5 = vdupq_n_f32(9.0);
fb5 = vdupq_n_f32(10.0);
fa6 = vdupq_n_f32(11.0);
fb6 = vdupq_n_f32(12.0);
fa7 = vdupq_n_f32(13.0);
fb7 = vdupq_n_f32(14.0);
fa8 = vdupq_n_f32(15.0);
fb8 = vdupq_n_f32(16.0);
fa9 = vdupq_n_f32(17.0);
fb9 = vdupq_n_f32(18.0);
fa10 = vdupq_n_f32(19.0);
fb10 = vdupq_n_f32(20.0);
fa11 = vdupq_n_f32(21.0);
fb11 = vdupq_n_f32(22.0);
fa12 = vdupq_n_f32(23.0);
fb12 = vdupq_n_f32(24.0);
fa13 = vdupq_n_f32(25.0);
fb13 = vdupq_n_f32(26.0);
fa14 = vdupq_n_f32(27.0);
fb14 = vdupq_n_f32(28.0);
fa15 = vdupq_n_f32(29.0);
fb15 = vdupq_n_f32(30.0);
fa16 = vdupq_n_f32(31.0);
fb16 = vdupq_n_f32(32.0);
fa17 = vdupq_n_f32(33.0);
fb17 = vdupq_n_f32(34.0);
fa18 = vdupq_n_f32(35.0);
fb18 = vdupq_n_f32(36.0);
fa19 = vdupq_n_f32(37.0);
fb19 = vdupq_n_f32(38.0);
fa20 = vdupq_n_f32(39.0);
#if(VERBOSE >= 1)
    cout << "Starting task type 8 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "8" << endl;
#endif
    while (done[_core]==0) {
        fr = vrsqrtsq_f32(fa,fb);
        fr2 = vrsqrtsq_f32(fa2,fb2);
        fr3 = vrsqrtsq_f32(fa3,fb3);
        fr4 = vrsqrtsq_f32(fa4,fb4);
        fr5 = vrsqrtsq_f32(fa5,fb5);
        fr6 = vrsqrtsq_f32(fa6,fb6);
        fr7 = vrsqrtsq_f32(fa7,fb7);
        fr8 = vrsqrtsq_f32(fa8,fb8);
        fr9 = vrsqrtsq_f32(fa9,fb9);
        fr10 = vrsqrtsq_f32(fa10,fb10);

        fr1 = vrsqrtsq_f32(fa11,fb11);
        fr12 = vrsqrtsq_f32(fa12,fb12);
        fr13 = vrsqrtsq_f32(fa13,fb13);
        fr14 = vrsqrtsq_f32(fa14,fb14);
        fr15 = vrsqrtsq_f32(fa15,fb15);
        fr16 = vrsqrtsq_f32(fa16,fb16);
        fr17 = vrsqrtsq_f32(fa17,fb17);
        fr18 = vrsqrtsq_f32(fa18,fb18);
        fr19 = vrsqrtsq_f32(fa19,fb19);
        fr20 = vrsqrtsq_f32(fa20,fb20);

  }
#if(VERBOSE == 2)
  cout << "Task type 8 done!" << endl;
#endif
}
void* __attribute__((optimize("O0"))) TaskType9(int _core){
#if(VERBOSE >= 1)
  cout << "Starting task type 9 on core " << _core << endl;
#elif(VERBOSE == 0)
    cout << "9" << endl;
#endif

  #define SIZE 1
  int m, n, p, q, c, d, k, sum = 0;
  int first[SIZE][SIZE], second[SIZE][SIZE], multiply[SIZE][SIZE];
  m=SIZE;
  n=SIZE;
  while (done[_core]==0) { 

  for (c = 0; c < m; c++)
    for (d = 0; d < n; d++)
	first[c][d]=2;

  p=SIZE;
  q=SIZE;
  if (n != p)
    printf("Matrices with entered orders can't be multiplied with each other.\n");
  else
  {
    for (c = 0; c < p; c++)
      for (d = 0; d < q; d++)
         second[c][d] = 2;
    for (c = 0; c < m; c++) {                                                                                                                          
      for (d = 0; d < q; d++) {                                                                                                                        
        for (k = 0; k < p; k++) {                                                                                                                      
          sum = sum + first[c][k]*second[k][d];                                                                                                        
        }
        multiply[c][d] = sum;                                                                                                                          
        sum = 0;                                                                                                                                       
      }
    }
  }
  }
#if(VERBOSE == 2)
  cout << "Task type 9 done!" << endl;
#endif
}


Schedule::Schedule(int id, Core* obj)
{
   CC = obj;
   ID = id;
}
Schedule::~Schedule()
{

}
Core Schedule::getCore(){
    return *CC;
}
void Schedule::addTaskSchedule(list* l){
    TASKLIST = l;
}
list* Schedule::getTaskSchedule(){
    return TASKLIST;
}

#define SLEEP 10000
/*Recommended to run with nice --19*/
void Schedule::execute(){
//    cout << "number of times " <<this->getTaskSchedule()->getNrItems()<<  endl;
    list::node* t;
    list::node* Temp;
    pthread_t timerthread;
    int arg[2];
    int sret;
    while(this->getTaskSchedule()->getNrItems() > 0){
        t = this->getTaskSchedule()->peekFirst();
        int time = t->metadata.getExecutionTimeMs();
        int freq = t->metadata.getFrequencyKHz();
        int core = t->metadata.getCoreNumber();
        string setfreq = "echo "+std::to_string(freq)+" > /sys/devices/system/cpu/cpu"+std::to_string(core)+"/cpufreq/scaling_setspeed";
        sret = system(setfreq.c_str());    //Set clock frequency for task
        switch (t->metadata.getTaskType()) {
        case 0:
           IdleTask(time);
           Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 1:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
            TaskType1(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 2:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
            TaskType2(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 3:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
            TaskType3(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 4:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
            TaskType4(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 5:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
            TaskType5(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 6:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
            TaskType6(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 7:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
            TaskType7(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 8:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
	    TaskType8(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 9:
	    arg[0] = core;
            arg[1] = time+(SLEEP/1000);  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(SLEEP);
            TaskType9(core);
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;

        default:
	    cout << "Invalid task ID" << endl;
            break;
        }
    }

}
