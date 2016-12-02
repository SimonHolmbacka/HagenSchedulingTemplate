#include <malloc.h>
#include "metadata.h"

MetaData::MetaData(){
    CPI = (double *)malloc(sizeof(double)*2);
}
MetaData::~MetaData(){
    delete CPI;
}
void MetaData::setCPI( double cpi_a7, double cpi_a15 ){
    CPI[0] = cpi_a7;
    CPI[1] = cpi_a15;
}
double *MetaData::getCPI(){
    return CPI;
}
void MetaData::setCoreType(int type){
    CTYPE = type;
}
int MetaData::getCoreType(){
    return CTYPE;
}
void MetaData::setFrequencyKHz(int f){
    FREQ = f;
}
int MetaData::getFrequencyKHz(){
    return FREQ;
}
void MetaData::setExecutionTimeMs(int e){
    EXEC = e;
}
int MetaData::getExecutionTimeMs(){
    return EXEC;
}
void MetaData::setTaskType(int t){
    TTYPE = t;
}
int MetaData::getTaskType(){
    return TTYPE;
}
void MetaData::setCoreNumber(int n){
    CNUMBER = n;
}
int MetaData::getCoreNumber(){
    return CNUMBER;
}
