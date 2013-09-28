
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#include "usb_cdc.h"
#include "shell.h"
#include "chprintf.h"

#include "usb_ctrl.h"
#include "hdw_cfg.h"
#include "pawn_ctrl.h"

/*===========================================================================*/
/* USB related stuff.                                                        */
/*===========================================================================*/

/*
 * USB Driver structure.
 */
static SerialUSBDriver SDU1;

/*
 * USB Device Descriptor.
 */
static const uint8_t vcom_device_descriptor_data[18] = {
  USB_DESC_DEVICE       (0x0110,        /* bcdUSB (1.1).                    */
                         0x02,          /* bDeviceClass (CDC).              */
                         0x00,          /* bDeviceSubClass.                 */
                         0x00,          /* bDeviceProtocol.                 */
                         0x40,          /* bMaxPacketSize.                  */
                         0x0483,        /* idVendor (ST).                   */
                         0x5740,        /* idProduct.                       */
                         0x0200,        /* bcdDevice.                       */
                         1,             /* iManufacturer.                   */
                         2,             /* iProduct.                        */
                         3,             /* iSerialNumber.                   */
                         1)             /* bNumConfigurations.              */
};

/*
 * Device Descriptor wrapper.
 */
static const USBDescriptor vcom_device_descriptor = {
  sizeof vcom_device_descriptor_data,
  vcom_device_descriptor_data
};

/* Configuration Descriptor tree for a CDC.*/
static const uint8_t vcom_configuration_descriptor_data[67] = {
  /* Configuration Descriptor.*/
  USB_DESC_CONFIGURATION(67,            /* wTotalLength.                    */
                         0x02,          /* bNumInterfaces.                  */
                         0x01,          /* bConfigurationValue.             */
                         0,             /* iConfiguration.                  */
                         0xC0,          /* bmAttributes (self powered).     */
                         50),           /* bMaxPower (100mA).               */
  /* Interface Descriptor.*/
  USB_DESC_INTERFACE    (0x00,          /* bInterfaceNumber.                */
                         0x00,          /* bAlternateSetting.               */
                         0x01,          /* bNumEndpoints.                   */
                         0x02,          /* bInterfaceClass (Communications
                                           Interface Class, CDC section
                                           4.2).                            */
                         0x02,          /* bInterfaceSubClass (Abstract
                                         Control Model, CDC section 4.3).   */
                         0x01,          /* bInterfaceProtocol (AT commands,
                                           CDC section 4.4).                */
                         0),            /* iInterface.                      */
  /* Header Functional Descriptor (CDC section 5.2.3).*/
  USB_DESC_BYTE         (5),            /* bLength.                         */
  USB_DESC_BYTE         (0x24),         /* bDescriptorType (CS_INTERFACE).  */
  USB_DESC_BYTE         (0x00),         /* bDescriptorSubtype (Header
                                           Functional Descriptor.           */
  USB_DESC_BCD          (0x0110),       /* bcdCDC.                          */
  /* Call Management Functional Descriptor. */
  USB_DESC_BYTE         (5),            /* bFunctionLength.                 */
  USB_DESC_BYTE         (0x24),         /* bDescriptorType (CS_INTERFACE).  */
  USB_DESC_BYTE         (0x01),         /* bDescriptorSubtype (Call Management
                                           Functional Descriptor).          */
  USB_DESC_BYTE         (0x00),         /* bmCapabilities (D0+D1).          */
  USB_DESC_BYTE         (0x01),         /* bDataInterface.                  */
  /* ACM Functional Descriptor.*/
  USB_DESC_BYTE         (4),            /* bFunctionLength.                 */
  USB_DESC_BYTE         (0x24),         /* bDescriptorType (CS_INTERFACE).  */
  USB_DESC_BYTE         (0x02),         /* bDescriptorSubtype (Abstract
                                           Control Management Descriptor).  */
  USB_DESC_BYTE         (0x02),         /* bmCapabilities.                  */
  /* Union Functional Descriptor.*/
  USB_DESC_BYTE         (5),            /* bFunctionLength.                 */
  USB_DESC_BYTE         (0x24),         /* bDescriptorType (CS_INTERFACE).  */
  USB_DESC_BYTE         (0x06),         /* bDescriptorSubtype (Union
                                           Functional Descriptor).          */
  USB_DESC_BYTE         (0x00),         /* bMasterInterface (Communication
                                           Class Interface).                */
  USB_DESC_BYTE         (0x01),         /* bSlaveInterface0 (Data Class
                                           Interface).                      */
  /* Endpoint 2 Descriptor.*/
  USB_DESC_ENDPOINT     (USB_CDC_INTERRUPT_REQUEST_EP|0x80,
                         0x03,          /* bmAttributes (Interrupt).        */
                         0x0008,        /* wMaxPacketSize.                  */
                         0xFF),         /* bInterval.                       */
  /* Interface Descriptor.*/
  USB_DESC_INTERFACE    (0x01,          /* bInterfaceNumber.                */
                         0x00,          /* bAlternateSetting.               */
                         0x02,          /* bNumEndpoints.                   */
                         0x0A,          /* bInterfaceClass (Data Class
                                           Interface, CDC section 4.5).     */
                         0x00,          /* bInterfaceSubClass (CDC section
                                           4.6).                            */
                         0x00,          /* bInterfaceProtocol (CDC section
                                           4.7).                            */
                         0x00),         /* iInterface.                      */
  /* Endpoint 3 Descriptor.*/
  USB_DESC_ENDPOINT     (USB_CDC_DATA_AVAILABLE_EP,     /* bEndpointAddress.*/
                         0x02,          /* bmAttributes (Bulk).             */
                         0x0040,        /* wMaxPacketSize.                  */
                         0x00),         /* bInterval.                       */
  /* Endpoint 1 Descriptor.*/
  USB_DESC_ENDPOINT     (USB_CDC_DATA_REQUEST_EP|0x80,  /* bEndpointAddress.*/
                         0x02,          /* bmAttributes (Bulk).             */
                         0x0040,        /* wMaxPacketSize.                  */
                         0x00)          /* bInterval.                       */
};

