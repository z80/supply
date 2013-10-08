
#ifndef __MCUCTRL_H_
#define __MCUCTRL_H_

class McuCtrl
{
public:
    McuCtrl();
    virtual ~McuCtrl();

    bool open();
    bool isOpen();
    void close();
    bool write( unsigned char addr, const unsigned char * data, int cnt );
    bool read( unsigned char addr, unsigned char * data, int cnt );

    bool setIo( int index, unsigned char value );
    bool io( int index, unsigned char & value );

private:
    class PD;
    PD * pd;
};


#endif




