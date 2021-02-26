#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void file_parser(FILE *arq, listaAluno l)
{
    int c, flagCampo = 1, flagNodo = 1;
    char buf[2], valorTmp[4], notaTmp[4], *endPtr;
    Aluno eAl;
    Disciplina eDisc;
    Avaliacao eAv;

    eAl.matricula[0]='\0';
    eAl.nome[0]='\0';
    eAl.dataNasc[0]='\0';
    eDisc.nomeDisciplina[0]='\0';
    eAv.nomeAvaliacao[0]='\0';
    valorTmp[0] = '\0';
    notaTmp[0] = '\0';
    
    fseek(arq,0,SEEK_END);
    if(ftell(arq)!=0)
    {
        fseek(arq,0,SEEK_SET);
        while ((c = fgetc(arq)) != EOF)
        {
            //printf("\nfgetc loop %c",c); //teste (apagar antes de entregar)
            if (c == '\n')
            {  
                if(flagNodo == 2 && flagCampo == 4)
                {
                    /* converter e armazenar valor e nota */
                    eAv.valor = strtol(valorTmp,&endPtr,10);
                    eAv.nota = strtol(notaTmp,&endPtr,10);
                    /* Inserir os dados */
                    insereFinalAvaliacao(l->last->L_Disc->last->L_Ava,eAv);
                    /* Resetar campos da avaliação */
                    eAv.nomeAvaliacao[0]='\0';
                    valorTmp[0] = '\0';
                    notaTmp[0] = '\0';

                }
                flagCampo = 1;
                flagNodo = 1;
                /* reiniciar campos do aluno aqui */
                eAl.matricula[0]='\0';
                eAl.nome[0]='\0';
                eAl.dataNasc[0]='\0';
            }

            else if (c == '@')
            {
                if(flagNodo == 1)
                {
                    /* inserir aluno na lista */
                    insereFinalAluno(l,eAl);
                    flagNodo = 2;
                    flagCampo = 1;
                }
                    
                else if(flagNodo == 2)
                {
                    /* converter e armazenar valor e nota */
                    eAv.valor = strtol(valorTmp,&endPtr,10);
                    eAv.nota = strtol(notaTmp,&endPtr,10);
                    /* Inserir Avaliação na lista*/
                    insereFinalAvaliacao(l->last->L_Disc->last->L_Ava,eAv);
                    /* Resetar campos da avaliação */
                    eAv.nomeAvaliacao[0]='\0';
                    valorTmp[0] = '\0';
                    notaTmp[0] = '\0';
                    /* resetar Campos da Disc */
                    eDisc.nomeDisciplina[0]='\0';
                    flagCampo = 1;
                } 
            }

            else if (c == '#')
            {
                if (flagCampo<4)
                {
                    if(flagNodo == 2 && flagCampo == 1)
                    {
                        /* inserir Disc na lista */
                        insereFinalDisciplina(l->last->L_Disc,eDisc);
                        /* resetar Campos da Disc */
                        eDisc.nomeDisciplina[0]='\0';
                    }
                        
                    flagCampo++;
                }
                    
                else
                {
                    /* converter e armazenar valor e nota */
                    eAv.valor = strtol(valorTmp,&endPtr,10);
                    eAv.nota = strtol(notaTmp,&endPtr,10);
                    /* Inserir Avaliação aqui?? */
                    insereFinalAvaliacao(l->last->L_Disc->last->L_Ava,eAv);
                    /* Resetar campos da avaliação aqui?? */
                    valorTmp[0] = '\0';
                    notaTmp[0] = '\0';
                    eAv.nomeAvaliacao[0]='\0';
                    flagCampo = 2;
                }
            }

            else
            {
                if (flagNodo ==1 && flagCampo == 1)
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eAl.matricula,buf);
                }
                else if (flagNodo ==1 && flagCampo == 2)
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eAl.nome,buf);
                }
                else if (flagNodo ==1 && flagCampo == 3)
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eAl.dataNasc,buf);
                }
                else if (flagNodo ==2 && flagCampo == 1)
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eDisc.nomeDisciplina,buf);
                }
                else if (flagNodo ==2 && flagCampo == 2)
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eAv.nomeAvaliacao,buf);
                }
                else if (flagNodo ==2 && flagCampo == 3)
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(valorTmp,buf);
                }
                else if (flagNodo ==2 && flagCampo == 4)
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(notaTmp,buf);
                }
            }
        }
    }
    else
        printf("\nArquivo vazio...");
}

