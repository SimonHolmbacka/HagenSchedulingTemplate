#ifndef METADATA_H
#define METADATA_H

#define IDLETASK 0
#define TASKTYPE1 1
#define TASKTYPE2 2
#define TASKTYPE3 3
#define TASKTYPE4 4
#define TASKTYPE5 5

class MetaData
{
public:
    MetaData();
    ~MetaData();
    void setCPI( double cpi_a7, double cpi_a15 );
    double * getCPI();
    void setCoreType(int type);
    int getCoreType();
    void setFrequencyKHz(int f);
    int getFrequencyKHz();
    void setExecutionTimeMs(int e);
    int getExecutionTimeMs();
    void setTaskType(int t);
    int getTaskType();
    void setCoreNumber(int n);
    int getCoreNumber();

private:
   double * CPI;
   int CTYPE;
   int FREQ;
   int EXEC;
   int TTYPE;
   int CNUMBER;
};

#endif // METADATA_H
