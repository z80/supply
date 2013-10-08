
#ifndef __SUPPLY_H_
#define __SUPPLY_H_

class Supply
{
public:
    Supply();
    ~Supply();

    bool setIo( int index, int value );
    int  io( int index );
    bool reopen();
private:
    class PD;
    PD * pd;
};


#endif


