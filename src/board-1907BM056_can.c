/***************************************************************************
    board-1907BM056_can.c	-    description platform device CAN.
    -------------------
    author		: A.Smirnov 
    email		: altemka@icloud.com 

    Description platform device CAN and registration in the kernel.
***************************************************************************/

#include <linux/platform_device.h>

#include "ncan.h"

/*---------------------- Base address and memory size of CAN device --------------------*/

#define NCAN_BASE_ADDRESS               0x0000
#define NCAN_MEMORY_SIZE                0x05F4

/*-------------------------- Description IRQ and memory map ----------------------------*/

static struct resource ncan_resource[]
{
    {
        .start = NCAN_BASE_ADDRESS,
        .end   = NCAN_BASE_ADDRESS + NCAN_MEMORY_SIZE,
        .flags = IORESOURCE_MEM,
    },
    {
        
    }
};
