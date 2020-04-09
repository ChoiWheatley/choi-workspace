//라면 조변 신청 알고리즘.
//인풋 아웃풋은 node.js로 대체할 예정
//<나중에> node.js의 IO 개념 획득하기 
// 일단은 html에다가 뿌리는 걸로..
//2. 4개의 상품을 분배해서 최종금액 만들기
//3. VBA의 오브젝트 개념을 공부하기
//4. N개의 상품을 분배해서 최종금액 만들기


var fnlPrc, rmn, sum;
var kind = {
    price: 0,
    max: 0
};
var kinds = new Array(kind, 4);

//나중에는 프롬프트로, 혹은 웹 양식으로 받을 예정
fnlPrc = 25000;
rmn = fnlPrc;
kinds[0].price = 3500;
kinds[1].price = 2400;
kinds[2].price = 1500;
kinds[3].price = 350;

kinds[0].max = Math.floor(fnlPrc / kinds[0].price);

function trace(idx, max){
    for (var i = max; i > 0; i--){
        rmn = rmn - kinds[idx].price * i;
        if (rmn > kinds[idx + 1].price){
            kinds[idx + 1].max = Math.floor(rmn / kinds[idx + 1].price);
        }
    }
}