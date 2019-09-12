#include <gb/gb.h>

void checkForRestart(){
	if(joypad() == J_START){
		transitionToPlaying();
	}
}

void gameoverStateUpdate(){
	checkForRestart();
}

gameoverStateInit(){
	printf("GAMEOVER\n");
	printf("PRESS START");
}
