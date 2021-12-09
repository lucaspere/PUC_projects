const { extrairAtivos, extrairValores } = require("./utils");

// Retorno Efetivo de um Ativo ( Rt )
const calRetEfetivo = (pC, pV, somD) =>
  Number(((pV + somD - pC) / pC).toPrecision(5));

// Retorno Esperado Retorno de um Ativo ( μ )
const calRetEsperado = (data) => {
  let Σ = 0;
  for (let t = 0; t < data.length; t++) {
    const [pC, pV, div] = extrairValores(data[t]);
    Σ += calRetEfetivo(pC, pV, div);
  }

  const μ = Σ / data.length;
  return Number(μ.toPrecision(5));
};

// Risco de um Ativo ( σ )
const calRisco = (data, retEsperado) => {
  let 𝚺 = 0;

  for (let i = 0; i < data.length; i++) {
    const [pC, pV, div] = extrairValores(data[i]);
    const retornoEfetivo = calRetEfetivo(pC, pV, div);

    𝚺 += Math.pow(retornoEfetivo - retEsperado, 2);
  }

  const σ = Math.sqrt(𝚺 / (data.length - 1));
  return Number(σ.toPrecision(4));
};

// Retorno do Portfólio ( σc )
const calRetPortfolio = (portfolio) => {
  let μc = 0;

  for (let i = 0; i < portfolio.length; i++) {
    μc += portfolio[i].retEsperado * (portfolio[i].qtd / portfolio.length)
  }

  return Number(μc.toPrecision(5));
};

// Risco do Portfólio ( σc )
const calRiscoPortfolio = (portfolio) => {
  let σc = 0;

  for (let i = 0; i < portfolio.length; i++) {
    σc += portfolio[i].risco * (portfolio[i].qtd / portfolio.length)
  }

  return Number(σc.toPrecision(5));
};

// Calcula os ativos
const calAtivos = (data) => {
  const ativos = Object.values(extrairAtivos(data));

  return ativos.map((ativo) => {
    const retEsperado = calRetEsperado(ativo);
    const risco = calRisco(ativo, retEsperado);

    return {
      ativo: ativo[0][0],
      qtd: ativo.length,
      retEsperado,
      risco,
    };
  });
};

module.exports = {
  calAtivos,
  calRetPortfolio,
  calRiscoPortfolio
};
