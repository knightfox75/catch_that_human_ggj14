/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Base

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
Metodos de la clase "CDraw"
*/

// Contructor clase CDraw
CDraw::CDraw(void) {

	// Inicializa las variables
	cat_print_blink = false;
	cat_print_time = 0;

}

// Destructor clase CDraw
CDraw::~CDraw(void) {
}

// Metodos globales de la clase CDraw
CDraw* Draw;



// Controla la GUI inferior (huella del gato)
void CDraw::CatPrint(void) {

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

}



// Crea los graficos
void CDraw::Create(void) {

	// Crea los fondos
	NF_CreateTiledBg(0, 3, "kitchen");
	NF_CreateTiledBg(1, 3, "to_play");
	NF_CreateTiledBg(1, 2, "cat_print");
	NF_HideBg(1, 2);

	// Crea los sprites
	Jake->Vram();
	Jake->Create(-64, -64);
	Milk->Vram();
	Milk->Create(-64, -64);
	Milk->CreateGui();
	Guard->Vram();
	Guard->Create(95, 63);
	Guard->CreateGui();

}



// Actualiza las pantallas
void CDraw::UpdateScreen(void) {

	// Dibuja la GUI inferior
	CatPrint();

	// Actualiza el OAM de NFlib
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);

	// Sincronismo
	swiWaitForVBlank();

	// Actualiza el OAM de Libnds
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

}
