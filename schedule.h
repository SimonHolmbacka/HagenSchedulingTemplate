#include "core.h"
#include "LinkedList.h"
#ifndef SCHEDULE_H
#define SCHEDULE_H




class Schedule
{
public:
    Schedule(int id, Core* obj);
    ~Schedule();
    Core getCore();
    void addTaskSchedule(list* l);
    list* getTaskSchedule();
    void execute();
private:
    Core* CC;
    list* TASKLIST;
    int ID;

};

#endif // SCHEDULE_H
