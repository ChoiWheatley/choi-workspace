/*
10875: 뱀
입력
첫 번째 줄에 정수 L(1 ≤ L ≤ 10.0e+8)이 주어진다. 
두 번째 줄에는 머리의 방향을 몇 번 회전할 것인지를 나타내는 
정수 N(0 ≤ N ≤ 10.0e+3)이 주어진다. 
다음 N 개의 줄에 뱀이 머리를 어떻게 회전하는지에 대한 정보가 주어진다. 
i(1 ≤ i ≤ N)번째 줄에 정수 ti(1 ≤ ti ≤ 20.0e+8)와 diri 가 차례로 주어지며 
diri 는 문자 L, 또는 R 중 하나이다. 
뱀은 i = 1인 경우 출발, 그 외의 경우엔 i − 1번째 회전으로부터 ti 초 후에 
diri 의 방향으로 머리를 회전하며, 
만일 diri 가 L 이라면 왼쪽 (반시계방향)으로, R 이라면 오른쪽 (시계방향)으로 90도 회전한다.

출력
첫 번째 줄에 답을 나타내는 값을 하나 출력한다. 이 값은 뱀이 출발한지 
몇 초 후에 숨을 거두는지를 나타낸다.

예제 입력 1 
3
4
2 L
2 L
1 L
5 R

예제 출력 1 
7
예제 입력 2 
3
3
2 L
4 L
4 R
예제 출력 2 
6
예제3
100000000
5
100000000 L
100000000 L
200000000 L
199999999 L
199999999 L
출력3
899999997
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
  const UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4;
  let l,
    n,
    t = new Array(n),
    dir = new Array(n);
  let head, tail;
  let die = false;
  class Snake {
    constructor(x, y, dir) {
      this.x = x;
      this.y = y;
      this.dir = dir; // 1=Up, 2=Right, 3=Down, 4=Left
    }
    turn(dir) {
      if (dir === "L") {
        if (--this.dir < 1) {
          this.dir = 4;
        }
      } else if (dir === "R") {
        if (++this.dir > 4) {
          this.dir = 1;
        }
      }
    }
    moveForward(n) {
      switch (this.dir) {
        case UP:
          this.y += n;
          break;

        case RIGHT:
          this.x += n;
          break;

        case DOWN:
          this.y -= n;
          break;

        case LEFT:
          this.x -= n;
          break;
      }
    }
  }
  //input
  l = Number(input[0]);
  n = Number(input[1]);
  for (let i = 0; i < n; i++) {
    let tmp = input[i + 2].split(" ");
    t[i] = Number(tmp[0]);
    dir[i] = tmp[1];
  }
  //
  head = new Snake(0, 0, RIGHT);
  tail = new Array(); //tail에 모든 경로를 집어넣지 말고 꺾인점만 넣는다.
  let i = 0; //뱀의 생존시간
  let ti = t.shift(); //다음 회전까지 남은 시간

  //debug
  let flag = 7;
  while (!die) {
    //head ~ head+ti 사이에 tail직선이나 boundary가 닿는지 확인
    let tmpHead = new Snake(head.x, head.y, head.dir);
    head.moveForward(ti);
    head.turn(dir.shift());
    let headTi = head;
    head = tmpHead;

    console.log("head, headTi :");
    console.log(head);
    console.log(headTi);

    //경계면에 닿는지부터 판단.
    if (Math.abs(headTi.x) > l) {
      console.log("bumped into boundary");
      die = true;
      i += ti - (Math.abs(headTi.x) - l);
    } else if (Math.abs(headTi.y) > l) {
      console.log("bumped into boundary");
      die = true;
      i += ti - (Math.abs(headTi.y) - l);
    }

    //자기 몸에 닿아 죽는지 판단.
    for (let j = 0; j < tail.length - 1; j++) {
      if (isSuicide(head, headTi, tail[j], tail[j + 1])) {
        if (head.x === headTi.x) {
          die = true;
          i += Math.abs(head.y - tail[j].y);
        } else {
          die = true;
          i += Math.abs(head.x - tail[j].x);
        }
      }
    }

    if (!die){
        i += ti;
    }
    ti = t.shift();
    tail.push(new Snake(head.x, head.y, head.dir));   
    head = headTi;

    //debug
    flag--;
    console.log(`i = ${i}`);
  }
  console.log(i);

  process.exit();
});

function isSuicide(head1, head2, tail1, tail2) {
  if (head1.x === head2.x && tail1.y === tail2.y) {
    if (
      head1.x <= max(tail1, tail2, true).x &&
      head1.x >= min(tail1, tail2, true).x
    ) {
      return true;
    }
  } else if (head1.y === head2.y && tail1.x === tail2.x) {
    if (
      head1.y <= max(tail1, tail2, false).y &&
      head1.y >= min(tail1, tail2, false).y
    ) {
      return true;
    }
  }
  return false;
}

function max(snk1, snk2, isHori) {
  if (isHori) {
    if (snk1.x > snk2.x) {
      return snk1;
    } else {
      return snk2;
    }
  } else {
    if (snk1.y > snk2.y) {
      return snk1;
    } else {
      return snk2;
    }
  }
}
function min(snk1, snk2, isHori) {
  if (isHori) {
    if (snk1.x < snk2.x) {
      return snk1;
    } else {
      return snk2;
    }
  } else {
    if (snk1.y < snk2.y) {
      return snk1;
    } else {
      return snk2;
    }
  }
}
