#include "Video.hpp"
#include "Sprite.hpp"
#include <malloc.h>
#include "input.h"

#define SUBARU_RESOURCE 1

#define DUCK_NUM 2

int main() {
	Video video;

	video.init();
	video.loadAtlasInMemory(SUBARU_RESOURCE);
	
	Sprite *s = video.createSprite(SUBARU_RESOURCE);
	// Sprite *sprites[128];
	// for (uint32 i = 0; i < 127; i++)
	// {
	// 	sprites[i] = video.createSprite(SUBARU_RESOURCE);
	// 	sprites[i]->setX((i*16) % 208);
	// 	sprites[i]->setY(((i * 16) / 208) * 16);
	// }
	// video.removeSprite(sprites[3]);
	// Sprite *sa = video.createSprite(SUBARU_RESOURCE);
	// sa->setY(100);


	uint32 dx, dy, d = 0;
	// uint16 x,y;
	while(1) {
		dx = 0, dy = 0;

		key_poll();
		if (key_pushed(KEY_LEFT)) {
			dx--;
		}
		if (key_pushed(KEY_RIGHT)) {
			dx++;
		}
		if (key_pushed(KEY_UP)) {
			dy--;
		}
		if (key_pushed(KEY_DOWN)) {
			dy++;
		}

		s->move(dx, dy);
		

		if (d % 5 == 0) {
			s->setFrame(d/5);
			// s->nextFrame();
			// d = 0;
		}
		video.waitVBlank();
		d++;
	}
}
