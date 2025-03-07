#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include "toolbox.h"

#define INLINE static inline
extern u16 __key_curr, __key_prev;

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0x03FF

// Polling function
INLINE void key_poll()
{
	__key_prev= __key_curr;
	__key_curr= ~REG_KEY_INPUT & KEY_MASK;
}

INLINE u32 key_hit(u32 key)
{
	return ( __key_curr &~ __key_prev) & key;
}

INLINE u32 key_pushed(u32 key)
{
	return ( __key_curr & key);
}

#endif
