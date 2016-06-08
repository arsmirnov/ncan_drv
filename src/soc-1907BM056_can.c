/*****************************************************************************
    soc-1907BM056_can.c	-   description device.
    -------------------
    author		: A.Smirnov 
    email		: altemka@icloud.com 

    Definition structure platform CAN device.
*****************************************************************************/

#include <linux/platform_device.h>

#include "ncan.h"
#include "soc-1907BM056_can.h"

// --------------------- Description IRQ and memory map ----------------------

static struct resource ncan_resource[] = {
    {
        .start = NCAN_BASE_ADDRESS,
        .end   = NCAN_BASE_ADDRESS + NCAN_MEMORY_SIZE,
        .flags = IORESOURCE_MEM,
    },
    {
        .start = NCAN_IRQ_LINE,
        .flags = IORESOURCE_IRQ,
    }
};

// ----------------------- Definition platform device ------------------------

struct platform_device ncan_device = {
    .name = DRV_NAME,
    .id = PLATFORM_DEVID_NONE,
    .resource = ncan_resource,
    .num_resources = ARRAY_SIZE(ncan_resource),
};