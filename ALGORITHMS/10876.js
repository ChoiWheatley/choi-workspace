/*
입력
첫 번째 줄에 테스트 케이스의 수 T (1 ≤ T ≤ 10^5)가 주어진다. 
이후 T 개의 테스트 케이스가 주어진다.

각 테스트 케이스는 한 줄로 구성되며, 
이 줄에는 A와 B (1 ≤ A ≤ B ≤ 10^18)가 공백을 사이로 두고 입력된다. 
이는 지학이가 A 이상 B 이하의 자연수들로 구성된 사전을 만들었음을 의미한다.

출력
각 테스트 케이스에 대해, 
수찬이가 읽어야 할 최소 페이지 수를 한 줄에 하나씩 출력한다.

예제 입력 1 
3
1 11
5 13
3 5
예제 출력 1 
4
5
3

힌트
각 테스트 케이스마다 사전을 앞에서부터 
차례로 읽어나가면 아래와 같다.
#1: 1, 10, 11, 2, 3, 4, 5, 6, 7, 8, 9
#2: 10, 11, 12, 13, 5, 6, 7, 8, 9
#3: 3, 4, 5
*/

let input = [];
let readline = require("readline");
let r = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});
r.on("line", function (line) {
  if (line === "exit") {
    r.close();
  }
  input.push(line);
});
r.on("close", function () {
  let t, a, b;
  let an, bn; //a와 b의 자릿수
  let out;
  t = input.shift();
  for (let i = 0; i < t; i++) {
    let tmpInput = input.shift().split(" ");
    a = tmpInput[0];
    b = tmpInput[1];
    an = a.length;
    bn = b.length;
    out = 0;

    a = Number(a);
    b = Number(b);
    if (an === bn) {
      out = b - a + 1;
    } else if (an < bn) {
      if (a * 10 ** (bn - an) <= b) {
        //a가 b보다 먼저 밝혀지는 경우
        out = Math.floor(b / 10 ** (bn - an)) - a + 1;
        for (let n = 1; n <= bn - an; n++) {
          out += Math.floor(b / (10 ** (bn - (an + n)))) - (10 ** (an + n - 1));
        }
        out += bn - an + 1;
      } else {
        //b가 a보다 먼저 밝혀지는 경우
        for (let n = 1; n <= bn - an; n++) {
          out += Math.floor(b / (10 ** (bn - (an + n)))) - (10 ** (an + n - 1));
        }
        out += bn - an + 1;
      }
    }
    console.log(out);
  }

  process.exit();
});
