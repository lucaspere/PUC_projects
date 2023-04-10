const { extrairAtivos } = require("../utils/utils");

// Primeiro dia, Final
// Retorno Efetivo de um Ativo ( Rt )
const calRetEfetivo = (pC, pV, somD) =>
  Number(((pV + somD - pC) / pC).toPrecision(5));

const retEfetivoNoTempoT = []; // Tabela Hash para ser reaproveitado no cálculo de risco

// Retorno Esperado Retorno de um Ativo ( μ )
const calRetEsperado = (data) => {
  let somDividendo = 0;
  let somRetEfetivo = 0;

  for (let t = 0; t < data.length; t++) {
    somDividendo += data[t].dividendo;
    const retEfetivo = calRetEfetivo(
      data[0].preco, // Preço de compra
      data[t].preco, // Preço de venda no tempo t
      somDividendo // Somatório dos dividendos recebidos no tempo t
    );
    somRetEfetivo += retEfetivo;
    retEfetivoNoTempoT[t] = retEfetivo; // Salva o valor na tabela hash
  }

  const μ = somRetEfetivo / data.length; // Media Aritmética dos retornos efetivos
  return Number(μ.toPrecision(5));
};

// Risco de um Ativo ( σ )
const calRisco = (data, retEsperado) => {
  let 𝚺 = 0;

  for (let t = 0; t < data.length; t++) {
    𝚺 += Math.pow(retEfetivoNoTempoT[t] - retEsperado, 2);
  }

  const σ = Math.sqrt(𝚺 / (data.length - 1));
  return Number(σ.toPrecision(4));
};

// Retorno do Portfólio ( σc )
const calRetPortfolio = (portfolio) => {
  let μc = 0;
  const valorTotal = portfolio.reduce((soma, ativo) => soma + ativo.valor, 0);
  for (let i = 0; i < portfolio.length; i++) {
    μc += portfolio[i].retEsperado * (portfolio[i].valor / valorTotal);
  }

  return Number(μc.toPrecision(5));
};

// Risco do Portfólio ( σc )
const calRiscoPortfolio = (portfolio) => {
  let σc = 0;
  const valorTotal = portfolio.reduce((soma, ativo) => soma + ativo.valor, 0);
  for (let i = 0; i < portfolio.length; i++) {
    σc += portfolio[i].risco * (portfolio[i].valor / valorTotal);
  }

  return Number(σc.toPrecision(5));
};

// Calcula os ativos
const calAtivos = (ativos) => {
  return ativos.map((ativo) => {
    const retEsperado = calRetEsperado(ativo);
    const risco = calRisco(ativo, retEsperado);

    return {
      ativo: ativo[0].ativo,
      valor: ativo[ativo.length - 1].valor,
      retEsperado,
      risco,
    };
  });
};

// Somente formata o output dos dados
const cal_portfolio = (ativos) => {
  return {
    ativos: ativos.reduce((arv, str) => `${arv}_${str?.ativo || ''}`, ""),
    valorTotal: ativos.reduce((soma, ativo) => soma + ativo?.valor, 0),
    retorno: calRetPortfolio(ativos),
    risco: calRiscoPortfolio(ativos),
  };
};

module.exports = {
  calAtivos,
  calRetPortfolio,
  calRiscoPortfolio,
  cal_portfolio,
};
