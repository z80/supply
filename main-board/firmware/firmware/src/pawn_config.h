

#ifndef __PAWN_CONFIG_H_
#define __PAWN_CONFIG_H_

// Total Pawn script, heap, stack size in cells, not in bytes (!!!)
#define PAWN_MEM_SIZE ( 2560 )
// Array of int type for host computer IO.
#define PAWN_IO_SIZE  ( 32 )
// FLASH parameters.
#define PAWN_PAGE_SIZE     1024
// Start FLASH block to keep pawn program in.
#define PAWN_START_PAGE    38
// Pawn permitted pages cnt.
// Here 128 is total pages cnt, 10 is DFU firmware at the very end of FLASH size.
#define PAWN_PAGES_CNT     ( 128 - PAWN_START_PAGE - 10 )
// Start of FLASH memory
#define PAWN_FLASH_START   0x08000000
// Chibios PAWN thread stack depth.
#define PAWN_THREAD_STACK_DEPTH 3072

#endif

