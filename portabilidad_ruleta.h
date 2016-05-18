/*
Este encabezado posee las constantes para lograr portabilidad del juego de Ruleta entre los SO Windows t GNU/Linux.
*/

//Sistema Operativo GNU/Linux
#ifdef SO_LINUX
#define _A_ 193//Imprime "Á"
#define _a_ 225//Imprime "á"
#define _E_ 201//Imprime "É"
#define _e_ 233//Imprime "é"
#define _I_ 205//Imprime "Í"
#define _i_ 237//Imprime "í"
#define _O_ 211//Imprime "Ó"
#define _o_ 243//Imprime "ó"
#define _U_ 218//Imprime "Ú"
#define _u_ 250//Imprime "ú"
#define _N_ 209//Imprime "Ñ"
#define _n_ 241//Imprime "ñ"
#define _sp_ 191//Imprime "¿"
#define _se_ 161//Imprime "¡"
#define _sg_ 176//Imprime "º"

#define _esqsupizq_ 124//Imprime la esquina superior izquierda.
#define _esqsupder_  124//Imprime la esquina superior derecha.
#define _linhor_ 175//Imprime la línea horizontal.
#define _linver_ 124//Imprime la línea vertical.
#define _esqinfizq_ 175//Imprime la esquina inferior izquierda.
#define _esqinfder_ 175//Imprime la esquina inferior derecha.

#define CURSOR 0
#define ENTER 10

#define CLS "clear"//Borrar pantalla.

#define FLECHA_ARR 65
#define FLECHA_ABA 66
#define FLECHA_DER 67
#define FLECHA_IZQ 68
#define CANT_CARAC 3//Cantidad de caracteres que componen la flecha de direcciÃ³n.
#define LETRA_DIFERENTE letra!=27&&letra!=91


//Encabezados.
#include <termios.h>
#include <unistd.h>

//Funciones

int getch( void ) {
	struct termios oldt,
		newt;
	int            ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

void gotoxy(const short int x, const short int y)
{
	printf("\033[%d;%df", y+1, x+1);
	fflush(stdout);
}

#endif


//Sistema Operativo Windows
#ifdef SO_WINDOWS
//Macros.
#define _A_ 181//Imprime "Á"
#define _a_ 160//Imprime "á"
#define _E_ 144//Imprime "É"
#define _e_ 130//Imprime "é"
#define _I_ 214//Imprime "Í"
#define _i_ 161//Imprime "í"
#define _O_ 244//Imprime "Ó"
#define _o_ 162//Imprime "ó"
#define _U_ 233//Imprime "Ú"
#define _u_ 163//Imprime "ú"
#define _N_ 165//Imprime "Ñ"
#define _n_ 164//Imprime "ñ"
#define _sp_ 168//Imprime "¿"
#define _se_ 173//Imprime "¡"
#define _sg_ 248//Imprime "º"
#define _esqsupizq_ 218//Imprime la esquina superior izquierda.
#define _esqsupder_  191//Imprime la esquina superior derecha.
#define _esqinfizq_ 192//Imprime la esquina inferior izquierda.
#define _esqinfder_ 217//Imprime la esquina inferior derecha.
#define _linhor_ 196//Imprime la línea horizontal.
#define _linver_ 179//Imprime la línea vertical.

#define CURSOR 254
#define ENTER 13

#define CLS "cls"//Borrar pantalla.

#define FLECHA_ARR 72
#define FLECHA_ABA 80
#define FLECHA_DER 77
#define FLECHA_IZQ 75
#define CANT_CARAC 2//Cantidad de caracteres que componen la flecha de direcciÃ³n.
#define LETRA_DIFERENTE letra!=-32


//Encabezados
#include<conio.h>
#include<windows.h>

//Funciones

void gotoxy( const int x, const int y )//Ubicar el cursor en diferentes coordenadas.
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
}

#endif
