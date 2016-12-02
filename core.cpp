#include "core.h"
#include <iostream>

using namespace std;

Core::Core(int type)
{
    if(this->getType() == BIG)
        setCurrFreq(FrequenciesB[0]);
    else if(this->getType() == LITTLE)
        setCurrFreq(FrequenciesL[0]);
    else
        cout << "Unsupported core type " << type << endl;
    setType(type);
}
Core::~Core()
{

}
void Core::setCurrFreq(int f){
    CURRFREQ = f;
}

int Core::getCurrFreq(){
    return CURRFREQ;
}

void Core::setType(int type){
    ARCHTYPE = type;
}
int Core::getType(){
    return ARCHTYPE;
}
