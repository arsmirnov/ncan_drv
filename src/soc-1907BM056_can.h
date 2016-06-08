/*********************************************************************************
	soc-1907BM056_can.h	-	SoC definitions.			
    -------------------
    author		: A.Smirnov 
    email		: altemka@icloud.com	 

    SoC 1907BM056 definitions required for working with CAN
********************************************************************************/

#ifndef SOC_1907BM056_CAN_H
#define SOC_1907BM056_CAN_H

// ---------------- Base address and memory size of CAN device ------------------

#define NCAN_BASE_ADDRESS               	0x0000
#define NCAN_MEMORY_SIZE                	0x05F4

// ------------------------------------ IRQ line --------------------------------

#define NCAN_IRQ_LINE						(0)


// ------------------ Declare global platform device structure ------------------

extern struct platform_device ncan_device;


#endif

