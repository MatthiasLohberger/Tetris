/*
* Tetris in C - header by Felix Weichselgartner
*/

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "Gamefunctions_Zei.h"
#include "Spielfeld_loh.h"
#include "Spielfiguren.h"
#include "Gameloop_Wei.h"

#define true 1
#define false 0

#define xlength 10
#define ylength 26

int punktestand = 0, farbe_formen = 0;
char spielfeld[xlength][ylength];

int abs(int x){
	if (x >= 0)
		return x;
	else return -x;
}

void delay(int milli_seconds) {
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds)
		;
}

void init_spielfeld(){
	for(int i=0; i<xlength; i++){
		for(int k=0; k<ylength; k++){
			spielfeld[i][k] = ' ';
		}
	}
}

int gameloop(){
	int direction, drehenrechts, drehenlinks;
	while(!verloren()){
		spawn();
		while(collision() == false){
			down();
			/*
			system("cls");
			ausgabe(farbe_formen);
			*/
			input();
		}
		reiheloeschen();
	}
	system("cls");
	ausgabe(farbe_formen);
	return true;
}

void down(){
	char tempfield[xlength][ylength];
	for(int i=0; i < ylength; i++){
		for(int k=0; k < xlength; k++){
			tempfield[k][i] = spielfeld[k][i];
			if (spielfeld[k][i] == 'O')
				spielfeld[k][i] = ' ';
		}
	}
	for(int i=0; i < ylength; i++){
		for(int k=0; k < xlength; k++){
			if (tempfield[k][i] == 'O')
				spielfeld[k][i+1] = 'O';
		}
	}
}

void input(){
	int flagleft = 0, flagright = 0, flagfast = 0, flagdrehenlinks = 0, flagdrehenrechts = 0;
	int milli_seconds = 1000, drehenrechts = 0, drehenlinks = 0;
	clock_t start_time = clock(); 

    while (clock() < start_time + milli_seconds) {
		system("cls");
		ausgabe(farbe_formen);

		//delay nur damit das Spielfeld nicht zu oft aktualisiert wird
		//schlecht f�r die Augen
		delay(100);

		flagleft = GetAsyncKeyState(VK_LEFT);
		if (abs(flagleft) > 10000) {
			copyleftright('l');
			flagleft = 0;
		}
		flagright = GetAsyncKeyState(VK_RIGHT);
		if (abs(flagright) > 10000) {
			copyleftright('r');
			flagright = 0;
		}
		flagfast = GetAsyncKeyState(VK_DOWN);
		if (abs(flagfast) > 10000) {
			break;
		}
		flagdrehenrechts = GetAsyncKeyState(0x41);
		if (abs(flagdrehenrechts) > 10000) {
			//rotate('r');
			flagdrehenrechts = 0;
		}
		flagdrehenlinks = GetAsyncKeyState(0x44);
		if (abs(flagdrehenlinks) > 10000) {
			//rotate('l');
			flagdrehenlinks = 0;
		}
	}
	return;
}

void copyleftright(char direction){
	int leftboarder = false, rightboarder = false, leftfigur = false, rightfigur = false;

	for(int i=0; i < ylength; i++){
		if (spielfeld[0][i] == 'O'){
			leftboarder = true;
		}
	}
	for (int i = 0; i < ylength; i++) {
		if (spielfeld[9][i] == 'O') {
			rightboarder = true;
		}
	}
	
	for (int i = 0; i < ylength; i++) {
		for (int k = 0; k < xlength; k++) {
			if (spielfeld[k][i] == 'O' && spielfeld[k - 1][i] == 'X') {
				leftfigur = true;
			}
		}
	}

	for (int i = 0; i < ylength; i++) {
		for (int k = 0; k < xlength; k++) {
			if (spielfeld[k][i] == 'O' && spielfeld[k + 1][i] == 'X') {
				rightfigur = true;
			}
		}
	}

	if(direction == 'l' && !leftboarder && !leftfigur){
		for(int i = 0; i < ylength; i++){
			for(int k = 0; k < xlength; k++){
				if (spielfeld[k][i] == 'O') {
					spielfeld[k][i] = ' ';
					spielfeld[k - 1][i] = 'O';
				}
			}
		}
	}
	if (direction == 'r' && !rightboarder && !rightfigur) {
		for (int i = 0; i < ylength; i++) {
			for (int k = xlength; k >= 0; k--) {
				if (spielfeld[k][i] == 'O') {
					spielfeld[k][i] = ' ';
					spielfeld[k + 1][i] = 'O';
				}
			}
		}
	}
}

int verloren(){
	for(int i=0; i<xlength; i++){
		if (spielfeld[i][4] == 'X') {
			return true;
		}
	}
	return false;
}