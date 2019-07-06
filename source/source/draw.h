#ifndef __DRAW_H__
#define __DRAW_H__



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



// Includes
#include <nds.h>



// Clase CDraw
class CDraw {

	// Segmento privado
	private:

		// Variables
		bool cat_print_blink;
		u8 cat_print_time;

		// Controla la GUI inferior (huella del gato)
		void CatPrint(void);


	// Segmento publico
	public:

		// Constructor
		CDraw(void);

		// Destructor
		~CDraw(void);

		// Crea los graficos
		void Create(void);

		// Actualiza la pantalla
		void UpdateScreen(void);

};
// Metodos globales de la clase "CDraw"
extern CDraw* Draw;



/*
Metodos principales de la clase "CBase"
*/





#endif