listaAluno criaListaAluno(){
    listaAluno l = (listaAluno)malloc(sizeof(TListaAluno));
    if(l){
        l->first = NULL;
        l->last = NULL;
        l->tamanho=0;
        l->current=NULL;
    }
    return l;
}

listaDisciplina criaListaDisciplina(){
    listaDisciplina l = (listaDisciplina)malloc(sizeof(TListaDisciplina));
    if(l){
        l->first = NULL;
        l->last = NULL;
        l->tamanho=0;
        l->current=NULL;
    }
    return l;
}

listaAvaliacao criaListaAvaliacao(){
    listaAvaliacao l = (listaAvaliacao)malloc(sizeof(TListaAvaliacao));
    if(l){
        l->first = NULL;
        l->last = NULL;
        l->tamanho=0;
        l->current=NULL;
    }
    return l;
}

void terminaListaAlunos(listaAluno l)
{
    TNodoAluno *p;
    while(l->first)
    {
        p = l->first;
        l->first = l->first->next;
        terminaListaDisciplina(p->L_Disc);
        free(p);
    }
    free(l);
}

void terminaListaDisciplina(listaDisciplina l)
{
    TNodoDisciplina *p;
    while(l->first)
    {
        p = l->first;
        l->first = l->first->next;
        terminaListaAvaliacao(p->L_Ava);
        free(p);
    }
    free(l);
}

void terminaListaAvaliacao(listaAvaliacao l)
{
    TNodoAvaliacao *p;
    while(l->first)
    {
        p = l->first;
        l->first = l->first->next;
        free(p);
    }
    free(l);
}

/* TODO: alterar as funções abaixo */

/*int inserePosicao(lista l,TElemento e,int posicao)
{
    TNodo *p,*pAux;
    int k;
    if(posicao==1)
        return insereInicio(l,e);
    else
        if(posicao == l->tamanho +1)
            return insereFinal(l,e);
    else
    {
        if(posicao<1 || posicao >l->tamanho +1)
            return 0;
        p=(TNodo*)malloc(sizeof(TNodo));
        p->info = e;
        if(!p)//veruficando se conseguiu alocar espa�o de mem��oria
            return 0;
        pAux=l->first;
        for(k=1;k<posicao;k++)
            pAux = pAux->next;
        p->next = pAux;
        p->prior = pAux->prior;
        pAux->prior->next =p;
        pAux->prior =p;
        l->tamanho++;
        return 1;
    }
}*/

int insereInicioAluno(listaAluno l,Aluno e)
{
    TNodoAluno *p;
    p=(TNodoAluno*)malloc(sizeof(TNodoAluno));

    if(!p)
        return 0;
    if((p->L_Disc = criaListaDisciplina())==NULL)
    {
        return 0;
    }
    p->info =e;
    p->prior = NULL;
    p->next = l->first;
    //p->L_Disc = criaListaDisciplina();
    if(l->first)/*verificando se a lista n�o est� vazia*/
        l->first->prior =p;
    else
        l->last =p;

    l->first = p;
    l->tamanho++;
        return 1;
}

int insereInicioDisciplina(listaDisciplina l,Disciplina e)
{
    TNodoDisciplina *p;
    p=(TNodoDisciplina*)malloc(sizeof(TNodoDisciplina));

    if(!p)
        return 0;
    if((p->L_Ava = criaListaAvaliacao())==NULL)
    {
        return 0;
    }
    p->info =e;
    p->prior = NULL;
    p->next = l->first;
    //p->L_Ava = criaListaAvaliacao();
    if(l->first)/*verificando se a lista n�o est� vazia*/
        l->first->prior =p;
    else
        l->last =p;

    l->first = p;
    l->tamanho++;
        return 1;
}

