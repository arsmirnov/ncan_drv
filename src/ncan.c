/***************************************************************************
	ncan.c	-	module of kernel.
    -------------------
    author		: A.Smirnov 
    email		: altemka@icloud.com

    CAN driver for SoC 1907BM056.
***************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/interrupt.h>
#include <linux/can/dev.h>
#include <linux/clk.h>
#include <linux/types.h>
#include <linux/io.h>
#include <linux/platform_device.h>

#include "ncan.h"
#include "soc-1907BM056_can.h"


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
---------------------- Basic functions: W/R registers value ------------------- 
-----------------------------------------------------------------------------*/

/****
* @fn ncan_write
*
* Write a value to device registers. 
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
*	reg - register offset.
*	value - value for writing.
* @return:
*	none		
**/
static inline void ncan_write( const struct ncan_priv *priv, u32 reg, u32 value )
{
	iowrite32( value, priv->reg_base + reg );
}

/****
* @fn ncan_read
*
* Read a value from the device register.
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
*	reg - register offset.
* @return:
*	value read from register	
**/
static inline u32 ncan_read( const struct ncan_priv *priv, u32 reg )
{
	return ioread32( priv->reg_base + reg );
}

/****
* @fn ncan_set_bit
*
* Set corresponding bit in register.
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
*	reg - register offset.
*	bit_mask - (1<<num_bit)
* @return:
*	 none 
**/
static inline void ncan_set_bit( const struct ncan_priv *priv, u32 reg, u32 bit_mask )
{
	u32 value = ( ncan_read( priv, reg ) | bit_mask );
	ncan_write( priv, reg, value );
}

/****
* @fn ncan_clear_bit
*
* Clear corresponding bit in register.
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
*	reg - register offset.
*	bit_mask - (1<<num_bit)
* @return:
*	 none 
**/
static inline void ncan_clear_bit( const struct ncan_priv *priv, u32 reg, u32 bit_mask )
{
	u32 value = ( ncan_read( priv, reg ) & (~bit_mask) );
	ncan_write( priv, reg, value );
}

/****
* @fn ncan_get_bit
*
* Get value corresponding bit.
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
*	reg - register offset.
*	bit_mask - (1<<num_bit)
* @return:
*	 bit value 
**/
static inline u32 ncan_get_bit( const struct ncan_priv *priv, u32 reg, u32 bit_mask )
{
	u32 value = ( ncan_read( priv, reg ) & bit_mask );
	return ( ( value ) ? 1 : 0 );
}

/*-----------------------------------------------------------------------------
------------------ Definitions functions for working with CAN ----------------- 
-----------------------------------------------------------------------------*/

/****
* @fn ncan_set_bittiming		
*
* Set bit-timing parameters.
*
* @param: 
*	ncan_priv - pointer to structure with CAN private data.
* @return:
*	null
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

	ncan_write( priv, NCAN_REG_TIME_CFG, ncan_btc );
	netdev_info( priv->ndev, "Setting register: TimeConfig = %#X\n", ncan_btc );

	return 0;
}      

/****
* @fn ncan_init		
*
* Initialization CAN controller.
*
* @param: 
*	ndev - pointer to structure with network device data
* @return:
*	none
**/
static void ncan_init( struct net_device *ndev )
{
	// Get private data from net_device structure 
	struct ncan_priv *priv = netdev_priv( ndev );

	netdev_info( ndev, "Initialization ncan...\n" );
	
	// --------- Initialization CAN ----------
	// 1. Software reset
	ncan_set_bit( priv, NCAN_REG_CNTRL, NCAN_CNTRL_CAN_RS_SRES );
	// 2. Setting bit-timing configuration
	ncan_set_bittiming( priv );
	// 3. Enable CAN and extern transceiver
	u32 val = NCAN_CNTRL_CAN_RS_ABO_EN | NCAN_CNTRL_CAN_RS_EN;
	ncan_write( priv, NCAN_REG_CNTRL, val );
}

/****
* @fn ncan_interrupt_handler
*
* Handler of CAN interrupts.
*
* @param: 
*	
* @return:
*	null
**/
static irqreturn_t ncan_interrupt_handler( int irq, void *dev_id )
{

}

/****
* @fn ncan_start
*
* Initialization CAN device.
*
* @param: 
*	ndev - pointer to structure with network device data
* @return:
*	none
**/
static void ncan_start( struct net_device *ndev )
{

}

/****
* @fn ncan_stop
*
* CAN device stop.
*
* @param: 
*	ndev - pointer to structure with network device data
* @return:
*	none
**/
static void ncan_stop( struct net_device *ndev )
{

}

