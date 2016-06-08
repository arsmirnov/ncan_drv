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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );	
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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );
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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );
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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );
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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );
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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );
	
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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );

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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );

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
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );
}

static int ncan_platform_remove( struct platform_device *pdev )
{
	printk( KERN_DEBUG "%s\n", __FUNCTION__ );

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