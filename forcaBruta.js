const { calRiscoPortfolio, calRetPortfolio } = require("./calculos");

const forcaBruta = (ativos) => {
  const auxAtivo = [ativos[0]];
  const portfolio = {
    riscoMaximo: 5,
    retorno: calRetPortfolio(auxAtivo),
    risco: calRiscoPortfolio(auxAtivo),
    carteira: auxAtivo,
  };

  for (let i = 1; i < ativos.length; i++) {
    const auxAtivos = [ativos[i]];
    const auxPortfolio = {
      retorno: calRetPortfolio(auxAtivos),
      risco: calRiscoPortfolio(auxAtivos),
      carteira: auxAtivos,
    };

    for (j = i + 1; j < ativos.length; j++) {
      const tempAtivos = auxPortfolio.carteira.concat(ativos[j]);
      const retPortfolio = calRetPortfolio(tempAtivos);
      const riscoPortfolio = calRiscoPortfolio(tempAtivos);
      if (
        retPortfolio > auxPortfolio.retorno &&
        riscoPortfolio < portfolio.riscoMaximo
      ) {
        auxPortfolio.retorno = retPortfolio;
        auxPortfolio.risco = riscoPortfolio;
        auxPortfolio.carteira.push(ativos[j]);
      }
    }

    if (
      auxPortfolio.risco <= portfolio.riscoMaximo &&
      auxPortfolio.retorno > portfolio.retorno
    ) {
      portfolio.carteira = auxPortfolio.carteira;
      portfolio.retorno = auxPortfolio.retorno;
      portfolio.risco = auxPortfolio.risco;
    }
  }

  return portfolio;
};

module.exports = {
  forcaBruta,
};
