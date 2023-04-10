/*
    Trabalho Prático Interdisciplinar
    Disciplinas: Fundamentos de Engenharia de Software
    Algoritmos e Estruturas de Dados I
    Curso: Engenharia de Software
    Profs.: Maria Augusta Nelson, Roberto Felipe Rocha e Ivre Marjorie R. Machado

    Autor: LUCAS FELLIPPE ALVES PEREIRA
    DATA: 06-2020
*/

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

int menu();
int menu_pesquisa();
int menu_relatorio();
void abre_arquivos();
void opcoes();
void opcoes_pesquisa();
void opcoes_relatorio();
void pagar_festa();

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
            printf("\npreenchendo o cliente...\n");
            cadastrar_cliente(clientC);
            system("pause");
            break;
        case 3:
            printf("\npreenchendo o funcionário...\n");
            cadastrar_funcionario(FuncionarioF);
            system("pause");
            break;
        case 4:
            printf("\npreenchendo o fornecedor...\n");
            cadastrar_fornecedor(fornecedorF);
            system("pause");
            break;
        case 5:
            opcoes_pesquisa();
            break;
        case 6:
            opcoes_relatorio();
            break;
        case 7:
            pagar_festa();
            system("pause");
            break;
        default:
            printf("\nEscolha incorreta!!\n");
            system("pause");
            break;
        }
    }
}

int menu(void)
{
    int menuChoice;
    system("cls");
    printf( "\n\tESCOLHA UMA OPÇÂO\n"
            "* * * * * * * * * * * * * * * * *\n"
            "* 1 --> CADASTRAR FESTA         *\n"
            "*                               *\n"
            "* 2 --> CADASTRAR CLIENTE       *\n"
            "*                               *\n"
            "* 3 --> CADASTRAR FUNCIONÁRIO   *\n"
            "*                               *\n"
            "* 4 --> CADASTRAR FORNECEDOR    *\n"
            "*                               *\n"
            "* 5 --> PESQUISAR               *\n"
            "*                               *\n"
            "* 6 --> RELATÓRIOS              *\n"
            "*                               *\n"
            "* 7 --> PAGAR FESTA             *\n"
            "*                               *\n"
            "* 9 --> SAIR                    *\n"
            "*                               *\n"
            "* * * * * * * * * * * * * * * * *\n?" );

    scanf( "%d", &menuChoice );
    return menuChoice;

}

void opcoes_pesquisa()
{
    int op, cCodigo;
    char nomeFun[50], nomeForne[50];

    while((op = menu_pesquisa()) != 5)
    {
        switch(op)
        {
        case 1:
            fflush(stdin);
            printf("Digite o código do cliente: ");
            scanf("%d", &cCodigo);
            imprime_cliente(clientC, cCodigo);
            system("pause");
            break;
        case 2:
            fflush(stdin);
            printf("Digite o nome do funcionário: ");
            gets(nomeFun);
            imprime_funcionario(FuncionarioF, nomeFun);
            system("pause");
            break;
        case 3:
            fflush(stdin);
            printf("Digite o nome do fornecedor: ");
            gets(nomeForne);
            imprime_fornecedor(fornecedorF, nomeForne);
            system("pause");
            break;
        default:
            printf("\nEscolha incorreta!!\n");
            system("pause");
            break;
        }
    }
}

void pagar_festa()
{
    printf("\n\t\t\tCONTRATOS");
    imprime_contratos(contratoC);

    pagar_contrato();
}

int menu_pesquisa()
{
    int menuChoice;
    system("cls");

    printf( "\n\tDigite sua escolha\n"
            "* * * * * * * * * * * * * * * * *\n"
            "* 1 --> PESQUISAR CLIENTE       *\n"
            "*                               *\n"
            "* 2 --> PESQUISAR FUNCIONÁRIO   *\n"
            "*                               *\n"
            "* 3 --> PESQUISAR FORNECEDOR    *\n"
            "*                               *\n"
            "* 5 --> VOLTAR MENU PRINCIPAL   *\n"
            "*                               *\n"
            "* * * * * * * * * * * * * * * * *\n?");

    scanf( "%d", &menuChoice);
    return menuChoice;
}

void opcoes_relatorio()
{
    int op;
    while((op = menu_relatorio()) != 5)
    {
        switch(op)
        {
        case 1:
            relatorio_festa();
            system("pause");
            break;
        case 2:
            imprime_festas_por_data();
            system("pause");
            break;
        default:
            printf("\nEscolha incorreta!!\n");
            system("pause");
            break;
        }
    }
}

int menu_relatorio()
{
    int menuChoice;
    system("cls");
    printf( "\n\tDigite sua escolha\n"
            "* * * * * * * * * * * * * * * * * * * * * *\n"
            "* 1 --> RELATORIO DE FESTA POR CLIENTE    *\n"
            "*                                         *\n"
            "* 2 --> FILTRAR FESTA POR DATA            *\n"
            "*                                         *\n"
            "* 5 --> VOLTAR MENU PRINCIPAL             *\n"
            "*                                         *\n"
            "* * * * * * * * * * * * * * * * * * * * * *\n?");


    scanf( "%d", &menuChoice);
    return menuChoice;
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
