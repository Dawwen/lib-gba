#include "Video.hpp"
#include "Sprite.hpp"


#define SUBARU_RESOURCE 1


int main() {
	Video video;

	video.init();
	video.loadAtlasInMemory(SUBARU_RESOURCE);
	Sprite *s = video.createSprite(SUBARU_RESOURCE);

	uint32 dx = 1, dy = 1, d = 0;
	uint16 x,y;
	while(1) {
		x = s->getX();
		y = s->getY();

		if (x < 0 || x  > 240 - 32) {
			dx = - dx;
		}
		if (y < 0 || y  > 160 - 32) {
			dy = - dy;
		}

		s->move(dx,dy);
		if (d == 5) {
			s->nextFrame();
			d = 0;
		}
		video.waitVBlank();
		d++;
	}

	// Sprite *s = video.createSprite(SUBARU_RESOURCE);
	// s.move(10,10);
	// s.nextFrame();

}
