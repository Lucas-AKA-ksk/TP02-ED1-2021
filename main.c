#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "listaTest.h"

int main(void) // usar argc e argv?
{
    FILE *fp_arq;
    open_file(&fp_arq,"dados.txt");
    listaAluno la = criaListaAluno();
    if(la!=NULL && fp_arq!=NULL)
    {
        file_parser(fp_arq,la);
    }

    TNodoAluno alunoInfo;
    TNodoDisciplina discInfo;
    Avaliacao avaInfo;
    getElementoAluno(la,1,&alunoInfo);
    

    fclose(fp_arq);
    terminaListaAlunos(la);
    return 0;
}