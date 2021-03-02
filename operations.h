#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

void file_parser(FILE *arq, listaAluno l);

int integrity_check(listaAluno l);

int integrity_check_discp(listaDisciplina l);

int integrity_check_aval(listaAvaliacao l);

void save_to_file(FILE *arq, listaAluno l);

void save_discp_to_file(FILE *arq,listaDisciplina l);

void save_aval_to_file(FILE *arq,listaAvaliacao l);

void cadastroAluno(listaAluno l);

void cadastroDisciplina(listaAluno l);

void cadastroAvaliacao(listaAluno l);

void consultaMatricula(listaAluno l);

void consultaPrefixo(listaAluno l);

void listarDisc(listaDisciplina l);

void listarAval(listaAvaliacao l);

void excluirAluno(listaAluno l);

void excluirDisciplina(listaAluno l);

void excluirAvaliacao(listaAluno l);

void alterarNota(listaAluno l);

void relatorioAprov(listaAluno l);

void relatorioReprov(listaAluno l);

int verificaNotas(listaAvaliacao l);

int pesquisaMatricula(listaAluno l,char* matricula);

int pesquisaDisciplina(listaDisciplina l,char* nome);

int pesquisaAvaliacao(listaAvaliacao l,char* nome);

#endif // OPERATIONS_H_INCLUDED