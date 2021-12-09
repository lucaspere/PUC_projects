const path = require("path");
const { calAtivos } = require("./calculos");
const { getDadosFromFile } = require("./config");
const { forcaBruta } = require("./forcaBruta");

function main() {
  const arg = process.argv[2];

  if (!arg)
    console.log("Especifique o arquivo de dados, como: node main.js [path]");
  else {
    const dados = getDadosFromFile(path.resolve(arg));
    const portfolio = calAtivos(dados);
    console.log(forcaBruta(portfolio));
  }
}

main();