/*
 * Configuration Descriptor wrapper.
 */
static const USBDescriptor vcom_configuration_descriptor = {
  sizeof vcom_configuration_descriptor_data,
  vcom_configuration_descriptor_data
};

/*
 * U.S. English language identifier.
 */
static const uint8_t vcom_string0[] = {
  USB_DESC_BYTE(4),                     /* bLength.                         */
  USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
  USB_DESC_WORD(0x0409)                 /* wLANGID (U.S. English).          */
};

/*
 * Vendor string.
 */
static const uint8_t vcom_string1[] = {
  USB_DESC_BYTE(26),                    /* bLength.                         */
  USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
  's', 0, 'u', 0, 'p', 0, 'p', 0, 'l', 0, 'y', 0, ' ', 0, 'b', 0,
  'o', 0, 'a', 0, 'r', 0, 'd'
};

/*
 * Device Description string.
 */
static const uint8_t vcom_string2[] = {
  USB_DESC_BYTE(48),                    /* bLength.                         */
  USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
  's', 0, 'u', 0, 'p', 0, 'p', 0, 'l', 0, 'y', 0, ' ', 0, 'v', 0,
  'i', 0, 'r', 0, 't', 0, 'u', 0, 'a', 0, 'l', 0, ' ', 0, 'c', 0,
  'o', 0, 'm', 0, ' ', 0, 'p', 0, 'o', 0, 'r', 0, 't', 0
};

/*
 * Serial Number string.
 */
static const uint8_t vcom_string3[] = {
  USB_DESC_BYTE(8),                     /* bLength.                         */
  USB_DESC_BYTE(USB_DESCRIPTOR_STRING), /* bDescriptorType.                 */
  '0' + CH_KERNEL_MAJOR, 0,
  '0' + CH_KERNEL_MINOR, 0,
  '0' + CH_KERNEL_PATCH, 0
};

/*
 * Strings wrappers array.
 */
