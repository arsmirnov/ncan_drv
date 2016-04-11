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
#include <linux/platform_device.h>

#include "can_ocp.h"



/*-----------------------------------------------------------------------------
----------------------- Definitions platform driver callbacks ------------------ 
-----------------------------------------------------------------------------*/

static int can23_ocp_probe( struct platform_device *pdev )
{

}

static int can23_ocp_remove( struct platform_device *pdev )
{

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