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
Core *CoreList = new Core[MAXCORES]{{BIG},{BIG},{BIG},{BIG},{LITTLE},{LITTLE},{LITTLE},{LITTLE}};
//Core *CoreList = new Core[MAXCORES]{{BIG},{BIG},{BIG},{BIG},{LITTLE}};
//Core *CoreList = new Core[MAXCORES]{{BIG},{BIG},{BIG},{BIG}};
//Core *CoreList = new Core[MAXCORES]{{BIG},{BIG},{BIG}};
//Core *CoreList = new Core[MAXCORES]{{BIG},{BIG}};
//Core *CoreList = new Core[MAXCORES]{{BIG}};


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

pthread_barrier_t barr;
int nr_schedule=0;
void *SchedTask(void *p) {
    int corenumber = *((int *)p);
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
cout << "              Shutting down core nr " << corenumber << endl;
  //pthread_exit(NULL); // will cause segfault sometimes
  //return 0;	// will cause segfault sometimes
  //return NULL; // will cause segfault sometimes
}

int main()
{
    int numTasks[MAXCORES];
    for(int i=0;i<MAXCORES;i++) numTasks[i] = 0;

    ifstream taskcount[MAXCORES];
    string path = "./sched/sched";
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

            //cout << "col 1 is " << tname << endl;
            //cout << "col 2 is " << ttype << endl;
            //cout << "col 3 is " << exec << endl;
            //cout << "col 4 is " << freq << endl;
            //cout << "col 5 is " << ctype << endl;
            //cout << "col 6 is " << cnum << endl;

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

#if 0
	    cout << "items0 "<< TaskList[0].getNrItems() << endl;
	    cout << "items1 "<< TaskList[1].getNrItems() << endl;
	    cout << "items2 "<< TaskList[2].getNrItems() << endl;
	    cout << "items3 "<< TaskList[3].getNrItems() << endl;
	    cout << "items4 "<< TaskList[4].getNrItems() << endl;
	    cout << "items5 "<< TaskList[5].getNrItems() << endl;
	    cout << "items6 "<< TaskList[6].getNrItems() << endl;
	    cout << "items7 "<< TaskList[7].getNrItems() << endl;
#endif

	if(TaskList[0].getNrItems() >= 1)
    	    sched0.addTaskSchedule(&TaskList[0]); //Attach task list to schedule
	if(TaskList[1].getNrItems() >= 1)
    	    sched1.addTaskSchedule(&TaskList[1]); //Attach task list to schedule
	if(TaskList[2].getNrItems() >= 1)
    	    sched2.addTaskSchedule(&TaskList[2]); //Attach task list to schedule
	if(TaskList[3].getNrItems() >= 1)
    	    sched3.addTaskSchedule(&TaskList[3]); //Attach task list to schedule
	if(TaskList[4].getNrItems() >= 1)
    	    sched4.addTaskSchedule(&TaskList[4]); //Attach task list to schedule
	if(TaskList[5].getNrItems() >= 1)
    	    sched5.addTaskSchedule(&TaskList[5]); //Attach task list to schedule
	if(TaskList[6].getNrItems() >= 1)
    	    sched6.addTaskSchedule(&TaskList[6]); //Attach task list to schedule
	if(TaskList[7].getNrItems() >= 1)
    	    sched7.addTaskSchedule(&TaskList[7]); //Attach task list to schedule

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

    pthread_barrier_init(&barr, NULL, MAXCORES);

    //Execute schedules


//for(int g=0;g<MAXCORES;g++){
//cout << "test core nr " << TaskList[g].p

    pthread_t schedthread[MAXCORES];
    int arg;
    for(int i=0;i<MAXCORES;i++){
	if(TaskList[i].getNrItems() >= 1){
	TaskList[i].reverse();
        arg=TaskList[i].peekFirst()->metadata.getCoreNumber();
        if (pthread_create(&schedthread[i], NULL, SchedTask,&arg) != 0) {
            usleep(10000);
            std::cerr << "Error in creating thread" << std::endl;
        }
	usleep(1000);
	}
    }
#if 1
    void* retval;
    for(int i=0;i<MAXCORES;i++){
	pthread_join(schedthread[i], &retval);
    }
#endif

#if 0
cout << "exiting thread... " << endl;
    int res = pthread_barrier_wait(&barr);
    if(res == PTHREAD_BARRIER_SERIAL_THREAD) {
        // this is the unique "serial thread"; you can e.g. combine some results here
    } else if(res != 0) {
        // error occurred
        cout << "Error in barrier!" << endl;
    } else {
        // non-serial thread released
        cout << "non-serial thread released" << endl;
    }
#endif

    cout << "End." << endl;
    exit(0);
    return 0;
}

