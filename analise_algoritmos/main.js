const path = require("path");
const { aleatorio } = require("./algoritmos/aleatorio");
const { calAtivos } = require("./lib/calculos");
const { getDadosFromFile } = require("./config");
const { forcaBruta } = require("./algoritmos/forcaBruta");
const { guloso } = require("./algoritmos/guloso");
const { extrairAtivos } = require("./utils/utils");
const { inspect } = require("util");

function main() {
  const arg = process.argv[3];
  const tamPort = Number(process.argv[2]);
  if (!arg)
    console.log("Especifique o arquivo de dados, como: node main.js [path]");
  else {
    const dados = getDadosFromFile(path.resolve(arg));
    const ativos = Object.values(extrairAtivos(dados));

    if (tamPort < 2 || tamPort > ativos.length)
      console.log(
        "Tamanho do portfolio tem que ser maior que 1 e menor que a quantidade de ativos"
      );
    else {
      const portfolio = calAtivos(ativos);
      console.log("Algoritmo Guloso: " + inspect(guloso(portfolio, tamPort)));
      console.log(
        "Algoritmo Aleatorio: " + inspect(aleatorio(portfolio, tamPort))
      );
    }
  }
}

main();
