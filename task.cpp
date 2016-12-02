#include "task.h"

Task::Task( String name){
    taskname = name;
}

void Task::setCPI( int c ){
    _CPI = c;
}
double Task::getCPI(){
    return _CPI;
}


