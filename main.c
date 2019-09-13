#include <stdio.h>
#include <gb/gb.h>
#include "playing_state.c"
#include "gameover_state.c"
#include "menu_state.c"

enum GameState{MENU, PLAYING, GAMEOVER};
enum GameState currentGameState = PLAYING;

void clearWindow(){
	set_win_tiles(0, 0, 32, 32, ClearBkgData);
}

void clearBackground(){
	set_bkg_tiles(0, 0, 32, 32, ClearBkgData);
}

void update(){
	switch(currentGameState){
		case MENU:
			menuStateUpdate();
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

void transitionToMenu(){
	menuStateInit();
	currentGameState = MENU;
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
	transitionToMenu();

	while(1){
		update();
		delay(40);
	}
}
