#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

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

int getElementoAvaliacao(listaAvaliacao l,int posicao,TNodoAvaliacao **e)
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