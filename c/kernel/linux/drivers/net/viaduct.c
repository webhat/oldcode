/**************************************************************************
 * This module is an example of how to make a kernel module, not everything
 * is correct, however I have tryed to make it as correct as possible.
 *
 *                                    04/03/2000
 *                                    -- Daniel Crompton
 **************************************************************************
 * $Id: $
 **************************************************************************/

/*
 *   Copyright (C) 1997-2000  Daniel W. Crompton <redhat@rphh.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * #define KERN_EMERG      "<0>"   system is unusable
 * #define KERN_ALERT      "<1>"   action must be taken immediately
 * #define KERN_CRIT       "<2>"   critical conditions
 * #define KERN_ERR        "<3>"   error conditions
 * #define KERN_WARNING    "<4>"   warning conditions
 * #define KERN_NOTICE     "<5>"   normal but significant condition
 * #define KERN_INFO       "<6>"   informational
 * #define KERN_DEBUG      "<7>"   debug-level messages
 *
 * printk(KERN_WARNING "warning: stuff happened %s\n", @args);
 *
 * printk is basically a printf to syslogd.
 */

/* struct device {
 * 			char *name;									// name of module
 *      char *dev_addr;							// device memory address
 *      int mem_start;							// memory start
 *      struct net_local *priv;			// unknown
 *      int tx_queue_len;						// unknown
 *      int flags;									// unknown
 *      int start;									// unknown
 *      int tbusy;									// unknown
 *      char *mc_list;							// multicast list
 *      __u8 broadcast;							// broadcast address ???
 *
 * * FUNCTIONS *
 *      char *open;	          	    // open function
 *      char *close;	          		// close function (not known if it exists)
 *      char *stop;	          			// stop function
 *      char *hard_start_xmit;      // start_xmit function
 *      char *get_stats;		        // stats function
 *      char *set_multicast_list;   // set MC addresses function
 * };
 */

/* $Id: $ */

#include <linux/module.h>
#include <linux/init.h>

#include <linux/config.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/major.h> /* Using HD_MAJOR for block device */
#include <linux/sched.h>
#include <linux/malloc.h>
#include <linux/fcntl.h>
#include <linux/delay.h>


#include <linux/netdevice.h>
#include <linux/inetdevice.h>

#define MAJOR_NR HD_MAJOR

/* unknown */
#include <asm/irq.h>
#include <asm/uaccess.h>
#include <asm/system.h>
/* end unknown */

#ifdef MODULE

//static char *parport[LP_NO] = { NULL,  };
static int reset = 0;

MODULE_AUTHOR( "Daniel Crompton");
MODULE_DESCRIPTION( "Kernel plugin for viaduct.");

MODULE_PARM(reset, "i");

//MODULE_PARM( (static *char), "1-" __MODULE_STRING( /* NUMBER */ ) "s");
//MODULE_SUPPORTED_DEVICE( char);

static char devicename[9] = { 0, };

/*
 * At this moment I have no idea what this is for,
 * but I will find out.
 */
static struct device dev_viaduct = {
        devicename,
        0, 0, 0, 0,
        1, 5,
        0, 0, 0, NULL, viaduct_setup
};


#else

static int reset __initdata = 0;

static int viaduct_open( struct device *dev);
static int viaduct_close( struct device *dev);
static int viaduct_start_xmit( struct sk_buff *skb, struct device *dev);
static net_device_stats *viaduct_get_stats( struct device *dev);

/* define the function you want the kernel to call here,
 * in this case, as with ethertap, I want to receive a
 * device from the kernel event demultiplexor.
 */
__initfunc( int viaduct_setup( struct device *dev)) {
				
				dev->priv = kmalloc( sizeof(struct net_local), GFP_KERNEL);
				if ( dev->priv == NULL)
								return -ENOMEM;
				memset( dev->priv, 0, sizeof(struct net_local));

				dev->open = viaduct_open;
				dev->close = viaduct_close;
				dev->hard_start_xmit = viaduct_start_xmit;
				dev->get_stats = viaduct_get_stats;
				
				ether_setup( dev);
				dev->tx_queue_len = 0;
				dev->flags |= IFF_NOARP;

				return 0;
}

#endif


#ifdef MODULE
int init_module(void) {

				/* In a module, like this, which uses a device
				 * the device must be named in memory and the
				 * device must be bound in /dev/
				 */
				dev_viaduct.base_addr=unit+NETLINK_TAPBASE;
        sprintf(devicename,"viaduct%d",unit);
        if (dev_get(devicename)) {
                printk(KERN_INFO "%s already loaded.\n", devicename);
                return -EBUSY;
        }
        if (register_netdev(&dev_viaduct) != 0)
                return -EIO;
        return 0;
}

void cleanup_module(void)
{
	unsigned int offset;

/*
	unregister_chrdev(HD_MAJOR, "lp");
	for (offset = 0; offset < LP_NO; offset++) {
		if (lp_table[offset].dev == NULL)
			continue;
		parport_unregister_device(lp_table[offset].dev);
	}
 */
}
#endif