int insereInicioAvaliacao(listaAvaliacao l,Avaliacao e)
{
    TNodoAvaliacao *p;
    p=(TNodoAvaliacao*)malloc(sizeof(TNodoAvaliacao));

    if(!p)
        return 0;

    p->info =e;
    p->prior = NULL;
    p->next = l->first;
    if(l->first)/*verificando se a lista n�o est� vazia*/
        l->first->prior =p;
    else
        l->last =p;

    l->first = p;
    l->tamanho++;
        return 1;
}

int getElementoAluno(listaAluno l,int posicao,TNodoAluno **e)
{
    int i;
    TNodoAluno *p;

    if(posicao<1 || posicao>l->tamanho)
        return 0;

    if(posicao<= l->tamanho/2){
        /*percorrendo a lista a partir do primeiro nodo*/
        p=l->first;
        for(i=1;i<posicao;i++)
            p=p->next;
        *e = p;
    }
    else{
        /*percorrendo a lista a partir do ultimo nodo*/
        p=l->last;
        for(i=l->tamanho;i>posicao;i--)
            p=p->prior;
        *e = p;
    }
    return 1;
}

int getElementoDisciplina(listaDisciplina l,int posicao,TNodoDisciplina **e)
{
    int i;
    TNodoDisciplina *p;

    if(posicao<1 || posicao>l->tamanho)
        return 0;

    if(posicao<= l->tamanho/2){
        /*percorrendo a lista a partir do primeiro nodo*/
        p=l->first;
        for(i=1;i<posicao;i++)
            p=p->next;
        *e = p;
    }
    else{
        /*percorrendo a lista a partir do ultimo nodo*/
        p=l->last;
        for(i=l->tamanho;i>posicao;i--)
            p=p->prior;
        *e = p;
    }
    return 1;
}

int getElementoAvaliacao(listaAvaliacao l,int posicao,Avaliacao *e)
{
    int i;
    TNodoAvaliacao *p;

    if(posicao<1 || posicao>l->tamanho)
        return 0;

    if(posicao<= l->tamanho/2){
        /*percorrendo a lista a partir do primeiro nodo*/
        p=l->first;
        for(i=1;i<posicao;i++)
            p=p->next;
        *e=p->info;
    }
    else{
        /*percorrendo a lista a partir do ultimo nodo*/
        p=l->last;
        for(i=l->tamanho;i>posicao;i--)
            p=p->prior;
        *e=p->info;
    }
    return 1;
}

int insereFinalAluno(listaAluno l,Aluno e)
{
    TNodoAluno *p;
    if(l->first==NULL)
        return insereInicioAluno(l,e);

    p=(TNodoAluno*)malloc(sizeof(TNodoAluno));

    if(!p)
        return 0;
    if((p->L_Disc = criaListaDisciplina())==NULL)
    {
        free(p); // não sei se precisa
        return 0;
    }
    p->info = e;
    p->next = NULL;
    p->prior = l->last;
    //p->L_Disc = criaListaDisciplina();
    l->last->next = p;
    l->last =p;
    l->tamanho++;
    return 1;
}

int insereFinalDisciplina(listaDisciplina l,Disciplina e)
{
    TNodoDisciplina *p;
    if(l->first==NULL)
        return insereInicioDisciplina(l,e);

    p=(TNodoDisciplina*)malloc(sizeof(TNodoDisciplina));

    if(!p)
        return 0;
    if((p->L_Ava = criaListaAvaliacao())==NULL)
    {
        free(p); // não sei se precisa
        return 0;
    }
    p->info = e;
    p->next=NULL;
    p->prior = l->last;
    //p->L_Ava = criaListaAvaliacao();
    l->last->next = p;
    l->last =p;
    l->tamanho++;
    return 1;
}

int insereFinalAvaliacao(listaAvaliacao l,Avaliacao e)
{
    TNodoAvaliacao *p;
    if(l->first==NULL)
        return insereInicioAvaliacao(l,e);

    p=(TNodoAvaliacao*)malloc(sizeof(TNodoAvaliacao));

    if(!p)
        return 0;

    p->info = e;
    p->next=NULL;
    p->prior = l->last;
    l->last->next = p;
    l->last =p;
    l->tamanho++;
    return 1;
}

