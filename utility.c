#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "lista.h"

/* Abre um arquivo existente para edição ou cria um arquivo caso não exista */
void open_file(FILE** fp,char* filename)
{
    *fp = fopen(filename,"r+");
    if(*fp == NULL){
        printf("\nArquivo %s não encontrado, um novo arquivo de mesmo nome será criado.", filename);
        *fp = fopen(filename, "w+");
    }
};

/* Substitui o newline(\n) por nul(\0) */
void newline_remover(char *s)
{
    if(s[strlen(s)-1]=='\n')
        s[strlen(s)-1]='\0';
}

/* Verifica a existencia de um newline em uma string 's',
caso não exista, consome o buffer, caso exista, chama newline_remover */
void check_newline(char *s)
{
    if(strchr(s,'\n')==NULL) /* Se \n  não for encontrado*/
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else 
        newline_remover(s);
}

/* Verifica se uma data é válida */
int verify_date(char *data)
{
    char dataF[11];
    strcpy(dataF, data);
    int dia, mes, ano, anoAtual=2021;
    if(strlen(data)!=10)
    {
        printf("Formato incorreto, caracteres insuficientes!");
        return 0;
    }
    if(data[2]!='/')
    {
        printf("formato incorreto, primeira barra faltando");
        return 0;
    }
    if(data[5]!='/')
    {
        printf("formato incorreto, segunda barra faltando!");
        return 0;
    }
    sscanf(strtok(dataF, "/"), "%d", &dia);
    sscanf(strtok(NULL, "/"), "%d", &mes);
    sscanf(strtok(NULL, "/"), "%d", &ano);
    
    if(ano>=1960 && ano<=anoAtual) //checa o ano de nascimento
    {
        
        if(mes>=1 && mes<=12) //checa mês de nascimento
        {
            //checa dia de nascimento
            if((dia>=1 && dia<=31) && (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12))
                printf("Data valida.\n");
            else if((dia>=1 && dia<=30) && (mes==4 || mes==6 || mes==9 || mes==11))
                printf("Data valida.\n");
            else if((dia>=1 && dia<=28) && (mes==2))
                printf("Data valida.\n");
            else if(dia==29 && mes==2 && (ano%400==0 ||(ano%4==0 && ano%100!=0)))
                printf("Data valida.\n");
            else{
                printf("Dia invalido.\n");
                return 0;
            }
        }
        else
        {
            printf("Mes invalido.\n");
            return 0;
        }
    }
    else
    {
        printf("Ano invalido.\n");
        return 0;
    }
    return 1;
}