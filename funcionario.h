#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

struct Funcionario
{
    int codigo, telefone, salario;
    char nome[100], endereco[200], funcao[50], tipo[10];
};

typedef struct Funcionario funcionario;

FILE *FuncionarioF;

int localiza_funcionario(FILE *FuncionarioF, int codigo)
{
    int posicao = -1, achou = 0;

    funcionario fun;
    fseek(FuncionarioF,0,SEEK_SET);
    fread(&fun, sizeof(fun),1, FuncionarioF);

    while(!feof(FuncionarioF) && !achou)
    {
        posicao++;

        if(fun.codigo==codigo)
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

    printf("Digite o codigo do funcionario: ");
    fflush(stdin);
    scanf("%d",&fun.codigo);

    posicao=localiza_funcionario(FuncionarioF, fun.codigo);

    if (posicao==-1)
    {
        printf("Digite o nome do funcionário: ");
        fflush(stdin);
        gets(fun.nome);

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
        scanf("%d",&fun.salario);

        printf("Digite o telefone do funcionário: ");
        fflush(stdin);
        scanf("%d",&fun.telefone);

        fseek(FuncionarioF,sizeof(fun) * (posicao),SEEK_SET);
        fwrite(&fun, sizeof(fun), 1, FuncionarioF);
        fflush(FuncionarioF);
    }
    else
        printf("Funcionário já cadastrado!!\n");

}

void imprime_funcionarios(FILE *FuncionarioF)
{
    funcionario fun;

    fseek(FuncionarioF, 0, SEEK_SET);
    fread(&fun, sizeof(fun), 1, FuncionarioF);

    printf("\n%6s%7s%28s%19s\n", "Codigo", "Nome",
           "função", "salario");

    while(!feof(FuncionarioF))
    {
        printf("%-9d%-22s%-18s%12d\n",
               fun.codigo, fun.nome, fun.funcao,
               fun.salario);


        fread(&fun, sizeof(fun), 1, FuncionarioF);
    }
    printf("\n");
}

#endif // FUNCIONARIO_H_INCLUDED
