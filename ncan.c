/***************************************************************************
	can_ocp.c	-	module of kernel
    -------------------
    author		: a.smirnov 
    email		: asmirnov.cs.niisi.ras.ru 

    Driver for CAN OCP.
 ***************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/can/dev.h>
#include <linux/clk.h>
#include <linux/platform_device.h>

#include "can_ocp.h"

/*-----------------------------------------------------------------------------
----------------- Definitions functions for working with CAN ------------------
-----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
--------------------- Definitions platform driver callbacks ------------------- 
-----------------------------------------------------------------------------*/

static int can23_ocp_probe( struct platform_device *pdev )
{

}

/*----------------------- Remove module from kernel -------------------------*/

static int can23_ocp_remove( struct platform_device *pdev )
{
	struct resource *res;
	struct net_device *ndev = platform_get_drvdata( pdev );
	struct can23_ocp *priv = netdev_priv( ndev );

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
static struct platform_driver can23_ocp = {
	.driver = {
		.name = DRV_NAME,
	},
	.probe = can23_ocp_probe,
	.remove = can23_ocp_remove,
	//.suspend = can_ocp_suspend,
	//.resume = can_ocp_resume,
};

// driver registration
module_platform_driver(can23_ocp);   

/*-----------------------------------------------------------------------------
------------------------- Information about the module ------------------------ 
-----------------------------------------------------------------------------*/

MODULE_AUTHOR("A.Smirnov <asmirnov.cs.niisi.ras.ru>");
MODULE_DESCRIPTION("CAN23 netdevice driver");
