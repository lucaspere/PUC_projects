#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <string.h>

struct Funcionario
{
    int codigo;
    float salario;
    char nome[50], telefone[15], endereco[150], funcao[50], tipo[10];
};

typedef struct Funcionario funcionario;

FILE *FuncionarioF;

int localiza_funcionario(FILE *FuncionarioF, const char *nome)
{
    int posicao = -1, achou = 0;

    funcionario fun;
    fseek(FuncionarioF,0,SEEK_SET);
    fread(&fun, sizeof(fun),1, FuncionarioF);

    while(!feof(FuncionarioF) && !achou)
    {
        posicao++;

        if(!strcmp(fun.nome, nome))
        {
            achou=1;
        }
        fread(&fun, sizeof(fun),1, FuncionarioF);
    }

    if(achou)
        return posicao;
    else
        return -1;
}

void cadastrar_funcionario(FILE *FuncionarioF)
{
    funcionario fun;
    int posicao;

    printf("Digite o nome do funcionário: ");
    fflush(stdin);
    gets(fun.nome);

    posicao=localiza_funcionario(FuncionarioF, fun.nome);

    if (posicao==-1)
    {
        fun.codigo = 1 + rand() % 130;

        printf("Digite o endereco do funcionário: ");
        fflush(stdin);
        gets(fun.endereco);

        printf("Digite a função do funcionário: ");
        fflush(stdin);
        gets(fun.funcao);

        printf("Temporário ou Fixo?: ");
        fflush(stdin);
        gets(fun.tipo);

        printf("Digite o salário do funcionário: ");
        fflush(stdin);
        scanf("%f",&fun.salario);

        printf("Digite o telefone do funcionário: ");
        fflush(stdin);
        gets(fun.telefone);

        fseek(FuncionarioF, sizeof(fun) * (posicao), SEEK_SET);
        fwrite(&fun, sizeof(fun), 1, FuncionarioF);
        fflush(FuncionarioF);
    }
    else
        printf("Funcionário já cadastrado!!\n");

}

void imprime_funcionario(FILE *FuncionarioF, const char *nomeFun)
{
    funcionario fun;
    int posicao;

    posicao = localiza_funcionario(FuncionarioF, nomeFun);

    if(posicao != -1)
    {
        fseek(FuncionarioF, sizeof(fun) * (posicao), SEEK_SET);
        fread(&fun, sizeof(fun), 1, FuncionarioF);

    printf("\n%-9s%-17s%-15s%-14s%-10s%-13s%-s\n", "Codigo", "Nome",
           "função", "telefone", "salario", "tipo", "endereço");

        printf("%-9d%-17s%-15s%-14d%-10.2f%-13s%-s\n",
               fun.codigo, fun.nome, fun.funcao,
               fun.telefone, fun.salario, fun.tipo, fun.endereco);
    }
    else
        printf("Funcionário não localizado\n");
}

void imprime_funcionarios(FILE *FuncionarioF)
{
    funcionario fun;

    fseek(FuncionarioF, 0, SEEK_SET);
    fread(&fun, sizeof(fun), 1, FuncionarioF);

    printf("\n%-9s%-17s%-15s%-14s%-10s%-13s%-s\n", "Codigo", "Nome",
           "função", "telefone", "salario", "tipo", "endereço");

    while(!feof(FuncionarioF))
    {
        printf("%-9d%-17s%-15s%-14d%-10.2f%-13s%-s\n",
               fun.codigo, fun.nome, fun.funcao,
               fun.telefone, fun.salario, fun.tipo, fun.endereco);


        fread(&fun, sizeof(fun), 1, FuncionarioF);
    }
    printf("\n");
}

#endif // FUNCIONARIO_H_INCLUDED
