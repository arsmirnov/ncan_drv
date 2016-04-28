/***************************************************************************
    ncan.h	-	header for CAN driver SoC 1907BM056
    -------------------
    author		: a.smirnov 
    email		: altemka@icloud.com 
	
	This file contains:
		- Driver`s information.
    	- Definitions registers CAN SoC 1907BM056.
    	- Definitions register masks.
    	- Description device.
 ***************************************************************************/

#ifndef CAN_NCAN_H
#define CAN_NCAN_H

/*-----------------------------------------------------------------------------
---------------------------- Driver`s information ----------------------------- 
-----------------------------------------------------------------------------*/

#define DRV_NAME #ncan

/*------------------------------------------------------------------------------
------------------------------ Control register -------------------------------- 
------------------------------------------------------------------------------*/

// Control and status registers

#define NCAN_CAN_ID 	 				0x0000
#define NCAN_CAN_CNTRL 					0x0004
#define NCAN_TIME_CFG 					0x0008
#define NCAN_ERR_STATE 					0x000C
#define NCAN_TX_ERR_CNT 				0x0010
#define NCAN_RX_ERR_CNT 				0x0014
#define NCAN_INT 						0x0018
#define NCAN_INT_EN 					0x001C
#define NCAN_TIME_DIV 					0x0020
#define NCAN_TIMER 						0x0024
#define NCAN_MBX_EN_SET 				0x0040
#define NCAN_MBX_EN_CLR 				0x0044
#define NCAN_MBX_DIR_SET 				0x0048
#define NCAN_MBX_DIR_CLR 				0x004C
#define NCAN_MBX_INT_EN_SET 			0x0050
#define NCAN_MBX_INT_EN_CLR 			0x0054
#define NCAN_TX_REQ_SET 				0x0058
#define NCAN_TX_REQ_CLR 				0x005C
#define NCAN_TX_ACK 					0x0060
#define NCAN_TX_ABORT_ACK 				0x0064
#define NCAN_RX_MSG_PEND				0x0068  
#define NCAN_RX_MSG_LOST 				0x006C
#define NCAN_RX_REMOTE 					0x0070
#define NCAN_OWRITE_DIS_SET 		    0x0074
#define NCAN_OWRITE_DIS_CLR 		    0x0078
#define NCAN_MBX_INT_STATUS 			0x007C

// Mailbox registers

#define NCAN_MBX_ID(num) 				(0x0400 + (0x0020 * num))
#define NCAN_MBX_CNTRL(num) 			(0x0404 + (0x0020 * num))
#define NCAN_MBX_DATA_H(num) 			(0x0408 + (0x0020 * num))
#define NCAN_MBX_DATA_L(num) 			(0x040C + (0x0020 * num))
#define NCAN_MBX_ACCEPT_MASK(num) 		(0x0410 + (0x0020 * num))
#define NCAN_MBX_TIMEOUT(num) 			(0x0414 + (0x0020 * num))

/*-----------------------------------------------------------------------------
------------------------ Register bit masks and shifts ------------------------ 
-----------------------------------------------------------------------------*/

// TimeConfig
#define NCAN_TIME_CFG_SAM_M				0x0080

#define NCAN_TIME_CFG_TSEG2_S			0
#define NCAN_TIME_CFG_TSEG1_S			3
#define NCAN_TIME_CFG_SJW_S				8
#define NCAN_TIME_CFG_BRP_S				16





/*-----------------------------------------------------------------------------
----------------------------- Description CAN device  ------------------------- 
-----------------------------------------------------------------------------*/

struct ncan_priv {   

	/* First field must be such */
	struct can_priv can; 	

	struct net_device *ndev;
	struct napi_struct napi;

	void __iomem *reg_base;

	//struct clk *clk;
};

#endif
