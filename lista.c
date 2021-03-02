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
    }
    return l;
}

listaDisciplina criaListaDisciplina(){
    listaDisciplina l = (listaDisciplina)malloc(sizeof(TListaDisciplina));
    if(l){
        l->first = NULL;
        l->last = NULL;
        l->tamanho=0;
    }
    return l;
}

listaAvaliacao criaListaAvaliacao(){
    listaAvaliacao l = (listaAvaliacao)malloc(sizeof(TListaAvaliacao));
    if(l){
        l->first = NULL;
        l->last = NULL;
        l->tamanho=0;
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

int insereInicioAluno(listaAluno l,Aluno e)
{
    TNodoAluno *p;
    p=(TNodoAluno*)malloc(sizeof(TNodoAluno));

    if(!p)
        return 0;
    /* Cria uma lista de disciplinas para o aluno,
     caso não seja possível, libera o espaço alocado
     para p e retorna 0 */
    if((p->L_Disc = criaListaDisciplina())==NULL)
    {
        free(p);
        return 0;
    }
    p->info =e;
    p->prior = NULL;
    p->next = l->first;
    if(l->first)
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
    /* Cria uma lista de avaliaçõess para a disciplina,
     caso não seja possível, libera o espaço alocado
     para p e retorna 0 */
    if((p->L_Ava = criaListaAvaliacao())==NULL)
    {
        free(p);
        return 0;
    }
    p->info =e;
    p->next = l->first;
    l->first = p;
    if(l->tamanho==0)
        l->last =p;
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
    p->next = l->first;
    l->first = p;
    if(l->tamanho==0)
        l->last =p;
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
        p=l->first;
        for(i=1;i<posicao;i++)
            p=p->next;
        *e = p;
    }
    else{
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

    p=l->first;
    for(i=1;i<posicao;i++)
        p=p->next;
    *e = p;
    return 1;
}

int getElementoAvaliacao(listaAvaliacao l,int posicao,TNodoAvaliacao **e)
{
    int i;
    TNodoAvaliacao *p;

    if(posicao<1 || posicao>l->tamanho)
        return 0;

    p=l->first;
    for(i=1;i<posicao;i++)
        p=p->next;
    *e = p;
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
    /* Cria uma lista de disciplinas para o aluno,
     caso não seja possível, libera o espaço alocado
     para p e retorna 0 */
    if((p->L_Disc = criaListaDisciplina())==NULL)
    {
        free(p);
        return 0;
    }
    p->info = e;
    p->next = NULL;
    p->prior = l->last;
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
    /* Cria uma lista de avaliações para a disciplina,
     caso não seja possível, libera o espaço alocado
     para p e retorna 0 */
    if((p->L_Ava = criaListaAvaliacao())==NULL)
    {
        free(p);
        return 0;
    }
    
    p->info = e;
    p->next=NULL;
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
                l->first = NULL;
                l->last = NULL;
            }
            else
            if(p==l->first)
            {
                l->first = l->first->next;
                l->first->prior = NULL;
            }
            else
            if(p==l->last)
            {
                l->last = l->last->prior;
                l->last->next = NULL;
            }
            else
            {
                p->prior->next = p->next;
                p->next->prior = p->prior;
            }
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
    TNodoDisciplina *p,*ant;
    p=l->first;
    while(p)
    {
        if(strcmp(p->info.nomeDisciplina,nomeDisc)==0)
        {
            if(l->tamanho==1)
            {
                //A lista possui um unico Nodo
                l->first = NULL;
                l->last = NULL;
            }
            else
            if(p==l->first)
            {
                //removendo o primeiro Lodo da lista
                l->first = l->first->next;
            }
            else
            if(p==l->last)
            {
                //Removendo o ultimo Nodo da lista
                l->last = ant;
                l->last->next = NULL;
            }
            else
            {
                //Removendo um nodo interno da lista
                ant->next = p->next;
            }
            terminaListaAvaliacao(p->L_Ava);
            free(p);
            l->tamanho--;
            return 1;
        }
        else
        {
            ant = p;
            p = p->next;
        }

    }
    return 0;
}

int removeElementoAvaliacao(listaAvaliacao l,char* nomeAva)
{
    TNodoAvaliacao *p, *ant;
    p=l->first;
    while(p)
    {
        if(strcmp(p->info.nomeAvaliacao,nomeAva)==0)
        {
            if(l->tamanho==1)
            {
                l->first =NULL;
                l->last=NULL;
            }
            else
            if(p==l->first)
            {
                l->first = l->first->next;
            }
            else
            if(p==l->last)
            {
                l->last = ant;
                l->last->next = NULL;
            }
            else
            {
                ant->next=p->next;
            }
            free(p);
            l->tamanho--;
            return 1;
        }
        else
        {
            ant = p;
            p = p->next;           
        }
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