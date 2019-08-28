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

const int numPipes = 2;
struct pipe pipes[2];
int pipeDistance = 125;
int pipeSpawnStart = 20;
int pipeSpeed = 3;
int i, j, k, l, m;

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

movePipes(){
	for(i = 0; i < numPipes; i++){
		pipes[i].x = pipes[i].x - pipeSpeed;
	}
}

void initPipes(){
	for(j = 0; j < numPipes; j++){
		pipes[j].x = pipeSpawnStart + (pipeDistance * j);
		pipes[j].y = 70;
		pipes[j].tileStart = 2 + (j * 16);

		//Pipe top
		set_sprite_tile(pipes[j].tileStart, 8);
		set_sprite_tile(pipes[j].tileStart + 1, 10);

		for(k = 0; k <= 12; k+=2){
			//Pipe bottom
			set_sprite_tile(pipes[j].tileStart + 2 + k, 12);
			set_sprite_tile(pipes[j].tileStart + 3 + k, 14);
		}
	}
}

int pipeStartY;
void drawPipe(int pipeNum){
	//Pipe top
	move_sprite(pipes[pipeNum].tileStart, pipes[pipeNum].x, pipes[pipeNum].y);
	move_sprite(pipes[pipeNum].tileStart + 1, pipes[pipeNum].x+8, pipes[pipeNum].y);
	pipeStartY = pipes[pipeNum].y + 8;

	for(l = 0; l <= 12; l+=2){
		//Pipe bottom
		move_sprite(pipes[pipeNum].tileStart + 2 + l, pipes[pipeNum].x, pipeStartY+(8*l));
		move_sprite(pipes[pipeNum].tileStart + 3 + l, pipes[pipeNum].x+8, pipeStartY+(8*l));
	}
}

void drawAllPipes(){
	for(m = 0; m < numPipes; m++){
		drawPipe(m);
	}
}

void update(){
	applyInputForce();
	applyGravity();

	characterAnimation();
	drawCharacter();

	movePipes();
	drawAllPipes();
}

void main(){
	SPRITES_8x16;
	set_sprite_data(0, 8, BirdData);
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 2);

	set_sprite_data(8, 8, PipesData);

	initPipes();

	SHOW_SPRITES;

	while(1){
		update();
		delay(50);
	}
}


