/* MARINICA ALEXANDRA-RALUCA  GRUPA 315CB*/
#include "fct.h"
#define CONST 1000
#define THIRTY 30

int main(){

    FILE * fin = fopen("tema1.in", "r");
    FILE * fout = fopen("tema1.out", "w");

    TBanda copiedeget;
    TBanda Banda = malloc(sizeof(TCelulaBanda));
    Banda->inceput = InitLista2();
    Banda->inceput->urm = AlocCelula2('#');
    Banda->deget = Banda->inceput->urm;
    Banda->deget->pre = Banda->inceput;

    TStiva vf_st_undo = NULL, vf_st_redo = NULL;
    int pointer = 0;
    vf_st_undo = InitS();
    vf_st_redo = InitS();

    int n = 0, i = 0, x = 0;
    char s[CONST], caracter;
    TCoada *c;
    c = InitQ();
    fscanf(fin, "%d", &n);
    fgetc(fin);
    for (i=0; i<n; i++)
        {
            fgets(s, CONST, fin);
            s [ strcspn (s, "\n")] = 0;
            
            if (strcmp(s, "MOVE_LEFT") == 0)
                    IntrQ(c,s);
            else if (strcmp(s, "MOVE_RIGHT") == 0)
                IntrQ(c,s);
            else if (strstr(s, "MOVE_LEFT_CHAR") != 0)
                    IntrQ(c,s);	            
            else if (strstr(s, "MOVE_RIGHT_CHAR") != 0)
                    IntrQ(c,s);
            else if (strstr(s, "INSERT_LEFT") != 0)
                IntrQ(c,s);
            else if (strstr(s, "INSERT_RIGHT") != 0)
                IntrQ(c,s);
            else if (strcmp(s, "SHOW_CURRENT") == 0)
                SHOW_CURRENT(&Banda, fout);
            else if (strcmp(s, "SHOW") == 0)
               SHOW(Banda, fout);
            else if (strstr(s, "WRITE") != 0)
                IntrQ(c,s);
            else if (strcmp(s, "EXECUTE") == 0) {
                if (c->inc != NULL) {
                    char f[THIRTY];
                    ExtrQ(c, f);
                    if (strcmp(f, "MOVE_LEFT") == 0) {
                            TLista2 copie;
                            copie = Banda->deget;
                            if (MOVE_LEFT(&Banda) == 1)
                                Push(&vf_st_undo, copie);
                        } else if (strcmp(f, "MOVE_RIGHT") == 0) {
                            Push(&vf_st_undo, Banda->deget);
                            MOVE_RIGHT(&Banda);
                        } else if (strstr(f, "WRITE") != 0) {
                            caracter = f[strlen(f)-1];
                            WRITE(&Banda, caracter);
                        } else if (strstr(f, "MOVE_LEFT_CHAR") != 0) {
                            caracter = f[strlen(f)-1];
                            MOVE_LEFT_CHAR(&Banda, caracter, fout);
                        } else if (strstr(f, "MOVE_RIGHT_CHAR") != 0) {
                            caracter = f[strlen(f)-1];
                            MOVE_RIGHT_CHAR(&Banda, caracter);
                        } else if (strstr(f, "INSERT_LEFT") != 0) {
                            caracter = f[strlen(f)-1];
                            INSERT_LEFT(&Banda, caracter, fout);
                        } else if (strstr(f, "INSERT_RIGHT") != 0){
                            caracter = f[strlen(f)-1];
                            INSERT_RIGHT(&Banda, caracter);
                        }
                }
            } else if (strcmp(s, "UNDO") == 0)
                    UNDO(&vf_st_undo, &vf_st_redo, &Banda);
            else if (strcmp(s, "REDO") == 0)
                    REDO(&vf_st_undo, &vf_st_redo, &Banda);
            

        }
    fclose(fin);
    fclose(fout);
    DistrQ(&c);
    DistrugeS(&vf_st_undo);
    DistrugeS(&vf_st_redo);
    DistrugeLista2(&Banda->inceput);

    DistrBanda(&Banda);
}