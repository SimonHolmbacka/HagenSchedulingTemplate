#ifndef SETTINGS_H
#define SETTINGS_H

#define MEM_SIZE 1000000

#define INTEL 1
#define ARM 2

/*User defined settings*/
#define ARCH ARM
#define MAXCORES 8
#define GTS 1
/*End user defined settings*/

#if (GTS==1)
#define BIG0 1
#define BIG1 2
#define BIG2 3
#define BIG3 4
#define LITTLE0 0
#define LITTLE1 5
#define LITTLE2 6
#define LITTLE3 7
#endif




#endif // SETTINGS_H
