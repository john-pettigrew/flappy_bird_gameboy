#include <gb/gb.h>

void checkForRestart(){
	if(joypad() == J_START){
		transitionToPlaying();
	}
}

void playCrashSound(){
	NR41_REG = 0x03;
	NR42_REG = 0x61;
	NR43_REG = 0x79;
	NR44_REG = 0xc0;
}

void gameoverStateUpdate(){
	checkForRestart();
}

gameoverStateInit(){
	playCrashSound();
	printf("GAMEOVER\n");
	printf("PRESS START");
}
