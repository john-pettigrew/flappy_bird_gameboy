#include <stdio.h>
#include <gb/gb.h>
#include "playing_state.c"

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
			break;
	}
}

void transitionToGameover(){
	currentGameState = GAMEOVER;
	printf("GAMEOVER");
}

void transitionToPlaying(){
	playStateInit();
	currentGameState = PLAYING;
}

void main(){
	SPRITES_8x16;
	DISPLAY_ON;
	SHOW_SPRITES;
	SHOW_BKG;

	//TEMP
	transitionToPlaying();

	while(1){
		update();
		delay(40);
	}
}
