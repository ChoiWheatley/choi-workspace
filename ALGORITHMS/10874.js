/*
10874 : 이교수님의 시험
입력
첫 번째 줄은 시험을 본 학생수를 나타내는 정수 N이 주어진다.(1 ≤ N ≤ 100)
N번째 줄까지는 1에서 5사이에 해당하는 정수 열개가 주어진다. i번째 줄의 j번째 수는 i번째 학생이 고른 j번째 문제의 답을 의미한다. (1 ≤ i ≤ N, 1 ≤ j ≤ 10)
한줄에 입력되는 수들은 공백으로 구분된다.

출력
재시험을 보아야하는 학생의 목록을 오름차순으로 출력한다.
각 학생의 번호는 한줄에 하나씩 출력한다.

예제 입력 1 
5
1 1 1 1 1 1 1 1 1 1
1 2 3 4 5 1 2 3 4 5
3 2 2 1 5 1 2 2 2 2
1 2 3 4 5 1 2 3 4 5
1 2 3 4 5 1 2 3 4 5
예제 출력 1 
2
4
5
*/
let answer = ["1","2","3","4","5","1","2","3","4","5"];
var input = [];
var readline = require("readline");
var r = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
r.on("line", function(line){
    if (line === "exit") { r.close(); }
    input.push(line);
});
r.on("close", function(){
    let n = input[0];
    let student = [n];
    for (let i = 1; i <=n; i++){
        student[i-1] = input[i].split(" ");
    }
    
    for (let i = 0; i < n; i++){
        let flag = true;
        for (let j = 0; j < 5; j++){
            if (student[i][j] !== answer[j]) {
                flag = false;
                break;
            }
        }
        if (flag) { console.log(i+1); }
    }
    
    
    
    process.exit();
});