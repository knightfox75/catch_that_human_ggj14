/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Milk (Leche)

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por Cesar Rincon "NightFox"
	http://www.nightfoxandco.com
	Inicio 24 de Enero del 2014

	(c) 2014 NightFox & Co.

-------------------------------------------------
*/



/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C
#include <stdio.h>
// Includes propietarios NDS
#include <nds.h>
// Includes librerias propias
#include <nf_lib.h>
// Includes del juego
#include "includes.h"



/*
Metodos de la clase "CMilk"
*/

// Contructor clase CMilk
CMilk::CMilk(void) {

	// Inicializa variables
	pos_x = 0, pos_y = 0;
	child = false;
	left = 3;

}

// Destructor clase CMilk
CMilk::~CMilk(void) {
}

// Metodos globales de la clase CMilk
CMilk* Milk;



// Carga los archivos
void CMilk::Load(void) {

	NF_LoadSpriteGfx("sprite/milk", MILK_GFX, 32, 32);	
	NF_LoadSpritePal("sprite/milk", MILK_PAL);

}



// Prepara los graficos en VRAM
void CMilk::Vram(void) {

	NF_VramSpriteGfx(0, MILK_GFX, MILK_GFX, false);
	NF_VramSpritePal(0, MILK_PAL, MILK_PAL);

}



// Crea el sprite de Jake en las coordenadas dadas
void CMilk::Create(s32 x, s32 y) {

	// Guarda la posicion
	pos_x = (x << 8), pos_y = (y << 8);

	// Crea el sprite de Jake con su grafico y paletas
	NF_CreateSprite(0, MILK_SPR, MILK_GFX, MILK_PAL, (pos_x >> 8), (pos_y >> 8));
	NF_SpriteLayer(0, MILK_SPR, 3);
	NF_SpriteFrame(0, MILK_SPR, 0);

}



// Mueve a Jake
void CMilk::Move(void) {

	// Si Jake tiene el brik
	if (child) {
		if (Jake->walk_speed > 0) {
			pos_x = (Jake->pos_x + (16 << 8));
			NF_HflipSprite(0, MILK_SPR, false);
		} else {
			pos_x = (Jake->pos_x - (16 << 8));
			NF_HflipSprite(0, MILK_SPR, true);
		}
		pos_y = (Jake->pos_y + (16 << 8));
	} else {
		pos_y = (159 << 8);
	}

	// Actualiza la posicion del Sprite
	NF_MoveSprite(0, MILK_SPR, (pos_x >> 8), (pos_y >> 8));

}



// Creat la Gui
void CMilk::CreateGui(void) {

	// Variables
	s16 x = 0, y = 8;
	u8 n = 0;

	// Crea la GUI
	for (n = 0; n < 3; n ++) {
		NF_CreateSprite(0, (MILK_GUI + n), MILK_GFX, MILK_PAL, x, y);
		NF_SpriteLayer(0, (MILK_GUI + n), 3);
		NF_SpriteFrame(0, (MILK_GUI + n), 0);
		x += 32;
	}

}



// Actualiza la GUI
void CMilk::UpdateGui(void) {

	// Variables
	u8 n = 0;

	for (n = 0; n < 3; n ++) {
		if (n < left) {
			NF_SpriteFrame(0, (MILK_GUI + n), 0);
		} else {
			NF_SpriteFrame(0, (MILK_GUI + n), 1);
		}
	}


}