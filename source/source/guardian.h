#ifndef __GUARDIAN_H__
#define __GUARDIAN_H__



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



// Includes
#include <nds.h>



// Clase CGuard
class CGuard {

	// Segmento privado
	private:

		// Variables
		bool touch;
		bool new_touch;
		s8 touch_time;
		u8 state, next_state;
		s16 points;				// Puntos conseguidos


	// Segmento publico
	public:

		// Variables
		s32 pos_x, pos_y;


		// Constructor
		CGuard(void);

		// Destructor
		~CGuard(void);

		// Carga los archivos necesarios
		void Load(void);

		// Prepara los graficos en VRAM
		void Vram(void);

		// Crea el Sprite del Guardian en las coordenadas especificadas
		void Create(s32 x, s32 y);

		// Mueve el Guardian
		void Move(void);

		// Crea la GUI
		void CreateGui(void);

		// Actualiza la GUI
		void UpdateGui(void);

};
// Metodos globales de la clase "CGuard"
extern CGuard* Guard;



/*
Metodos principales de la clase "CGuard"
*/





#endif
