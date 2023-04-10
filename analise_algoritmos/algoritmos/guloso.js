const { cal_portfolio } = require("../lib/calculos");

const guloso = (data, tamPort) => {
  let proximo = 0;
  const random = Math.floor(Math.random() * data.length);
  const portfolio = {
    ativos: [data[random]], // Inicia numa posição aleatória
  };
  data[random].visitado = true;
  for (let i = 0; portfolio.ativos.length < tamPort; i++) {
    // Vai filtrar os ativos que ainda não foram usados (Não visitados)
    const ativosNaoVisitados = data.filter((ativo) => !ativo.visitado);
    // Vai guardar o melhor local no loop
    const ativos = [data[proximo], ativosNaoVisitados[0]];
    const melhorLocal = {      ...cal_portfolio(ativos),      ativos,
    };

    // Um loop em todos os ativos que ainda falta visitar
    for (let j = 1; j < ativosNaoVisitados.length; j++) {
      const aux = cal_portfolio([data[proximo], ativosNaoVisitados[j]]);

      if (eh_melhor(aux, melhorLocal) && !data[j].visitado) {
        // Se achou um melhor, vai remover ele e vai adicionar outro melhor
        melhorLocal.ativos.pop();
        melhorLocal.ativos.push(data[j]);
      }
    }

    // Vai adicionar um ativo escolhido no portfolio
    portfolio.ativos.push(melhorLocal.ativos[1]);

    // Busca a posição do ativo no array e seta como visitado
    data.forEach((ativo, idx) => {
      if (ativo.ativo === melhorLocal.ativos[1].ativo) {
        data[idx].visitado = true;
        proximo = idx;
      }
    });
  }

  return cal_portfolio(portfolio.ativos);
};

// O cálculo q fiz pra otimizar é (retornoEfetivo + risco) * valorTotal entre dois ativos
const eh_melhor = (ativo1, ativo2) =>
  (ativo1.retorno + ativo1.risco) * ativo1.valorTotal >=
  (ativo2.retorno + ativo2.risco) * ativo2.valorTotal;

module.exports = {
  guloso,
};
