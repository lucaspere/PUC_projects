#ifndef CONTRATO_H_INCLUDED
#define CONTRATO_H_INCLUDED

#include <string.h>

// !strcmp(con.status, "Pendente")

struct Contrato
{
    int codigo_da_festa, num_contrato;
    float valor_total, desconto, valor_final;
    char forma_de_pagamento[10];
    char status[10];
};

typedef struct Contrato contrato;

float calcule_valorTotal(int qtd_convidados, const char *dia_da_semana);
void imprime_contratos(FILE *contratoC);
float calcule_valorFinal(int, float, float *);

FILE *contratoC;

int localiza_contrato(int codigo)
{
    int posicao = -1, achou = 0;

    contrato con;
    fseek(contratoC,0,SEEK_SET);
    fread(&con, sizeof(con),1, contratoC);

    while(!feof(contratoC) && !achou)
    {
        posicao++;

        if(con.num_contrato==codigo)
        {
            achou=1;
        }
        fread(&con, sizeof(con),1, contratoC);
    }

    if(achou)
        return posicao;
    else
        return -1;
}

void registra_contrato(int codigo_da_festa, int qtd_convidados, const char *dia_da_semana)
{
    contrato con;

    int posicao;

    con.valor_total = calcule_valorTotal(qtd_convidados, dia_da_semana);
    con.num_contrato = 1 + rand() % 130;
    con.desconto = 0.0;
    con.valor_final = 0.0;
    con.codigo_da_festa = codigo_da_festa;
    strcpy(con.status, "Pendente");

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

    printf("\n%-11s%-8s%-14s%-14s%-14s%-s\n", "Contrato", "Festa",
           "Valor total", "Desconto", "Valor Final", "Status");

    while(!feof(contratoC))
    {
        if(con.num_contrato != 0)
        {
        printf("%-11d%-8d%-14.2f%-14.2f%-14.2f%-s\n",
               con.num_contrato, con.codigo_da_festa,
               con.valor_total, con.desconto, con.valor_final, con.status);
        }

        fread(&con, sizeof(con), 1, contratoC);
    }
    printf("\n");
}

void pagar_contrato()
{
    contrato con;
    int posicao, pagamento_escolha, codigo;
    float desconto, resultado_valorFinal;

    printf("Digite o código do contrato que deseja pagar: ");
    scanf("%d", &codigo);

    posicao = localiza_contrato(codigo);

    if(posicao != 1)
    {
        fseek(contratoC, sizeof(con) * posicao, SEEK_SET);
        fread(&con, sizeof(con), 1, contratoC);

        printf("Escolha a forma de pagamento:\n"
               "1 -> A Vista: 10% desconto\n"
               "2 -> Duas vezes: 5%\n"
               "3 -> Três vezes: 2%\n"
               "4 -> Quatro ou mais: sem desconto");
        scanf("%d", &pagamento_escolha);

        resultado_valorFinal = calcule_valorFinal(pagamento_escolha, con.valor_total, &desconto);

        con.valor_final = resultado_valorFinal;
        con.desconto = desconto;
        strcpy(con.status, "Pago");

        fseek(contratoC, sizeof(con) * posicao, SEEK_SET);
        fwrite(&con, sizeof(con), 1, contratoC);
        fflush(contratoC);
    }
    else
        printf("Contrato não localizado\n");
}

float calcule_valorFinal(int escolha, float valorTotal, float *desconto)
{

    float valor_final;

    switch(escolha)
    {
    case 1:
        valor_final = valorTotal * (float) 90 / 100;
        *desconto = valorTotal * (float) 10 / 100;
        break;
    case 2:
        valor_final = valorTotal * (float) 95 / 100;
        *desconto = valorTotal * (float) 5 / 100;
        break;
    case 3:
        valor_final = valorTotal * (float) 98 / 100;
        *desconto = valorTotal * (float) 2 / 100;
        break;
    case 4:
        valor_final = valorTotal * (float) 90 / 100;
        break;
    }

    return valor_final;
}

float calcule_valorTotal(int qtd_convidados, const char *dia_da_semana)
{
    int i;
    float valor = 0.0;

    char *semana[] = {"segunda-feira", "terca-feira", "quarta-feira", "quinta-feira", "sexta-feira", "sabado", "domingo"};

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