static const USBDescriptor vcom_strings[] = {
  {sizeof vcom_string0, vcom_string0},
  {sizeof vcom_string1, vcom_string1},
  {sizeof vcom_string2, vcom_string2},
  {sizeof vcom_string3, vcom_string3}
};

/*
 * Handles the GET_DESCRIPTOR callback. All required descriptors must be
 * handled here.
 */
static const USBDescriptor *get_descriptor(USBDriver *usbp,
                                           uint8_t dtype,
                                           uint8_t dindex,
                                           uint16_t lang) {

  (void)usbp;
  (void)lang;
  switch (dtype) {
  case USB_DESCRIPTOR_DEVICE:
    return &vcom_device_descriptor;
  case USB_DESCRIPTOR_CONFIGURATION:
    return &vcom_configuration_descriptor;
  case USB_DESCRIPTOR_STRING:
    if (dindex < 4)
      return &vcom_strings[dindex];
  }
  return NULL;
}

/**
 * @brief   EP1 initialization structure (IN only).
 */
static const USBEndpointConfig ep1config = {
  USB_EP_MODE_TYPE_BULK | USB_EP_MODE_PACKET,
  NULL,
  sduDataTransmitted,
  NULL,
  0x0040,
  0x0000,
  NULL,
  NULL
};

/**
 * @brief   EP2 initialization structure (IN only).
 */
static const USBEndpointConfig ep2config = {
  USB_EP_MODE_TYPE_INTR | USB_EP_MODE_PACKET,
  NULL,
  sduInterruptTransmitted,
  NULL,
  0x0010,
  0x0000,
  NULL,
  NULL
};

/**
 * @brief   EP3 initialization structure (OUT only).
 */
static const USBEndpointConfig ep3config = {
  USB_EP_MODE_TYPE_BULK | USB_EP_MODE_PACKET,
  NULL,
  NULL,
  sduDataReceived,
  0x0000,
  0x0040,
  NULL,
  NULL
};

/*
 * Handles the USB driver global events.
 */
static void usb_event(USBDriver *usbp, usbevent_t event) {

  switch (event) {
  case USB_EVENT_RESET:
    return;
  case USB_EVENT_ADDRESS:
    return;
  case USB_EVENT_CONFIGURED:
    /* Enables the endpoints specified into the configuration.
       Note, this callback is invoked from an ISR so I-Class functions
       must be used.*/
    chSysLockFromIsr();
    usbInitEndpointI(usbp, USB_CDC_DATA_REQUEST_EP, &ep1config);
    usbInitEndpointI(usbp, USB_CDC_INTERRUPT_REQUEST_EP, &ep2config);
    usbInitEndpointI(usbp, USB_CDC_DATA_AVAILABLE_EP, &ep3config);
    chSysUnlockFromIsr();
    return;
  case USB_EVENT_SUSPEND:
    return;
  case USB_EVENT_WAKEUP:
    return;
  case USB_EVENT_STALLED:
    return;
  }
  return;
}

/*
 * Serial over USB driver configuration.
 */
static const SerialUSBConfig serusbcfg = {
  &USBD1,
  {
    usb_event,
    get_descriptor,
    sduRequestsHook,
    NULL
  }
};

/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/

#define SHELL_WA_SIZE   THD_WA_SIZE( (1024 * 3) )

static void cmd_pawnSetIo(BaseChannel *chp, int argc, char *argv[])
{
    if ( argc > 1 )
    {
        int ind     = atoi( argv[0] );
        int i;
        for ( i=1; i<argc; i++ )
        {
            uint8_t val = atoi( argv[i] );
            pawnSetIo( ind+i-1, val );
        }
    }
    else
        chprintf( chp, "ERROR: more args expected \r\n" );
}

static void cmd_pawnIo(BaseChannel *chp, int argc, char *argv[])
{
    if ( argc > 0 )
    {
        int ind = atoi( argv[0] );
        uint8_t val = pawnIo( ind );
	    chprintf( chp, "{%d}\r\n", val );
    }
    else
        chprintf( chp, "ERROR: more args expected \r\n" );
}

