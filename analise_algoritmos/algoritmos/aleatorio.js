const {
  cal_portfolio,
} = require("../lib/calculos");

const aleatorio = (ativos, tamPort) => {
  const portfolio = {
    valorTotal: 0,
    retorno: 0,
    risco: 0,
    ativos: [],
  };

  while (portfolio.ativos.length < tamPort) {
    const random = Math.floor(Math.random() * ativos.length);
    if (!ativos[random].visited) {
      ativos[random].visited = true;
      portfolio.ativos.push(ativos[random]);
    }
  }

  return cal_portfolio(portfolio.ativos);
};

module.exports = {
  aleatorio,
};
