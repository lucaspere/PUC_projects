
$(document).ready(function () {

   let text = '';

   window.onload = function () {
      fetch("https://newsapi.org/v2/top-headlines?country=br&apiKey=c8423062c93a4db7bfa845c323fa0fd3")
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
                        <p class="title">${article.title}</p>
                        <p class="info"><time datetime="2020-06-05T16:47:42Z">${new Date(article.publishedAt)}</time>- Fonte:<strong>${article.source.name}</strong></p>
                     </div>
                     <div class="container-text">
                        <p class="text">${article.content}</p>
                     </div>
                  </div>
               </div>
            `
            });

            $(".teste").html(text);

         })
   }
});