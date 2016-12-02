#ifndef FIXDATA_H
#define FIXDATA_H

class FixData
{
public:
    FixData();
    void setDeadline(double D);
    void setPressure(double P);
    double getDeadline();
    double getPressure();
private:
   double Deadline;
   double Pressure;
};

#endif // FIXDATA_H


