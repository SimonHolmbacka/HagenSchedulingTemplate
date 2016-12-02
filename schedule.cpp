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

volatile int done[12]={0,0,0,0,0,0,0,0,0,0,0,0};
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
    //cout << "id " << info[0] << " time " << info[1] << endl;
    done[info[0]] = 0;
    //cout << "done is now " << done[info[0]] << endl;
    usleep(1000*info[1]);
    done[info[0]] = 1;
    //cout << "done is now " << done[info[0]] << endl;
    return NULL;
}

void IdleTask(int d){
    //cout << "delay " << d << endl;
    while(--d >= 0){
        usleep(1000); //Sleep one millisecond
    }
}

void TaskType1(){ //bitbyte intense
    cout << "Starting task type 1" << endl;
    volatile int x = 0x1ff;
    volatile int y;
    while (done[1]==0) {
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
}

void TaskType2(){ //memory and cache intense
    cout << "Starting task type 2" << endl;
    int index = 0;
    while (done[2]==0) {

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
}

#if(ARCH==ARM)
void TaskType3(){ //Branch heavy
    cout << "Starting task type 3" << endl;
    while (done[3]==0) {
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
}
#elif(ARCH == INTEL)
void* __attribute__((optimize("O0"))) TaskType3(){
    cout << "Starting task type 3" << endl;
    while (done[3]==0) {
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
}
#endif

#if(ARCH==ARM)
void TaskType4(){ //Logic intense
    cout << "Starting task type 4" << endl;
    while (done[4]==0) {
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
}
#elif(ARCH == INTEL)
//foo 16 ok
void TaskType4(){
    cout << "Starting task type 4" << endl;
    volatile int x;
    while (done[4]==0) {
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
}
#endif


#if(ARCH==ARM)
void TaskType5(){ //Integer add intense
    while (done[5]==0) {
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
 }
#elif(ARCH == INTEL)
void TaskType5(){
    cout << "Starting task type 5" << endl;
        volatile int x = 0, y = 1, z = 3;
    while (done[5]==0) {
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
}
#endif
#if(ARCH==ARM)
void TaskType6(){ //Floating point mul intense
    while (done[6]==0) {
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
}
#elif(ARCH == INTEL)
void TaskType6(){ //Floating point mul intense
    cout << "Starting task type 6" << endl;
    volatile double x = 1.123, y = 0.23, z = 6.32;
    while (done[6]==0) {
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
}
#endif

#if(ARCH==ARM)
void TaskType7(){ //SIMD mult intense
    cout << "Starting task type 7" << endl;
    while (done[7]==0) {
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
}
#elif(ARCH == INTEL)
void TaskType7(){
    cout << "Starting task type 7" << endl;
    volatile __m128d vec1;
    volatile __m128d vec2;
    volatile __m128d vec3;
    while (done[7]==0) {
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
}
#endif

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
void Schedule::execute(){
    //cout << "number of times " <<this->getTaskSchedule()->getNrItems()<<  endl;
    list::node* t;
    list::node* Temp;
    pthread_t timerthread;
    int arg[2];
    while(this->getTaskSchedule()->getNrItems() > 0){
        t = this->getTaskSchedule()->peekFirst();
        int time = t->metadata.getExecutionTimeMs();
        int freq = t->metadata.getFrequencyKHz();
        int core = t->metadata.getCoreNumber();
        string setfreq = "echo "+std::to_string(freq)+" > /sys/devices/system/cpu/cpu"+std::to_string(core)+"/cpufreq/scaling_setspeed";
        system(setfreq.c_str());    //Set clock frequency for task
        switch (t->metadata.getTaskType()) {
        case 0:
           IdleTask(time);
           Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 1:
            arg[0] = 1;     //Task ID
            arg[1] = time;  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(1000);
            TaskType1();
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 2:
            arg[0] = 2;     //Task ID
            arg[1] = time;  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(1000);
            TaskType2();
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 3:
            arg[0] = 3;     //Task ID
            arg[1] = time;  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(1000);
            TaskType3();
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 4:
            arg[0] = 4;     //Task ID
            arg[1] = time;  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(1000);
            TaskType4();
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 5:
            arg[0] = 5;     //Task ID
            arg[1] = time;  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(1000);
            TaskType5();
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 6:
            arg[0] = 6;     //Task ID
            arg[1] = time;  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(1000);
            TaskType6();
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        case 7:
            arg[0] = 7;     //Task ID
            arg[1] = time;  //Task active time
            if (pthread_create(&timerthread, NULL, TimerTask,arg) != 0) std::cerr << "Error in creating thread" << std::endl;
            usleep(1000);
            TaskType7();
            Temp = this->getTaskSchedule()->popFirst(); //Destroy task
            break;
        default:
            break;
        }
    }

}
