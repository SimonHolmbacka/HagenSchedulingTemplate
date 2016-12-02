#include <iostream>
#include <string>
#include <malloc.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include "LinkedList.h"
#include "metadata.h"
#include "fixdata.h"
#include "schedule.h"
#include "core.h"
#include "settings.h"

using namespace std;

//Create Cores
//Core *CoreList = new Core[MAXCORES]{{BIG},{BIG},{BIG},{BIG},{LITTLE},{LITTLE},{LITTLE},{LITTLE}};
Core *CoreList = new Core[MAXCORES]{{BIG},{BIG},{BIG},{BIG}};

//Create schedules
Schedule sched0(0,&CoreList[0]);    //Attach core to schedule
Schedule sched1(1,&CoreList[1]);    //Attach core to schedule
Schedule sched2(2,&CoreList[2]);    //Attach core to schedule
Schedule sched3(3,&CoreList[3]);    //Attach core to schedule
Schedule sched4(4,&CoreList[4]);    //Attach core to schedule
Schedule sched5(5,&CoreList[5]);    //Attach core to schedule
Schedule sched6(6,&CoreList[6]);    //Attach core to schedule
Schedule sched7(7,&CoreList[7]);    //Attach core to schedule

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

int nr_schedule=0;
void *SchedTask(void *p) {
    int corenumber = *((int *)p);
#if(GTS==1)
    int biglittle;
    switch(nr_schedule++){
    case 0:
        biglittle = sched0.getTaskSchedule()->peekFirst()->metadata.getCoreType();
        if(biglittle == BIG)
            set_core_nr(BIG0);
        else
            set_core_nr(LITTLE0);
        sched0.execute();
        break;
    case 1:
        biglittle = sched1.getTaskSchedule()->peekFirst()->metadata.getCoreType();
        if(biglittle == BIG)
            set_core_nr(BIG1);
        else
            set_core_nr(LITTLE1);
        sched1.execute();
        break;
    case 2:
        biglittle = sched2.getTaskSchedule()->peekFirst()->metadata.getCoreType();
        if(biglittle == BIG)
            set_core_nr(BIG2);
        else
            set_core_nr(LITTLE2);
        sched2.execute();
        break;
    case 3:
        biglittle = sched3.getTaskSchedule()->peekFirst()->metadata.getCoreType();
        if(biglittle == BIG)
            set_core_nr(BIG3);
        else
            set_core_nr(LITTLE3);
        sched3.execute();
        break;
    default:
        cout << "Schedule not supported" << endl;
        break;
    }
#else
    switch(nr_schedule++){
    case 0:
        cout << "Setting schedule 0 on core " << corenumber << endl;
        set_core_nr(sched0.getTaskSchedule()->peekFirst()->metadata.getCoreNumber());
        sched0.execute();
        break;
    case 1:
        cout << "Setting schedule 1 on core " << corenumber << endl;
        set_core_nr(sched1.getTaskSchedule()->peekFirst()->metadata.getCoreNumber());
        sched1.execute();
        break;
    case 2:
        cout << "Setting schedule 2 on core " << corenumber << endl;
        set_core_nr(sched2.getTaskSchedule()->peekFirst()->metadata.getCoreNumber());
        sched2.execute();
        break;
    case 3:
        cout << "Setting schedule 3 on core " << corenumber << endl;
        set_core_nr(sched3.getTaskSchedule()->peekFirst()->metadata.getCoreNumber());
        sched3.execute();
        break;
    case 4:
        cout << "Setting schedule 4 on core " << corenumber << endl;
        set_core_nr(sched4.getTaskSchedule()->peekFirst()->metadata.getCoreNumber());
        sched4.execute();
        break;
    case 5:
        cout << "Setting schedule 5 on core " << corenumber << endl;
        set_core_nr(sched5.getTaskSchedule()->peekFirst()->metadata.getCoreNumber());
        sched5.execute();
        break;
    case 6:
        cout << "Setting schedule 6 on core " << corenumber << endl;
        set_core_nr(sched6.getTaskSchedule()->peekFirst()->metadata.getCoreNumber());
        sched6.execute();
        break;
    case 7:
        cout << "Setting schedule 7 on core " << corenumber << endl;
        set_core_nr(sched7.getTaskSchedule()->peekFirst()->metadata.getCoreNumber());
        sched7.execute();
        break;
    default:
        cout << "Schedule not supported" << endl;
        break;
    }
#endif
cout << "exiting thread... " << endl;
pthread_exit(NULL);
}

