#include "xiic.h"

XIic_Config XIic_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,axi-iic-2.1", /* compatible */
		0x40800000, /* reg */
		0x0, /* xlnx,ten-bit-adr */
		0x1, /* xlnx,gpo-width */
		0xffff, /* interrupts */
		0xffff /* interrupt-parent */
	},
	 {
		 NULL
	}
};