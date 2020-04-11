//백준 온라인
// node.js의 인풋과 아웃풋을 연습한다.
/*
두 정수 A와 B를 입력받은 다음, A+B를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 A와 B가 주어진다. (0 < A, B < 10)

출력
첫째 줄에 A+B를 출력한다.

예제 입력 1 
1 2
예제 출력 1 
3
*/
//어쩔 수 없지만... 변수 선언은 여기에다가 해야 한다... 
var a, b, c;
var readline = require("readline");
var lines = [];

var r = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
r.on("line", function(line){
    if (line === "exit"){
        r.close();
    }
    // 이제 lines에서 원하는 정보를 가져오면 된다.
    lines.push(line);

    //여기부터 원하는 알고리즘을 작성해보자
    a = Number(lines[0].split(" ")[0]);
    b = Number(lines[0].split(" ")[1]);
    c = a + b;
    
});
r.on("close", function(){
    // 이 아리에 출력값을 console.log() 
    //하는 식으로 넣으면 된다.
    console.log(c);
    process.exit;
});

