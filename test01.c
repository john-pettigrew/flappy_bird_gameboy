#include <stdio.h>
#include "sprites.c"
#include <gb/gb.h>

int gravity = 4;
int jumpPower = 25;
int playerPosX = 30;
int playerPosY = 60;
int lastAStatus = 0;
int currentPlayerFrame = 0;

void applyInputForce(){
	if(joypad() == J_A){
		if(lastAStatus == 0){
			lastAStatus = 1;
			playerPosY -= jumpPower;
		}
	}else{
		lastAStatus = 0;
	}
}

void characterAnimation(){
	if(joypad() == J_A){
		currentPlayerFrame = 1;
	}else{
		currentPlayerFrame = 0;
	}
}

void applyGravity(){
	playerPosY += gravity;
}

void drawCharacter(){
	if(currentPlayerFrame == 0){
		set_sprite_tile(0, 0);
		set_sprite_tile(1, 2);
	}else{
		set_sprite_tile(0, 5);
		set_sprite_tile(1, 7);
	}

	move_sprite(0, playerPosX, playerPosY);
	move_sprite(1, playerPosX + 8, playerPosY);
}

void update(){
	applyInputForce();
	applyGravity();

	characterAnimation();
	drawCharacter();
}

void main(){
	SPRITES_8x16;
	set_sprite_data(0, 8, Stripes);
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 2);

	SHOW_SPRITES;

	while(1){
		update();
		delay(50);
	}
}


