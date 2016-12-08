#include <iostream>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include <errno.h>
#include <string>
#include <cstdlib>
#include <arm_neon.h>
#include <stdio.h>

using namespace std;

//g++ -O0 -mfpu=neon speed.cpp -o speed -lpthread
int set_core_nr(int core_id) {
  int num_cores = sysconf(_SC_NPROCESSORS_ONLN);
  if (core_id < 0 || core_id >= num_cores)
      return EINVAL;

   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(core_id, &cpuset);

   pthread_t current_thread = pthread_self();
   return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

#define MEM_SIZE 1000000
volatile double dmemBuf[MEM_SIZE];
void TaskType2(){ //memory and cache intense
    cout << "Starting task type 2" << endl;
    long i = 0;
    int index = 0;
    while (i++ < 99999999) {

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
    cout << "Task type 2 done!" << endl;
}

void TaskType3(){ //Branch heavy
    cout << "Starting task type 3" << endl;
    long i = 0;
    while (i++ < 299999999) {
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
    cout << "Task type 3 done!" << endl;
}

void TaskType6(){ //Floating point mul intense
    cout << "Starting task type 6" << endl;
    long i = 0;
    while (i++ < 999999999) {
        asm volatile (
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            "fmuld      d24, d26, d23\n"
            : // no output
            :  // no input
            : "memory", "d26", "d23", "d24" //clobber
            );
    }
    cout << "Task type 6 done!" << endl;
}

void* __attribute__((optimize("O0"))) TaskType8(){

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

    cout << "Starting task type 8" << endl;
    long i = 0;
    while (i++ < 299999999) {
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
  cout << "Task type 8 done!" << endl;
}


void* __attribute__((optimize("O0"))) TaskType9(){
  #define SIZE 1
  int m, n, p, q, c, d, k, sum = 0;
  int first[SIZE][SIZE], second[SIZE][SIZE], multiply[SIZE][SIZE];
  m=SIZE;
  n=SIZE;
  long i = 0;
  while (i++ < 99999999*2) { 

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

  cout << "Task type 9 done!" << endl;
}

int main(int argc, char *argv[]){
  int x = atoi(argv[1]);
  set_core_nr(x);

  TaskType9();
return 0;
}
