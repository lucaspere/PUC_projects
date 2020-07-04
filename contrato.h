#ifndef CONTRATO_H_INCLUDED
#define CONTRATO_H_INCLUDED

#include <string.h>


struct Contrato
{
    int codigo_da_festa, num_contrato;
    float valor_total, desconto;
    char status[10], forma_de_pagamento[10];
};

typedef struct Contrato contrato;

float calcule_valorTotal(int qtd_convidados, const char *dia_da_semana);
void imprime_contratos(FILE *contratoC);

FILE *contratoC;

/*int localiza_contrato(FILE *contratoC, int codigo)
{
    int posicao = -1, achou = 0;

    contrato con;
    fseek(contratoC,0,SEEK_SET);
    fread(&con, sizeof(con),1, contratoC);

    while(!feof(contratoC) && !achou)
    {
        posicao++;

        if(con.codigo==codigo)
        {
            achou=1;
        }
        fread(&con, sizeof(con),1, contratoC);
    }

    if(achou)
        return posicao;
    else
        return -1;
}*/

void registra_contrato(int codigo_da_festa, int qtd_convidados, const char *dia_da_semana)
{
    contrato con;

    int posicao;

    con.valor_total = calcule_valorTotal(qtd_convidados, dia_da_semana);
    con.num_contrato = 1 + rand() % 130;

    con.codigo_da_festa = codigo_da_festa;

    fseek(contratoC, sizeof(con) * con.num_contrato, SEEK_SET);
    fwrite(&con, sizeof(con), 1, contratoC);
    fflush(contratoC);

    imprime_contratos(contratoC);
}

void imprime_contratos(FILE *contratoC)
{
    contrato con;

    fseek(contratoC, 0, SEEK_SET);
    fread(&con, sizeof(con), 1, contratoC);

    printf("\n%6s%7s%28s\n", "Numero do Contrato", "Codigo da Festa",
           "Valor total");

    while(!feof(contratoC))
    {
        if(con.num_contrato != 0)
        {
            printf("%-9d%-22d%12.2f\n",
                   con.num_contrato, con.codigo_da_festa, con.valor_total);
        }

        fread(&con, sizeof(con), 1, contratoC);
    }
    printf("\n");
}

float calcule_valorTotal(int qtd_convidados, const char *dia_da_semana)
{
    int i;
    float valor = 0.0;

    char *semana[] = {"segunda", "terca", "quarta", "quinta", "sexta", "sabado", "domingo"};

    int index;
    for(i = 0; i < 7; i++)
    {
        if(!strcmp(dia_da_semana, semana[i]))
        {
            index = i;
        }
    }

    int x = qtd_convidados <= 30 ? 30
            : qtd_convidados > 30 && qtd_convidados <= 50 ? 50
            : qtd_convidados > 50 && qtd_convidados <= 80 ? 80
            : qtd_convidados > 80 ? 100 : 0;

    switch(x)
    {
    case 30:
        if(index <= 3)
        {
            valor = 1899.00;
        }
        else
            valor = 2099.00;
        break;
    case 50:
        if(index <= 3)
        {
            valor = 2199.00;
        }
        else
            valor = 2299.00;
        break;
    case 80:
        if(index <= 3)
        {
            valor = 3199.00;
        }
        else
            valor = 3499.00;
        break;
    case 100:
        if(index <= 3)
        {
            valor = 3799.00;
        }
        else
            valor = 3999.00;
        break;
    }

    return valor;

}
#endif // CONTRATO_H_INCLUDED
