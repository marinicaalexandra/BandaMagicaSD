/* MARINICA ALEXANDRA-RALUCA  GRUPA 315CB*/
#include "fct.h"

// LISTA DUBLU INLANTUITA CU SANTINELA

/* Aloca un element de tip TCelula2 si returneaza pointerul aferent */
TLista2 AlocCelula2(char x) {
    TLista2 aux = (TLista2) malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }

    aux->info = x;
    aux->pre = aux->urm = NULL;

    return aux;
}

/* Creeaza santinela pentru lista folosita */
TLista2 InitLista2() {
    TLista2 aux = (TLista2) malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }

    aux->info = 0;                  /* informatia din santinela are valoarea 0 */
    aux->pre = NULL;
    aux->urm = NULL;

    return aux;
}

/* Citeste de la tastatura numere de adaugat in lista */
TLista2 CitireLista2(int* dimLista) {
    TLista2 L = NULL, aux = NULL, ultim = NULL;
    int x = 0;
    *dimLista = 0;
    L = InitLista2();   /* creeaza santinela */
    if (!L) return NULL;
    ultim = L;
    printf("Introduceti numerele de adaugat in lista:\n");
    while (scanf("%i", &x) == 1) {   /* se citesc numere pana cand se citeste un caracter */
        aux = AlocCelula2(x);
        if (!aux) return L;
        ultim->urm = aux;
        aux->pre = ultim;
        ultim = aux;
        (*dimLista)++;
    }

    return L;
}

/* Afisare continut lista */
void AfisareLista2(TLista2 L) {
    TLista2 p = L->urm;    
    //printf("Lista: [");
    while (p != NULL) {         /* parcurgere lista */
        printf("%c ", p->info);   
        p = p->urm;
    }
    //printf("]\n");
    printf("\n");
}

/* Distrugere lista */
void DistrugeLista2(TLista2 *aL) {
    TLista2 p = (*aL)->urm, aux = NULL;
    while (p != NULL) {         /* distrugere elementele listei */
        aux = p;
        p = p->urm;
        free(aux);
    }

    free(*aL);                  /* distrugere santinela */
    *aL = NULL;
}



//COADA

TCoada* InitQ ()  /* creeaza coada vida cu elemente de dimensiune d;  anumite implementari pot necesita si alti parametri */
{ 
  TCoada* c;          /* spatiu pentru descriptor coada */
  c = (TCoada*)malloc(sizeof(TCoada));
  if ( !c ) return NULL;                  /* nu exista spatiu -> "esec" */

  c->inc = c->sf = NULL;
  return c;          /* intoarce adresa descriptorului cozii */
}

int IntrQ(TCoada *c, char *s)  /* adauga element la sfarsitul cozii */
{ 
  TLista aux = NULL;
  aux = (TLista)malloc(sizeof(TCelula));      /* aloca o noua celula */
  if ( !aux) return 0;             /* alocare imposibila -> "esec" */

  strcpy(aux->info, s); aux->urm = NULL;

  if (c->sf != NULL)          /* coada nevida */
    c->sf->urm = aux;                   /* -> leaga celula dupa ultima din coada */
  else                              /* coada vida */
    c->inc = aux;                    /* -> noua celula se afla la inceputul cozii */
  c->sf = aux;  	            /* actualizeaza sfarsitul cozii */
  return 1;                         /* operatie reusita -> "succes" */
}

void DistrQ(TCoada **c) /* distruge coada */
{
  TLista p = NULL, aux = NULL;
  p = (*c)->inc;
  while(p) {
    aux = p;
    p = p->urm;
    free(aux);
  }
  free(*c);
  *c = NULL;
}

void AfisareQ(TCoada *c, FILE *fout)  /* afisare elementele cozii */
{
  TLista p = NULL;
  if(c->inc == NULL)  /* coada vida */
  {
    fprintf(fout, "Coada vida\n");
    return;
  } 
  //printf("Elementele cozii: ");
  for(p = c->inc; p != NULL; p = p->urm)
    fprintf(fout, "%s\n", p->info);
  fprintf(fout, "\n");
}

int ExtrQ (TCoada *c, char *x) /* extrage primul element din coada */
{
  TLista aux = NULL;
  if(c->inc != NULL ) {
    aux = c->inc;
    strcpy(x,  aux->info);
    c->inc = aux->urm;
    if (c->inc == NULL)
      c->sf = NULL;
    free (aux);
    return 1;
  }
  else return 0;
}




//afisarea pozitie degetului
void SHOW_CURRENT(TBanda *b, FILE *fout){
    if( (*b)->deget->pre != NULL )
        fprintf(fout, "%c\n", (*b)->deget->info);
}

//afisarea listei dublu inlantuite
void SHOW(TBanda b, FILE *fout){
    TLista2 p = b->inceput->urm;
    while(p!=NULL) {
        if( b->deget == p )
            fprintf(fout, "|%c|", p->info);
        else
            fprintf(fout, "%c", p->info);
        p = p->urm;
    }
    fprintf(fout, "\n");
}

//suprascrierea informatiei din pozitia degetului
void WRITE(TBanda *b, char c){
    if((*b)->deget->pre !=NULL)
        (*b)->deget->info = c;
}

//mutarea cu o poztie in stanga a degetului
int MOVE_LEFT(TBanda *b){
    if((*b)->deget->pre->pre != NULL) {
        (*b)->deget = (*b)->deget->pre;
        return 1;
    }
    return 0;//cazul in care degetul se afla pe al doilea elem din lista(primul fiind santinela); nu se poate efectua operatia
}

