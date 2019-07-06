#ifndef __GAME_H__
#define __GAME_H__



/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Archivo de funciones del juego

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por Cesar Rincon "NightFox"
	http://www.nightfoxandco.com
	Inicio 24 de Enero del 2014

	(c) 2014 NightFox & Co.

-------------------------------------------------
*/



// Includes
#include <nds.h>



// Clase CGame
class CGame {

	// Segmento privado
	private:

		// Inicializa el juego
		void Init(void);

		// Carga los archivos
		void LoadFiles(void);


		// Nucleo del juego
		void Play(void);

		// Pulsa para Empezar
		void Menu(void);

		// Game Over
		void GameOver(void);


	// Segmento publico
	public:

		// Constructor
		CGame(void);

		// Destructor
		~CGame(void);

		// Ejecuta el juego
		void Run(void);


};
// Metodos globales de la clase "CGame"
extern CGame* Game;



/*
Metodos principales de la clase "CGame"
*/





#endif
