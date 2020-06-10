const form = document.querySelector('form');
const tableHead = document.querySelector('thead');
const tableBody = document.querySelector('tbody');
const tubeMix = document.querySelector('input[name=tubeMix]');
const inputTableTitle = document.querySelector("#inputTableTitle");
const buttonAmostra = document.querySelector('#amostra');
const captionTable = document.querySelector("#captionTable");


let check = 0;
if (check) {
   tubeMix.setAttribute('disabled', true);
}

form.onsubmit = (e) => {
   e.preventDefault();

   const inputs = document.querySelectorAll('input[type=text]');
   const tr = document.createElement('tr');

   inputs.forEach(data => {
      const td = document.createElement('td');
      td.textContent = data.name === "tubeMix" ? '' : data.value;
      tr.appendChild(td);
      data.value = '';
   })

   tableBody.appendChild(tr)
}


function handleSubmit(e) {
   e.preventDefault();


}

buttonAmostra.onclick = function () {

   const tubeMixValue = Number.parseInt(tubeMix.value);
   const inputs = document.querySelectorAll('form input[type=text]');

   captionTable.textContent = inputTableTitle.value;

   for (let i = 0; i < tubeMixValue; i++) {
      const tr = document.createElement('tr');
      for (let j = 0; j < inputs.length; j++) {
         const td = document.createElement('td');
         tr.appendChild(td)
      }
      tableBody.appendChild(tr);
   }

   tubeMix.value = '';
   tubeMix.value = '';
   inputTableTitle.setAttribute('disabled', true);
   inputTableTitle.setAttribute('disabled', true);
}