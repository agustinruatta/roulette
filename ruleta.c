/*
*****Licencia*****
Éste programa está licenciado bajo "GNU GENERAL PUBLIC LICENSE, VERSION 3".

Licencia: GNU GPL.
Lenguaje de programación: C.
SO: Windows y GNU/Linux.


*****Consideraciones al compilar*****
Seleccionar e indicar en qué Sistema Operativo se compila (`#define SO_LINUX` para compliar en GNU/Linux. `#define SO_WINDOWS` para compilar en Windows).
Para más información, ver al inicio de la codificación

*****Cómo compilar en GNU/LINUX*****
1-Entrar a la consola.
2-Ubicarse con el comando "cd" en la carpeta donde se encuentra el código fuente.
3-Ejecutar "gcc ruleta.cpp" (Si el archivo de código fuente cambio de nombre, cambiar "ruleta.cpp" por el nombre
que tiene.


Historial
--------

*****Versión 0.x*****
Se creó el juego, pero funcionaba solamente ingresando las opciones, no poseía la posibilidad de moverse por la
ruleta. Además poseía 6 opciones de apuestas y una gran cantidad de bugs.
Para más información, se encuentra el código fuente en el archivo "Ruleta original.cpp", que se puede ejecutar,
aunque se encuentran pueden encontrar bugs, causando que el programa funcione erroneamente.



*****Versión 1.0*****

Notas de la versión:
Ésta versión se la considera como la primera estable. En las próximas versiones se mejorará la calidad del código
y se agregarán nuevas características.Además se planea portarlo a GNU/Linux.
Fecha de entrega: 29/01/2012

Características de la versión:
*Posee todos los tipos de apuestas (12 en total).
*Movimiento por la ruleta con flechas de dirección.
*Movimiento inteligente por la ruleta, ya que no permite posarse sobre una apuesta no válida.
*Fondo y letras de color.
*Análisis y realización de la apuesta.
*Corregido gran cantidad de bugs.



*****Versión 1.1*****

Cambios:
*Se añadieron controles para lograr una mejor experiencia de juego.
*Se puede seleccionar controles personalizados.
*Ajuste automático del tamaño de la ventana para Windows.
*Título propio para Windows.
*Se añadieron y corrigeron los comentarios en el código fuente.
*Posibilidad de realizar la apuesta anterior.
*Corrección de gran cantidad de bugs.
*Se logro portarlo a GNU/Linux.
*Se quitaron los fflush(stdin) y se los reemplazaron con getch para lograr una mayor portabilidad.
*Se creo el encabezado "portabilidad_ruleta.h".
*Se reemplazo el encabezado "stdcar.h" por "portabilidad_ruleta.h", para lograr una mayor portabilidad.
*Se modificó el código para lograr una mejor ingeniería en software y permitir un código más legible.
*Muchos cambios más.
*Se toma como una versión muy estable, ya que se han reducido los bugs al mínimo.


Bugs corregido:
*Mal análisis apuesta columna a caballo y docena a caballo al sumar fichas (Siempre se perdía).
*Mal análisis columna y docena (Devolvía el doble, debe devolver el triple).
*Mal análisis columna 21 (Tomaba siempre como columna a caballo).
*Mal análisis calle (Siempre tomaba línea, por más que fuese calle).
*Otros problemas de análisis
*Muchos bugs más.



*****Versión 1.2*****
*Se inicializan los vectores y matrices en 0 (No es un bug ya que no causaba problemas, pero es para prevenir
errores en ciertos compiladores).


*****Versión 1.3*****

Cambios:
*Se agregó la posibilidad de elegir la cantidad de fichas para apostar con las teclas direccionales.
*Se corrigieron alguos bugs.
Fecha de entrega: 01/04/2012


*****Versión 1.4*****

Bugs corregidos:
*Se cambiaro algunos "getchar" por "while(getch()!=ENTER)", para evitar que se saltee unas partes.
*Cuando se iba a modificar los controles desde la ruleta, no se refrescaba la pantalla completamente.
Fecha de entrega: 12/06/2012


*****Versión 1.5*****
*Cambios en ciertos aspectos de la codificación.
Fecha de entrega: 29/10/2012


*****Versión 1.6*****
*Se cambió los if(SO=X) por ifdef, para que se seleccione el código fuente directamente cuando se compila.
Fecha de entrega: 13/03/2013

*****Versión 1.7*****
*Se crearon nuevas constantes y se reemplazaron por los 'números mágicos que existían'
Fecha de entrega: 18/03/2016


*****Diferencias entre GNU/Linux y Windows*****
*En Windows posee fondo y letras diferentes al color predeterminado. En GNU/Linux no.
*Windows posee Escape como tecla predeterminada para salir. Linux utiliza "q".
*En Linux no se puede seleccionar la tecla Escape, ya que sino generaría problemas en moverse_ruleta(), debido
a que las flechas direccionales en GNU/Linux están compuestas por tres números (27, 91, número específico de flecha).
*Para ver más diferencias, consultar el encabezado "portabilidad_ruleta.h"

*/


/*****Inicio de codificación*****/

//#define SO_LINUX para compliar en GNU/Linux. #define SO_WINDOWS para compilar en Windows.
//#define SO_LINUX//Utilizado para la librería portabilidad_ruleta.h
#define SO_WINDOWS 

#include<stdio.h>
#include<stdlib.h>
//Librería propia, con las constantes referidas a letras con acentos, carácteres especiales y constantes propias del SO.
#include"portabilidad_ruleta.h"
#include<time.h>


/*****Definición de constantes*****/
#define DIBUJAR_TODA_LA_PANTALLA 0

#define TRUE 1
#define FALSE 0

#define APUESTA_COLORADO 0
#define APUESTA_PAR 0
#define APUESTA_MENOR 0


/*****Prototipos de funciones.*****/

//Funciones para el funcionamiento del programa en general.
void dibujar_ruleta( short int y );
void moverse_ruleta( void );
void opcion_elegida_ruleta( short int x, short int y );
void mostrar_ayuda( short int posibilidad_mostrar );
void mostrar_instrucciones( void );
void evaluacion( int numero_sorteado );
void borrar_apuestas( void );
void asignar_controles( void );
void ver_controles( void );
void repetir_apuesta( void );
void eleccion_forma_apostar( void );
short int esta_dentro_de_los_limites( short int x, short int i  );
short int es_un_lugar_prohibido(short int x, short int y);
short int sortear_numero( void );
short int instrucciones_apuesta_fichas( void );
short int instrucciones_opcion_repetida( void );
short int controles_repetidos( void );
long int elegir_apuesta_fichas( void );


//Funciones para el desarrollo de las apuestas.
void apuesta_numero( short int numero_apostado );
void apuesta_semiplenos_vertical(short int fila, short int columna);
void apuesta_semiplenos_horizontal(short int fila, short int columna);
void apuesta_calles(short int calle_elegida);
void apuesta_cuadrados(short int fila_cuadrado_elegido, short int columna_cuadrado_elegido);
void apuesta_lineas(short int linea_elegida);
void apuesta_color( short int color_elegido );
void apuesta_par_impar( short int paridad_elegida );
void apuesta_menor_mayor( short int tamanio_elegido );
void apuesta_docenas( short int docena_elegida );
void apuesta_columnas( short int columna_elegida );
void apuesta_docenas_caballo( short int docena_caballo_elegida );
void apuesta_columnas_caballo( short int columna_caballo_elegida );

