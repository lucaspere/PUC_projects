const fs = require("fs");

const getDadosFromFile = (path) => {
  const dados = fs.readFileSync(path, { encoding: "utf8" }).split("\n");
  dados.shift();
  !dados[dados.length - 1] && dados.pop;

  return dados;
};

module.exports = {
  getDadosFromFile,
};
