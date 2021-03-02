#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "operations.h"
#include "utility.h"

/* Lê as informações salvas em um arquivo e as armazena
 na lista l de acordo com os characteres separadores (#,@,"\n"),
 espera-se que o arquivo estaja sem erros na hora da leitura */
void file_parser(FILE *arq, listaAluno l)
{
    /* flagNodo e flagCampo representam em qual campo de qual nodo o char
    lido por fgetc deve ser concatenado, os caracteres separadores (@,#,"\n")
    são os responsáveis por inserir os dados lidos e alterar os valores dos
    flags. */
    int c, flagCampo = 1, flagNodo = 1;
    char buf[2], valorTmp[4], notaTmp[4], *endPtr;
    Aluno eAl;
    Disciplina eDisc;
    Avaliacao eAv;

    /* Colocando nul terminator na primeira posição de modo a "resetar" o campo
    de modo que a concatenação de cada char lido funcione, feito inicialmente aqui
    e sempre após inserir os valores em uma lista. */
    eAl.matricula[0]='\0';
    eAl.nome[0]='\0';
    eAl.dataNasc[0]='\0';
    eDisc.nomeDisciplina[0]='\0';
    eAv.nomeAvaliacao[0]='\0';
    valorTmp[0] = '\0';
    notaTmp[0] = '\0';
    
    /* verificando se o arquivo não está vazio */
    fseek(arq,0,SEEK_END);
    if(ftell(arq)!=0)
    {
        fseek(arq,0,SEEK_SET);
        /* loop fgetc */
        while ((c = fgetc(arq)) != EOF)
        {
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
                    /* Resetar campos da avaliação aqui*/
                    valorTmp[0] = '\0';
                    notaTmp[0] = '\0';
                    eAv.nomeAvaliacao[0]='\0';
                    flagCampo = 2;
                }
            }

            else
            {
                if (flagNodo ==1 && flagCampo == 1)/* campo matricula */
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eAl.matricula,buf);
                }
                else if (flagNodo ==1 && flagCampo == 2)/*  campo nome ALUNO*/
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eAl.nome,buf);
                }
                else if (flagNodo ==1 && flagCampo == 3)/* campo data de nascimento */
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eAl.dataNasc,buf);
                }
                else if (flagNodo ==2 && flagCampo == 1)/* campo nome DISCIPLINA */
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eDisc.nomeDisciplina,buf);
                }
                else if (flagNodo ==2 && flagCampo == 2)/* campo nome AVALIAÇÃO */
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(eAv.nomeAvaliacao,buf);
                }
                else if (flagNodo ==2 && flagCampo == 3)/* campo valor */
                {
                    buf[0] = c;
                    buf[1] = '\0';
                    strcat(valorTmp,buf);
                }
                else if (flagNodo ==2 && flagCampo == 4)/* campo nota */
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

/* Caso a lista de Alunos não esteja vazia e cada aluno
 passe no teste de integridade de suas disciplinas, retorna 1 */
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

/* Caso a lista de Disciplinas não esteja vazia e nenhuma das
 disciplinas falhe no teste de integridade de suas avaliações, retorna 1 */
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

/* Caso a lista de avaliações não esteja vazia e a soma dos
 valores das avaliações cadastradas seja 100, retorna 1 */
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

/* Salva as informações dos Alunos,
 assim como suas Disciplinas e avaliações no formato especificado */
