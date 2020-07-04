#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

struct Cliente
{
    int codigo, telefone;
    char nome[50], endereco[100], datanasci[9];
};

typedef struct Cliente cliente;

FILE *clientC;

int localiza_cliente(FILE *clientC, int codigo)
{
    int posicao = -1, achou = 0;

    cliente cli;
    fseek(clientC,0,SEEK_SET);
    fread(&cli, sizeof(cli),1, clientC);

    while(!feof(clientC) && !achou)
    {
        posicao++;

        if(cli.codigo==codigo)
        {
            achou=1;
        }
        fread(&cli, sizeof(cli),1, clientC);
    }

    if(achou)
        return posicao;
    else
        return -1;
}

void cadastrar_cliente(FILE *clientC)
{
    cliente cli;

    int posicao;

    printf("Digite o codigo do cliente :");
    fflush(stdin);
    scanf("%d",&cli.codigo);

    posicao=localiza_cliente(clientC, cli.codigo);

    if (posicao==-1)
    {
        printf("Digite o nome do cliente:");
        fflush(stdin);
        gets(cli.nome);

        printf("Digite o endereco do cliente:");
        fflush(stdin);
        gets(cli.endereco);

        printf("Digite o telefone do cliente:");
        fflush(stdin);
        scanf("%d",&cli.telefone);

        printf("Digite a data de nascimento do cliente:(Exemplo: 19 03 1997)\n?");
        fflush(stdin);
        gets(cli.datanasci);

        fseek(clientC,sizeof(cli) * (posicao),SEEK_SET);
        fwrite(&cli, sizeof(cli), 1, clientC);
        fflush(clientC);
    }
    else
        printf("Cliente já cadastrado!!\n");

}

void imprime_clientes(FILE *clientC)
{
    cliente cli;

    fseek(clientC, 0, SEEK_SET);
    fread(&cli, sizeof(cli), 1, clientC);

    printf("\n%6s%7s%28s%19s\n", "Codigo", "Nome",
           "Nascimento", "Telefone");

    while(!feof(clientC))
    {
        printf("%-9d%-22s%-18s%12d\n",
               cli.codigo, cli.nome, cli.datanasci,
               cli.telefone);


        fread(&cli, sizeof(cli), 1, clientC);
    }
    printf("\n");
}


#endif // CLIENTE_H_INCLUDED
