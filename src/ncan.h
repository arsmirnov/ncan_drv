/******************************************************************************
    ncan.h	-	device description.
    -------------------
    author		: A.Smirnov 
    email		: altemka@icloud.com 

	Header for CAN driver SoC 1907BM056.

	This file contains:
		- Driver's information.
    	- Definitions registers CAN SoC 1907BM056.
    	- Definitions register masks.
    	- Description device.
******************************************************************************/

#ifndef NCAN_H
#define NCAN_H

/*-----------------------------------------------------------------------------
---------------------------- Driver's information ----------------------------- 
-----------------------------------------------------------------------------*/

#define DRV_NAME #ncan

/*------------------------------------------------------------------------------
------------------------------ Control register -------------------------------- 
------------------------------------------------------------------------------*/

// ---------------------- Control and status registers -------------------------

#define NCAN_REG_ID 	 					0x0000
#define NCAN_REG_CNTRL 						0x0004
#define NCAN_REG_TIME_CFG 					0x0008
#define NCAN_REG_ERR_STATE 					0x000C
#define NCAN_REG_TX_ERR_CNT 				0x0010
#define NCAN_REG_RX_ERR_CNT 				0x0014
#define NCAN_REG_INT 						0x0018
#define NCAN_REG_INT_EN 					0x001C
#define NCAN_REG_TIME_DIV 					0x0020
#define NCAN_REG_TIMER 						0x0024
#define NCAN_REG_MBX_EN_SET 				0x0040
#define NCAN_REG_MBX_EN_CLR 				0x0044
#define NCAN_REG_MBX_DIR_SET 				0x0048
#define NCAN_REG_MBX_DIR_CLR 				0x004C
#define NCAN_REG_MBX_INT_EN_SET 			0x0050
#define NCAN_REG_MBX_INT_EN_CLR 			0x0054
#define NCAN_REG_TX_REQ_SET 				0x0058
#define NCAN_REG_TX_REQ_CLR 				0x005C
#define NCAN_REG_TX_ACK 					0x0060
#define NCAN_REG_TX_ABORT_ACK 				0x0064
#define NCAN_REG_RX_MSG_PEND				0x0068  
#define NCAN_REG_RX_MSG_LOST 				0x006C
#define NCAN_REG_RX_REMOTE 					0x0070
#define NCAN_REG_OWRITE_DIS_SET 		    0x0074
#define NCAN_REG_OWRITE_DIS_CLR 		    0x0078
#define NCAN_REG_MBX_INT_STATUS 			0x007C

// Mailbox registers

#define NCAN_REG_MBX_ID(num) 				(0x0400 + (0x0020 * num))
#define NCAN_REG_MBX_CNTRL(num) 			(0x0404 + (0x0020 * num))
#define NCAN_REG_MBX_DATA_H(num) 			(0x0408 + (0x0020 * num))
#define NCAN_REG_MBX_DATA_L(num) 			(0x040C + (0x0020 * num))
#define NCAN_REG_MBX_ACCEPT_MASK(num) 		(0x0410 + (0x0020 * num))
#define NCAN_REG_MBX_TIMEOUT(num) 			(0x0414 + (0x0020 * num))

/*-----------------------------------------------------------------------------
------------------------ Register bit masks and shifts ------------------------ 
-----------------------------------------------------------------------------*/

// -------------------------- TimeConfig register -----------------------------

#define NCAN_TIME_CFG_SAM_EN				BIT(7) // Triple sampling

// Shifts TSEG2, TSEG1, SJW, BRP
#define NCAN_TIME_CFG_TSEG2_S				0
#define NCAN_TIME_CFG_TSEG1_S				3
#define NCAN_TIME_CFG_SJW_S					8
#define NCAN_TIME_CFG_BRP_S					16

// ---------------------------- Control register ------------------------------

#define NCAN_CNTRL_CAN_LOM_EN				BIT(5)	// Listen-only mode
#define NCAN_CNTRL_CAN_STM_EN				BIT(6)	// Self-mode testing
#define NCAN_CNTRL_CAN_RS_SRES				BIT(7)	// Software reset
#define NCAN_CNTRL_CAN_RS_ABO_EN			BIT(9)	// CAN enable	
#define NCAN_CNTRL_CAN_RS_EN				BIT(10) // Extern transceiver

/*-----------------------------------------------------------------------------
----------------------------- Description CAN device  ------------------------- 
-----------------------------------------------------------------------------*/

// ----------------------------- Private data NCAN ----------------------------

struct ncan_priv {   

	/* First field must be such */
	struct can_priv can; 	

	struct net_device *ndev;
	struct napi_struct napi;

	void __iomem *reg_base;

	//struct clk *clk;
};


#endif
