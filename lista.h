#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

//typedef int TChave;

/*Elemento Aluno*/
typedef struct
{
    //TChave chave;
    char nome[100], matricula[10],dataNasc[11];
}Aluno;

/*Elemento Disciplina*/
typedef struct
{
    //TChave chave;
    char nomeDisciplina [50];
}Disciplina;

/*Elemento Avaliação*/
typedef struct
{
    //TChave chave;
    char nomeAvaliacao [50];
    int valor, nota;
}Avaliacao;

/*Nodo Avaliação*/
typedef struct NodoAv
{
    Avaliacao info;
    struct NodoAv *next, *prior;  
}TNodoAvaliacao;

/*Lista Avaliação*/
typedef struct{
   TNodoAvaliacao *first,*last,*current;
   int tamanho;
}TListaAvaliacao;

/*Nodo Disciplina*/
typedef struct NodoD
{
    Disciplina info;
    struct NodoD *next, *prior;
    /*listaAvaliacao*/ TListaAvaliacao *L_Ava;
}TNodoDisciplina;

/*Lista Disciplina*/
typedef struct{
   TNodoDisciplina *first,*last,*current;
   int tamanho;
}TListaDisciplina;

/*Nodo Aluno*/
typedef struct NodoAl
{
    Aluno info;
    struct NodoAl *next, *prior;
    /*listaDisciplina*/ TListaDisciplina *L_Disc;
}TNodoAluno;

/*Lista Aluno*/
typedef struct{
   TNodoAluno *first,*last,*current;
   int tamanho;
}TListaAluno;

typedef TListaAluno *listaAluno;
typedef TListaDisciplina *listaDisciplina;
typedef TListaAvaliacao *listaAvaliacao;

//void file_parser(FILE *arq, listaAluno l);

listaAluno criaListaAluno();

listaDisciplina criaListaDisciplina();

listaAvaliacao criaListaAvaliacao();

void terminaListaAlunos(listaAluno l);

void terminaListaDisciplina(listaDisciplina l);

void terminaListaAvaliacao(listaAvaliacao l);

int insereInicioAluno(listaAluno l,Aluno e);

int insereInicioDisciplina(listaDisciplina l,Disciplina e);

int insereInicioAvaliacao(listaAvaliacao l,Avaliacao e);

int getElementoAluno(listaAluno l,int posicao,TNodoAluno **e);

int getElementoDisciplina(listaDisciplina l,int posicao,TNodoDisciplina **e);

int getElementoAvaliacao(listaAvaliacao l,int posicao,TNodoAvaliacao **e);

int insereFinalAluno(listaAluno l,Aluno e);

int insereFinalDisciplina(listaDisciplina l,Disciplina e);

int insereFinalAvaliacao(listaAvaliacao l,Avaliacao e);

int removeElementoAluno(listaAluno l,char* matricula);

int removeElementoDisciplina(listaDisciplina l,char* nomeDisc);

int removeElementoAvaliacao(listaAvaliacao l,char* nomeAva);

int getTamanhoAluno(listaAluno l);

int getTamanhoDisciplina(listaDisciplina l);

int getTamanhoAvaliacao(listaAvaliacao l);

#endif //LISTA_H_INCLUDED