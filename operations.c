#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "operations.h"
#include "utility.h"

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

int integrity_check(listaAluno l)
{
    TNodoAluno *nA;
    if(l->tamanho > 0)
    {
        nA = l->first;
        while (nA)
        {
            if (!integrity_check_discp(nA->L_Disc))
                return 0;
            nA = nA->next;
        }
        return 1;
    }
    else
        printf("\nLista vazia...");
    return 0;
}

int integrity_check_discp(listaDisciplina l)
{
    TNodoDisciplina *nD;
    if (l->tamanho > 0)
    {
        nD = l->first;
        while(nD)
        {
            if(!integrity_check_aval(nD->L_Ava))
                return 0;
            nD = nD->next;
        }
        return 1;
    }
    else
        return 0;
}

int integrity_check_aval(listaAvaliacao l)
{
    TNodoAvaliacao *nAv;
    int soma = 0;
    if(l->tamanho > 0)
    {
        nAv = l->first;
        while (nAv)
        {
            soma += nAv->info.valor;
            nAv = nAv->next;
        }
        if(soma == 100)
            return 1;
    }
    return 0;
}

void save_to_file(FILE *arq, listaAluno l)
{
    TNodoAluno *nA;
    if (integrity_check(l))
    {
        freopen("dados.txt","w+",arq);
        fseek(arq,0,SEEK_SET);
        nA = l->first;
        while (nA)
        {
            fprintf(arq,"%s#%s#%s",nA->info.matricula,nA->info.nome,nA->info.dataNasc);
            save_discp_to_file(arq,nA->L_Disc);
            nA = nA->next;
            fprintf(arq,"\n");
        }
    }
    else
        printf("\nNão é possivel salvar uma lista com erros de integridade...");
}

void save_discp_to_file(FILE *arq,listaDisciplina l)
{
    TNodoDisciplina *nD;
    nD = l->first;
    while (nD)
    {
        fprintf(arq,"@%s",nD->info.nomeDisciplina);
        save_aval_to_file(arq,nD->L_Ava);
        nD = nD->next;
    }
}

void save_aval_to_file(FILE *arq,listaAvaliacao l)
{
    TNodoAvaliacao *nAv;
    nAv = l->first;
    while (nAv)
    {
        fprintf(arq,"#%s#%d#%d",nAv->info.nomeAvaliacao,nAv->info.valor,nAv->info.nota);
        nAv = nAv->next;
    }
}

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

void consultaMatricula(listaAluno l)
{
    int sair, posicao;
    char matricula[10];
    TNodoAluno *nA;
    do
    {
        printf("\nDigite a MATRICULA do aluno a ser consultado: ");
        fgets(matricula,sizeof(matricula),stdin);
        check_newline(matricula);

        posicao = pesquisaMatricula(l,matricula);

        if (posicao!=0)
        {
            getElementoAluno(l,posicao,&nA);
            printf("\n##########~ Dados do aluno ~##########");
            printf("\n####~ Matricula: %s\n####~ Nome: %s\n####~ Data de Nasc. : %s",nA->info.matricula,nA->info.nome,nA->info.dataNasc);
            listarDisc(nA->L_Disc);
        }
        else
            printf("\nA matricula fornecida não corresponde a nenhum cadastro.");
        
        printf("\nDeseja Repetir esta operação??  1->SIM 2->NÃO \nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

void consultaPrefixo(listaAluno l)
{
    int sair, matches;
    char prefixo[4];
    TNodoAluno *nA;
    do
    {
        matches = 0;
        printf("\nDigite o PREFIXO do nome a ser consultado: ");
        fgets(prefixo,sizeof(prefixo),stdin);
        check_newline(prefixo);

        nA = l->first;
        while (nA)
        {
            if (strncmp(nA->info.nome,prefixo,3)==0)
            {
                //getElementoAluno(l,posicao,&nA);
                printf("\n##########~ Dados do aluno ~##########");
                printf("\n####~ Matricula: %s\n####~ Nome: %s\n####~ Data de Nasc. : %s",nA->info.matricula,nA->info.nome,nA->info.dataNasc);
                listarDisc(nA->L_Disc);
                matches++;
            }
            nA = nA->next;
        }
        printf("\nForam encontrados %d matches para o prefixo fornecido",matches);
        printf("\nDeseja Repetir esta operação??  1->SIM 2->NÃO \nEscolha: ");
        scanf("%d",&sair);
        setbuf(stdin,NULL);
    } while (sair!=2);
    
}

void listarDisc(listaDisciplina l)
{
    TNodoDisciplina *nD;

    nD = l->first;
    printf("\n\n##########~ Disciplinas cursadas ~##########");
    while(nD)
    {
        printf("\n####~ Nome da Disc.: %s",nD->info.nomeDisciplina);
        listarAval(nD->L_Ava);
        nD = nD->next;
    }
}

void listarAval(listaAvaliacao l)
{
    TNodoAvaliacao *nAv;

    nAv = l->first;
    printf("\n\n######~ Avaliações da Disciplina ~######");
    while (nAv)
    {
        printf("\n####~ Nome da Aval.: %s\n####~ Valor: %d\n####~ Nota: %d\n",nAv->info.nomeAvaliacao,nAv->info.valor,nAv->info.nota);
        nAv = nAv->next;
    }
    
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

void alterarNota(listaAluno l)
{
    int sair, posicaoA, posicaoD, posicaoAv;
    Aluno a;
    Disciplina d;
    Avaliacao av;
    TNodoAluno *nA;
    TNodoDisciplina *nD;
    TNodoAvaliacao *nAv;

    do
    {
        printf("\nDigite a MATRICULA do Aluno ao qual deseja alterar a nota de uma avaliação: ");
        fgets(a.matricula,sizeof(a.matricula),stdin);
        check_newline(a.matricula);
        
        posicaoA = (pesquisaMatricula(l,a.matricula));

        if (posicaoA!=0)
        {
            getElementoAluno(l,posicaoA,&nA);

            printf("\nDigite o NOME da disciplina da avaliacao: ");
            fgets(d.nomeDisciplina,sizeof(d.nomeDisciplina),stdin);
            check_newline(d.nomeDisciplina);

            posicaoD = pesquisaDisciplina(nA->L_Disc,d.nomeDisciplina);

            if (posicaoD!=0)
            {
                getElementoDisciplina(nA->L_Disc,posicaoD,&nD);

                printf("\nDigite o NOME da avaliação: ");
                fgets(av.nomeAvaliacao,sizeof(av.nomeAvaliacao),stdin);
                check_newline(av.nomeAvaliacao);

                posicaoAv = pesquisaAvaliacao(nD->L_Ava,av.nomeAvaliacao);

                if (posicaoAv!=0)
                {
                    getElementoAvaliacao(nD->L_Ava,posicaoAv,&nAv);
                    printf("\nDigite a nova nota: ");
                    scanf("%d",&nAv->info.nota);
                    setbuf(stdin,NULL);
                    printf("\nNota Alterada com sucesso.");
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

int pesquisaMatricula(listaAluno l,char* matricula)
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

int pesquisaDisciplina(listaDisciplina l,char* nome)
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

int pesquisaAvaliacao(listaAvaliacao l,char* nome)
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