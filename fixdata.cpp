#include "fixdata.h"

FixData::FixData()
{

}

void FixData::setDeadline(double D){
    Deadline = D;
}

void FixData::setPressure(double P){
    Pressure = P;
}

double FixData::getDeadline(){
    return Deadline;
}

double FixData::getPressure(){
    return Pressure;
}
