#ifndef __MILK_H__
#define __MILK_H__



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



// Includes
#include <nds.h>



// Clase CMilk
class CMilk {

	// Segmento privado
	private:

		// Variables


	// Segmento publico
	public:

		// Variables
		s32 pos_x, pos_y;
		bool child;			// Jake tiene el brik
		s8 left;			// Numero de briks restantes

		// Constructor
		CMilk(void);

		// Destructor
		~CMilk(void);

		// Carga los archivos necesarios
		void Load(void);

		// Prepara los graficos en VRAM
		void Vram(void);

		// Crea el Sprite del Brik en las coordenadas especificadas
		void Create(s32 x, s32 y);

		// Mueve el Brik
		void Move(void);

		// Crea la GUI
		void CreateGui(void);

		// Actualiza la GUI
		void UpdateGui(void);

};
// Metodos globales de la clase "CMilk"
extern CMilk* Milk;



/*
Metodos principales de la clase "CBase"
*/





#endif
