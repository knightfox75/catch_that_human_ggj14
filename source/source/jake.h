#ifndef __JAKE_H__
#define __JAKE_H__



/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Jake (Enemigo)

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



// Clase CJake
class CJake {

	// Segmento privado
	private:

		// Variables
		u8 frame;				// Frame actual
		u8 anim_time;			// Temporizador de animacion
		u8 anim_speed;			// Velocidad de la animacion
		s16 delay;				// Retardo entre acciones
		bool new_touch;			// Control del tactil



	// Segmento publico
	public:

		// Variables
		s32 pos_x, pos_y;		// Posicion
		s32 base_speed;			// Velocidad base
		s32 walk_speed;
		u8 run_count;
		u8 state, next_state;	// Maquina de estados
		bool go;				// Jake se pone en marcha

		// Constructor
		CJake(void);

		// Destructor
		~CJake(void);

		// Carga los archivos necesarios
		void Load(void);

		// Prepara los graficos en VRAM
		void Vram(void);

		// Crea el Sprite de Jake en las coordenadas especificadas
		void Create(s32 x, s32 y);

		// Mueve a Jake
		void Move(void);

		// IA de Jake
		bool AI(void);

};
// Metodos globales de la clase "CJake"
extern CJake* Jake;



/*
Metodos principales de la clase "CBase"
*/





#endif
