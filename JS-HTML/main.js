const displayedImage = document.querySelector('.displayed-img');
const thumbBar = document.querySelector('.thumb-bar');

const btn = document.querySelector('button');
const overlay = document.querySelector('.overlay');

/* Looping through images */

const newImages = new Array(6); //[0]은 안쓸거야
for (let i = 1; i <= 5; i++) {
    newImages[i] = document.createElement("img");
    newImages[i].setAttribute('src', `images/pic${i}.jpg`);
    newImages[i].setAttribute('id', i);
    thumbBar.appendChild(newImages[i]);
}

//thumb-bar에 이벤트핸들러 부착하기
thumbBar.addEventListener("click", e => {
    //참고로 e.target.id는 무조건 String을 반환한다.
    switch (Number(e.target.id)) {
        case 1:
            displayedImage.setAttribute("src", "images/pic1.jpg");
            break;
        case 2:
            displayedImage.setAttribute("src", "images/pic2.jpg");
            break;
        case 3:
            displayedImage.setAttribute("src", "images/pic3.jpg");
            break;
        case 4:
            displayedImage.setAttribute("src", "images/pic4.jpg");
            break;
        case 5:
            displayedImage.setAttribute("src", "images/pic5.jpg");
            break;
    };
});


/* Wiring up the Darken/Lighten button */
btn.addEventListener("click", e => {
    if (e.target.getAttribute("class") === "dark") {
        e.target.setAttribute("class", "light");
        e.target.textContent = "Lighten";

        overlay.style.backgroundColor = "rgba(0,0,0,0.5)";
    } else if (e.target.getAttribute("class") === "light"){
        e.target.setAttribute("class", "dark"); 
        e.target.textContent = "Darken"
        overlay.style.backgroundColor = "rgba(0,0,0,0)";
    }
});