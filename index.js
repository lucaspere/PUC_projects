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

select.onchange = function(e) {
   inputs[0].value = e.target.value;
}
let count = 0;

body.onload = function () {
   form.style.display = "none";
   count = 0;
}

form.onsubmit = onsubmitHandler;
buttonSample.onclick = onclickHandler;


function onsubmitHandler(e) {
   e.preventDefault();

   const tableRows = document.querySelectorAll('tbody tr');
   for(let i = 0; i < tableRows[count].childNodes.length; i++) {
      tableRows[count].childNodes[i].textContent = inputs[i].value;
      inputs[i].value = '';
   }

   count++;
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