/***************************************************************************
	ncan.c	-	module of kernel
    -------------------
    author		: a.smirnov 
    email		: altemka@icloud.com

    CAN driver for SoC 1907BM056.
 ***************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/can/dev.h>
#include <linux/clk.h>
#include <linux/types.h>
#include <linux/io.h>
#include <linux/platform_device.h>

#include "ncan.h"

/*-----------------------------------------------------------------------------
------------------------ Initialization data structures ----------------------- 
-----------------------------------------------------------------------------*/

// Initialization bittiming constants
static const struct can_bittiming_const ncan_bittiming_const 
{		
	.name = DRV_NAME,
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 3,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
};

/*-----------------------------------------------------------------------------
------------------ Definitions functions for working with CAN ----------------- 
-----------------------------------------------------------------------------*/

/****
* @fn ncan_write
*
* Write a value to device registers. 
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
*	reg_offset - register offset.
*	value - value for writing.
* @return:
*	none		
**/
static inline void ncan_write( const struct ncan_priv *priv, u32 reg_offset, u32 value )
{
	iowrite32( value, priv->reg_base + reg_offset );
}

/****
* @fn ncan_read
*
* Read a value from the device register.
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
* @return:
*	value read from register	
**/
static inline u32 ncan_read( const struct ncan_priv *priv, u32 reg_offset )
{
	return ioread32( priv->reg_base + reg_offset );
}

/****
* @fn ncan_set_bittiming		
*
* Set bit-timing parameters.
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
* @return:
*	null
*	
**/
static int ncan_set_bittiming( struct ncan_priv *priv )
{
	struct can_bittiming *bit_timing = &priv->can.bittiming;
	u32 ncan_btc;

	// Setting phase segment 2(TSEG2)
	ncan_btc = ( bit_timing->phase_seg2 - 1 ) << NCAN_TIME_CFG_TSEG2_S;

	// Setting phase segment 1(TSEG1)
	ncan_btc |= ( bit_timing->phase_seg1 - 1 ) << NCAN_TIME_CFG_TSEG1_S;

	// Setting the number of samples
	if( priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES )
		ncan_btc |= NCAN_TIME_CFG_SAM_M;

	// Setting synchronization jump width(SJW)
	ncan_btc |= ( bit_timing->sjw - 1 ) << NCAN_TIME_CFG_SJW_S;

	// Setting time quantum prescaler
	ncan_btc |= ( bit_timing->brp - 1 ) << NCAN_TIME_CFG_BRP_S;

	ncan_write( priv, NCAN_TIME_CFG, ncan_btc );
	netdev_info( priv->ndev, "Setting register: TimeConfig = %#X\n", ncan_btc );

	return 0;
}









/*-----------------------------------------------------------------------------
--------------------- Definitions platform driver callbacks ------------------- 
-----------------------------------------------------------------------------*/

static int ncan_probe( struct platform_device *pdev )
{

}

/*----------------------- Remove module from kernel -------------------------*/

static int ncan_remove( struct platform_device *pdev )
{
	struct resource *res;
	struct net_device *ndev = platform_get_drvdata( pdev );
	struct ncan_priv *priv = netdev_priv( ndev );

	// shut down and remove module from the kernel tables
	unregister_netdev( ndev );

	// free memory
	iounmap( priv->reg_base );
	res = platform_get_resource( pdev, IORESOURCE_MEM, 0 );
	release_mem_region( res->start, resource_size( res ) );

	// free clock source
	clk_put( priv->clk );	// !!!!!!!!

	// free can-device
	free_candev( ndev );

	return 0;
}
 
/*-----------------------------------------------------------------------------
------------------------- Register platform driver ---------------------------- 
-----------------------------------------------------------------------------*/

// definition platform_driver structure
static struct platform_driver ncan_driver = {
	.driver = {
		.name = DRV_NAME,
	},
	.probe = ncan_probe,
	.remove = ncan_remove,
	//.suspend = can_ocp_suspend,
	//.resume = can_ocp_resume,
};

// driver registration
module_platform_driver(ncan_driver);   

/*-----------------------------------------------------------------------------
------------------------- Information about the module ------------------------ 
-----------------------------------------------------------------------------*/

MODULE_AUTHOR("A.Smirnov <altemka@icloud.com>");
MODULE_DESCRIPTION("CAN driver for SoC 1907BM056 ncan RAS");