//mutarea degetului cu o pozitie la dreapta
int MOVE_RIGHT(TBanda *b){
    if((*b)->deget->urm != NULL) {
        (*b)->deget = (*b)->deget->urm;
    } else {
        TLista2 aux = AlocCelula2('#');
        (*b)->deget->urm = aux;
        aux->pre = (*b)->deget;
        aux->urm = NULL;
        (*b)->deget = (*b)->deget->urm;
    }
    return 1;
}

// mutarea degetului in stanga pana la un anumit caracter
int MOVE_LEFT_CHAR(TBanda *b, char c, FILE *fout){
    TLista2 p = NULL;
    p = (*b)->deget;
    while ((p)->pre->pre != NULL) {
        if ((p)->info == c) {
                (*b)->deget = p;
                return 1;
            }
        (p) = (p)->pre;
    }
    if ((p)->info == c) {
            (*b)->deget = p;
            return 1;
        }
    // caz in care caracterul nu a fost gasit in banda
    fprintf(fout, "ERROR\n");
    return 0;
}

// mutarea degetului in dreapta pana la un caracter
int MOVE_RIGHT_CHAR(TBanda *b, char c){
    while ((*b)->deget->urm != NULL) {
        if ((*b)->deget->info == c)
            return 0;
        (*b)->deget = (*b)->deget->urm;
    }
    if ((*b)->deget->info == c)
        return 0;
    TLista2 aux = AlocCelula2('#');
    (*b)->deget->urm = aux;
    aux->pre = (*b)->deget;
    aux->urm = NULL;
    (*b)->deget = (*b)->deget->urm;
    return 1;
}

// inserarea unui caracter in stanga pozitiei degetului
int INSERT_LEFT(TBanda *b, char c, FILE *fout){
    if ((*b)->deget->pre->pre == NULL) {
        fprintf(fout, "ERROR\n");
        return 0;
    } else {
        TLista2 aux = AlocCelula2(c); 
        aux->pre = (*b)->deget->pre;
        aux->urm = (*b)->deget;
        (*b)->deget->pre->urm = aux;
        (*b)->deget->pre = aux;
        (*b)->deget = (*b)->deget->pre;
        return 1;
    }
}

// inserarea unui caracter in dreapta pozitiei degetului
int INSERT_RIGHT(TBanda *b, char c){
    if ((*b)->deget->urm == NULL) {
        TLista2 aux = AlocCelula2(c);
        aux->pre = (*b)->deget;
        aux->urm = NULL;
        (*b)->deget->urm = aux;
        (*b)->deget = (*b)->deget->urm;
        return 1;
    } else {
        TLista2 aux = AlocCelula2(c);
        aux->pre = (*b)->deget;
        aux->urm = (*b)->deget->urm;
        (*b)->deget->urm->pre = aux;
        (*b)->deget->urm = aux;
        (*b)->deget = (*b)->deget->urm;
        return 1;
    }
    
}

// distrugere stiva
void DistrugeS(TStiva* vf) {
    TStiva aux = NULL;
    while(*vf) {
        aux = *vf;
        *vf = (*vf)->urm;
        free(aux);
    }
}

// initializare stiva
TStiva InitS(void)
{ 
    TStiva aux = (TStiva)malloc(sizeof(TCelulaStiva));
    aux->urm = NULL;
    aux->info = 0;
    return aux;
}

// inserarea unui pointer catre pozitia curenta a degtului in stiva
int Push(TStiva* vf, TLista2 deget)
{

    TStiva aux = (TStiva)malloc(sizeof(TCelulaStiva)); 
    if(!aux) 
        return 0;
    if( (*vf) == NULL ) {
            aux->info = deget;
            aux->urm = NULL;
            *vf = aux;
        } else {
            aux->info = deget;
            aux->urm = NULL;
            aux->urm = *vf; 
            *vf = aux;
        }
    return 1;
}

// extragerea pointerului din varful stivei
int Pop(TStiva* vf, TLista2 *copie)
{
    TStiva aux = NULL;
    if (*vf == NULL) 
        return 0;
    *copie = (*vf)->info; 
    aux = *vf; 
    *vf = aux->urm; 
    free(aux); 
    return 1;
}

// anularea ultimei operatii
void UNDO (TStiva *vf_st_undo, TStiva *vf_st_redo, TBanda *b) {
        int x = 0;
        TLista2 *copie;
        copie = malloc(sizeof(TLista2 *));
        *copie = (*b)->deget;
        x = Push(vf_st_redo, (*b)->deget);
        x = Pop(vf_st_undo, copie);
        
        (*b)->deget = *copie;
        free(copie);
    }

// refacerea ultimei operatii
void REDO (TStiva *vf_st_undo, TStiva *vf_st_redo, TBanda *b) {
        TLista2 *copie;
        copie = malloc(sizeof(TLista2 *));
        *copie = (*b)->deget;
        Push(vf_st_undo, (*b)->deget);
        Pop(vf_st_redo, copie);
        
        (*b)->deget = *copie;
        free(copie);
    }

// distrugerea banda
void DistrBanda(TBanda *b)
{
  TLista2 p = NULL, aux = NULL;
  p = (*b)->inceput;
  while (p) {
    aux = p;
    p = p->urm;
    free(aux);
  }
  free(*b);
  *b = NULL;
}