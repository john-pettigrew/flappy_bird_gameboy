#include <stdio.h>
#include "sprites.c"
#include <gb/gb.h>

void main(){
	set_sprite_data(0, 1, Stripes);
	set_sprite_tile(0, 0);
	set_sprite_tile(0, 1);
	set_sprite_tile(0, 2);
	move_sprite(0, 88, 78);
	SHOW_SPRITES;
}
