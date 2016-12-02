#ifndef TASK_H
#define TASK_H

class Task
{
public:
    Task();
};

#endif // TASK_H


class Task{
   public:
      void setCPI( int c );
      double getLength( void );
      Task(String name);  // or ID or something?

   private:
      String taskname;
      double _CPI;
      LinkedList InstructionList;
};
