/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Titulo

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
Metodos de la clase "CTitle"
*/

// Contructor clase CTitle
CTitle::CTitle(void) {
}

// Destructor clase CTitle
CTitle::~CTitle(void) {
}

// Metodos globales de la clase CTitle
CTitle* Title;



// Inicializa la presentacion
void CTitle::Init(void) {

	// Borra todo el contenido de la memoria
	System->Reset();

	// Pantalla en negro
	setBrightness(3, -16);
	swiWaitForVBlank();

	// Carga los archivos necesarios
	NF_LoadTiledBg("bg/cat_print", "cat_print", 256, 256);
	NF_LoadTiledBg("bg/to_start", "to_start", 256, 256);
	NF_LoadTiledBg("bg/title", "title", 256, 256);

	// Crea los graficos
	NF_CreateTiledBg(0, 3, "title");
	NF_CreateTiledBg(1, 3, "to_start");
	NF_CreateTiledBg(1, 2, "cat_print");

}


// Menu y titulo del juego
void CTitle::Menu(void) {

	// Variables
	bool loop = true;
	u8 cat_print_time = 0;
	bool cat_print_blink = false;
	bool new_touch = false;
	s32 bright = 0;
	u8 state = 0;
	u8 next_state = 0;


	// Menu
	while (loop) {

		// Lee los inputs
		System->ReadKeys();
		System->ReadTouchpad();

		// Estados
		switch (state) {

			case 0:	// Fade in
				bright += 64;
				if (bright > (16 << 8)) {
					bright = (16 << 8);
					next_state = 1;
				}
				setBrightness(3, (-16 + (bright >> 8)));
				break;

			case 1:	// Espera que se pulse
				if (Touchpad->touch) {
					if (new_touch) {
						new_touch = false;
						bright = 0;
						next_state = 2;
					}
				} else {
					new_touch = true;
				}
				break;

			case 2:	// Fade out
				bright += 64;
				if (bright > (16 << 8)) {
					bright = (16 << 8);
					loop = false;
				}
				setBrightness(3, -(bright >> 8));
				break;
		}
		// Cambio de estado?
		if (state != next_state) state = next_state;


		// Parpadeo de la huella
		cat_print_time ++;
		if (cat_print_time >= CAT_PRINT_BLINK) {
			cat_print_time = 0;
			cat_print_blink = !cat_print_blink;
			if (cat_print_blink) {
				NF_ShowBg(1, 2);
			} else {
				NF_HideBg(1, 2);
			}
		}

		// Sincronismo veritcal
		swiWaitForVBlank();

	}

}



// Titulo del juego
void CTitle::Run(void) {

	// Inicializa
	Init();

	// Menu
	Menu();

}