/*-----------------------------------------------------------------------------
---------------------------- Network device driver ---------------------------- 
-----------------------------------------------------------------------------*/

// ----------------------- Network device callbacks ---------------------------

/****
* @fn ncan_net_device_open
*
* Network device driver callback: open network device.
*
* @param: 
*	ndev - pointer to structure with network device data
* @return:
*	null
**/
static int ncan_net_device_open( struct net_device *ndev )
{
	// Get private data from net_device structure 
	struct ncan_priv *priv = netdev_priv( ndev );
	int err_status;	
	
	// Register interrupt handler
	err_status = request_irq( ndev->irq, ncan_interrupt_handler, IRQF_SHARED, ndev->name, ndev );
	if( err_status )
	{
		netdev_err( ndev, "Request interrupt is failed: %d\n", err_status );
		return err_status;
	}

	// Open CAN device(check params and switch on)
	err_status = open_candev(ndev);
	if( err_status )
	{
		netdev_err( ndev, "Cannot open CAN device: %d\n", err_status );
		free_irq( ndev->irq, ndev );
		return err_status;
	}
	
	// Initialization CAN
	ncan_start( ndev );
	// Enable NAPI scheduling
	napi_enable( &priv->napi );
	// Allow working net device(rx/tx)
	netif_start_queue( ndev );
	
	return 0;
}

/****
* @fn ncan_net_device_close
*
* Network device driver callback: close network device.
*
* @param: 
*	ndev - pointer to structure with network device data
* @return:
*	null
**/
static int ncan_net_device_close( struct net_device *ndev )
{
	// Get private data from net_device structure 
	struct ncan_priv *priv = netdev_priv( ndev );
	
	// Stop working net device(rx/tx)
	netif_stop_queue( ndev );
	// Disable NAPI scheduling
	napi_disable( &priv->napi );
	// Stop CAN device work
	ncan_stop( ndev );
	// Free interrupt
	free_irq( ndev->irq, ndev );
	// Close CAN device
	close_candev( ndev );

	return 0;
}

/****
* @fn ncan_net_device_xmit
*
* Network device driver callback: called when a packet needs to be transmitted.
*
* @param: 
*	ndev - pointer to structure with network device data
* @return:
*	null
**/
static int ncan_net_device_xmit( struct net_device *ndev )
{

	return 0;
}

// ------------ Definition structure with network device options --------------

static const struct net_device_ops ncan_net_device_ops = {
	.ndo_open			= ncan_net_device_open,	
	.ndo_stop			= ncan_net_device_close,
	.ndo_start_xmit		= ncan_net_device_xmit,
	.ndo_change_mtu		= can_change_mtu,
};

/*-----------------------------------------------------------------------------
--------------------------- Platform device driver ----------------------------
-----------------------------------------------------------------------------*/

static int ncan_platform_probe( struct platform_device *pdev )
{

}

static int ncan_platform_remove( struct platform_device *pdev )
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

// ------------ Definition structure with parameters platform driver ----------

static struct platform_driver ncan_driver = {
	.driver = {
		.name = DRV_NAME,
	},
	.probe = ncan_probe,
	.remove = ncan_remove,
};

/*-----------------------------------------------------------------------------
----------------- Functions of module initialization and exit ----------------- 
-----------------------------------------------------------------------------*/

/****
* @fn ncan_module_init
*
* This function is called when module is loaded in kernel.
*
* @param: 
*	none
* @return:
*	if everything is good - 0, otherwise any other value
**/
static int __init ncan_module_init( void )
{
	int status;

	printk( KERN_INFO "start module %s...\n", DRV_NAME );

	// Register of platform device
	status = platform_device_register(&ncan_device);
	// Register of platform driver
	status |= platform_driver_register(&ncan_driver);

	return status;
} 

/****
* @fn ncan_module_exit
*
* This function is called when module is unloaded from kernel.
*
* @param: 
*	none
* @return:
*	none
**/
static void __exit ncan_module_exit( void )
{

	printk( KERN_INFO "stop module %s...\n", DRV_NAME );

	// Unregister of platform device
	platform_device_register(&ncan_device);
	// Unregister of platform driver
	platform_driver_register(&ncan_driver);
} 

// ---------------------- Register init/exit functions ------------------------

module_init( ncan_module_init );
module_exit( ncan_module_exit );

/*-----------------------------------------------------------------------------
------------------------- Information about the module ------------------------ 
-----------------------------------------------------------------------------*/

MODULE_AUTHOR("A.Smirnov <altemka@icloud.com>");
MODULE_DESCRIPTION("CAN driver for SoC 1907BM056");