/*****Definición de vectores globales*****/
long int lugares_apostados[37]={0};//Números de ruleta apostado. El 0 equivale al 0, 36 al 36
long int semiplenos_vertical_apostados[12][2]={ {0} };//Semiplenos en líneas verticales (2 por fila).
long int semiplenos_horizontal_apostados[12][3]={ {0} };//Semiplenos en líneas horizontales (3 por fila).
long int calles_apostadas[14]={0};//0=[0, 1, 2]; 1=[0, 2, 3]; restantes son las diferentes filas.
long int cuadrados_apostados[12][2]={ {0} };//Columna 0 y 1 , de la fila 0, equivalen a [0, 1, 2, 3].
long int lineas_apostadas[11]={0};//Líneas por filas.
long int color_apostado[2]={0};//0 colorado, 1 negro
long int par_impar_apostado[2]={0};//0 par, 1 impar
long int menor_mayor_apostado[2]={0};//0 menor, 1 mayor
long int docenas_apostado[3]={0};//0 primer docena, 1 segunda docea, 2 tercer docena
long int columna_apostado[3]={0};//0 primer columna, 1 segunda columna, 2 tercer columna
long int docenas_caballo_apostadas[2]={0};
long int columnas_caballo_apostadas[2]={0};

/*****Definición de variables globales*****/
long int cantidad_fichas=500;//Cantidad de fichas que posee
long int cantidad_fichas_apostadas;
char bandera_primer_while=1, bandera_segundo_while;

char control_tirar, control_apuesta, control_salir, control_ayuda, control_repetir, control_asignar, control_ver;
short int posibilidad_repetir;//Si no se hizo apuesta es 0, caso contrario es 1. Se utiliza para saber si se puede repetir apuesta.
short int eleccion_apuesta;


int main()//Función principal
{
	long int cantidad_fichas_antes_jugar, cantidad_fichas_antes_tirar;
	short int numero_sorteado;
	
#ifdef SO_WINDOWS
	//Dar nombre a la aplicación.
	system("title Ruleta");
	
	//Redimensionar ventana.
	system("mode con cols=80 lines=35");
	
	//Establecer colores de fondo y de letra
	system("color 27");
#endif
	
	srand(time(NULL));
	
	posibilidad_repetir=0;
	
	mostrar_ayuda( 0 );
	
	asignar_controles();
	
	eleccion_forma_apostar();
	
	
	//Do-While repetidor del programa.
	do{
		
		cantidad_fichas_antes_jugar=cantidad_fichas;
		
		//Do-While para volver a apostar.
		do{
			
			bandera_segundo_while=1;
			
			//Controlar si posee fichas.
			if(cantidad_fichas > 0 || cantidad_fichas_antes_jugar != 0){
				moverse_ruleta();
			}
			
			else{
				system(CLS);
				dibujar_ruleta( DIBUJAR_TODA_LA_PANTALLA );
				gotoxy(39,1);
				printf("%cTe quedaste sin fichas! Juego Terminado.", _se_);
				bandera_primer_while=bandera_segundo_while=0;//Salir de los whiles
				getchar();
			}
			
			cantidad_fichas_antes_tirar=cantidad_fichas;
			
		}while(bandera_segundo_while==1);
		
		
		if(bandera_primer_while!=0){
			numero_sorteado=sortear_numero();
			
			
			system(CLS);
			dibujar_ruleta( 0 );
			gotoxy(39, 1);
			printf("N%cmero Sorteado: %d", _u_, numero_sorteado);
			gotoxy(39, 2);
			
			
			evaluacion(numero_sorteado);
			
			gotoxy(39, 8);
			if(cantidad_fichas-cantidad_fichas_antes_jugar>0)printf("Usted gan%c %ld fichas.", _o_, cantidad_fichas-cantidad_fichas_antes_tirar);
			else if(cantidad_fichas-cantidad_fichas_antes_jugar==0)printf("Usted no gan%c ni perdi%c fichas.", _o_, _o_);
			else printf("Usted perdi%c %ld fichas.", _o_, (cantidad_fichas-cantidad_fichas_antes_jugar)*-1);
			
			posibilidad_repetir=0;
			
			while(getch()!=ENTER);
		}	
		
		
	}while(bandera_primer_while==1);//Repetición del proceso hasta salir del programa.
	
	system(CLS);
	
	return 0;
	
}


