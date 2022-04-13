#include "Video.hpp"
#include "Sprite.hpp"


#define SUBARU_RESOURCE 1


int main() {
	Video video;

	video.init();
	video.loadAtlasInMemory(SUBARU_RESOURCE);
	Sprite *s = video.createSprite(SUBARU_RESOURCE);

	while(1) ;
	// Sprite *s = video.createSprite(SUBARU_RESOURCE);
	// s.move(10,10);
	// s.nextFrame();

}
