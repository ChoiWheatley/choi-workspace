/*
문제
대학생 새내기들의 90%는 자신이 반에서 평균은 넘는다고 생각한다. 
당신은 그들에게 슬픈 진실을 알려줘야 한다.

입력
첫째 줄에는 테스트 케이스의 개수 C가 주어진다.

둘째 줄부터 각 테스트 케이스마다 학생의 수 N(1 ≤ N ≤ 1000, N은 정수)이 
첫 수로 주어지고, 이어서 N명의 점수가 주어진다. 점수는 0보다 크거나 같고, 
100보다 작거나 같은 정수이다.

출력
각 케이스마다 한 줄씩 평균을 넘는 학생들의 비율을 반올림하여 
소수점 셋째 자리까지 출력한다.

예제 입력 1 
5
5 50 50 70 80 100
7 100 95 90 80 70 60 50
3 70 90 80
3 70 90 81
9 100 99 98 97 96 95 94 93 91
예제 출력 1 
40.000%
57.143%
33.333%
66.667%
55.556%
*/

var input = [];
var rl = require("readline");
var r = rl.createInterface({
    input: process.stdin,
    output: process.stdout
});
r.on("line", function(line){
    if (line === "exit") { r.close(); }
    input.push(line);
});
r.on("close", function(){
    var caseCount = Number(input[0]);
    for (var i = 1; i <= caseCount; i++){
        var str, num, avr, cnt;
        var rec = [];
        avr = 0;
        cnt = 0;
        str = input[i].split(" ");
        num = str[0];
        //평균을 먼저 구한다
        for (var j = 1; j < str.length; j++){
            //console.log(str[j]);
            avr += Number(str[j]);
        }
        avr /= num;
        //console.log("avr = " + avr.toFixed(3)); //toFixed(n)은 실수의 소수점 자리를 반올림해준다.
        //평균 이상인 값의 개수를 구한다
        str.forEach(student => { if(Number(student) > avr) { cnt++; }});
        console.log((Math.round(cnt / num * 100 * 1000) / 1000).toFixed(3) + "%\n");
    }
    
    process.exit();
});