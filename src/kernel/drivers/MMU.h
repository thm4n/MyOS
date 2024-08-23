#ifndef _MMU_H_
#define _MMU_H_

#include "stdint.h"

extern uint32_t endkernel;

#define USED 1
#define FREE 0

#endif
   
/*
 * | 00 0000 0000 | 00 0000 0000 | 0000 0000 0000 |
 * +--------------+--------------+----------------+
 *        A              B                C        
 * 
 * A - index of the page directory entry
 * B - index of the page table entry
 * C - page offset
 * 
 * 
Page Directory:
    array of Page Directory Entries.
    addresses must be 4KiB aligned
    









 */