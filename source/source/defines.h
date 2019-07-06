#ifndef __DEFINES_H__
#define __DEFINES_H__



/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Archivo de definiciones

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por Cesar Rincon "NightFox"
	http://www.nightfoxandco.com
	Inicio 24 de Enero del 2014

	(c) 2014 NightFox & Co.

-------------------------------------------------
*/



/*
	Defines para el control del sonido
*/
#define BGM_NUMBER 1		// Numero de temas musicales
#define SFX_NUMBER 1		// Numero de efectos de sonido
#define VOICE_NUMBER 1		// Numero de voces

/*
	Defines de Jake
*/
#define JAKE_GFX 0					// Grafico
#define JAKE_PAL 0					// Paleta
#define JAKE_SPR 100				// ID de sprite
#define JAKE_ANIM_WALK_START 0		// Parametros de movimiento
#define JAKE_ANIM_WALK_END 1
#define JAKE_ANIM_WALK_SPEED 5
#define JAKE_WALK (2 << 8)
#define JAKE_ST_PREPARE 0			// Parametros de la maquina de estados
#define JAKE_ST_DELAY 1
#define JAKE_ST_STEAL 2
#define JAKE_ST_RUN 3
#define JAKE_ST_SCAPE 4
#define JAKE_ST_REDO 5
#define JAKE_ST_DEAD 6
#define JAKE_ST_TOUCH 7
#define JAKE_ST_EXIT 8

/*
	Defines del brick de leche
*/
#define MILK_GFX 1					// Grafico
#define MILK_PAL 1					// Paleta
#define MILK_SPR 99					// ID de sprite
#define MILK_GUI 10					// ID del primer sprite de la GUI

/*
	Defines del guardian
*/
#define GUARD_GFX 2					// Grafico
#define GUARD_PAL 2					// Paleta
#define GUARD_SPR 101				// ID de sprite
#define GUI_GUARD_FACE_GFX 3		// Datos para la GUI de la puntuacion
#define GUI_GUARD_NUM_GFX 4
#define GUI_GUARD_PAL 3
#define GUI_GUARD_FACE_SPR 75
#define GUI_GUARD_NUM_SPR 80



/*
	Defines de la GUI del CAT PRINT
*/
#define CAT_PRINT_BLINK 20		// Velocidad del parpadeo

#endif
