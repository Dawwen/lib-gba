#include "video.h"
#include "toolbox.h"

namespace video {

volatile unsigned short* scanline_counter = (volatile unsigned short*) 0x4000006;

static VideoManager* 	videoManagerCreated		= nullptr; 
static ResourceManager* resourceManagerCreated 	= nullptr; 


void
setupDefaultMode0()
{
	REG_DISPLAY = DISP_MODE_0 | DISP_BG0 | DISP_OBJ_MEM | DISP_1D_SPRITE;
	REG_BG0CNT = 31 * BG_SCREENBLOCK; 
}


void
waitVBlank()
{
	/* wait until all 160 lines have been updated */
	while (*scanline_counter >= 160);
	while (*scanline_counter < 160);
}

VideoManager*
getVideoManager()
{
	if (!videoManagerCreated)
	{
		videoManagerCreated = new VideoManager();
	}
	return videoManagerCreated;
}

ResourceManager*
createResourceManager(void* startData, void* endData)
{
	resourceManagerCreated = new ResourceManager(startData, endData);
	return resourceManagerCreated;
}

ResourceManager*
getResourceManager()
{
	// if (!resourceManagerCreated)
	// {
	// 	resourceManagerCreated = new ResourceManager();
	// }
	return resourceManagerCreated;
}

}
