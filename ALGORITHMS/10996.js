/*
문제
예제를 보고 규칙을 유추한 뒤에 별을 찍어 보세요.

입력
첫째 줄에 N(1 ≤ N ≤ 100)이 주어진다.

출력
첫째 줄부터 차례대로 별을 출력한다.

예제 입력 1 
1
예제 출력 1 
*
예제 입력 2 
2
예제 출력 2 
*
 *
*
 *
예제 입력 3 
3
예제 출력 3 
* *
 *
* *
 *
* *
 *
예제 입력 4 
4
예제 출력 4 
* *
 * *
* *
 * *
* *
 * *
* *
 * *
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
    var n = Number(input[0]);
    var fstln, scnln;
    var outln = "";
    fstln = Math.ceil(n / 2);
    scnln = Math.floor(n / 2);
    for (var i = 0; i < n; i++){
        for (var j = 0; j < fstln; j++){ outln += "* "; }
        outln += "\n";
        for (var j = 0; j < scnln; j++){ outln += " *"; }
        outln += "\n";
    }
    console.log(outln);
    

    process.exit();
}); 