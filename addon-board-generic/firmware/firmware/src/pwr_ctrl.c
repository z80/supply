
#include "pwr_ctrl.h"
#include "hal.h"

static void extCallback( EXTDriver * extp, expchannel_t channel );

static const EXTConfig extcfg = {
  {
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_DISABLED, NULL},
   {EXT_CH_MODE_FALLING_EDGE, extCallback},
   {EXT_CH_MODE_DISABLED, NULL},
  },
  EXT_MODE_EXTI(0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                EXT_MODE_GPIOC,
                0)
};

void initPwr( void )
{
    extStart( &EXTD1, &extcfg );
    palSetPadMode( PORT_WAKEUP, PAD_WAKEUP, PAL_MODE_INPUT );
}

void sleep( void )
{
    extChannelEnable( &EXTD1, 14 );

    PWR->CR |= (PWR_CR_LPDS | PWR_CR_CSBF | PWR_CR_CWUF);
    PWR->CR &= ~PWR_CR_PDDS;
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __WFI();
}

// This is callback it reinitializes clock and turns wkaeup channel off
// to prevent dummy wakeupds without going into sleep mode.
static void extCallback( EXTDriver *extp, expchannel_t channel )
{

    (void)extp;
    (void)channel;

    chSysLockFromIsr();
    // Reinitialize clock system.
    stm32_clock_init();

    extChannelDisableI( &EXTD1, 14 );
    chSysUnlockFromIsr();
}







