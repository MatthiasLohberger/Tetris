#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
char *gets(char *buffer);

#include <stdio.h>
#include <time.h>
#include "Gameloop_Wei.h"
#include "Gamefunctions_Zei.h"
#include "Spielfeld_loh.h"
#include "Spielfiguren.h"

#define true 1
#define false 0

#define DEBUG 0

#define xlength 10
#define ylength 26

void main() {
	getch();
	int vorbei;
	init_spielfeld();
	#if DEBUG
		single_ausgabe();
		getch();
	#endif
	vorbei = gameloop();
	if(vorbei == true){
		highscore();
	}
}