#ifndef CORE_H
#define CORE_H

#define LITTLE 0
#define BIG 1

class Core
{
public:
    Core(int type);
    ~Core();
    void setCurrFreq(int f);
    int getCurrFreq();
    void setType(int type);
    int getType();

private:
    int FrequenciesB[6] = {800000,10000000,12000000,14000000,1600000};
    int FrequenciesL[6] = {600000,800000,1000000,1200000,1400000};
    int CURRFREQ;
    int ARCHTYPE;
};

#endif // CORE_H
