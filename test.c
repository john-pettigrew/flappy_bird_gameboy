#include "sprites.c"
#include <stdio.h>
#include "pipes.c"

int n, o, pipeToAssign;
int pipePos = 0;

#define NUM_PIPES 1
struct pipe pipes[NUM_PIPES];

int main(){
	
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
			pipes[pipePos].pipeData[n + o] = availablePipeTiles[pipeToAssign][3];
			printf("%d, ", n+o);
		}

	}
	for(n = 0; n < PIPE_DATA_SIZE; n++){
		printf("0x%02x, ", pipes[pipePos].pipeData[n]);
		if(n % 2){
			printf("\n");
		}
	}

}
