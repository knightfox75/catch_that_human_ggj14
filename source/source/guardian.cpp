/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Guardian (Gato)

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
Metodos de la clase "CGuard"
*/

// Contructor clase CGuard
CGuard::CGuard(void) {

	// Inicializa variables
	pos_x = 0, pos_y = 0;
	touch = false;
	new_touch = false;
	touch_time = 0;
	state = 0, next_state = 0;
	points = 0;

}

// Destructor clase CGuard
CGuard::~CGuard(void) {
}

// Metodos globales de la clase CGuard
CGuard* Guard;



// Carga los archivos
void CGuard::Load(void) {

	NF_LoadSpriteGfx("sprite/guardian", GUARD_GFX, 64, 64);	
	NF_LoadSpritePal("sprite/guardian", GUARD_PAL);

	NF_LoadSpriteGfx("sprite/face", GUI_GUARD_FACE_GFX, 32, 32);
	NF_LoadSpriteGfx("sprite/numbers", GUI_GUARD_NUM_GFX, 16, 32);	
	NF_LoadSpritePal("sprite/guard_gui", GUI_GUARD_PAL);

}



// Prepara los graficos en VRAM
void CGuard::Vram(void) {

	NF_VramSpriteGfx(0, GUARD_GFX, GUARD_GFX, false);
	NF_VramSpritePal(0, GUARD_PAL, GUARD_PAL);

	NF_VramSpriteGfx(0, GUI_GUARD_FACE_GFX, GUI_GUARD_FACE_GFX, false);
	NF_VramSpriteGfx(0, GUI_GUARD_NUM_GFX, GUI_GUARD_NUM_GFX, false);
	NF_VramSpritePal(0, GUI_GUARD_PAL, GUI_GUARD_PAL);

}



// Crea el sprite del Guardian en las coordenadas dadas
void CGuard::Create(s32 x, s32 y) {

	// Guarda la posicion
	pos_x = (x << 8), pos_y = (y << 8);

	// Crea el sprite de Jake con su grafico y paletas
	NF_CreateSprite(0, GUARD_SPR, GUARD_GFX, GUARD_PAL, (pos_x >> 8), (pos_y >> 8));
	NF_SpriteLayer(0, GUARD_SPR, 3);
	NF_SpriteFrame(0, GUARD_SPR, 0);
	NF_CreateSprite(0, (GUARD_SPR + 1), GUARD_GFX, GUARD_PAL, (pos_x >> 8), ((pos_y >> 8) + 64));
	NF_SpriteLayer(0, (GUARD_SPR + 1), 3);
	NF_SpriteFrame(0, (GUARD_SPR + 1), 1);

}



// Mueve a Jake
void CGuard::Move(void) {

	// Variables
	s32 x = 0;

	// Segun el estado
	switch (state) {

		// Preparacion del ataque
		case 0:
			if (!Touchpad->touch) {
				touch = false;
				new_touch = true;
				next_state = 1;
			}
			break;

		// Espera a que se pulse la pantalla
		case 1:
			if (Touchpad->touch) {
				new_touch = false;
				touch = true;
				touch_time = 10;
				next_state = 2;
			}
			break;

		// Espera a la animacion
		case 2:
			touch_time --;
			if (touch_time <= 0) {
				touch = false;
				touch_time = 20;
				next_state = 3;
			}
			break;

		// Rearme
		case 3:
			touch_time --;
			if (touch_time <= 0) {
				touch_time = 0;
				next_state = 0;
			}
			break;

	}

	// Cambio de estado
	if (state != next_state) state = next_state;


	// Si se pone en marcha, prepara al guardian
	if (Jake->go) {
		state = 0;
		next_state = 0;
		touch = false;
		new_touch = false;
		Jake->go = false;
	}


	// Dependiendo de si tocas la pantalla
	if (touch) {
		NF_SpriteFrame(0, GUARD_SPR, 2);
		NF_SpriteFrame(0, (GUARD_SPR + 1), 3);
	} else {
		NF_SpriteFrame(0, GUARD_SPR, 0);
		NF_SpriteFrame(0, (GUARD_SPR + 1), 1);
	}

	// Si le golpeas, que suelte el brick de leche
	if (touch && Milk->child) {
		x = ((Jake->pos_x >> 8) + 16);
		if ((x >= 134) && (x <= 152)) {
			// Si le has dado, actua en consecuencia
			Milk->child = false;
			Jake->walk_speed = -(Jake->base_speed << 1);
			Jake->next_state = JAKE_ST_DEAD;
			// Marca un punto
			UpdateGui();
		}
	}

}


// Crea la GUI
void CGuard::CreateGui(void) {

	// Variables
	u8 n = 0;

	// Icono
	NF_CreateSprite(0, GUI_GUARD_FACE_SPR, GUI_GUARD_FACE_GFX, GUI_GUARD_PAL, 144, 8);
	NF_SpriteLayer(0, GUI_GUARD_FACE_SPR, 3);
	NF_SpriteFrame(0, GUI_GUARD_FACE_SPR, 0);

	// Marcador
	for (n = 0; n < 4; n ++) {
		NF_CreateSprite(0, (GUI_GUARD_NUM_SPR + n), GUI_GUARD_NUM_GFX, GUI_GUARD_PAL, (184 + (n << 4)), 8);
		NF_SpriteLayer(0, (GUI_GUARD_NUM_SPR + n), 3);
		NF_SpriteFrame(0, (GUI_GUARD_NUM_SPR + n), 0);
	}
	NF_SpriteFrame(0, GUI_GUARD_NUM_SPR, 10);

}



// Actualiza el marcador
void CGuard::UpdateGui(void) {

	// Variables
	s16 a, b, c;
	s16 p;

	// Actualiza el marcador
	points ++;
	if (points > 999) points = 999;
	p = points;

	// Calcula los digitos
	a = (int)(p / 100);
	p -= (a * 100);
	b = (int)(p / 10);
	c = p - (b * 10);

	// Actualiza la GUI
	NF_SpriteFrame(0, (GUI_GUARD_NUM_SPR + 1), a);
	NF_SpriteFrame(0, (GUI_GUARD_NUM_SPR + 2), b);
	NF_SpriteFrame(0, (GUI_GUARD_NUM_SPR + 3), c);

}
