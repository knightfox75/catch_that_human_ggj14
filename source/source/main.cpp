/*
-------------------------------------------------

	Catch that Human - Global Game Jam 2014

	Archivo de gestion del juego

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
-------------------------------------------------
	Main() - Bloque general del programa
-------------------------------------------------
*/

int main(int argc, char **argv) {

	// Activar en caso de debug
	// defaultExceptionHandler();
 

	/*
	Creacion de objetos
	*/

	Kernel = new CKernel();



	/*
	Programa
	*/

	// Inicializa el hardware y la libreria
	System->Boot();
	// Nucleo de ejecucion
	Kernel->Run();



	/*
	Eliminacion de objetos
	*/

	delete Kernel;
	Kernel = NULL;



	/*
	Fin del programa
	*/

	// Devuelve 0
	return 0;

}
