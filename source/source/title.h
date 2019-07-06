#ifndef __TITLE_H__
#define __TITLE_H__



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



// Includes
#include <nds.h>



// Clase CTitle
class CTitle {

	// Segmento privado
	private:

		// Inicializa la presentacion
		void Init(void);

		// Menu
		void Menu(void);




	// Segmento publico
	public:

		// Constructor
		CTitle(void);

		// Destructor
		~CTitle(void);

		// Muestra el titulo
		void Run(void);

};
// Metodos globales de la clase "CTitle"
extern CTitle* Title;



/*
Metodos principales de la clase "CTitle"
*/





#endif