void save_to_file(FILE *arq, listaAluno l)
{
    TNodoAluno *nA;
    /* Para ser gravada em um arquivo,
     as informações precisam estar integras */
    if (integrity_check(l))
    {
        /* Apaga os dados existentes no arquivo,
         de modo a evitar characteres "leftovers" caso
         os dados a serem gravados seja de tamanho menor
         do que os que estavam no arquivo */
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
        printf("\nNão é possivel salvar uma lista vazia ou com erros de integridade...");
}

/* Função auxiliar de save_to_file() que percorre a lista de disciplinas de um aluno para salvar as infos */
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

/* Função auxiliar de save_discp_to_file() que percorre a lista de avaliações de uma disciplina para salvar as infos */
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

            if(pesquisaDisciplina(n->L_Disc,d.nomeDisciplina)==0)
            {
                if (insereFinalDisciplina(n->L_Disc,d))
                    printf("\nDisciplina cadastrada com com sucesso.");
                else
                    printf("\nFalha ao cadastrar disciplina...");
            }
            else
                printf("\nEsta Disciplina já foi cadastrada para o Aluno %s",n->info.nome);
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

/* Consulta de alunos por matricula */
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

/* Consulta de alunos por prefixo do nome, percorre a lista de alunos e printa as infos de todos os alunos os quais o prefixo */
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

/* Função auxiliar de consultaMatricula() e consultaPrefixo()
 para printar a lista de disciplinas de um aluno */
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

/* Função auxiliar de listaDisc() para
 printar a lista de avaliações de uma Disciplina */
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

/* Printa os alunos que tenham nota final acima da média
 em TODAS as disciplinas, assim como a média das notas finais */
void relatorioAprov(listaAluno l)
{
    int aprovado, nota;
    int media;
    TNodoAluno *nA;
    TNodoDisciplina *nD;
    TNodoAvaliacao *nAv;
    nA = l->first;
    while (nA)
    {
        aprovado = 1;
        nD = nA->L_Disc->first;
        while (nD)
        {
            if(!verificaNotas(nD->L_Ava))
            {
                aprovado = 0;
                break;
            }
            nD = nD->next;
        }
        if (aprovado)
        {
            media = 0;
            printf("\n\n#~ Matricula: %s #~ Nome: %s #~ Data de Nasc.: %s",nA->info.matricula,nA->info.nome,nA->info.dataNasc);
            nD = nA->L_Disc->first;
            while (nD)
            {
                nota = 0;
                printf("\t\n#~ Disciplina: %s #~ Nota:",nD->info.nomeDisciplina);
                nAv = nD->L_Ava->first;
                while(nAv)
                {
                    nota += nAv->info.nota;
                    nAv = nAv->next;
                }
                printf("%d",nota);
                media += nota;
                nD = nD->next;
            }
            printf("\nMédia: %d",media/nA->L_Disc->tamanho);
        }
        nA = nA->next;
    }
}

/* Printa os alunos que tenham nota final abaixo da média
 em PELO MENOS UMA disciplina, assim como a média das notas finais */
void relatorioReprov(listaAluno l)
{
    int aprovado, nota;
    int media;
    TNodoAluno *nA;
    TNodoDisciplina *nD;
    TNodoAvaliacao *nAv;
    nA = l->first;
    while (nA)
    {
        aprovado = 1;
        nD = nA->L_Disc->first;
        while (nD)
        {
            if(!verificaNotas(nD->L_Ava))
            {
                aprovado = 0;
                break;
            }
            nD = nD->next;
        }
        if (!aprovado)
        {
            media = 0;
            printf("\n\n#~ Matricula: %s #~ Nome: %s #~ Data de Nasc.: %s",nA->info.matricula,nA->info.nome,nA->info.dataNasc);
            nD = nA->L_Disc->first;
            while (nD)
            {
                nota = 0;
                printf("\t\n#~ Disciplina: %s #~ Nota:",nD->info.nomeDisciplina);
                nAv = nD->L_Ava->first;
                while(nAv)
                {
                    nota += nAv->info.nota;
                    nAv = nAv->next;
                }
                printf("%d",nota);
                media += nota;
                nD = nD->next;
            }
            printf("\nMédia: %d",media/nA->L_Disc->tamanho);
        }
        nA = nA->next;
    }
}

/* Soma as notas de um aluno nas avaliações de uma disciplina
 e verifica se estão acima da média estabelecida (60pts) ,
 função auxiliar de relatorioAprov() e relatorioReprov() */
int verificaNotas(listaAvaliacao l)
{
    int soma = 0;
    TNodoAvaliacao *nAv;
    nAv = l->first;
    while(nAv)
    {
        soma += nAv->info.nota;   
        nAv = nAv->next;
    }
    if(soma>=60)
        return 1;
    return 0;
}

/* Pesquisa um aluno através da sua matricula, caso encontre,
 retorna a posição do mesmo na lista, e caso contrário, retorna 0 */
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

/* Pesquisa uma Disciplina através do seu nome, caso encontre,
 retorna a posição da mesma na lista, e caso contrário, retorna 0 */
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

/* Pesquisa uma Avaliação através do seu nome, caso encontre,
 retorna a posição da mesma na lista, e caso contrário, retorna 0 */
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