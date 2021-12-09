const extrairValores = (ativo) => {
  const pC = Number(ativo[3]);
  const pV = Number(ativo[2]);
  const div = Number(ativo[4]);

  return [pC, pV, div];
};

const extrairAtivos = (data) => {
  const ativos = {};
  for (let i = 0; i < data.length; i++) {
    const ativo = data[i].split(",");
    if (ativos[ativo[0]]) ativos[ativo[0]].push(ativo);
    else if (ativo[0].match(/[a-zA-Z]/g)) ativos[ativo[0]] = [];
  }

  return ativos;
};

const calMedia = (val1, val2) => Number(((val1, val2) / 2).toPrecision(5))

module.exports = {
  extrairAtivos,
  extrairValores,
  calMedia
};
