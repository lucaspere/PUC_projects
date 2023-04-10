let test = document.querySelector(".teste");

let text = '';

window.onload = function () {
   fetch("https://newsapi.org/v2/top-headlines?sources=cbs-news&apiKey=c8423062c93a4db7bfa845c323fa0fd3")
      .then(res => res.json())
      .then((data) => {
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

      })
}