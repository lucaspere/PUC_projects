#ifndef FESTA_H_INCLUDED
#define FESTA_H_INCLUDED

#include "cliente.h"
#include "contrato.h"

struct Festa
{
    int codigoFesta, codigoCliente, quanConvidados,
        dia, mes, ano, horas, minutos;
    char tema[15], dia_da_semana[7];
};

typedef struct Festa festa;

FILE *festaF;

int localiza_festa(FILE *festaF, int dia, int mes, int ano, int codigo)
{
    int posicao = -1, achou = 0;

    festa f;
    fseek(festaF, 0, SEEK_SET);
    fread(&f, sizeof(f), 1, festaF);

    while(!feof(festaF) && !achou)
    {
        posicao++;

        if((f.dia == dia) && (f.mes == mes) && (f.ano == ano))
        {
            achou = 1;
        }
        if(f.codigoFesta == codigo)
        {
            achou = 1;
        }

        fread(&f, sizeof(f), 1, festaF);
    }
    if(achou)
        return posicao;
    else
        return -1;
}
void cadastrar_festa(FILE *festaF)
{
    festa f;
    int posicao,restricao_cliente;

    printf("Digite o codigo do cliente: ");
    fflush(stdin);
    scanf("%d",&f.codigoCliente);
    restricao_cliente = localiza_cliente(clientC, f.codigoCliente);

    if(restricao_cliente != -1)
    {
        printf("Digite o codigo da festa: ");
        fflush(stdin);
        scanf("%d",&f.codigoFesta);

        printf("Digite a data da festa (Exemplo: 28-06-2020)\n?");
        scanf("%d%*c%d%*c%d", &f.dia, &f.mes, &f.ano);

        posicao = localiza_festa(festaF, f.dia, f.mes, f.ano, f.codigoFesta);

        if(posicao == -1)
        {

            printf("Qual dia da semana? (Exemplo segunda) ");
            fflush(stdin);
            scanf("%s", &f.dia_da_semana);

            printf("Define o horário da festa (Exemplo: 22:45)\n?");
            scanf("%d%*c%d", &f.horas, &f.minutos);

            printf("Digite o tema da festa: ");
            fflush(stdin);
            gets(f.tema);

            printf("Insira quantidade de convidados: ");
            scanf("%d", &f.quanConvidados);

            fseek(festaF, sizeof(f) * (posicao), SEEK_SET);
            fwrite(&f, sizeof(f), 1, festaF);
            fflush(festaF);

            registra_contrato(f.codigoFesta, f.quanConvidados, f.dia_da_semana);
        }
        else
            printf("Festa já registrada!\n");
    }
    else
        printf("Cliente não cadastrado!");

}

void imprime_festas(FILE *festaF)
{
    festa f;

    fseek(festaF, 0, SEEK_SET);
    fread(&f, sizeof(f), 1, festaF);

    printf("\n%6s%17s%15s\n", "Convidados", "Cliente",
           "Tema");

    while(!feof(festaF))
    {
        printf("%-20d%-15s%-9s\n",
               f.quanConvidados, f.dia_da_semana,
               f.tema);


        fread(&f, sizeof(f), 1, festaF);
    }
    printf("\n");
}


#endif // FESTA_H_INCLUDED