int removeElementoAluno(listaAluno l,char* matricula)
{
    TNodoAluno *p;
    p = l->first;
    while(p)
    {
        if(strcmp(p->info.matricula,matricula)==0)
        {
            if(l->tamanho==1)
            {
                /*A lista possui um �nico Nodo*/
                l->first = NULL;
                l->last = NULL;
            }
            else
            if(p==l->first)
            {
                /*removendo o primeiro Lodo da lista*/
                l->first = l->first->next;
                l->first->prior = NULL;
            }
            else
            if(p==l->last)
            {
                /*Removendo o �ltimo Nodo da lista*/
                l->last = l->last->prior;
                l->last->next = NULL;
            }
            else
            {
                /*Removendo um nodo interno � lista*/
                p->prior->next = p->next;
                p->next->prior = p->prior;
            }
            //*e=p->info; //Qual a utilidade disso pra mim??
            terminaListaDisciplina(p->L_Disc);
            free(p);
            l->tamanho--;
            return 1;
        }
        else
            p=p->next;
    }
    return 0;
}

int removeElementoDisciplina(listaDisciplina l,char* nomeDisc)
{
    TNodoDisciplina *p;
    p=l->first;
    while(p)
    {
        if(strcmp(p->info.nomeDisciplina,nomeDisc)==0)
        {
            if(l->tamanho==1)
            {
                /*A lista possui um �nico Nodo*/
                l->first =NULL;
                l->last=NULL;
            }
            else
            if(p==l->first)
            {
                /*removendo o primeiro Lodo da lista*/
                l->first = l->first->next;
                l->first->prior = NULL;
            }
            else
            if(p==l->last)
            {
                /*Removendo o �ltimo Nodo da lista*/
                l->last = l->last->prior;
                l->last->next = NULL;
            }
            else
            {
                /*Removendo um nodo interno � lista*/
                p->prior->next = p->next;
                p->next->prior = p->prior;
            }
            //*e=p->info;
            terminaListaAvaliacao(p->L_Ava);
            free(p);
            l->tamanho--;
            return 1;
        }
        else
            p=p->next;
    }
    return 0;
}

int removeElementoAvaliacao(listaAvaliacao l,char* nomeAva)
{
    TNodoAvaliacao *p;
    p=l->first;
    while(p)
    {
        if(strcmp(p->info.nomeAvaliacao,nomeAva))
        {
            if(l->tamanho==1)
            {
                /*A lista possui um �nico Nodo*/
                l->first =NULL;
                l->last=NULL;
            }
            else
            if(p==l->first)
            {
                /*removendo o primeiro Lodo da lista*/
                l->first = l->first->next;
                l->first->prior = NULL;
            }
            else
            if(p==l->last)
            {
                /*Removendo o �ltimo Nodo da lista*/
                l->last = l->last->prior;
                l->last->next = NULL;
            }
            else
            {
                /*Removendo um nodo interno � lista*/
                p->prior->next = p->next;
                p->next->prior = p->prior;
            }
            //*e=p->info;
            free(p);
            l->tamanho--;
            return 1;
        }
        else
            p=p->next;
    }
    return 0;
}

int getTamanhoAluno(listaAluno l)
{
    return l->tamanho;
}

int getTamanhoDisciplina(listaDisciplina l)
{
    return l->tamanho;
}

int getTamanhoAvaliacao(listaAvaliacao l)
{
    return l->tamanho;
}

/*int setCorrente(lista l,int posicao)
{
    int i;
    if(posicao<1 || posicao >l->tamanho)
        return 0;

    if(posicao <l->tamanho/2){
        //percorrer do in�cio
        l->current = l->first;
        for(i=1;i<posicao ;i++)
            l->current = l->current->next;
    }
    else{
        //Percorrer do final
        l->current= l->last;
        for(i=l->tamanho;i>posicao;i++)
            l->current=l->current->prior;
    }
    return 1;
}

int getCorrente(lista l,TElemento*e)
{
    if(l->current)
    {
        *e=l->current->info;
        l->current = l->current->next;
        return 1;
    }
    else
        return 0;
}

int listaVazia(lista l)
{
    return l->first==NULL;//return !l->first
}

int listaCheia(lista l)
{
    TNodo *p;
    p=(TNodo*)malloc(sizeof(TNodo));
    if(p)
    {
        free(p);
        return 0;
    }
    else
        return 1;
}*/