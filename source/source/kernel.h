#ifndef __KERNEL_H__
#define __KERNEL_H__



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



// Includes
#include <nds.h>



// Clase CKernel
class CKernel {

	// Segmento publico
	public:

		// Constructor
		CKernel(void);

		// Destructor
		~CKernel(void);

		// Metodo Principal (Nucleo de ejecucion del programa)
		void Run(void);


};
// Metodos globlales de la clase CGame
extern CKernel* Kernel;

/*
Metodos principales del programa (CKernel)
*/





#endif
