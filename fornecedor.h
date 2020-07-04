#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED

struct Fornecedor

{
    int codigo, telefone;
    char nome[50], produto[50];
};

typedef struct Fornecedor fornecedor;

FILE *fornecedorF;

int localiza_fornecedor(FILE *fornecedorF, int codigo)
{
    fornecedor forne;
    int posicao = -1, achou = 0;

    fseek(fornecedorF,0,SEEK_SET);
    fread(&forne, sizeof(forne),1, fornecedorF);

    while(!feof(fornecedorF) && !achou)
    {
        posicao++;

        if(forne.codigo==codigo)
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

    forne.codigo = 1 + rand() % 130;

    posicao=localiza_fornecedor(fornecedorF, forne.codigo);

    if (posicao==-1)
    {
        printf("Digite o nome do fornecedor:");
        fflush(stdin);
        gets(forne.nome);

        printf("Digite o produto do fornecedor:");
        fflush(stdin);
        gets(forne.produto);

        printf("Digite o telefone do fornecedor:");
        fflush(stdin);
        scanf("%d",&forne.telefone);

        fseek(fornecedorF,sizeof(forne) * (posicao),SEEK_SET);
        fwrite(&forne, sizeof(forne), 1, fornecedorF);
                    fflush(fornecedorF);
    }
    else
        printf("Fornecedor já cadastrado!!\n");

}

void imprime_fornecedores(FILE *fornecedorF)
{
    fornecedor forne;

    fseek(fornecedorF, 0, SEEK_SET);
    fread(&forne, sizeof(forne), 1, fornecedorF);

    printf("\n%6s%7s%28s%19s\n", "Codigo", "Nome",
           "Produto", "Telefone");

    while(!feof(fornecedorF))
    {
        printf("%-9d%-22s%-18s%12d\n",
               forne.codigo, forne.nome, forne.produto,
               forne.telefone);


        fread(&forne, sizeof(forne), 1, fornecedorF);
    }
    printf("\n");
}

#endif // FORNECEDOR_H_INCLUDED
