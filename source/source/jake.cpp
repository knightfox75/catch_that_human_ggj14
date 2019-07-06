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
Metodos de la clase "CJake"
*/

// Contructor clase CJake
CJake::CJake(void) {


	frame = 0;				// Frame actual
	anim_time = 0;			// Temporizador de animacion
	anim_speed = 0;			// Velocidad de la animacion
	delay = 0;				// Retardo entre acciones
	new_touch = false;		// Control del tactil

	// Inicializa variables
	pos_x = 0, pos_y = 0;
	base_speed = JAKE_WALK;
	walk_speed = 0;
	run_count = 0;
	state = JAKE_ST_PREPARE;
	next_state = JAKE_ST_PREPARE;
	go = false;

}

// Destructor clase CJake
CJake::~CJake(void) {
}

// Metodos globales de la clase CJake
CJake* Jake;



// Carga los archivos
void CJake::Load(void) {

	NF_LoadSpriteGfx("sprite/jake", JAKE_GFX, 32, 64);		// Jake (enemigo)
	NF_LoadSpritePal("sprite/jake", JAKE_PAL);

}



// Prepara los graficos en VRAM
void CJake::Vram(void) {

	NF_VramSpriteGfx(0, JAKE_GFX, JAKE_GFX, false);				// Jake (enemigo)
	NF_VramSpritePal(0, JAKE_PAL, JAKE_PAL);

}



// Crea el sprite de Jake en las coordenadas dadas
void CJake::Create(s32 x, s32 y) {

	// Guarda la posicion
	pos_x = (x << 8), pos_y = (y << 8);

	// Crea el sprite de Jake con su grafico y paletas
	NF_CreateSprite(0, JAKE_SPR, JAKE_GFX, JAKE_PAL, (pos_x >> 8), (pos_y >> 8));
	NF_SpriteLayer(0, JAKE_SPR, 3);

	// Inicializa los parametros de Jake
	frame = JAKE_ANIM_WALK_START;
	anim_time = 0;
	anim_speed = JAKE_ANIM_WALK_SPEED;
	walk_speed = base_speed;

}



// Mueve a Jake
void CJake::Move(void) {

	// Mueve a Jake
	pos_x += walk_speed;

	// Actualiza la posicion del Sprite
	NF_MoveSprite(0, JAKE_SPR, (pos_x >> 8), (pos_y >> 8));

	// Actualiza el flip del Sprite
	if (walk_speed > 0) {
		NF_HflipSprite(0, JAKE_SPR, false);
	} else if (walk_speed < 0) {
		NF_HflipSprite(0, JAKE_SPR, true);
	}

	// Animacion del Sprite (Si esta andando)
	if (walk_speed != 0) {
		anim_time ++;
		if (anim_time >= anim_speed) {
			anim_time = 0;
			frame ++;
			if (frame > JAKE_ANIM_WALK_END) {
				frame = JAKE_ANIM_WALK_START;
			}
			NF_SpriteFrame(0, JAKE_SPR, frame);
		}
	}

}



// IA de Jake
bool CJake::AI(void) {

	// Variables
	s32 x = 0;
	bool exit = false;

	// Maquina de estados
	switch (state) {

		// Preparate
		case JAKE_ST_PREPARE:
			pos_x = -(64 << 8) ;
			pos_y = (129 << 8);
			next_state = JAKE_ST_TOUCH;
			break;

		// Espera
		case JAKE_ST_DELAY:
			delay --;
			if (delay <= 0) {
				delay = 0;
				walk_speed = base_speed;
				next_state = JAKE_ST_STEAL;
			}
			break;

		// Roba
		case JAKE_ST_STEAL:
			// Mira si coges el brik de leche
			if (!Milk->child) {
				x = (pos_x + (16 << 8));
				if ((x >= Milk->pos_x) && (x <= (Milk->pos_x + (32 << 8)))) {
					Milk->child = true;
				}
			}
			// Cambia de sentido
			if (pos_x > (223 << 8)) {
				pos_x = (223 << 8);
				walk_speed = -base_speed;
				run_count ++;
			}
			// Salta de estado si has cojogido el brick
			if ((pos_x < (191 << 8)) && Milk->child) {
				next_state = JAKE_ST_RUN;
			}
			break;

		// Intenta huir
		case JAKE_ST_RUN:
			// Patrulla simple
			if (pos_x < (32 << 8)) {
				pos_x = (32 << 8);
				walk_speed = base_speed;

			}
			if (pos_x > (191 << 8)) {
				pos_x = (191 << 8);
				walk_speed = -base_speed;
				run_count ++;
				if (run_count >= 2) {
					next_state = JAKE_ST_SCAPE;
				}
			}
			break;

		// Escapa
		case JAKE_ST_SCAPE:
			// Patrulla simple
			if (pos_x < -(32 << 8)) {
				// Ajusta posicion
				pos_x = -(32 << 8);
				// Quita un brick de leche si lo llevas encima
				if (Milk->child) {
					Milk->left --;
					if (Milk->left < 0) Milk->left = 0;
					Milk->UpdateGui();
					// Para a jake
					walk_speed = 0;
					// Dependiendo de cuantos bricks de leche has robado...
					if (Milk->left > 0) { // <- to 0
						NF_CreateTiledBg(1, 3, "to_play");
						// Siguiente estado
						next_state = JAKE_ST_TOUCH;
					} else {
						next_state = JAKE_ST_EXIT;
					}
				} else {
					// Siguiente estado
					next_state = JAKE_ST_REDO;
				}
			}
			break;

		// Espera al siguiente brik de leche
		case JAKE_ST_REDO:
			// Para a jake
			walk_speed = 0;
			run_count = 0;
			delay = 30;
			// Reinicia el brick de leche
			Milk->child = false;
			Milk->pos_x = (223 << 8);
			Milk->pos_y = (159 << 8);
			// Aumenta la velocidad
			base_speed += 64;
			if (base_speed > (16 << 8)) base_speed = (16 << 8);
			// Cambio de estado
			next_state = JAKE_ST_DELAY;
			break;

		// Te han cazado
		case JAKE_ST_DEAD:
			// Patrulla simple
			if (pos_x < -(32 << 8)) {
				// Ajusta posicion
				pos_x = -(32 << 8);
				// Siguiente estado
				next_state = JAKE_ST_REDO;
			}
			break;


		// Espera a tocar el tactil para empezar
		case JAKE_ST_TOUCH:
			if (Touchpad->touch) {
				if (new_touch) {
					new_touch = false;
					// Cambia el fondo
					NF_CreateTiledBg(1, 3, "dear_cat");
					// Indica que se pone en marcha
					go = true;
					// Siguiente estado
					next_state = JAKE_ST_REDO;
				}
			} else {
				new_touch = true;
			}
			break;

		// Sal del juego (Game OVER)
		case JAKE_ST_EXIT:
			exit = true;
			break;

		// Error
		default:
			break;

	}

	// Cambio de estado
	if (state != next_state) state = next_state;

	// Devuelve el resultado
	return exit;

}