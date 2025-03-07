#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "types.h"

#define MEM_IO   0x04000000

#define DISP_MODE_0		0x0000
#define DISP_OBJ_MEM	0x1000
#define DISP_1D_SPRITE	0x0040
#define DISP_BG0		0x0100
#define DISP_BG1		0x0200

#define REG_DISPLAY			(*((volatile u32 *)(MEM_IO)))
#define REG_DISPLAY_VCOUNT	(*((volatile u32 *)(MEM_IO + 0x0006)))

#define BG_PRIORITY		0x0001
#define BG_CHARBLOCK	0x0004
#define BG_8BPP	        0x0080
#define BG_SCREENBLOCK	0x0100
#define BG_SCREENSIZE	0x4000

#define REG_BG0CNT			(*((volatile u32 *)(MEM_IO + 0x0008)))
#define REG_BG1CNT			(*((volatile u32 *)(MEM_IO + 0x000A)))
#define REG_BG2CNT			(*((volatile u32 *)(MEM_IO + 0x000C)))
#define REG_BG3CNT			(*((volatile u32 *)(MEM_IO + 0x000E)))

#define REG_KEY_INPUT		(*((volatile u32 *)(MEM_IO + 0x0130)))

#endif