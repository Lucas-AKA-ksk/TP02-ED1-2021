#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

void cadastroAluno(listaAluno l);

void cadastroDisciplina(listaAluno l);

void cadastroAvaliacao(listaAluno l);

void excluirAluno(listaAluno l);

void excluirDisciplina(listaAluno l);

void excluirAvaliacao(listaAluno l);

int pesquisaMatricula(listaAluno l,char* matricula); // mudar de header??

int pesquisaDisciplina(listaDisciplina l,char* nome); //mudar de header??

int pesquisaAvaliacao(listaAvaliacao l,char* nome); //mudar de header??

#endif // OPERATIONS_H_INCLUDED