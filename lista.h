#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef int TChave;


typedef struct
{
    TChave chave;
    char nome[100], matricula[10],dataNasc[11];
}Aluno;

typedef struct
{
    TChave chave;
    char nomeDisciplina [50];
}Disciplina;

typedef struct
{
    TChave chave;
    char nomeAvaliacao [50];
    int valor, nota;
}Avaliacao;

typedef struct NodoAv
{
    Avaliacao info;
    struct NodoAv *next, *prior;  
}TNodoAvaliacao;

typedef struct NodoD
{
    Disciplina info;
    struct NodoD *next, *prior;
    /*listaAvaliacao*/ TListaAvaliacao *L_Ava;
}TNodoDisciplina;

typedef struct NodoAl
{
    Aluno info;
    struct NodoAl *next, *prior;
    /*listaDisciplina*/ TListaDisciplina *L_Disc;
}TNodoAluno;


typedef struct{
   TNodoAluno *first,*last,*current;
   int tamanho;
}TListaAluno;

typedef struct{
   TNodoDisciplina *first,*last,*current;
   int tamanho;
}TListaDisciplina;

typedef struct{
   TNodoAvaliacao *first,*last,*current;
   int tamanho;
}TListaAvaliacao;

typedef TListaAluno *listaAluno;
typedef TListaDisciplina *listaDisciplina;
typedef TListaAvaliacao *listaAvaliacao;

listaAluno criaListaAluno();

listaDisciplina criaListaDisciplina();

listaAvaliacao criaListaAvaliacao();

void terminaListaAlunos(listaAluno l);

void terminaListaDisciplina(listaDisciplina l);

void terminaListaAvaliacao(listaAvaliacao l);

int insereInicioAluno(listaAluno l,Aluno e);

int insereInicioDisciplina(listaDisciplina l,Disciplina e);

int insereInicioAvaliacao(listaAvaliacao l,Avaliacao e);

int getElementoAluno(listaAluno l,int posicao,Aluno *e);

int getElementoDisciplina(listaDisciplina l,int posicao,Disciplina *e);

int getElementoAvaliacao(listaAvaliacao l,int posicao,Avaliacao *e);

int insereFinalAluno(listaAluno l,Aluno e);

int insereFinalDisciplina(listaDisciplina l,Disciplina e);

int removeElementoAluno(listaAluno l,TChave ch,Aluno *e);

int removeElementoDisciplina(listaDisciplina l,TChave ch,Disciplina *e);

int removeElementoAvaliacao(listaAvaliacao l,TChave ch,Avaliacao *e);

int getTamanhoAluno(listaAluno l);

int getTamanhoDisciplina(listaDisciplina l);

int getTamanhoAvaliacao(listaAvaliacao l);

#endif // LISTA_H_INCLUDED
