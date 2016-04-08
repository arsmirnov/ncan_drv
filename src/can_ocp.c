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

#include "can_ocp.h"






  
/*-----------------------------------------------------------------------------
------------------------- Register platform driver ---------------------------- 
-----------------------------------------------------------------------------*/

module_platform_driver();   