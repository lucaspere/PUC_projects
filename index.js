const body = document.querySelector('body');
const form = document.querySelector('form');
const tableHead = document.querySelector('thead');
const tableBody = document.querySelector('tbody');
const tubeMix = document.querySelector('input[name=tubeMix]');
const inputTableTitle = document.querySelector("#inputTableTitle");
const buttonSample = document.querySelector('#amostra');
const captionTable = document.querySelector("#captionTable");
const inputs = document.querySelectorAll('form input[type=text]');
const select = document.querySelector('select');

let count = 0;

select.onchange = onchangeHandler;
body.onload = defaultValues;
form.onsubmit = onsubmitHandler;
buttonSample.onclick = onclickHandler;


function onsubmitHandler(e) {
   e.preventDefault();
   let product = 1;
   const tableRows = document.querySelectorAll('tbody tr');
   for (let i = 0; i < tableRows[count].childNodes.length; i++) {
      if(i > 2) {
         let stringWithoutComma = inputs[i].value.replace(',', '.');
         product *= i !== 4 ? Number.parseFloat(stringWithoutComma) : (Number.parseFloat(stringWithoutComma) + 2);
      }
      tableRows[count].childNodes[i].textContent = i !== 4 ? inputs[i].value
      : tableRows[count].childNodes[0].textContent.toUpperCase() === 'DNA' ? 'NÃO SE COLOCA NO MIX'
      : product;
      
      inputs[i].value = '';
   }
   count++;
   select.value = "";
}

function onclickHandler() {
   const tubeMixValue = Number.parseInt(tubeMix.value);

   captionTable.textContent = inputTableTitle.value;

   for (let i = 0; i < tubeMixValue; i++) {
      const tr = document.createElement('tr');
      for (let j = 0; j < inputs.length; j++) {
         const td = document.createElement('td');
         tr.appendChild(td)
      }
      tableBody.appendChild(tr);
   }

   inputTableTitle.value = '';
   inputTableTitle.setAttribute('disabled', true);

   tubeMix.value = '';
   tubeMix.setAttribute('disabled', true);
   buttonSample.setAttribute('disabled', true);

   form.style.display = "initial";
}

function defaultValues() {
   for (let i = 0; i < inputs.length; i++) {
      inputs[i].value = '';
   }
   select.value = "";
   form.style.display = "none";
   count = 0;
}

function onchangeHandler(e) {
   inputs[0].value = e.target.value;
}