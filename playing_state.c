#include <stdio.h>
#include <rand.h>
#include <time.h>
#include "sprites.c"
#include "pipes.c"
#include <gb/gb.h>

int gravity = 4;
int jumpPower = 30;
int playerPosX = 30;
int playerPosY = 60;
int lastAStatus = 0;
int currentPlayerFrame = 0;
int scrollPlayerOffset = 0;
int spawnMarker = 0;
int currentPoints = 0;
int currentPointCounted = 0;

const int BOTTOM_PIPE_TILE = 8;
const int MID_PIPE_TILE = 10;
const int TOP_PIPE_TILE = 10;
const int SCREEN_MAX_X = 128;

#define MIN_CHARACTER_Y_POS 16
#define MAX_CHARACTER_Y_POS 144

#define NUM_PIPES 1
struct pipe pipes[NUM_PIPES];
int pipeDistanceX = 16;
int pipeSpawnStart = -16;
int pipeSpeed = 3;
int i, j, k, l, m, n, o, p;
int currentScroll = (SCREEN_MAX_X * 2);

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

void handleCharacterExtremes(){
	if(playerPosY < MIN_CHARACTER_Y_POS){
		playerPosY = MIN_CHARACTER_Y_POS;
	}else if(playerPosY > MAX_CHARACTER_Y_POS){
		playerPosY = MAX_CHARACTER_Y_POS;
	}
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

void checkForCollisions(){
	if(spawnMarker >= 1){
		if(currentScroll >= 217 && currentScroll <= 217 + 16){
			if(playerPosY > (pipes[0].y + 8) * 4 || playerPosY < (pipes[0].y - 8) * 4){
				transitionToGameover();
			}else{
				currentPointCounted = 1;
				currentPoints += 1;
			}
		}else{
			currentPointCounted = 0;
		}
	}
}

void drawPipe(int pipeNum){
	set_bkg_tiles(0, 0, 2, 28, pipes[pipeNum].pipeData);
}

void clearPipe(int pipeNum){
	set_bkg_tiles(pipes[pipeNum].x, pipes[pipeNum].y, 2, 28, ClearPipeBkgData);
}

void clearBackground(){
	set_bkg_tiles(0, 0, 32, 32, ClearBkgData);
}

int pipeToAssign = 0;
void setPipeData(int pipePos){
	for(n = 0; n < 56; n+=4){
		//pipe top opening
		if(n == pipes[pipePos].y - 8){
			pipeToAssign = 0;
		}
		//blank
		else if(n == pipes[pipePos].y - 4){
			pipeToAssign = 1;
		}
		else if(n == pipes[pipePos].y){
			pipeToAssign = 1;
		}
		else if(n == pipes[pipePos].y + 4){
			pipeToAssign = 1;
		}
		//pipe bottom opening
		else if(n == pipes[pipePos].y + 8){
			pipeToAssign = 2;
		}
		//regular pipe
		else if(n < pipes[pipePos].y){
			pipeToAssign = 3;
		}
		else if(n > pipes[pipePos].y){
			pipeToAssign = 3;
		}

		for(o = 0; o < 4; o++){
			pipes[pipePos].pipeData[n + o] = availablePipeTiles[pipeToAssign][o];
		}
	}
}

void initPipes(){
	for(j = 0; j < NUM_PIPES; j++){
		pipes[j].x = -16;
		pipes[j].y = 70;
		pipes[j].tileStart = 2 + (j * 20);

		//bottom pipe
		set_sprite_tile(pipes[j].tileStart, BOTTOM_PIPE_TILE);
		set_sprite_tile(pipes[j].tileStart + 1, BOTTOM_PIPE_TILE + 1);

		//pipe
		set_sprite_tile(pipes[j].tileStart + 2, MID_PIPE_TILE);
		set_sprite_tile(pipes[j].tileStart + 3, MID_PIPE_TILE + 1);

		//top pipe
		set_sprite_tile(pipes[j].tileStart + 4, TOP_PIPE_TILE);
		set_sprite_tile(pipes[j].tileStart + 5, TOP_PIPE_TILE + 1);

		setPipeData(j);
	}
}

void movePipes(){
	for(i = 0; i < NUM_PIPES; i++){
		pipes[i].x = pipes[i].x - pipeSpeed;
		if(currentScroll >= (SCREEN_MAX_X * 2) + 16){
			currentScroll = 16;
			pipes[i].x = -16;
			pipes[i].y = ((rand() % (7 + 1 - 4)) + 4) * 4;
			setPipeData(i);
			drawPipe(i);
			if(spawnMarker < 1){
				spawnMarker += 1;
			}
		}
	}
	currentScroll += pipeSpeed;
	scroll_bkg(pipeSpeed, 0);
}

void playStateUpdate(){
	applyInputForce();
	applyGravity();
	handleCharacterExtremes();

	characterAnimation();
	drawCharacter();

	movePipes();
	checkForCollisions();
}

playStateInit(){
	//srand(time(0));
	currentPoints = 0;
	currentPointCounted = 0;
	set_sprite_data(0, 8, BirdData);
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 2);

	set_bkg_data(0, 64, PipesData);

	clearBackground();
	initPipes();
}
