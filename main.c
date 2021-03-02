#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "utility.h"
#include "lista.h"
#include "operations.h"

void menu(FILE*,listaAluno);

int main(void)
{
    setlocale(LC_ALL,"");
    FILE *fp_arq;
    open_file(&fp_arq,"dados.txt");
    listaAluno l = criaListaAluno();
    if(l!=NULL && fp_arq!=NULL)
    {
        file_parser(fp_arq,l);
        menu(fp_arq,l);
    }

    fclose(fp_arq);
    terminaListaAlunos(l);
    return 0;
}

void menu(FILE* arq, listaAluno l)
{
    int option, subOption;
    do
    {
        printf("\n\n##########~ Menu de Operacoes ~##########");
        printf("\n###~ 1->Cadastros ~######################");
        printf("\n###~ 2->Consultas ~######################");
        printf("\n###~ 3->Exclusões ~######################");
        printf("\n###~ 4->Alterar notas ~##################");
        printf("\n###~ 5->Verificar integridade ~##########");
        printf("\n###~ 6->Releatórios ~####################");
        printf("\n###~ 7->Gravar alterações ~##############");
        printf("\n###~ 0->Fechar Programa ~################");
        printf("\n\nEscolha: ");
        scanf("%d",&option);
        setbuf(stdin,NULL);

        switch (option)
        {
        case 0:
            printf("\nTerminando as listas e fechando o programa...");
            break;
        
        case 1:
            do
            {
                printf("\n\n############~ Submenu de Cadastros ~############");
                printf("\n###~ 1->Cadastro de aluno ~#####################");
                printf("\n###~ 2->Cadastro de Disciplina ~################");
                printf("\n###~ 3->Cadastro de avaliação ~#################");
                printf("\n###~ 0->Retornar ao Menu Principal ~############");
                printf("\n\nEscolha: ");
                scanf("%d",&subOption);
                setbuf(stdin,NULL);

                switch (subOption)
                {
                case 0:
                    break;
                
                case 1:
                    cadastroAluno(l);
                    break;

                case 2:
                    cadastroDisciplina(l);
                    break;

                case 3:
                    cadastroAvaliacao(l);
                    break;

                default:
                    printf("\nDigite um valor valido para relizar uma operação...");
                    break;
                }

            } while (subOption!=0);
            
            break;

        case 2:
            do
            {
                printf("\n\n############~ Submenu de Consultas ~############");
                printf("\n###~ 1->Consulta de aluno por Matricula ~#######");
                printf("\n###~ 2->Consulta de aluno por Prefixo ~#########");
                printf("\n###~ 0->Retornar ao Menu Principal ~############");
                printf("\n\nEscolha: ");
                scanf("%d",&subOption);
                setbuf(stdin,NULL);

                switch (subOption)
                {
                case 0:
                    break;
                
                case 1:
                    consultaMatricula(l);
                    break;

                case 2:
                    consultaPrefixo(l);
                    break;

                default:
                    printf("\nDigite um valor valido para relizar uma operação...");
                    break;
                }

            } while (subOption!=0);
            break;

        case 3:
            do
            {
                printf("\n\n############~ Submenu de Exclusões ~############");
                printf("\n###~ 1->Exclusão de aluno ~#####################");
                printf("\n###~ 2->Exclusão de Disciplina ~################");
                printf("\n###~ 3->Exclusão de avaliação ~#################");
                printf("\n###~ 0->Retornar ao Menu Principal ~############");
                printf("\n\nEscolha: ");
                scanf("%d",&subOption);
                setbuf(stdin,NULL);

                switch (subOption)
                {
                case 0:
                    break;
                
                case 1:
                    excluirAluno(l);
                    break;

                case 2:
                    excluirDisciplina(l);
                    break;

                case 3:
                    excluirAvaliacao(l);
                    break;

                default:
                    printf("\nDigite um valor valido para relizar uma operação...");
                    break;
                }

            } while (subOption!=0);
            break;

        case 4:
            alterarNota(l);
            break;

        case 5:
            if(integrity_check(l))
                printf("\nNenhum erro de integridade encontrado.");
            else
                printf("\nErros de integridade encontrados.");
            break;

        case 6:
            do
            {
                printf("\n\n############~ Submenu de Registros ~############");
                printf("\n###~ 1->Registro de alunos Aprovados ~##########");
                printf("\n###~ 2->Registro de alunos Reprovados ~#########");
                printf("\n###~ 0->Retornar ao Menu Principal ~############");
                printf("\n\nEscolha: ");
                scanf("%d",&subOption);
                setbuf(stdin,NULL);

                switch (subOption)
                {
                case 0:
                    break;
                
                case 1:
                    relatorioAprov(l);
                    break;

                case 2:
                    relatorioReprov(l);
                    break;

                default:
                    printf("\nDigite um valor valido para relizar uma operação...");
                    break;
                }

            } while (subOption!=0);
            break;

        case 7:
            save_to_file(arq,l);
            break;

        default:
            printf("\nDigite um valor valido para relizar uma operação...");
            break;
        }
        
    } while (option!=0);
    
}