static void cmd_pawnSetMem(BaseChannel *chp, int argc, char *argv[])
{
    (void)chp;
    if ( argc > 1 )
    {
        int at = atoi( argv[0] );
        int i;
        for ( i=1; i<argc; i++ )
        {
	        uint8_t v = atoi( argv[i] );
	        pawnSetMem( at+i-1, v );
	    }
    }
    else
        chprintf( chp, "ERROR: more arguments expected\r\n" );
}

/*
static void cmd_pawnMem(BaseChannel *chp, int argc, char *argv[])
{
    (void)chp;
    if ( argc > 0 )
    {
        int at = atoi( argv[0] );
	uint8_t res = pawnMem( at );
	chprintf( chp, "%d\r\n", res );
    }
    else
        chprintf( chp, "ERROR: more arguments expected\r\n" );
}
*/

static void cmd_pawnWriteFlash(BaseChannel *chp, int argc, char *argv[])
{
    (void)chp;
    if ( argc > 0 )
    {
        int n = atoi( argv[0] );
        n = pawnWriteFlash( n );
        chprintf( chp, "{%d}\r\n", n );
    }
    else
        chprintf( chp, "ERROR: 0 based page index expected\r\n" );
}

static void cmd_pawnRun(BaseChannel *chp, int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    pawnRun();
    chprintf( chp, "ok\r\n" );
}

static void cmd_pawnIsRunning(BaseChannel *chp, int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    uint8_t res = pawnIsRunning();
    chprintf( chp, "{%d}\r\n", res );
}

static void cmd_pawnStop( BaseChannel *chp, int argc, char *argv[] )
{
	(void)chp;
    (void)argc;
    (void)argv;
    pawnStop();
}

static void cmd_pawnResult( BaseChannel *chp, int argc, char *argv[] )
{
    (void)argc;
    (void)argv;
    int res = pawnResult();
    chprintf( chp, "{%d}\r\n", res );
}

static void cmd_pawnError( BaseChannel *chp, int argc, char *argv[] )
{
    (void)argc;
    (void)argv;
    int res = pawnError();
    chprintf( chp, "{%d}\r\n", res );
}





static const ShellCommand commands[] =
{
    // Commands for inputs/outputs.
    //{ "mem",            cmd_mem },
     //{ "threads",        cmd_threads },

    { "setIo",      cmd_pawnSetIo },
    { "io",         cmd_pawnIo },
    { "setMem",     cmd_pawnSetMem },
    //{ "pawnMem",        cmd_pawnMem }, 
    { "wrFl",       cmd_pawnWriteFlash },
    { "run",        cmd_pawnRun },
    { "isRun",      cmd_pawnIsRunning },
    { "stop",       cmd_pawnStop },
    { "res",        cmd_pawnResult },
    { "err",        cmd_pawnError },

    { NULL,             NULL }
};

static const ShellConfig shell_cfg1 =
{
  (BaseChannel *)&SDU1,
  commands
};

























/*===========================================================================*/
/* Generic code.                                                             */
/*===========================================================================*/

static Thread * shelltp = NULL;

void initUsb( void )
{
    // Disconnect bus.
    usbDisconnectBus(serusbcfg.usbp);
    // Wait for a while for computer to feel device is disconnected.
    chThdSleepMilliseconds( 1000 );
    // Init USB
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);
    // Connect bus.
    usbConnectBus(serusbcfg.usbp);
    // Initialize text shell.
    shellInit();
}

void finitUsb( void )
{
    usbDisconnectBus();
    sduStop( &SDU1 );
}

void processShell( void )
{
    if (!shelltp && (SDU1.config->usbp->state == USB_ACTIVE))
        shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);
    else if (chThdTerminated(shelltp))
    {
        chThdRelease( shelltp );    // Recovers memory of the previous shell.
        shelltp = NULL;             // Triggers spawning of a new shell.
    }
}

void usbWrite( char * stri )
{
    chprintf( (BaseChannel *)&SDU1, stri );
}


