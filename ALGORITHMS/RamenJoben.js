/*
N개의 물품을 M원에 맞춰 구매하고자 한다.
x축을 물품들, y축을 누적 가격이라고 친다면 가장 이상적인 결과는
선형적으로 상승하는 그래프여야 한다.
물론 완벽하게 선형적일 수는 없기 때문에 각 x값에 따른 이상적인
preferQnt를 정하고 거기에서부터 앞,뒤로 탐색을 시작할 생각이다.
모든 경우의 수를 따질 생각은 전혀 없고 대신 max의 20퍼센트 정도만 탐색할
생각이다.

필요한 변수들은 다음과 같을 것이다. (OOP 개념은 안쓸 예정)
- fnlPrc : 최종가격
- rmPrc : 나머지가격 (iteration 도중 0 이하면 바로 break;)
- prc[] : 물품별 가격들
- max[] : 각 물품별 최대 숫자 floor(fnlPrc / prc[])
- preferQnt[] : 사전에 정의하면 그 값을 기준으로 탐색하고
아니면 floor(max[] / 2)의 값을 할당할 예정
- sample : preferQnt[]로부터 탐색하는 지점
- sampleTable[][] : 모든 종류의 가격들의 sample들을 모은 이차원 배열
- sampleScope : 20퍼센트만을 탐색할 것인지 N%만을 탐색할 것인지 나중에 변경하기
쉽게 하려고 만든 변수
- watcher[] : 0 ~ sampleTable[].length까지의 값을 가진다. 
sampleTable[][]의 위치를 파악하려고 삽입

예시 입력
5 50000 
3600 3 
5200 0
3870 7
2480 0
360 130

*/

var sampleScope = 30;
var input = [];
var rl = require("readline");
var r = rl.createInterface({
    input: process.stdin,
    output: process.stdout
});
r.on("line", line => {
    if (line === "exit") { r.close(); }
    input.push(line);
});
r.on("close", function(){
    var n = input[0].split(" ")[0];
    var fnlPrc = input[0].split(" ")[1];
    var prc = new Array(n);
    var max = new Array(n);
    var preferQnt = new Array(n);
    var sampleTable = new Array(n);
    var watcher = new Array(n);

    //입력
    for (var i = 0; i < n; i++){ 
        var tmpstr = input[i+1].split(" "); 
        prc[i] = tmpstr[0];
        preferQnt[i] = tmpstr[1];
        max[i] = Math.floor(fnlPrc / prc[i]);
        if (preferQnt[i] === "0"){ preferQnt[i] = Math.floor(max[i] / 2); }
        //debug
        console.log(`max[${i}] = ${max[i]} /// preferQnt[${i}] = ${preferQnt[i]}`);
        
        //sampleTable[][]에 샘플가격들을 입력
        //범위 : preferQnt-(대충20%) ~ perferQnt+(대충20%)
        var zigzag = -1;
        var scope = Math.floor(max[i] * sampleScope / 100);
        //console.log(`scope = ${scope}`);
        sampleTable[i] = new Array(2 * scope);
        var tmpQnt = preferQnt[i];
        if (preferQnt[i] < scope) { tmpQnt = scope; }
        if (preferQnt[i] + scope > max[i]) { tmpQnt = max[i] - scope + 1; }
        for (var j = 0; j < 2 * scope; j++){
            sampleTable[i][j] = prc[i] * (tmpQnt + Math.round(j / 2) * zigzag);
            zigzag *= -1;
            //debug
            console.log(`sampleTable[${i}][${j}] = *${tmpQnt + Math.round(j / 2) * zigzag} = ${sampleTable[i][j]}`);
        }
    }
    
    //탐색 (brute force)
    //어차피 sampleTable에서 잘 섞어놨으니 순서대로 접근하면 된다.
    for (var i = 0; i < n; i++){ watcher[i] = 0; }
    while (watcher[0] <= sampleTable[0].length){
        
    }




    
    
    process.exit();
});