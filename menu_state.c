#include <gb/gb.h>

void checkForStart(){
	if(joypad() == J_START){
		transitionToPlaying();
	}
}

void menuStateUpdate(){
	checkForStart();
}

menuStateInit(){
	font_t min_font;

	font_init();
	min_font = font_load(font_min);
	font_set(min_font);

	clearWindow();
	clearBackground();

	set_win_tiles(0, 0, 20, 18, menuScreen);
}
