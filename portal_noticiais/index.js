
let test = document.querySelector(".teste");
const buttonSearch = document.getElementById("search-button");
const inputSearch = document.getElementById("search-input");
const h1 = document.querySelector('h1');
const divTitle = document.getElementById('div-title');
const buttonSave = document.querySelector('#div-title button');
const searchUl = document.getElementById('search-ul')

let x = ''
const state = {
   inputValue: '',
   mainTitle: 'Principais Manchetes',
   buttonDisplay: 'none',
   count: 0
}

window.onload = () => {
   inputSearch.value = ''
   state.count = localStorage.length
   if (localStorage.length > 0) {
      for (let i = 1; i <= localStorage.length; i++) {
         x +=
            `
         <li class="nav-item">
         <button id="${i}" class="btn btn-primary"
            style="background: none; border: none; color: var(--primary); font-size: 22px"
            onclick="onClickHandler(i)">${localStorage.getItem(i.toString())}</button>
         </li>
         `
      }
      searchUl.innerHTML = x
   }
   const url = "https://newsapi.org/v2/top-headlines?country=br&apiKey=c8423062c93a4db7bfa845c323fa0fd3";
   fetchData(url, displayData);
}

buttonSave.onclick = () => {
   const result = window.prompt(`
      Texto de Pesquisa: ${state.inputValue}
      Título do Menu:
      `, state.inputValue)
   if (result) {
      localStorage.setItem((state.count += 1).toString(), result);
      searchUl.innerHTML += `
      <li class="nav-item">
         <button class="btn btn-primary"
            style="background: none; border: none; color: var(--primary); font-size: 22px"
            onclick="onClickHandler">${localStorage.getItem(state.count)}</button>
      </li>`
   }
}
inputSearch.onchange = (e) => {
   state.inputValue = e.target.value
}


buttonSearch.onclick = () => {
   const search = state.inputValue;
   const url = `https://newsapi.org/v2/everything?q=${search}&language=pt&apiKey=c8423062c93a4db7bfa845c323fa0fd3`;
   state.mainTitle = ` Pesquisa: ${search}`;
   state.buttonDisplay = 'unset';
   fetchData(url, displayData);
}

const fetchData = async (url, callback) => {

   fetch(url)
      .then(result => result.json())
      .then(data => callback(data));
}

const displayData = (data) => {
   text = '';
   h1.textContent = state.mainTitle
   buttonSave.style.display = state.buttonDisplay;
   data.articles.map(article => {
      text +=
         `
         <div class="container1">
            <div class="container-img">
               <img class="img-responsive"
               src="${article.urlToImage}">
            </div>
            <div class="container-body">
               <div class="container-titles">
                  <p class="title"><a href="${article.url}" class="text-primary" target="_blank">${article.title}</a></p>
                  <p class="info"><time datetime="2020-06-05T16:47:42Z">${new Date(article.publishedAt)}</time>- <strong> ${article.source.name}</strong></p>
               </div>
               <div class="container-text">
                  <p class="text">${article.content}</p>
               </div>
            </div>
         </div>
      `
   });

   test.innerHTML = text;
}