#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#include "festa.h"
#include "cliente.h"
#include "funcionario.h"
#include "fornecedor.h"
#include "contrato.h"

typedef struct Cliente cliente;

int menu(void);
void abre_arquivos();
void opcoes();

int main(void)
{
    srand(time(NULL));

    setlocale (LC_ALL, "portuguese");

    abre_arquivos();
    opcoes();

    fclose(festaF);
    fclose(clientC);
    fclose(FuncionarioF);
    fclose(fornecedorF);
    fclose(contratoC);

    return 0;
}

void opcoes()
{
    int op;

    while((op = menu()) != 9)
    {
        switch(op)
        {
        case 1:
            printf("\npreenchendo o festa...\n");
            cadastrar_festa(festaF);
            system("pause");
            break;
        case 2:
            printf("\nlistando festa...\n");
            imprime_festas(festaF);
            system("pause");
            break;
        case 3:
            printf("\npreenchendo o cliente...\n");
            cadastrar_cliente(clientC);
            system("pause");
            break;
        case 4:
            printf("\nlistando o cliente...\n");
            imprime_clientes(clientC);
            system("pause");
            break;
        case 5:
            printf("\npreenchendo o funcionário...\n");
            cadastrar_funcionario(FuncionarioF);
            system("pause");
            break;
        case 6:
            printf("\nlistando o funcionário...\n");
            imprime_funcionarios(FuncionarioF);
            system("pause");
            break;
        case 7:
            printf("\npreenchendo o fornecedor...\n");
            cadastrar_fornecedor(fornecedorF);
            system("pause");
            break;
        case 8:
            printf("\nlistando o fornecedor...\n");
            imprime_fornecedores(fornecedorF);
            system("pause");
            break;
        default:
            printf("\nEscolha incorreta!!\n");
            system("pause");
            break;
        }
    }
}

void abre_arquivos()
{
    if((festaF = fopen("festa.dat", "r+b")) == NULL)
    {
        printf("Arquivo 'festa.dat' não existe ... criando arquivo!\n");
        if((festaF = fopen("festa.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo festa.dat!!");
            exit(1);
        }
        system("pause");
    }

    if((clientC = fopen("cliente.dat", "r+b")) == NULL)
    {
        printf("Arquivo 'cliente.dat' não existe ... criando arquivo!\n");
        if((clientC = fopen("cliente.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo cliente.dat!!");
            exit(1);
        }
        system("pause");
    }

    if((FuncionarioF = fopen("funcionario.dat", "r+b")) == NULL)
    {
        printf("Arquivo 'funcionario.dat' não existe ... criando arquivo!\n");
        if((FuncionarioF = fopen("funcionario.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo funcionario.dat!!");
            exit(1);
        }
        system("pause");
    }

    if((fornecedorF = fopen("fornecedor.dat", "r+b")) == NULL)
    {
        printf("Arquivo 'fornecedor.dat' não existe ... criando arquivo!\n");
        if((fornecedorF = fopen("fornecedor.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo funcionario.dat!!");
            exit(1);
        }
        system("pause");
    }

    if((contratoC = fopen("contrato.dat", "r+b")) == NULL)
    {
        printf("Arquivo 'contrato.dat' não existe ... criando arquivo!\n");
        if((contratoC = fopen("contrato.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo funcionario.dat!!");
            exit(1);
        }
        system("pause");
    }
}

int menu(void)
{
    int menuChoice;
    system("cls");
    imprime_contratos(contratoC);
    printf( "\nDigite sua escolha\n"
            "1 - cadastrar festa\n"
            "2 - listar festa\n"
            "\n"
            "3 - cadastrar clientes\n"
            "4 - listar clientes\n"
            "\n"
            "5 - cadastrar funcionários\n"
            "6 - listar funcionários\n"
            "\n"
            "7 - cadastrar fornecedor\n"
            "8 - listar fornecedores\n"
            "\n"
            "9 - termina o programa\n? " );

    scanf( "%d", &menuChoice );
    return menuChoice;

}
