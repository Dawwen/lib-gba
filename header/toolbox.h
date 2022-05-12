#ifndef TOOLBOX_H
#define TOOLBOX_H

#define MEM_IO   0x04000000

#define DISP_MODE_0		0x0000
#define DISP_OBJ_MEM	0x1000
#define DISP_1D_SPRITE	0x0040
#define DISP_BG0		0x0100
#define DISP_BG1		0x0200

#define REG_DISPLAY			(*((volatile uint32 *)(MEM_IO)))
#define REG_DISPLAY_VCOUNT	(*((volatile uint32 *)(MEM_IO + 0x0006)))

#define REG_KEY_INPUT		(*((volatile uint32 *)(MEM_IO + 0x0130)))

#endif