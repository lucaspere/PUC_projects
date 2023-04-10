#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

#include <string.h>

struct Fornecedor

{
    int codigo;
    char nome[50], telefone[16],produto[50];
};

typedef struct Fornecedor fornecedor;

FILE *fornecedorF;

int localiza_fornecedor(FILE *fornecedorF, const char *nomeForne)
{
    fornecedor forne;
    int posicao = -1, achou = 0;

    fseek(fornecedorF,0,SEEK_SET);
    fread(&forne, sizeof(forne),1, fornecedorF);


    while(!feof(fornecedorF) && !achou)
    {
        posicao++;

        if(!strcmp(forne.nome, nomeForne))
        {
            achou=1;
        }
        fread(&forne, sizeof(forne),1, fornecedorF);
    }

    if(achou)
        return posicao;
    else
        return -1;
}

void cadastrar_fornecedor(FILE *fornecedorF)
{
    fornecedor forne;

    int posicao;

    printf("Digite o nome do fornecedor: ");
    fflush(stdin);
    gets(forne.nome);

    posicao=localiza_fornecedor(fornecedorF, forne.nome);

    if (posicao==-1)
    {

        forne.codigo = 1 + rand() % 130;
        printf("Digite o produto: ");
        fflush(stdin);
        gets(forne.produto);

        printf("Digite o telefone do fornecedor: ");
        fflush(stdin);
        gets(forne.telefone);

        fseek(fornecedorF,sizeof(forne) * (posicao),SEEK_SET);
        fwrite(&forne, sizeof(forne), 1, fornecedorF);
        fflush(fornecedorF);
    }
    else
        printf("Fornecedor já cadastrado!!\n");

}

void imprime_fornecedor(FILE *fornecedorF, const char *nomeForne)
{
    fornecedor forne;
    int posicao;

    posicao = localiza_fornecedor(fornecedorF, nomeForne);

    if(posicao != -1)
    {
        fseek(fornecedorF, sizeof(forne) * (posicao), SEEK_SET);
        fread(&forne, sizeof(forne), 1, fornecedorF);

        printf("\n%-9s%-18s%-15s%-15s\n", "Codigo", "Nome",
               "Produto", "Telefone");

        printf("%-9d%-18s%-15s%-15s\n",
               forne.codigo, forne.nome, forne.produto,
               forne.telefone);
    }
    else
        printf("Fornecedor não localizado\n");
}

void imprime_fornecedores(FILE *fornecedorF)
{
    fornecedor forne;

    fseek(fornecedorF, 0, SEEK_SET);
    fread(&forne, sizeof(forne), 1, fornecedorF);

    printf("\n%-9s%-18s%-15s%-15s\n", "Codigo", "Nome",
           "Produto", "Telefone");

    while(!feof(fornecedorF))
    {
        printf("%-9d%-18s%-15s%-15s\n",
               forne.codigo, forne.nome, forne.produto,
               forne.telefone);


        fread(&forne, sizeof(forne), 1, fornecedorF);
    }
    printf("\n");
}

#endif // FORNECEDOR_H_INCLUDED
