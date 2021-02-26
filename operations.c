#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "operations.h"
#include "utility.h"

void cadastroAluno(listaAluno l)
{
    Aluno a;
    int sair;
    do
    {
        printf("\nDigite a MATRICULA do Aluno o qual deseja cadastrar: ");
        fgets(a.matricula,sizeof(a.matricula),stdin);
        check_newline(a.matricula);
        
        if (pesquisaMatricula(l,a.matricula)==0)
        {
            printf("\nDigite o NOME do Aluno: ");
            fgets(a.nome,sizeof(a.nome),stdin);
            check_newline(a.nome);
        
            do
            {
                printf("\nDigite a DATA DE NASCIMENTO do Aluno: ");
                fgets(a.dataNasc,sizeof(a.dataNasc),stdin);
                check_newline(a.dataNasc);
            } while (verify_date(a.dataNasc)==0);
        
            if (insereFinalAluno(l,a))
                printf("\nAluno cadastrado com com sucesso.");
            else
                printf("\nFalha ao cadastrar aluno...");
        }
        else
            printf("\nA matricula %s já foi cadastrada...",a.matricula);
        
        printf("\nDeseja Repetir esta operação??  1->SIM 2->NÃO \nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
}

void cadastroDisciplina(listaAluno l)
{
    Aluno a;
    Disciplina d;
    TNodoAluno *n;
    int sair, posicao;
    do
    {
        printf("\nDigite a MATRICULA do Aluno ao qual deseja CADASTRAR uma disciplina: ");
        fgets(a.matricula,sizeof(a.matricula),stdin);
        check_newline(a.matricula);
        
        posicao = (pesquisaMatricula(l,a.matricula));
        
        if(posicao!=0)
        {
            getElementoAluno(l,posicao,&n);

            printf("\nDigite o NOME da disciplina: ");
            fgets(d.nomeDisciplina,sizeof(d.nomeDisciplina),stdin);
            check_newline(d.nomeDisciplina);

            if (insereFinalDisciplina(n->L_Disc,d))
                printf("\nDisciplina cadastrada com com sucesso.");
            else
                printf("\nFalha ao cadastrar disciplina...");
        }
        else
            printf("\nAluno não cadastrado...");

        printf("\nDeseja Repetir esta operação??  1->SIM 2->NÃO \nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
}

void cadastroAvaliacao(listaAluno l)
{
    Aluno a;
    Disciplina d;
    Avaliacao av;
    TNodoAluno *nA;
    TNodoDisciplina *nD;
    int sair, posicaoA, posicaoD;
    do
    {
        
        printf("\nDigite a MATRICULA do Aluno ao qual deseja CADASTRAR uma avaliacao: ");
        fgets(a.matricula,sizeof(a.matricula),stdin);
        check_newline(a.matricula);
        
        posicaoA = (pesquisaMatricula(l,a.matricula));
        
        if(posicaoA!=0)
        {
            getElementoAluno(l,posicaoA,&nA);

            printf("\nDigite o NOME da disciplina da avaliacao: ");
            fgets(d.nomeDisciplina,sizeof(d.nomeDisciplina),stdin);
            check_newline(d.nomeDisciplina);

            posicaoD = pesquisaDisciplina(nA->L_Disc,d.nomeDisciplina);

            if(posicaoD!=0)
            {
                getElementoDisciplina(nA->L_Disc,posicaoD,&nD);

                printf("\nDigite o NOME da avaliação: ");
                fgets(av.nomeAvaliacao,sizeof(av.nomeAvaliacao),stdin);
                check_newline(av.nomeAvaliacao);
                printf("\nDigite o VALOR da avaliação: ");
                scanf("%d",&av.valor);
                setbuf(stdin,NULL);
                // bloquear notas maiores que o valor??
                printf("\nDigite a NOTA do aluno nesta avaliação: ");
                scanf("%d",&av.nota);
                setbuf(stdin,NULL);

                /* Verificar o limite de valor de nota aqui */

                if (insereFinalAvaliacao(nD->L_Ava,av))
                    printf("\nAvaliação cadastrada com com sucesso.");
                else
                    printf("\nFalha ao cadastrar avaliação...");
            }
            else
                printf("\nDisciplina não cadastrada...");
        }
        else
            printf("\nAluno não cadastrado...");

        printf("\nDeseja Repetir esta operação??  1->SIM 2->NÃO \nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
}

void excluirAluno(listaAluno l)
{
    Aluno a;
    int sair;
    do
    {
        printf("\nDigite a MATRICULA do Aluno que deseja excluir: ");
        fgets(a.matricula,sizeof(a.matricula),stdin);
        check_newline(a.matricula);

        if(pesquisaMatricula(l,a.matricula)!=0)
        {
            removeElementoAluno(l,a.matricula);
            printf("\nTodas as informações do aluno de matricula \"%s\" foram excluidas, incluindo disciplinas, avaliações e notas.",a.matricula);
        }
        else
            printf("\nA matricula fornecida mão está cadastrada...");
        
        printf("\nDeseja Repetir esta operação??  1->SIM 2->NÃO \nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

void excluirDisciplina(listaAluno l)
{
    Aluno a;
    Disciplina d;
    TNodoAluno *n;
    int sair, posicao;
    do
    {
        printf("\nDigite a MATRICULA do Aluno ao qual deseja EXCLUIR uma disciplina: ");
        fgets(a.matricula,sizeof(a.matricula),stdin);
        check_newline(a.matricula);
        
        posicao = (pesquisaMatricula(l,a.matricula));
        
        if(posicao!=0)
        {
            getElementoAluno(l,posicao,&n);

            printf("\nDigite o NOME da disciplina: ");
            fgets(d.nomeDisciplina,sizeof(d.nomeDisciplina),stdin);
            check_newline(d.nomeDisciplina);

            if(pesquisaDisciplina(n->L_Disc,d.nomeDisciplina)!=0)
            {
                removeElementoDisciplina(n->L_Disc,d.nomeDisciplina);
                printf("\nA disciplina \"%s\", suas avaliações e notas foram removidas do cadastro do aluno %s.",d.nomeDisciplina,n->info.nome);
            }
            else
                printf("\nDisciplina fornecida não está cadastrada no aluno %s...",n->info.nome);
        }
        else
            printf("\nA Matricula \"%s\" não corresponde a nenhum cadastro...",a.matricula);

        printf("\nDeseja Repetir esta operação??  1->SIM 2->NÃO \nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

void excluirAvaliacao(listaAluno l)
{
    Aluno a;
    Disciplina d;
    Avaliacao av;
    TNodoAluno *nA;
    TNodoDisciplina *nD;
    int sair, posicaoA, posicaoD;
    do
    {
        printf("\nDigite a MATRICULA do Aluno ao qual deseja EXCLUIR uma avaliação: ");
        fgets(a.matricula,sizeof(a.matricula),stdin);
        check_newline(a.matricula);
        
        posicaoA = (pesquisaMatricula(l,a.matricula));
        
        if(posicaoA!=0)
        {
            getElementoAluno(l,posicaoA,&nA);

            printf("\nDigite o NOME da disciplina da avaliacao: ");
            fgets(d.nomeDisciplina,sizeof(d.nomeDisciplina),stdin);
            check_newline(d.nomeDisciplina);

            posicaoD = pesquisaDisciplina(nA->L_Disc,d.nomeDisciplina);

            if(posicaoD!=0)
            {
                getElementoDisciplina(nA->L_Disc,posicaoD,&nD);

                printf("\nDigite o NOME da avaliação a ser excluida: ");
                fgets(av.nomeAvaliacao,sizeof(av.nomeAvaliacao),stdin);
                check_newline(av.nomeAvaliacao);

                if(pesquisaAvaliacao(nD->L_Ava,av.nomeAvaliacao)!=0)
                {
                    removeElementoAvaliacao(nD->L_Ava,av.nomeAvaliacao);
                    printf("\nA avaliação \"%s\" da disciplina \"%s\" do aluno %s foi excluida.",av.nomeAvaliacao,d.nomeDisciplina,nA->info.nome);
                }
                else
                    printf("\nA avaliação \"%s\" não corresponde a nenhuma avaliação cadastrada...",av.nomeAvaliacao);

            }
            else
                printf("\nDisciplina fornecida não está cadastrada no aluno %s...",nA->info.nome);
        }
        else
            printf("\nA Matricula \"%s\" não corresponde a nenhum cadastro...",a.matricula);

        printf("\nDeseja Repetir esta operação??  1->SIM 2->NÃO \nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

int pesquisaMatricula(listaAluno l,char* matricula) // mudar de Header??
{
    int pos;
    TNodoAluno *p;

    if (getTamanhoAluno(l)==0)
        return 0;
    else
    {
        p = l->first;
        if(strcmp(p->info.matricula,matricula)==0)
            return 1;
        
        for(pos=2;pos<=l->tamanho;pos++)
        {
            p = p->next;
            if(strcmp(p->info.matricula,matricula)==0)
                return pos;
        }
    }
    return 0;
}

int pesquisaDisciplina(listaDisciplina l,char* nome) // mudar de Header??
{
    int pos;
    TNodoDisciplina *p;

    if (getTamanhoDisciplina(l)==0)
        return 0;
    else
    {
        p = l->first;
        if(strcmp(p->info.nomeDisciplina,nome)==0)
            return 1;
        
        for(pos=2;pos<=l->tamanho;pos++)
        {
            p = p->next;
            if(strcmp(p->info.nomeDisciplina,nome)==0)
                return pos;
        }
    }
    return 0;
}

int pesquisaAvaliacao(listaAvaliacao l,char* nome) //mudar de header??
{
    int pos;
    TNodoAvaliacao *p;

    if (getTamanhoAvaliacao(l)==0)
        return 0;
    else
    {
        p = l->first;
        if(strcmp(p->info.nomeAvaliacao,nome)==0)
            return 1;
        
        for(pos=2;pos<=l->tamanho;pos++)
        {
            p = p->next;
            if(strcmp(p->info.nomeAvaliacao,nome)==0)
                return pos;
        }
    }
    return 0;
}