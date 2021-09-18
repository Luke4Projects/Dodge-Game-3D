#include "game.h"

int main(int argv, char* argc[]) {
	
	Game game;
	if (game.Init() != 0) {
		return -1;
	}
	game.RunMainLoop();
	game.Cleanup();

	return 0;
}