/*
El argumento que se le envía es la coordenada y en donde se encuentra el cursor. Ésto nos sirve para que en
vez de dibujar la ruleta completa, dibujemos las secciones que utilizamos anteriormente (Para borrar el 
cuadrado que se dibuja para indicar la posición anterior) y la actual (Por si vamos a la derecha, borramos
el cuadrado anterior). Evitamos así el barrido de pantalla que se produce al tener que dibujar la ruleta 
completa.

Si se le envía el argumento 0 indica que se tiene que dibujar la ruleta completa.
*/
void dibujar_ruleta( short int y )//Dibujo de la ruleta.
{
	register short int c;
	
	//Número 0.
	if(y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 1 );
		printf(" %c", _esqsupizq_);
		for(c=0;c<=33;c++){
			printf("%c", _linhor_);
		}
		printf("%c", _esqsupder_);
	}
	
	if(y+1==2||y-1==2||y-2==2||y==2||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 2 );
		printf(" %c  Ayuda  %c      00      %c  Tirar  %c", _linver_, _linver_, _linver_, _linver_);
	}
	
	//Parte superior.
	if(y+1==3||y-1==3||y==3||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 3 );
		printf(" %c", _esqsupizq_);//Esquina superior izquierda.
		for(c=0;c<34;c++)printf("%c", _linhor_);//Límite superior.
		printf("%c", _esqsupder_);//Esquina superior derecha.
		printf("                                          ");
	}
	
	
	//Primer parte.
	if(y+1==4||y-1==4||y+2==4||y==4||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 4 );
		printf(" %c         %c 01 %c 02 %c 03 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==5||y-1==5||y==5||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 5 );
		printf(" %c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c         %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==6||y-1==6||y==6||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 6 );
		printf(" %c         %c 04 %c 05 %c 06 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==7||y-1==7||y==7||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 7 );
		printf(" %c Menores %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c Mayores %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==8||y-1==8||y==8||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 8 );
		printf(" %c         %c 07 %c 08 %c 09 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==9||y-1==9||y==9||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 9 );
		printf(" %c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c         %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==10||y-1==10||y-2==10||y==10||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 10 );
		printf(" %c         %c 10 %c 11 %c 12 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==11||y-1==11||y==11||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 11 );
		printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_);//Separación de números.
	}
	
	//Segunda parte.
	if(y+1==12||y-1==12||y+2==12||y==12||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 12 );
		printf(" %c         %c 13 %c 14 %c 15 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==13||y-1==13||y==13||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 13 );
		printf(" %c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c         %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==14||y-1==14||y==14||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 14 );
		printf(" %c         %c 16 %c 17 %c 18 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==15||y-1==15||y==15||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 15 );
		printf(" %cColorado %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  Negro  %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==16||y-1==16||y==16||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 16 );
		printf(" %c         %c 19 %c 20 %c 21 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==17||y-1==17||y==17||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 17 );
		printf(" %c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c         %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==18||y-1==18||y-2==18||y==18||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 18 );
		printf(" %c         %c 22 %c 23 %c 24 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==19||y-1==19||y==19||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 19 );
		printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_);//Separación de números.
	}
	
	//Tercera parte.
	if(y+1==20||y-1==20||y+2==20||y==20||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 20 );
		printf(" %c         %c 25 %c 26 %c 27 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==21||y-1==21||y==21||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 21 );
		printf(" %c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c         %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==22||y-1==22||y==22||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 22 );
		printf(" %c         %c 28 %c 29 %c 30 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==23||y-1==23||y==23||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 23 );
		printf(" %c   Par   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  Impar  %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==24||y-1==24||y==24||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 24 );
		printf(" %c         %c 31 %c 32 %c 33 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y+1==25||y-1==25||y==25||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 25 );
		printf(" %c         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c         %c", _linver_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linver_);//Separación de números.
	}
	if(y+1==26||y-2==26||y==26||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 26 );
		printf(" %c         %c 34 %c 35 %c 36 %c         %c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Números.
	}
	if(y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 27 );
		printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linhor_, _linver_);//Separación de números.
	}
	
	//Parte inferior
	if(y+2==28||y-1==28||y==28||y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 28 );
		printf(" %c I%cII%cIII%c  I %c II %c III%c I%cII%cIII%c", _linver_, _linver_, _linver_, _linver_, _linver_, _linver_, _linver_, _linver_, _linver_, _linver_);//Docenas y columnas.
	}
	
	if(y==DIBUJAR_TODA_LA_PANTALLA){
		gotoxy( 0 , 29 );
		printf(" %c", _esqinfizq_);//Esquina inferior izquierda.
		for(c=0;c<34;c++)printf("%c", _linhor_);//Límite superior.
		printf("%c", _esqinfder_);//Esquina inferior derecha.
		
		gotoxy( 0 , 30 );
		printf("   Docenas     Columnas     Docenas");
		
		gotoxy(39,28);
		printf("Cantidad de fichas: %ld", cantidad_fichas);//Mostrar la cantidad de fichas
	}
	
	
	
	
	
}

//Toma de carácteres para moverse por la ruleta.
void moverse_ruleta( void )
{
	short int toma_caracteres, bandera_dibujo=1, bandera_while=1;
	static short int x=19, y=3;
	char letra;
	
	
	system(CLS);
	dibujar_ruleta( 0 );
	
	do{
		if(bandera_dibujo!=1)dibujar_ruleta( y );
		else bandera_dibujo=0;
		
		gotoxy(x, y);
		printf("%c", CURSOR);
		
		for(toma_caracteres=0;toma_caracteres<CANT_CARAC;toma_caracteres++){
			letra=getch();
			if(LETRA_DIFERENTE){
				toma_caracteres=CANT_CARAC;//Terminar for.
			}
		}
		
		
		/****No se utiliza el switch ya que no son expresiones constantes.*****/
		
		if(letra==FLECHA_ARR){//Flecha arriba.
			y--;
			if(!esta_dentro_de_los_limites(x, y))y++;
			if(es_un_lugar_prohibido(x, y))y--;
			if(es_un_lugar_prohibido(x, y))y +=2;
		}
			
		else if(letra==FLECHA_IZQ){//Flecha izquierda.
			x--;
			if(!esta_dentro_de_los_limites(x, y))x++;
			if(es_un_lugar_prohibido(x, y))x--;
			if(es_un_lugar_prohibido(x, y))x +=2;
		}
		
		else if(letra==FLECHA_DER){//Flecha derecha
			x++;
			if(!esta_dentro_de_los_limites(x, y))x--;
			if(es_un_lugar_prohibido(x, y))x++;
			if(es_un_lugar_prohibido(x, y))x -=2;
		}
		
		else if(letra==FLECHA_ABA){//Flecha abajo.
			y++;
			if(!esta_dentro_de_los_limites(x, y))y--;
			if(es_un_lugar_prohibido(x, y))y++;
			if(es_un_lugar_prohibido(x, y))y -=2;
		}
			
			
		else if(letra==control_apuesta){//Apostar (Enter).
			bandera_while=0;
			if(posibilidad_repetir==0){
				borrar_apuestas();
				posibilidad_repetir=1;
			}
			
		}
		
		else if(letra==control_asignar){//Asignar controles.
			asignar_controles();
			dibujar_ruleta( 0 );
		}
		
		else if(letra==control_ayuda){//Mostrar ayuda.
			mostrar_ayuda( 1 );
			system(CLS);
			dibujar_ruleta( 0 );
		}
			
		else if(letra==control_repetir){//Repetir apuesta.
			if(posibilidad_repetir==0){
				repetir_apuesta();
				
				posibilidad_repetir=1;
				
				gotoxy( 39, 2 );
				printf("Se ha repetido la apuesta exitosamente.");
				gotoxy( 39, 3 );
				printf("Presione enter para continuar.");
			}
			else{
				gotoxy( 39, 2 );
				printf("No puede repetir la apuesta una vez que");
				gotoxy( 39, 3 );
				printf("se ha apostado antes o ya se repiti%c la", _o_);
				gotoxy( 39, 4 );
				printf("apuesta anterior.");
				
			}
			;
			getchar();
			system(CLS);
			dibujar_ruleta( 0 );	
		}
		
		else if(letra==control_salir){//Salir del programa.
			bandera_primer_while=bandera_segundo_while=bandera_while=0;
		}
		
		else if(letra==control_tirar){//Tirar.
			if(posibilidad_repetir==0)borrar_apuestas();
			bandera_while=bandera_segundo_while=0;
		}
		else if(letra==control_ver){//Ver controles.
			ver_controles();
			system(CLS);
			dibujar_ruleta( 0 );
		}		
		
	}while(bandera_while==1);
	
	if(letra!=control_salir && letra!=control_tirar){
		opcion_elegida_ruleta(x, y);
	}
}


void opcion_elegida_ruleta( short int x, short int y )//Según la coordenada enviada, analiza la apuesta realizada.
{
	int contador, limite_contador_pleno, numero_contado;
	
	/*
	El análisis se hace barriendo las x, analizando después por y.
	*/
	
	if(x>=2&&x<=10){
		if(y==2)mostrar_ayuda( 1 );
		else if(y>=4&&y<=10)apuesta_menor_mayor( 0 );
		else if(y>=12&&y<=18)apuesta_color( 0 );
		else if(y>=20&&y<=26)apuesta_par_impar( 0 );
		else{
			if(x==2||x==3)apuesta_docenas( 0 );
			else if(x==4)apuesta_docenas_caballo( 0 );
			else if(x==5||x==6)apuesta_docenas( 1 );
			else if(x==7)apuesta_docenas_caballo( 1 );
			else apuesta_docenas( 2 );
			
		}
	}
	
	
	
	
	else if(x==11){
		if(y%2==0) apuesta_calles( y/2 );//Calle.
		else apuesta_lineas( (y/2)-2 );//Línea.
	}
	
	
	
	
	else if(x>=12&&x<=15){
		
		if(y==2)apuesta_numero( 0 );
		
		else if(y==3)apuesta_semiplenos_horizontal( 0 , 0 );
		
		else if(y>=4&&y<=26){
			
			if(y%2==0){//Pleno.
				limite_contador_pleno = (y/2)-2;
				numero_contado=1;
				
				for( contador=0; contador<limite_contador_pleno; contador++ ){
					numero_contado += 3;
				}
				
				apuesta_numero( numero_contado );
			}
			
			else{//Semipleno horizontal.
				apuesta_semiplenos_horizontal( (y/2)-1 , 0 );
			}
			
		}
		
		else apuesta_columnas( 0 );
		
	}
	
	
	
	
	else if(x==16){
		
		if(y==2)apuesta_numero( 0 );
		
		if(y==3)apuesta_calles( 0 );
		
		else if(y>=4&&y<=26){
			
			if(y%2==0){//Semipleno vertical.
				apuesta_semiplenos_vertical( (y/2)-2 , 0);
			}
			
			else{//Cuadro.
				apuesta_cuadrados( (y/2)-1 , 0 );
			}
		}
		
		else apuesta_columnas_caballo( 0 );
		
	}
	
	
	
	
	else if(x>=17&&x<=20){
		
		if(y==2)apuesta_numero( 0 );
		
		else if(y==3)apuesta_semiplenos_horizontal( 0 , 1 );
		
		else if(y>=4&&y<=26){
			
			if(y%2==0){//Pleno.
				limite_contador_pleno = (y/2)-2;
				numero_contado=2;
				
				for( contador=0; contador<limite_contador_pleno; contador++ ){
					numero_contado += 3;
				}
				
				apuesta_numero( numero_contado );
			}
			
			else{//Semipleno horizontal.
				apuesta_semiplenos_horizontal( (y/2)-1 , 1 );
			}
			
		}
		
		else apuesta_columnas( 1 );
		
	}
	
	
	
	
	else if(x==21){
		
		if(y==2)apuesta_numero( 0 );
		
		else if(y==3)apuesta_calles( 1 );
		
		else if(y>=4&&y<=26){
			
			if(y%2==0){//Semipleno vertical.
				apuesta_semiplenos_vertical( (y/2)-2 , 1);
			}
			
			else{//Cuadro.
				apuesta_cuadrados( (y/2)-1 , 1 );
			}
		}
		
		else apuesta_columnas_caballo( 1 );
		
	}
	
	
	
	
	else if(x>=22&&x<=25){
		
		if(y==2)apuesta_numero( 0 );
		
		else if(y==3)apuesta_semiplenos_horizontal( 0 , 3 );
		
		else if(y>=4&&y<=26){
			
			if(y%2==0){//Pleno.
				limite_contador_pleno = (y/2)-2;
				numero_contado=3;
				
				for( contador=0; contador<limite_contador_pleno; contador++ ){
					numero_contado += 3;
				}
				
				apuesta_numero( numero_contado );
			}
			
			else{//Semipleno horizontal.
				apuesta_semiplenos_horizontal( (y/2)-1 , 1 );
			}
			
		}
		
		else apuesta_columnas( 2 );
		
	}
	
	
	
	
	else if(x==26)apuesta_cuadrados( 0 , 0 );
	
	
	
	
	else{
		if(y==2){
			bandera_segundo_while=0;//Tirar.
		}
		else if(y>=4&&y<=10)apuesta_menor_mayor( 1 );
		else if(y>=12&&y<=18)apuesta_color( 1 );
		else if(y>=20&&y<=26)apuesta_par_impar( 1 );
		else{
			if(x==27||x==28)apuesta_docenas( 0 );
			else if(x==29)apuesta_docenas_caballo( 0 );
			else if(x==30||x==31)apuesta_docenas( 1 );
			else if(x==32)apuesta_docenas_caballo( 1 );
			else apuesta_docenas( 2 );
			
		}
	}	
	
}


short int esta_dentro_de_los_limites( short int x, short int y )
{
	if((y>=2&&y<=28) && (x>=2&&x<=35)){
		return TRUE;
	}
	else{
		return FALSE;
	}
}


short int es_un_lugar_prohibido(short int x, short int y)//Retorna si en un lugar se puede o no apostar.
{
	if(x==26 && y!=3){
		return TRUE;
	}
	
	if( (y==2||y==28) && x==11){
		return TRUE;
	}
	
	if(y==3){
		if(x>=2&&x<=11){
			return TRUE;
		}
		if(x>=27&&x<=35){
			return TRUE;
		}
	}
	
	if(y==11){
		if(x>=2&&x<=10){
			return TRUE;
		}
		if(x>=27&&x<=35){
			return TRUE;
		}
	}
	
	if(y==19){
		if(x>=2&&x<=10){
			return TRUE;
		}
		if(x>=27&&x<=35){
			return TRUE;
		}
	}
	
	if(y==27){
		return TRUE;
	}
	
	return FALSE;//En la coordena enviada es viable apostar.
}


void apuesta_numero(short int numero_apostado)//Realiza una apuesta pleno (Número).
{
	short int bandera_while;
	
	/*
	numero_apostado:
	0=0;
	1=1;
	...
	*/
	
	
	do{		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: N%cmero %d.", _u_, numero_apostado);
		
		
		if(lugares_apostados[numero_apostado]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)lugares_apostados[numero_apostado]=cantidad_fichas_apostadas;
		}
			
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += lugares_apostados[numero_apostado];
				lugares_apostados[numero_apostado]=0;
			}
		}
		
	}while(bandera_while==1);
	
	
}


void apuesta_semiplenos_vertical(short int fila, short int columna)//Realiza una apuesta semipleno vertical.
{
	short int bandera_while;
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: Semipleno vertical.");
		
		
		if(semiplenos_vertical_apostados[fila][columna]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)semiplenos_vertical_apostados[fila][columna]=cantidad_fichas_apostadas;
			
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += semiplenos_vertical_apostados[fila][columna];
				semiplenos_vertical_apostados[fila][columna]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
}


void apuesta_semiplenos_horizontal(short int fila, short int columna)//Realiza una semipleno horizontal.
{
	short int bandera_while;
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: Semipleno horizontal.");
		
		
		if(semiplenos_horizontal_apostados[fila][columna]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)semiplenos_horizontal_apostados[fila][columna]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += semiplenos_horizontal_apostados[fila][columna];
				semiplenos_horizontal_apostados[fila][columna]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
}


void apuesta_calles(short int calle_elegida)//Realiza una apuesta de calle.
{
	short int bandera_while;
	
	/*
	calle_elegida:
	0=[0, 1, 2]; 
	1=[0, 2, 3]; 
	Restantes son las diferentes filas.
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: Calle.");
		
		
		if(calles_apostadas[calle_elegida]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)calles_apostadas[calle_elegida]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += calles_apostadas[calle_elegida];
				calles_apostadas[calle_elegida]=0;
			}
		}
		
		
	}while(bandera_while==1);
}


void apuesta_cuadrados(short int fila_cuadrado_elegido, short int columna_cuadrado_elegido)//Realiza una apuesta de cuadrado.
{
	short int bandera_while;
	
	
	/*
	cuadrados_apostados[0][0]=[0, 1, 2, 3].
	cuadrados_apostados[0][1]=No se utiliza, pero se puede representar como [0, 1, 2, 3].
	cuadrados_apostados[1][0]=[1, 2, 4, 5];
	cuadrados_apostados[1][0]=[2, 3, 5, 6];
	...
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: Cuadrado.");
		
		
		if(cuadrados_apostados[fila_cuadrado_elegido][columna_cuadrado_elegido]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)cuadrados_apostados[fila_cuadrado_elegido][columna_cuadrado_elegido]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += cuadrados_apostados[fila_cuadrado_elegido][columna_cuadrado_elegido];
				cuadrados_apostados[fila_cuadrado_elegido][columna_cuadrado_elegido]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
}


void apuesta_lineas(short int linea_elegida)//Realiza una apuesta de línea.
{
	short int bandera_while;
	
	/*
	linea_elegida:
	lineas_apostadas[0]=[1, 2, 3, 4, 5, 6];
	lineas_apostadas[1]=[4, 5, 6, 7, 8, 9];
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: L%cnea.", _i_);
		
		
		if(lineas_apostadas[linea_elegida]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)lineas_apostadas[linea_elegida]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += lineas_apostadas[linea_elegida];
				lineas_apostadas[linea_elegida]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
}


void apuesta_color( short int color_elegido )//Realiza una apuesta de color.
{
	short int bandera_while;
	
	/*
	color_elegido:
	0=Colorado;
	1=Negro;
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		if(color_elegido==APUESTA_COLORADO){
			printf("Apuesta: Colorado.");
		}
		else{
			printf("Apuesta: Negro.");
		}
		
		
		if(color_apostado[color_elegido]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)color_apostado[color_elegido]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += color_apostado[color_elegido];
				color_apostado[color_elegido]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
	
}

void apuesta_par_impar( short int paridad_elegida )//Realiza una apuesta de par-impar.
{
	short int bandera_while;
	
	/*
	paridad_elegida:
	0=par;
	1=impar;
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		if(paridad_elegida==APUESTA_PAR){
			printf("Apuesta: Par.");
		}
		else{
			printf("Apuesta: Impar.");
		}
		
		
		if(par_impar_apostado[paridad_elegida]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)par_impar_apostado[paridad_elegida]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += par_impar_apostado[paridad_elegida];
				par_impar_apostado[paridad_elegida]=0;
			}
		}
		
	}while(bandera_while==1);
}

void apuesta_menor_mayor( short int tamanio_elegido )//Realiza una apuesta de menor-mayor.
{
	short int bandera_while;
	
	/*
	tamanio_elegido:
	0=menor;
	1=mayor;
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		if(tamanio_elegido==APUESTA_MENOR){
			printf("Apuesta: Menor.");
		}
		else{
			printf("Apuesta: Mayor.");
		}
		
		
		if(menor_mayor_apostado[tamanio_elegido]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)menor_mayor_apostado[tamanio_elegido]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += menor_mayor_apostado[tamanio_elegido];
				menor_mayor_apostado[tamanio_elegido]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
	
}

void apuesta_docenas( short int docena_elegida )//Realiza una apuesta de docena.
{
	short int bandera_while;
	
	/*
	docena_elegida:
	0=primera docena;
	1=segunda docena;
	2=tercer docena;
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: %d%c Docena.", docena_elegida+1, _sg_);
		
		
		if(docenas_apostado[docena_elegida]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)docenas_apostado[docena_elegida]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += docenas_apostado[docena_elegida];
				docenas_apostado[docena_elegida]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
}

void apuesta_columnas( short int columna_elegida )//Realiza una apuesta de columna.
{
	short int bandera_while;
	
	/*
	columna_elegida:
	0=primer columna;
	1=segunda columna;
	2=tercer columna;
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: %d%c Columna.", columna_elegida+1, _sg_);
		
		
		if(columna_apostado[columna_elegida]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(bandera_while==0)columna_apostado[columna_elegida]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += columna_apostado[columna_elegida];
				columna_apostado[columna_elegida]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
}


void apuesta_docenas_caballo( short int docena_caballo_elegida )//Realiza una apuesta de docena a caballo.
{
	short int bandera_while;
	
	/*
	codena_caballo_elegida:
	0=primer y segunda docena;
	1=segunda y tercer docena;
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: %d%c Docena a Caballo.", docena_caballo_elegida+1, _sg_);
		
		
		if(docenas_caballo_apostadas[docena_caballo_elegida]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(cantidad_fichas_apostadas%2!=0){
				gotoxy(39, 5);
				printf("%cEl n%cmero de fichas apostadas debe ser", _se_, _u_);
				gotoxy(39, 6);
				printf("par!.");
				gotoxy(39, 7);
				printf("Presione enter para continuar.");
				;
				getchar();
				
				cantidad_fichas += cantidad_fichas_apostadas;
				
				bandera_while=1;
			}
			
			if(bandera_while==0)docenas_caballo_apostadas[docena_caballo_elegida]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += docenas_caballo_apostadas[docena_caballo_elegida];
				docenas_caballo_apostadas[docena_caballo_elegida]=0;
			}
		}
		
		
		
	}while(bandera_while==1);
}


void apuesta_columnas_caballo( short int columna_caballo_elegida )//Realiza una apuesta de columna a caballo.
{
	short int bandera_while;
	
	/*
	columna_caballo_elegida:
	0=primer y segunda columna;
	1=segunda y tercer columna;
	*/
	
	
	do{
		
		bandera_while=0;
		
		system(CLS);
		dibujar_ruleta( 0 );
		
		gotoxy(39, 1);
		printf("Apuesta: %d%c Columna a Caballo.", columna_caballo_elegida+1, _sg_);
		
		
		if(columnas_caballo_apostadas[columna_caballo_elegida]==0){
			bandera_while=instrucciones_apuesta_fichas();
			if(cantidad_fichas_apostadas%2!=0){
				gotoxy(39, 5);
				printf("%cEl n%cmero de fichas apostadas debe ser", _se_, _u_);
				gotoxy(39, 6);
				printf("par!.");
				gotoxy(39, 7);
				printf("Presione enter para continuar.");
				;
				getchar();
				
				cantidad_fichas += cantidad_fichas_apostadas;
				
				bandera_while=1;
			}
			
			if(bandera_while==0)columnas_caballo_apostadas[columna_caballo_elegida]=cantidad_fichas_apostadas;
		}
		
		else{
			bandera_while=instrucciones_opcion_repetida();
			if(bandera_while==1){
				system(CLS);
				dibujar_ruleta( 0 );
				cantidad_fichas += columnas_caballo_apostadas[columna_caballo_elegida];
				columnas_caballo_apostadas[columna_caballo_elegida]=0;
			}
		}
		
		
	}while(bandera_while==1);
}


short int sortear_numero( void )//Tirada de ruleta, numero al azar entre 0 y 36.
{
	int numero_sorteado;
	
	numero_sorteado=rand()%37;//Sorteo del número.
	return numero_sorteado;
}

void evaluacion( int numero_sorteado )//Evalúa las apuesta y recompensa los aciertos.
{
	short int fila_numero, columna_numero;//0<=fila_numero<=11 ; 0<=columna_numero<=2
	
	
	
	fila_numero = (numero_sorteado-1)/3;//Fila (Primera=0).
	columna_numero = (numero_sorteado%3)-1;//Columna (Primera=0).
	if(columna_numero==-1)columna_numero=2;
	
	
	//Evaluación plenos.
	cantidad_fichas += lugares_apostados[numero_sorteado]*35;
	
	
	
	//Evaluación semiplenos horizontal.
	
	if(numero_sorteado==0){
		
		//Evaluación semiplenos horizontal.
		cantidad_fichas += semiplenos_horizontal_apostados[0][0]*17;
		cantidad_fichas += semiplenos_horizontal_apostados[0][1]*17;
		cantidad_fichas += semiplenos_horizontal_apostados[0][2]*17;
		
		//Evaluación calle.
		cantidad_fichas += calles_apostadas[0]*11;
		cantidad_fichas += calles_apostadas[1]*11;
		
		//Evaluación cuadrado.
		cantidad_fichas += cuadrados_apostados[0][0]*8;
		
		//Evaluación línea.
		cantidad_fichas += lineas_apostadas[0]*5;
		
	}
	
	
	
	else{
		
		//Evaluación semiplenos horizontal.
		
		cantidad_fichas += semiplenos_horizontal_apostados[fila_numero][columna_numero]*17;
		if(fila_numero!=11)cantidad_fichas += semiplenos_horizontal_apostados[fila_numero+1][columna_numero]*17;
		
		
		//Evaluación semiplenos vertical.
		
		if(columna_numero==0)cantidad_fichas += semiplenos_vertical_apostados[fila_numero][0]*17;
		else if(columna_numero==1)cantidad_fichas += ( semiplenos_vertical_apostados[fila_numero][0] + semiplenos_vertical_apostados[fila_numero][1] )*17;
		else cantidad_fichas +=semiplenos_vertical_apostados[fila_numero][1];
		
		
		//Evaluación calles.
		cantidad_fichas += calles_apostadas[fila_numero+2]*11;
		
		
		//Evaluación cuadrados.
		if(fila_numero!=11){//Abajo.
			if(columna_numero!=2)cantidad_fichas += cuadrados_apostados[fila_numero+1][columna_numero]*8;//Abajo-Derecha.
			if(columna_numero!=0)cantidad_fichas += cuadrados_apostados[fila_numero+1][columna_numero-1]*8;//Abajo izquierda.
		}
		
		if(fila_numero!=0){//Arriba.
			if(columna_numero!=2)cantidad_fichas += cuadrados_apostados[fila_numero][columna_numero]*8;//Abajo-Derecha.
			if(columna_numero-1!=-1)cantidad_fichas += cuadrados_apostados[fila_numero][columna_numero-1]*8;//Abajo izquierda.
		}
		
		
		//Evaluación líneas.
		if(fila_numero!=0)cantidad_fichas += lineas_apostadas[fila_numero-1]*5;
		if(fila_numero!=11)cantidad_fichas += lineas_apostadas[fila_numero]*5;
		
		
		
		//Evaluación  color.
		gotoxy(39, 2);
		printf("Color: ");
		
		if(numero_sorteado<=10){
			if(numero_sorteado%2==0){
				cantidad_fichas += color_apostado[1]*2;//Negro.
				printf("Negro.");
			}
			else{
				cantidad_fichas += color_apostado[0]*2;//Colorado.
				printf("Colorado.");
			}
		}
		else if(numero_sorteado>=11&&numero_sorteado<=18){
			if(numero_sorteado%2==0){
				cantidad_fichas += color_apostado[0]*2;//Colorado.
				printf("Colorado.");
			}
			else{
				cantidad_fichas += color_apostado[1]*2;//Negro.
				printf("Negro.");
			}
		}
		else if(numero_sorteado>=19&&numero_sorteado<=28){
			if(numero_sorteado%2==0){
				cantidad_fichas += color_apostado[1]*2;//Negro.
				printf("Negro.");
			}
			else{
				cantidad_fichas += color_apostado[0]*2;//Colorado.
				printf("Colorado.");
			}
		}
		else{
			if(numero_sorteado%2==0){
				cantidad_fichas += color_apostado[0]*2;//Colorado.
				printf("Colorado.");
			}
			else{
				cantidad_fichas += color_apostado[1]*2;//Negro.
				printf("Negro.");
			}
		}
		
		
		//Evaluación par-impar.
		gotoxy(39, 3);
		printf("Paridad: ");
		if(numero_sorteado%2==0){
			cantidad_fichas += par_impar_apostado[0]*2;//Par.
			printf("Par");
		}
		else{
			cantidad_fichas += par_impar_apostado[1]*2;//Impar.
			printf("Impar");
		}
		
		
		//Evaluación menor-mayor
		gotoxy(39, 4);
		printf("Ubicaci%cn: ", _o_);
		if(numero_sorteado<=18){
			cantidad_fichas += menor_mayor_apostado[0]*2;//Menor.
			printf("Menor");
		}
		else{
			cantidad_fichas += menor_mayor_apostado[1]*2;//Mayor.
			printf("Mayor");
		}
		
		
		//Evaluación docenas.
		gotoxy(39, 5);
		printf("Docena: ");
		if(numero_sorteado<=12){
			cantidad_fichas += docenas_apostado[0]*3;//Primera docena.
			printf("1.");
			
			//Evaluación docenas a caballo.
			cantidad_fichas += docenas_caballo_apostadas[0]+docenas_caballo_apostadas[0]/2;
			
		}
		
		else {
			
			if(numero_sorteado>=13&&numero_sorteado<=24){
				cantidad_fichas += docenas_apostado[1]*3;//Segunda docena.
				printf("2.");
				
				//Evaluación docenas a caballo.
				cantidad_fichas += docenas_caballo_apostadas[0]+docenas_caballo_apostadas[0]/2;
				cantidad_fichas += docenas_caballo_apostadas[1]+docenas_caballo_apostadas[1]/2;
				
			}
			
			else{
				cantidad_fichas += docenas_apostado[2]*3;//Tercera docena.
				printf("3.");
				
				//Evaluación docenas a caballo.
				cantidad_fichas += docenas_caballo_apostadas[1]+docenas_caballo_apostadas[1]/2;
				
			}
			
		}
		
		
		//Evaluación columnas.
		gotoxy(39, 6);
		printf("Columna: ");
		if(numero_sorteado%3-1==0){
			cantidad_fichas += columna_apostado[0]*3;//Primer columna.
			printf("1.");
			
			cantidad_fichas += columnas_caballo_apostadas[0]+columnas_caballo_apostadas[0]/2;
		}
		else{
			if(numero_sorteado%3-1==1){
				cantidad_fichas += columna_apostado[1]*3;//Segunda columna.
				printf("2.");
				
				cantidad_fichas += columnas_caballo_apostadas[0]+columnas_caballo_apostadas[0]/2;
				cantidad_fichas += columnas_caballo_apostadas[1]+columnas_caballo_apostadas[1]/2;
			}
				
			else{
				cantidad_fichas += columna_apostado[2]*3;//Tercer columna
				printf("3.");
				
				cantidad_fichas += columnas_caballo_apostadas[1]+columnas_caballo_apostadas[1]/2;
				
			}
		}		
	}
	
}


short int instrucciones_apuesta_fichas( void )
{
	/*
	Guía para realizar las apuestas y detectar fallas en la introducción de datos.
	Devuelve 1 si para repetir el proceso en la función llamado, caso contrario devuelve 0.
	*/
	
	gotoxy(39, 3);
	if(eleccion_apuesta==1){//Elección de fichas con teclas direccionales.
		printf("%cCuantas fichas desea apostar?: 0", _sp_);
		cantidad_fichas_apostadas=elegir_apuesta_fichas();
		
	cantidad_fichas -= cantidad_fichas_apostadas;//Quita las fichas apostadas.
	}
	
	else{
		printf("%cCuantas fichas desea apostar?: ", _sp_);
		scanf("%ld", &cantidad_fichas_apostadas);
		getchar();
		
		if(cantidad_fichas_apostadas<0){
			gotoxy(39, 5);
			printf("%cNo pod%cs hacer apuestas negativas!.", _se_, _e_);
			gotoxy(39, 6);
			printf("Presione enter para continuar.");
			getchar();
			
			return 1;
		}
		
		
		else if( ( cantidad_fichas - ( cantidad_fichas_apostadas ) ) < 0){
			gotoxy(39, 5);
			printf("%cApostaste m%cs fichas de las que tenes!.", _se_, _a_);
			gotoxy(39, 6);
			printf("Presione enter para continuar.");
			getchar();
			
			return 1;
		}
		
		else{
			cantidad_fichas -= cantidad_fichas_apostadas;//Quita las fichas apostadas.
			return 0;
		}
	}
	
	return 0;
}

short int instrucciones_opcion_repetida( void )
{
	/*
	Se llama cuando una apuesta ya fue realizada. Ésta función se encarga de preguntar si el ususario desea 
	cambiar la apuesta. Caso afirmativo devuelve 1 a la función que la llama, caso contrario devuelve 0.
	*/
	
	short int opcion_cambiar_apuesta;
	
	gotoxy(39, 3);
	printf("%cEsta opci%cn ya fue elegida!", _se_, _o_);
	
	gotoxy(39, 4);
	printf("%cDesea cambiar la apuesta?: ", _sp_);
	gotoxy(39, 5);
	printf("1)Si.");
	gotoxy(39, 6);
	printf("2)No.");
	gotoxy(39, 8);
	printf("Opci%cn N%c: ", _o_, _sg_);
	scanf("%hd", &opcion_cambiar_apuesta);
	getchar();
	
	
	switch(opcion_cambiar_apuesta){
		
	case 1:
		return 1;
		break;
		
	case 2:
		return 0;
		break;
		
		
	default:gotoxy(39, 10);
		printf("%cOpci%cn ingresada incorrecta!", _se_, _o_);
		gotoxy(39, 9);
		printf("Presione enter para continuar.");
		getchar();
		return 1;
		break;
	}
}


long int elegir_apuesta_fichas()
{
	short int toma_caracteres;
	long int cantidad_apuesta=0;
	char letra;
	
	do{
		for(toma_caracteres=0;toma_caracteres<CANT_CARAC;toma_caracteres++){
			letra=getch();
			if(LETRA_DIFERENTE){
				toma_caracteres=CANT_CARAC;//Terminar for.
			}
		}
		
		
		if((letra==FLECHA_ARR || letra==FLECHA_DER) && cantidad_apuesta<cantidad_fichas){
		cantidad_apuesta++;
		}
	
		else if((letra==FLECHA_ABA || letra==FLECHA_IZQ) && cantidad_apuesta!=0){
			cantidad_apuesta--;
		}
		
		
		dibujar_ruleta(3);
		gotoxy(39, 3);
		printf("%cCuantas fichas desea apostar?: %ld", _sp_, cantidad_apuesta);
		
	}while(letra!=ENTER);
	
	
	return cantidad_apuesta;
	
}

void mostrar_ayuda( short int posibilidad_mostrar )//Instrucciones de ayuda.
{
	system(CLS);
	printf("\t\t\t\tAYUDA.");
#ifdef SO_WINDOWS
	printf("\n");
#endif
	
	printf("\nPara realizar una apuesta, debe dirigirse con las flechas direccionales hacia\nel lugar donde desea realizarla y presione la tecla elegida para realizar la\napuesta (Predeterminado Enter).");
	printf("\n\nAdem%cs de seleccionar, se pueden utilizar los controles establecidos para evitarmoverse por toda la ruleta.", _a_);
	printf(" El programa lo guiar%c por lugares donde se puedan\napostar y le brindar%c las indicaciones necesarias.\n", _a_, _a_);
	printf("\nS%clo se puede repetir la apuesta de la mano anterior si no ha apostado todav%ca osi no se ha repetido la apuesta.", _o_, _i_);
	
#ifdef SO_LINUX
	printf("\n\nUsted est%c utilizando GNU-Linux. Antes de jugar agrande la ventana verticalmente\npara evitar problemas de visualizaci%cn o , mejor a%cn, maximizela completamente.", _a_, _o_, _u_);
	printf("\nAdem%cs seleccione la codificaci%cn de la terminal como ISO 8859-15 ", _a_, _o_);
	printf("(En la\nterminal de Gnome seleccionar \"Terminal->Establecer codificaci%cn de caracteres->Occidental (ISO 8859-15)\".", _o_);
#endif

	
	if(posibilidad_mostrar==1){
		printf("\n\nSi durante el juego desea ver los controles presione \"%c\".", control_ver);
	}

	while(getch()!=ENTER);
	
	system(CLS);
	
}


void asignar_controles( void )
{
	short int opcion_elegida;
	
	system(CLS);
	printf("A continuaci%cn asignar%c los controles que usted desea.\n\n", _o_, _a_);
	
	do{
		
		printf("%cDesea asignar controles predeterminados o elegirlos usted?:\n", _sp_);
		printf("1)Controles predeterminados (Recomendado).\n2)Elegir los controles.\n\nOpci%cn N%c: ", _o_, _sg_);
		scanf("%hd", &opcion_elegida);
		getchar();
		
		if(opcion_elegida!=1&&opcion_elegida!=2){
			printf("\n%cHa ingresado una opci%cn incorrecta. Presione enter para continuar.", _se_, _o_);
			getchar();
			system(CLS);
		}
	}while(opcion_elegida!=1&&opcion_elegida!=2);
	
	if(opcion_elegida==1){//Controles predeterminados.
		control_apuesta=ENTER;
		control_asignar='s';
		control_ayuda='a';
		control_repetir='r';
#ifdef SO_LINUX//Linux.
		control_salir='q';
		printf("\n\nControles predeterminados:\nRealizar apuesta=Enter\nAsignar controles=\"s\"\nVer ayuda=\"a\"\nRepetir apuesta anterior=\"r\"\nSalir del programa=\"q\"\nTirar la bola=\"t\"\nVer controles=\"v\"\n");
#endif
#ifdef SO_WINDOWS
		control_salir=27;
		printf("\n\nControles predeterminados:\nRealizar apuesta=Enter\nAsignar controles=\"s\"\nVer ayuda=\"a\"\nRepetir apuesta anterior=\"r\"\nSalir del programa=Escape\nTirar la bola=\"t\"\nVer controles=\"v\"\n");
#endif
		control_tirar='t';
		control_ver='v';
		
	}
	
	else{//Controles elegidos por el usuario.
		printf("\n\n");
		
		do{
			getchar();
			
			printf("Eliga los controles:\n");
			printf("\nRealizar apuesta=");
			control_apuesta=getch();
			printf("\nVer ayuda=");
			control_ayuda=getch();
			printf("\nRepetir apuesta anterior=");
			control_repetir=getch();
			printf("\nSalir del programa=");
			control_salir=getch();
			printf("\nTirar la bola=");
			control_tirar=getch();
			printf("\nVer controles=");
			control_ver=getch();
			
			
			if(controles_repetidos()){
				#ifdef SO_LINUX
				printf("\n\n%cSe ha detectado controles iguales o que se utiliz%c el escape como control!.\nPresione enter para continuar y reasignarlos.", _se_, _o_);
				#endif
				
				#ifdef SO_WINDOWS
				printf("\n\n%cSe ha detectado controles iguales!. Presione enter para continuar y\nreasignarlos.", _se_);
				#endif
				
				getchar();
				system(CLS);
			}
			
			else{
				if(control_apuesta!=13)printf("\n\nControles elegidos:\nRealizar apuesta=%c\nAsignar controles=\"%c\"\nVer ayuda=\"%c\"\nRepetir apuesta=\"%c\"\nSalir del programa=\"%c\"\nTirar la bola=\"%c\"\nVer controles=\"%c\"\n", control_apuesta, control_asignar, control_ayuda, control_repetir, control_salir, control_tirar, control_ver);
				else printf("\n\nControles elegidos:\nRealizar apuesta=Enter\nAsignar controles=\"%c\"\nVer ayuda=\"%c\"\nRepetir apuesta=\"%c\"\nSalir del programa=\"%c\"\nTirar la bola=\"%c\"\nVer controles=\"%c\"\n", control_asignar, control_ayuda, control_repetir, control_salir, control_tirar, control_ver);
				getchar();
			}
			
			
		}while(controles_repetidos());
		
	}
	
	
	printf("\nRecuerde que puede modificar los controles durante el juego.");
	
	while(getch()!=ENTER);
	
}


void eleccion_forma_apostar( void )
{
	do{
		system(CLS);
		
		printf("%cC%cmo desea elegir las cantidad de fichas?:\n 1)Con las teclas direccionales(Recomendado).\n 2)Introduciendo la cantidad de fichas deseadas.\n\nOpci%cn N%c: ", _sp_, _o_, _o_, _sg_);
		scanf("%hd", &eleccion_apuesta);
		
		if(eleccion_apuesta!=1 && eleccion_apuesta!=2){
			printf("\nOpci%cn elegida incorrecta. Presione enter para continuar.", _o_);
			while(getch()!=ENTER);
		}
		
	}while(eleccion_apuesta!=1 && eleccion_apuesta!=2);
	
	
	if(eleccion_apuesta==1)printf("\n\nPara aumentar la cantidad de fichas que se apuestan presione la tecla direccio-\nnal arriba o derecha. Caso contrario presione la tecla direccional abajo o iz-\nquierda.");
	
	getchar();
	getchar();
	
	system(CLS);
	
	
}

short int controles_repetidos( void )
{
	if(control_apuesta==control_asignar||control_apuesta==control_ayuda||control_apuesta==control_repetir||control_apuesta==control_salir||control_apuesta==control_tirar||control_apuesta==control_ver){
		return TRUE;
	}
	if(control_asignar==control_ayuda||control_asignar==control_repetir||control_asignar==control_salir||control_asignar==control_tirar||control_asignar==control_ver){
		return TRUE;
	}
	if(control_ayuda==control_repetir||control_ayuda==control_salir||control_ayuda==control_tirar||control_ayuda==control_ver){
		return TRUE;
	}
	if(control_repetir==control_salir||control_repetir==control_tirar||control_repetir==control_ver){
		return TRUE;
	}
	if(control_salir==control_tirar||control_salir==control_ver){
		return TRUE;
	}
	if(control_tirar==control_ver){
		return TRUE;
	}

#ifdef SO_LINUX
	//Ver que no se utilize escape como control.
	if(control_apuesta==27||control_asignar==27||control_ayuda==27||control_repetir==27||control_salir==27||control_tirar==27||control_ver==27){
		return TRUE;
	}
#endif
	
	return FALSE;
}


void ver_controles( void )
{
	system(CLS);
	
	printf("Controles elegidos:\n\nRealizar apuesta=%c\nAsignar controles=\"%c\"\nVer ayuda=\"%c\"\nRepetir apuesta=\"%c\"\nSalir del programa=\"%c\"\nTirar la bola=\"%c\"\nVer controles=\"%c\"\n", control_apuesta, control_asignar, control_ayuda, control_repetir, control_salir, control_tirar, control_ver);
	while(getch()!=ENTER);
}


void borrar_apuestas( void )//Borrar la apuesta hechas anteriormente.
{
	short int fila, columna;
	
	//Números.
	for(fila=0; fila<=36; fila++)lugares_apostados[fila]=0;
	//Semiplanos verticales.
	for(fila=0; fila<=11; fila++)for(columna=0; columna<=1; columna++)semiplenos_vertical_apostados[fila][columna]=0;
	//Semiplanos horizontales.
	for(fila=0; fila<=11; fila++)for(columna=0; columna<=2; columna++)semiplenos_horizontal_apostados[fila][columna]=0;
	//Calles.
	for(fila=0; fila<=13; fila++)calles_apostadas[fila]=0;
	//Cuadrados.
	for(fila=0; fila<=11; fila++)for(columna=0; columna<=1; columna++)cuadrados_apostados[fila][columna]=0;
	//Línea.
	for(fila=0; fila<=10; fila++)lineas_apostadas[fila]=0;
	//Color.
	for(fila=0; fila<=1; fila++)color_apostado[fila]=0;
	//Paridad.
	for(fila=0; fila<=1; fila++)par_impar_apostado[fila]=0;
	//Menor-Mayor.
	for(fila=0; fila<=1; fila++)menor_mayor_apostado[fila]=0;
	//Docenas.
	for(fila=0; fila<=2; fila++)docenas_apostado[fila]=0;
	//Columna.
	for(fila=0; fila<=2; fila++)columna_apostado[fila]=0;
	//Docena a caballo.
	for(fila=0; fila<=1; fila++)docenas_caballo_apostadas[fila]=0;
	//Columna a caballo.
	for(fila=0; fila<=1; fila++)columnas_caballo_apostadas[fila]=0;
}

void repetir_apuesta( void )
{
	short int fila, columna;
	
	//Números.
	for(fila=0; fila<=36; fila++)cantidad_fichas -= lugares_apostados[fila];
	//Semiplanos verticales.
	for(fila=0; fila<=11; fila++)for(columna=0; columna<=1; columna++)cantidad_fichas -= semiplenos_vertical_apostados[fila][columna];
	//Semiplanos horizontales.
	for(fila=0; fila<=11; fila++)for(columna=0; columna<=2; columna++)cantidad_fichas -= semiplenos_horizontal_apostados[fila][columna];
	//Calles.
	for(fila=0; fila<=13; fila++)cantidad_fichas -= calles_apostadas[fila];
	//Cuadrados.
	for(fila=0; fila<=11; fila++)for(columna=0; columna<=1; columna++)cantidad_fichas -= cuadrados_apostados[fila][columna];
	//Línea.
	for(fila=0; fila<=10; fila++){
		if(lineas_apostadas[fila]!=0){
			printf("%d %ld", fila, lineas_apostadas[fila]);
			getchar();
		}
		cantidad_fichas -= lineas_apostadas[fila];
	}
	//Color.
	for(fila=0; fila<=1; fila++)cantidad_fichas -= color_apostado[fila];
	//Paridad.
	for(fila=0; fila<=1; fila++)cantidad_fichas -= par_impar_apostado[fila];
	//Menor-Mayor.
	for(fila=0; fila<=1; fila++)cantidad_fichas -= menor_mayor_apostado[fila];
	//Docenas.
	for(fila=0; fila<=2; fila++)cantidad_fichas -= docenas_apostado[fila];
	//Columna.
	for(fila=0; fila<=2; fila++)cantidad_fichas -= columna_apostado[fila];
	//Docena a caballo.
	for(fila=0; fila<=1; fila++)cantidad_fichas -= docenas_caballo_apostadas[fila];
	//Columna a caballo.
	for(fila=0; fila<=1; fila++)cantidad_fichas -= columnas_caballo_apostadas[fila];
}
