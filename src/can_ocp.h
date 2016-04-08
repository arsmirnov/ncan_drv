/***************************************************************************
	can_ocp.h	-	header for can23_ocp driver 
    -------------------
    author		: a.smirnov 
    email		: asmirnov.cs.niisi.ras.ru 
	
	This file contains:
		- Driver`s information
    	- Definitions registers CAN OCP.
    	- Description device
 ***************************************************************************/

#ifndef CAN_OCP_H
#define CAN_OCP_H

/*-----------------------------------------------------------------------------
---------------------------- Driver`s information ----------------------------- 
-----------------------------------------------------------------------------*/

#define DRV_NAME #can23_ocp

/*------------------------------------------------------------------------------
------------------------------ Control register -------------------------------- 
------------------------------------------------------------------------------*/

// Control and status registers

#define CAN23_CAN_ID 				0x000
#define CAN23_CNTRL 				0x004
#define CAN23_TIME_CFG 				0x008
#define CAN23_ERR_STATE 			0x00C
#define CAN23_TX_ERR_CNT 			0x010
#define CAN23_RX_ERR_CNT 			0x014
#define CAN23_INT 					0x018
#define CAN23_INT_EN 				0x01C
#define CAN23_TIME_DIV 				0x020
#define CAN23_TIMER 				0x024
#define CAN23_MBX_EN_SET 			0x040
#define CAN23_MBX_EN_CLR 			0x044
#define CAN23_MBX_DIR_SET 			0x048
#define CAN23_MBX_DIR_CLR 			0x04C
#define CAN23_MBX_INT_EN_SET 		0x050
#define CAN23_MBX_INT_EN_CLR 		0x054
#define CAN23_TX_REQ_SET 			0x058
#define CAN23_TX_REQ_CLR 			0x05C
#define CAN23_TX_ACK 				0x060
#define CAN23_TX_ABORT_ACK 			0x064
#define CAN23_RX_MSG_PEND			0x068  
#define CAN23_RX_MSG_LOST 			0x06C
#define CAN23_RX_REMOTE 			0x070
#define CAN23_OWRITE_DIS_SET 		0x074
#define CAN23_OWRITE_DIS_CLR 		0x078
#define CAN23_MBX_INT_STATUS 		0x07C

// Mailbox registers

#define CAN23_MBX_ID(num) 			(0x400 + (0x020 * num))
#define CAN23_MBX_CNTRL(num) 		(0x404 + (0x020 * num))
#define CAN23_MBX_DATA_H(num) 		(0x408 + (0x020 * num))
#define CAN23_MBX_DATA_L(num) 		(0x40C + (0x020 * num))
#define CAN23_MBX_ACCEPT_MASK(num) 	(0x410 + (0x020 * num))
#define CAN23_MBX_TIMEOUT(num) 		(0x414 + (0x020 * num))

/*-----------------------------------------------------------------------------
----------------------------- Description device  ----------------------------- 
-----------------------------------------------------------------------------*/

struct can23_ocp {   

	/* First field must be such */
	struct can_priv can; 	

	struct net_device *ndev;
	struct napi_struct napi;
};










#endif