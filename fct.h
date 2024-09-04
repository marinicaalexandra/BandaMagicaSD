/* MARINICA ALEXANDRA-RALUCA  GRUPA 315CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define THIRTY 30

/* definire lista dublu inlantuita cu santinela */
typedef struct celula2 {
  char info;       
  struct celula2 *pre, *urm;
} TCelula2, *TLista2;

/*definire coada*/
typedef struct celula { 
  char info[THIRTY];
  struct celula* urm;
} TCelula, *TLista;

typedef struct coada { 
  TLista inc, sf;       /* adresa primei si ultimei celule */
} TCoada;

/*definire stiva
typedef struct celst
{
int info;
struct celst *urm;
} TCelulaStiva, *TStiva;*/
typedef struct stiva {
  TLista2 info;
  struct stiva *urm;
} TCelulaStiva, *TStiva;

/*definire banda*/
typedef struct banda {
  TLista2 deget;
  TLista2 inceput;
} TCelulaBanda, * TBanda;


TStiva InitS(void);
void DistrugeS(TStiva* vf);
int Push(TStiva* vf, TLista2 deget);
int Pop(TStiva* vf, TLista2 *copie);
void UNDO (TStiva *vf_st_undo, TStiva *vf_st_redo, TBanda *b);
void REDO (TStiva *vf_st_undo, TStiva *vf_st_redo, TBanda *b);


TLista2 AlocCelula2(char x);
TLista2 InitLista2();
TLista2 CitireLista2();
void AfisareLista2(TLista2 L);
void DistrugeLista2(TLista2 *aL);

TCoada* InitQ () ;
int ExtrQ(TCoada*c, char *x);
int IntrQ(TCoada *c, char *s);
void DistrQ(TCoada **c);
void AfisareQ(TCoada *c, FILE *fout);

void SHOW_CURRENT(TBanda *b, FILE *fout);
void SHOW(TBanda b, FILE *fout);
void WRITE(TBanda *b, char c);
int MOVE_LEFT(TBanda *b);
int MOVE_RIGHT(TBanda *b);
int MOVE_LEFT_CHAR(TBanda *b, char c, FILE *fout);
int MOVE_RIGHT_CHAR(TBanda *b, char c);
int INSERT_LEFT(TBanda *b, char c, FILE *fout);
int INSERT_RIGHT(TBanda *b, char c);

void DistrBanda(TBanda *b);