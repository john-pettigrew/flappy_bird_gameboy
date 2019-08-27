#include <stdio.h>
#include "sprites.c"
#include "pipes.c"
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

int i;
int pipeStartY;
void drawPipe(struct pipe *pipe){
	//Pipe top
	set_sprite_tile(2, 8);
	set_sprite_tile(3, 10);

	move_sprite(2, pipe->x, pipe->y);
	move_sprite(3, pipe->x+8, pipe->y);
	pipeStartY = pipe->y + 8;

	for(i = 0; i <= 12; i+=2){
		//Pipe bottom
		set_sprite_tile(4+i, 12);
		set_sprite_tile(5+i, 14);

		move_sprite(4+i, pipe->x, pipeStartY+(8*i));
		move_sprite(5+i, pipe->x+8, pipeStartY+(8*i));
	}
}
struct pipe p;
void main(){
	SPRITES_8x16;
	set_sprite_data(0, 8, BirdData);
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 2);

	p.x = 75;
	p.y = 70;

	set_sprite_data(8, 8, PipesData);
	
	drawPipe(&p);

	SHOW_SPRITES;

	while(1){
		update();
		delay(50);
	}
}


