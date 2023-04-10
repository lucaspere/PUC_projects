const extrairValores = (ativo) => ({
  ativo: ativo[0],
  data: ativo[1],
  preco: Number(ativo[2]),
  valor: Number(ativo[3]),
  dividendo: Number(ativo[4]),
});

// Somente vai formatar os dados como se fosse uma biblioteca
const extrairAtivos = (data) => {
  const ativos = {};
  for (let i = 0; i < data.length; i++) {
    const ativo = data[i].split(",");
    const ativoObj = extrairValores(ativo);

    if (ativos[ativo[0]]) ativos[ativo[0]].push(ativoObj);
    else if (ativo[0].match(/[a-zA-Z]/g)) ativos[ativo[0]] = [ativoObj];
  }

  return ativos;
};

const calMedia = (val1, val2) => Number(((val1, val2) / 2).toPrecision(5));

module.exports = {
  extrairAtivos,
  extrairValores,
  calMedia,
};
