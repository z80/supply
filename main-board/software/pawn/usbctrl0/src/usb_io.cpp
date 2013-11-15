

#include <string.h>
#include "usb_io.h"
extern "C"
{
    #include <lusb0_usb.h>
    #include "opendevice.h"
}

#ifdef WIN32
    #include <windows.h>
    #define  _msleep( arg ) Sleep( arg )
#else
    #include <unistd.h>
    #define _msleep( arg ) usleep( 1000 * (arg) )
#endif

class UsbIo::PD
{
public:
    PD() {}
    ~PD() {}

    void clearOutput();

    usb_dev_handle  * handle;
    int timeout;
    static const int VENDOR_ID;
    static const int PRODUCT_ID;
    static const int TIMEOUT;
    static const int EP_OUT;
    static const int EP_IN;
    static const int STRI_MIN_LEN;

    static const int ATTEMPTS_CNT;
    static const int DELAY_MS;
};

const int UsbIo::PD::VENDOR_ID  = 0x0483;
const int UsbIo::PD::PRODUCT_ID = 0x5740;
const int UsbIo::PD::TIMEOUT    = 5;

const int UsbIo::PD::EP_OUT = 0x03;
const int UsbIo::PD::EP_IN  = 0x81;

const int UsbIo::PD::STRI_MIN_LEN = 64;

const int UsbIo::PD::ATTEMPTS_CNT = 10;
const int UsbIo::PD::DELAY_MS = 10;


void UsbIo::PD::clearOutput()
{
    int actual_length;

	unsigned char data[ STRI_MIN_LEN ];
    do {
        actual_length = usb_bulk_read( handle,
                                       EP_IN, (char *)( data ), //static_cast<char *>( data ), 
                                       STRI_MIN_LEN, 1 );
        char * err = usb_strerror();
   } while ( actual_length > 0 );
}

UsbIo::UsbIo()
{
    pd = new PD();
    pd->handle  = 0;
    pd->timeout = PD::TIMEOUT;
    usb_init();
}

UsbIo::~UsbIo()
{
    if ( isOpen() )
        close();
    //usb_exit( pd->cxt );
    delete pd;
}

bool UsbIo::open( const std::string & arg )
{
    int res = usbOpenDevice( &(pd->handle),
                             PD::VENDOR_ID, NULL,
                             PD::PRODUCT_ID, NULL,
                             NULL, NULL, NULL );
    bool result = (res == 0);
    if ( !result )
    	return false;

    res = usb_set_configuration( pd->handle, 1 );
    res = usb_claim_interface( pd->handle, 1 );

    //pd->clearOutput();
	return result;
}

void UsbIo::close()
{
    if ( isOpen() )
    {
        usb_close( pd->handle );
        pd->handle = 0;
    }
}

bool UsbIo::isOpen() const
{
    return (pd->handle != 0);
}

int UsbIo::write( const std::string & stri )
{
	pd->clearOutput();
    int actual_length;
    char * data = const_cast<char *>( stri.data() );
    unsigned int cnt = 0;
    unsigned int attempts = 0;
    while ( ( cnt < stri.size() ) && ( attempts < PD::ATTEMPTS_CNT ) )
    {
        actual_length = usb_bulk_write( pd->handle, 
                                        PD::EP_OUT, &(data[cnt]), stri.size(), 
                                        pd->timeout );
        char * err = usb_strerror();
        if ( actual_length > 0 )
            cnt += actual_length;
        if ( cnt >= stri.size() )
            break;
        msleep( PD::DELAY_MS );
        attempts++;
    }
    return cnt;
}

int UsbIo::read( std::string & stri )
{
	unsigned int len = 0;
	int timeout = pd->timeout;
	if ( stri.size() < PD::STRI_MIN_LEN )
		stri.resize( PD::STRI_MIN_LEN );
	while ( ( timeout > 0 ) && ( len < stri.size() ) )
	{
		char * data = const_cast<char *>( stri.data() ) + len;
		int actual_length = usb_bulk_read( pd->handle, 
						                   PD::EP_IN, data, stri.size() - len, 
						                   pd->timeout );
        // If error reading.
		if ( actual_length < 0 )
		{
			if ( len > 0 )
			{
				stri.resize( len );
				return len;
			}
			else
				return actual_length;
		}
		len += actual_length;
        if ( ( len > 0 ) && ( stri.find( ">\r\n", 0 ) != std::string::npos ) )
			break;
        timeout--;
        // On timeout return what we have for the moment.
        if ( timeout <= 0 )
            break;
        msleep( 1 );
	}
	stri.resize( len );
    return len;
}

int UsbIo::setTimeout( int ms )
{
    pd->timeout = ms;
    return 0;
}

void UsbIo::msleep( int ms )
{
    _msleep( ms );
}







