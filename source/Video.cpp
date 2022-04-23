#include "Video.hpp"

#include "toolbox.h"

volatile unsigned short* scanline_counter = (volatile unsigned short*) 0x4000006;

Video::Video() {
	REG_DISPLAY = DISP_MODE_0 | DISP_BG0 | DISP_OBJ_MEM | DISP_1D_SPRITE;// | DISP_OBJ_MEM | DISP_BG0  ;

}

void Video::init() {

}

uint32 Video::loadAtlasInMemory(uint16 resourceId) {
	this->atlasManager.loadAtlasInMemory(resourceId);
	return 1;
}

Sprite* Video::createSprite(uint16 resourceId) {
	MemoryTiles& resource = this->atlasManager.getAtlasInMemory(resourceId);
	return this->objectManager.createSprite(resource);
}

void Video::waitVBlank() {
	/* wait until all 160 lines have been updated */
	while (*scanline_counter >= 160);
	while (*scanline_counter < 160);
}


