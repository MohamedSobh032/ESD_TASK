#ifndef STD_MACROS_H_INCLUDED
#define STD_MARCOS_H_INCLUDED


#define SETBIT(Reg,bit)     Reg = Reg | (1 << bit)
#define CLEARBIT(Reg,bit)   Reg = Reg & (~(1 << bit))
#define TOGGLEBIT(Reg,bit)  Reg = Reg ^ (1 << bit)
#define READBIT(Reg,bit)    ((Reg >> bit) & 1)




#endif