int main()
{
    int numTasks[MAXCORES];
    for(int i=0;i<MAXCORES;i++) numTasks[i] = 0;

    ifstream taskcount[MAXCORES];
    //string path = "C:/Users/Simon/Dropbox/HagenShare/Cpp_TaskTemplate/sched/sched";
    string path = "/root/Desktop/Dropbox/HagenShare/Cpp_TaskTemplate/sched/sched";
    string txt = ".txt";

    //Count the number of tasks in each schedule
    for(int i=0;i<MAXCORES;i++){
        string numberstring = std::to_string(i+1);
        string res = path+numberstring+txt;
        taskcount[i].open(res);
    }
    string unused;
    for(int i=0;i<MAXCORES;i++){
        while (getline(taskcount[i], unused) ) ++numTasks[i];
    }

    //Read all files
    ifstream ifs[MAXCORES];
    for(int i=0;i<MAXCORES;i++){
        string numberstring = std::to_string(i+1);
        string res = path+numberstring+txt;
        ifs[i].open(res);
    }

    //Define task lists for schedules
    list TaskList[MAXCORES];

    //Parse the content of each file
    for(int i=0;i<MAXCORES;i++){
        list::node* Tasks[numTasks[i]];
        MetaData Metas[numTasks[i]];
        string line;

        int idx = 0;
        while(getline(ifs[i], line)){
            istringstream iss(line);
            string tname;
            int ttype;
            int exec;
            int freq;
            int ctype;
            int cnum;
            iss >> tname >> ttype >> exec >> freq >> ctype >> cnum;
    #if 1
            //cout << "col 1 is " << tname << endl;
            //cout << "col 2 is " << ttype << endl;
            //cout << "col 3 is " << exec << endl;
            //cout << "col 4 is " << freq << endl;
            //cout << "col 5 is " << ctype << endl;
            //cout << "col 6 is " << cnum << endl;

    #endif
            Tasks[idx] = TaskList[i].initNode(tname, idx+1); //name and ID
            Metas[idx].setTaskType(ttype);
            Metas[idx].setExecutionTimeMs(exec);
            Metas[idx].setFrequencyKHz(freq);
            Metas[idx].setCoreType(ctype);
            Metas[idx].setCoreNumber(cnum);
            Tasks[idx]->metadata = Metas[idx];
            TaskList[i].addLast(Tasks[idx]);
            idx++;
        }
    }
#if 1

    sched0.addTaskSchedule(&TaskList[0]); //Attach task list to schedule
    sched1.addTaskSchedule(&TaskList[1]); //Attach task list to schedule
    sched2.addTaskSchedule(&TaskList[2]); //Attach task list to schedule
    sched3.addTaskSchedule(&TaskList[3]); //Attach task list to schedule
    sched4.addTaskSchedule(&TaskList[4]); //Attach task list to schedule
    sched5.addTaskSchedule(&TaskList[5]); //Attach task list to schedule
    sched6.addTaskSchedule(&TaskList[6]); //Attach task list to schedule
    sched7.addTaskSchedule(&TaskList[7]); //Attach task list to schedule

#endif

    //Set frequency governor
#if(ARCH==INTEL)
    string setfreq;
    setfreq = "echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor";
    system(setfreq.c_str());
    setfreq = "echo userspace > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor";
    system(setfreq.c_str());
    setfreq = "echo userspace > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor";
    system(setfreq.c_str());
    setfreq = "echo userspace > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor";
    system(setfreq.c_str());
#elif(ARCH==ARM)
    string setfreq;
    setfreq = "echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor";
    system(setfreq.c_str());
    setfreq = "echo userspace > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor";
    system(setfreq.c_str());
#endif

    //Execute schedules
    pthread_t schedthread;
    int arg;
    for(int i=0;i<MAXCORES;i++){
        usleep(1000);
        arg=TaskList[i].peekFirst()->metadata.getCoreNumber();
        if (pthread_create(&schedthread, NULL, SchedTask,&arg) != 0) {
            std::cerr << "Error in creating thread" << std::endl;
        }
    }

    pthread_join(schedthread, NULL);
    cout << "End." << endl;
    exit(0);
    while(1){
        sleep(1);
    }

#if 0
    /*
     * TEST CASES
     */
    //Testing cores
    cout << "Core type is: " << CoreList[0].getType() << endl;
    cout << "Core type is: " << CoreList[1].getType() << endl;
    //Testing task schedule
    cout << "Testing core on schedule: "<< sched0.getCore().getType() << endl;
    cout << "Testing core on schedule: "<< sched1.getCore().getType() << endl;
    cout << "Testing task list " << sched0.getTaskSchedule()->peekFirst()->id << endl;
    cout << "Testing task list " << sched0.getTaskSchedule()->peekFirst()->name << endl;
    //Testing task parameters
    cout << "Getting the first task from FIFO " << endl;
    cout << "It is Task id: "<< TaskList[0].peekFirst()->id << endl;
    cout << "It has Freq meta data: " << TaskList[0].peekFirst()->metadata.getFrequencyKHz() << endl;
    cout << "It has Exec meta data: " << TaskList[0].peekFirst()->metadata.getExecutionTimeMs() << endl;
    cout << "Core type is: " << TaskList[0].peekFirst()->metadata.getCoreType() <<endl;
    cout << "Now we take it from the queue" << endl;
    list::node* TempTask1 = TaskList[0].popFirst();
    cout << "Getting the first task from FIFO " << endl;
    cout << "It is Task id: "<< TaskList[0].peekFirst()->id << endl;
    cout << "It has Freq meta data: " << TaskList[0].peekFirst()->metadata.getFrequencyKHz() << endl;
    cout << "It has Exec meta data: " << TaskList[0].peekFirst()->metadata.getExecutionTimeMs() << endl;
    cout << "Now we take it from the queue" << endl;
    list::node* TempTask2 = TaskList[0].popFirst();
    cout << "Getting the first task from FIFO " << endl;
    cout << "It is Task id: "<< TaskList[1].peekFirst()->id << endl;
    cout << "It has Freq meta data: " << TaskList[1].peekFirst()->metadata.getFrequencyKHz() << endl;
    cout << "It has Exec meta data: " << TaskList[1].peekFirst()->metadata.getExecutionTimeMs() << endl;
    cout << "Now we take it from the queue" << endl;
    list::node* TempTask3 = TaskList[1].popFirst();
    cout << "Done!" << endl;
#endif
    exit(0);
    return 0;
}

