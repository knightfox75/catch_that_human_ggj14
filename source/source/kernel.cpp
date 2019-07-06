/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Archivo de gestion del programa

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
Metodos de la clase "CKernel"
*/

// Contructor clase CKernel
CKernel::CKernel(void) {

	// Crea los objetos de las clases principales del programa
	System = new CSystem();			// Objetos del sistema
	Sound = new CSound();			// Objetos de la gestion de sonido

}



// Destructor clase CKernel
CKernel::~CKernel(void) {

	// Elimina los objetos al destruir la clase
	delete Sound;
	Sound = NULL;
	delete System;
	System = NULL;

}



// Metodos globales de la clase CKernel
CKernel* Kernel;



// Nucleo de ejecucion del programa
void CKernel::Run(void) {

	// Repite para siempre
	while (1) {

		// Splash Screens
		Splash = new CSplash();
		Splash->SplashScreens();
		delete Splash;
		Splash = NULL;

		// Titulo
		Title = new CTitle();
		Title->Run();
		delete Title;
		Title = NULL;

		// Ejecuta el juego
		Game = new CGame();
		Game->Run();
		delete Game;
		Game = NULL;

	}

}
