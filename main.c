#include <stdio.h>
#include <gb/gb.h>
#include "playing_state.c"
#include "gameover_state.c"

enum GameState{MENU, PLAYING, GAMEOVER};
enum GameState currentGameState = PLAYING;

void update(){
	switch(currentGameState){
		case MENU:
			break;
		case PLAYING:
			playStateUpdate();
			break;
		case GAMEOVER:
			gameoverStateUpdate();
			break;
	}
}

void transitionToGameover(){
	gameoverStateInit();
	currentGameState = GAMEOVER;
}

void transitionToPlaying(){
	playStateInit();
	currentGameState = PLAYING;
}

void enableSound(){
	NR52_REG = 0x80;
	NR50_REG = 0x77;
	NR51_REG = 0xFF;
}

void main(){
	SPRITES_8x16;
	DISPLAY_ON;
	SHOW_SPRITES;
	SHOW_BKG;
	SHOW_WIN;
	enableSound();

	//TEMP
	transitionToPlaying();

	while(1){
		update();
		delay(40);
	}
}
