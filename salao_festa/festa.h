#ifndef FESTA_H_INCLUDED
#define FESTA_H_INCLUDED

#include "cliente.h"
#include "contrato.h"

struct Festa
{
    int codigoFesta, codigoCliente, quanConvidados,
        dia, mes, ano, horas, minutos;
    char tema[15], dia_da_semana[15];
};

typedef struct Festa festa;

FILE *festaF;

void relatorio_festa()
{
    festa f;
    int codigo, posicao;

    fflush(stdin);
    printf("Digite o código do cliente: ");
    scanf("%d", &codigo);

    posicao = localiza_cliente(clientC, codigo);

    if(posicao != -1)
    {
        fseek(festaF, 0, SEEK_SET);
        fread(&f, sizeof(f), 1, festaF);

        printf("%-8s%-10s%-19s%-21s%-14s%-10s%-16s",
               "Festa", "Cliente", "Quant.Convidados", "Tema",
               "Data", "Horário", "Dia da Semana");

        while(!feof(festaF))
        {
            if(f.codigoCliente == codigo)
            {
                printf("\n%-8d%-10d%-19d%-13s%10d-%-d-%-d%7d:%-7d%-s",
                       f.codigoFesta, f.codigoCliente, f.quanConvidados,
                       f.tema, f.dia, f.mes, f.ano, f.horas, f.minutos, f.dia_da_semana);
            }
            fread(&f, sizeof(f), 1, festaF);
        }
        printf("\n");
    }
    else
    {
        printf("Não há festas com esse cliente!\n");
    }

}
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

            printf("Qual dia da semana? (Exemplo terca-feira) ");
            fflush(stdin);
            gets(f.dia_da_semana);

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
        printf("Cliente não cadastrado!\n");

}

void imprime_festas_por_data()
{
    festa f;
    int dia, mes, ano;
    float filtro;

    fflush(stdin);
    printf("A partir de qual data deseja filtrar? (Exemplo: 15-05-2020)\n?");
    scanf("%d%*c%d%*c%d", &dia, &mes, &ano);

    filtro = ((float) dia / 365) + ((float) mes / 12) + ((float) ano / 1);

    fseek(festaF, 0, SEEK_SET);
    fread(&f, sizeof(f), 1, festaF);

    printf("%-8s%-10s%-19s%-21s%-14s%-10s%-16s",
           "Festa", "Cliente", "Quant.Convidados", "Tema",
           "Data", "Horário", "Dia da Semana");

    while(!feof(festaF))
    {
        float data_atual = ((float) f.dia / 365) + ((float) f.mes / 12) + ((float) f.ano / 1);

        if(data_atual >= filtro)
        {
            printf("\n");
            printf("%-8d%-10d%-19d%-13s%10d-%-d-%-d%7d:%-7d%-s",
                   f.codigoFesta, f.codigoCliente, f.quanConvidados,
                   f.tema, f.dia, f.mes, f.ano, f.horas, f.minutos, f.dia_da_semana);
        }
        fread(&f, sizeof(f), 1, festaF);
    }
    printf("\n");
}

void imprime_festas(FILE *festaF)
{
    festa f;

    fseek(festaF, 0, SEEK_SET);
    fread(&f, sizeof(f), 1, festaF);

    printf("%-8s%-10s%-19s%-21s%-14s%-10s%-16s",
           "Festa", "Cliente", "Quant.Convidados", "Tema",
           "Data", "Horário", "Dia da Semana");

    while(!feof(festaF))
    {
        printf("\n%-8d%-10d%-19d%-13s%10d-%-d-%-d%7d:%-7d%-s",
               f.codigoFesta, f.codigoCliente, f.quanConvidados,
               f.tema, f.dia, f.mes, f.ano, f.horas, f.minutos, f.dia_da_semana);

        fread(&f, sizeof(f), 1, festaF);
    }
    printf("\n");
}


#endif // FESTA_H_INCLUDED
