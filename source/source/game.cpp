/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Archivo de gestion de las pantallas de presentacion

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
Metodos de la clase "CGame"
*/

// Contructor clase CGame
CGame::CGame(void) {

	// Crea los objetos necesarios
	Draw = new CDraw();		// Dibujado de elementos en pantalla
	Jake = new CJake();		// Sprites
	Milk = new CMilk();
	Guard = new CGuard();

}

// Destructor clase CGame
CGame::~CGame(void) {

	// Destruye todos los elementos
	delete Guard;
	Guard = NULL;
	delete Milk;
	Milk = NULL;
	delete Jake;
	Jake = NULL;
	delete Draw;
	Draw = NULL;

}

// Metodos globales de la clase CGame
CGame* Game;



// Ejecuta el juego
void CGame::Run(void) {

	// Inicializa
	Init();

	// Ejecuta el juego
	Play();

	// Game over
	GameOver();

}



// Inicializa el juego
void CGame::Init(void) {

	// Variables
	s32 bright = 0;

	// Borra todo el contenido de la memoria
	System->Reset();

	// Pantalla en negro
	setBrightness(3, -16);
	swiWaitForVBlank();

	// Carga los archivos
	LoadFiles();

	// Crea los graficos necesarios
	Draw->Create();

	// Inicializa a Jake
	Jake->pos_x = -(32 << 8) ;
	Jake->pos_y = (129 << 8);
	Jake->walk_speed = 0;

	// Inicializa el brik de leche
	Milk->pos_x = (223 << 8);
	Milk->pos_y = (159 << 8);

	// Inicializa el escenario
	Jake->Move();
	Milk->Move();
	Guard->Move();

	// Restaura el brillo
	while (bright < (16 << 8)) {
		bright += 64;
		if (bright > (16 << 8)) bright = (16 << 8);
		setBrightness(3, (-16 + (bright >> 8)));
		Draw->UpdateScreen();
	}
	setBrightness(3, 0);
	swiWaitForVBlank();

}



// Carga los archivos
void CGame::LoadFiles(void) {

	// Carga los archivos necesarios de fondos
	NF_LoadTiledBg("bg/dear_cat", "dear_cat", 256, 256);
	NF_LoadTiledBg("bg/to_play", "to_play", 256, 256);
	NF_LoadTiledBg("bg/to_exit", "to_exit", 256, 256);
	NF_LoadTiledBg("bg/cat_print", "cat_print", 256, 256);
	NF_LoadTiledBg("bg/kitchen", "kitchen", 256, 256);
	NF_LoadTiledBg("bg/game_over", "game_over", 256, 512);

	// Carga los archivos necesarios de sprites
	Jake->Load();
	Milk->Load();
	Guard->Load();

}



// Nucleo del juego
void CGame::Play(void) {

	// Variables
	bool loop = true;
	
	while (loop) {

		// Lee el teclado
		System->ReadKeys();
		System->ReadTouchpad();

		// Control del personaje
		loop = !Jake->AI();
		Jake->Move();

		// Brik de leche
		Milk->Move();

		// Ataque del minino
		Guard->Move();

		// Actualiza la pantalla y espera al sincronismo
		Draw->UpdateScreen();

	}

}



// Muestra la pantalla de Game Over
void CGame::GameOver(void) {

	// Variables
	s32 y = (320 << 8);
	s32 speed = (1 << 8);
	bool new_touch = false;
	bool loop = true;
	s32 bright = 0;

	// Crea el fondo de game over
	NF_CreateTiledBg(0, 0, "game_over");
	NF_ScrollBg(0, 0, 0, (y >> 8));
	NF_CreateTiledBg(1, 3, "to_exit");
	NF_HideBg(1, 2);

	// Animacion de la pantalla Game Over
	while (y > (128 << 8)) {

		// Mueve el fondo
		speed += 64;
		if (speed > (16 << 8)) speed = (16 << 8);
		y -= speed;
		NF_ScrollBg(0, 0, 0, (y >> 8));

		// Actualiza la pantalla y espera al sincronismo
		swiWaitForVBlank();

	}

	// Ajusta la posicion del fondo al salir
	NF_ScrollBg(0, 0, 0, 128);

	// Espera a que se toque la pantalla y sal
	while (loop) {

		// Lee la entrada
		System->ReadKeys();
		System->ReadTouchpad();

		// Detecta la pulsacion
		if (Touchpad->touch) {
			if (new_touch) {
				new_touch = false;
				loop = false;
			}
		} else {
			new_touch = true;
		}

		// Actualiza la pantalla
		Draw->UpdateScreen();

	}

	// Fade out y sal
	while (bright < (16 << 8)) {
		bright += 64;
		if (bright > (16 << 8)) bright = (16 << 8);
		setBrightness(3, -(bright >> 8));
		Draw->UpdateScreen();
	}
	setBrightness(3, -16);
	swiWaitForVBlank();

}