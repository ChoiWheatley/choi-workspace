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
const UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3;
let lastTime = 0;
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
  let l, //격자의 크기
    n, //회전수
    t, //회전에 대한 정보 - 시간
    dir; //회전에 대한 정보 - 방향
  let time = 0; //전체 생존시간
  let head, body; //대가리와 몸통

  l = Number(input.shift());
  n = Number(input.shift());
  t = new Array(n);
  dir = new Array(n);
  for (let i = 0; i < n; i++) {
    let tmp = input.shift();
    tmp = tmp.split(" ");
    t[i] = Number(tmp[0]);
    dir[i] = tmp[1];
  }

  head = new Snake(0, 0, RIGHT);
  body = new Array(1);
  body.fill(new Snake(0, 0, RIGHT));
  let i = 0;
  for (; i <= n; i++) {
    if (i === n) {
      //회전정보가 끝났다고 뱀이 뒤진게 아니다. 죽을 때까지 직진하자.
      t.push(2 * l + 1);
      dir.push("L");
      head = move(head, t[i], dir[i]);
    } else {
      head = move(head, t[i], dir[i]);
    }

    if (i && isSuicide(body, head)) {
      //마지막 time 구하고 break
      time += lastTime;
      break;
    }
    //
    //벽에 부딪히는 경우를 안따졌다!!!!!
    //
    if (Math.abs(head.x) > l) {
      time += t[i] - Math.abs(l - head.x) + 1;
      break;
    } else if (Math.abs(head.y) > l) {
      time += t[i] - Math.abs(l - head.y) + 1;
      break;
    }
    body.push(new Snake(head.x, head.y, head.dir));
    time += t[i];
    console.log(`${head.x}, ${head.y}`);
    console.log(time);
  }

  console.log(`lastTime : ${lastTime}`);
  console.log(`${head.x}, ${head.y}`);
  console.log(time);

  process.exit();
});

class Snake {
  constructor(x, y, dir) {
    this.x = x;
    this.y = y;
    this.dir = dir;
  }
}

function rotate(snake, dir) {
  if (dir === "L") {
    if (--snake.dir < 0) {
      snake.dir = LEFT;
    }
  } else {
    if (++snake.dir > 3) {
      snake.dir = UP;
    }
  }
  return snake;
}

function move(head, t, dir) {
  let tmpHead = new Snake(head.x, head.y, head.dir);
  switch (tmpHead.dir) {
    case UP:
      tmpHead.y += t;
      break;
    case RIGHT:
      tmpHead.x += t;
      break;
    case DOWN:
      tmpHead.y -= t;
      break;
    case LEFT:
      tmpHead.x -= t;
      break;
  }
  tmpHead = rotate(tmpHead, dir);
  return tmpHead;
}

function isSuicide(body, head) {
  for (let i = 0; i < body.length - 2; i++) {
    if (isHit(body[i], body[i + 1], body[body.length - 1], head)) {
      return true;
    }
  }
  return false;
}

function isHit(body1, body2, head1, head2) {
  //서로 수직인 경우
  if (body1.y === body2.y && head1.x === head2.x) {
    if (
      body1.y >= min(head1, head2, 1) &&
      body1.y <= max(head1, head2, 1) &&
      head1.x >= min(body1, body2, 0) &&
      head1.x <= max(body1, body2, 0)
    ) {
      lastTime = Math.abs(head1.y - body1.y);
      return true;
    }
  } else if (body1.x === body2.x && head1.y === head2.y) {
    if (
      body1.x >= min(head1, head2, 0) &&
      body1.x <= max(head1, head2, 0) &&
      head1.y >= min(body1, body2, 1) &&
      head1.y <= max(body1, body2, 1)
    ) {
      lastTime = Math.abs(head1.x - body1.x);
      return true;
    }
    //평행이지만 서로 겹치는 경우
  } else if (
    body1.y === body2.y &&
    head1.y === head2.y &&
    body1.y === head1.y
  ) {
    if (head1.x < min(body1, body2, 0)) {
      lastTime = Math.abs(head1.x - min(body1, body2, 0));
      return true;
    } else if (head1.x > max(body1, body2, 0)) {
      lastTime = Math.abs(head1.x - max(body1, body2, 0));
      return true;
    }
  } else if (
    body1.x === body2.x &&
    head1.x === head2.x &&
    body1.x === head1.x
  ) {
    if (head1.y < min(body1, body2, 1)) {
      lastTime = Math.abs(head1.y - min(body1, body2, 1));
      return true;
    } else if (head1.y > max(body1, body2, 1)) {
      lastTime = Math.abs(head1.y - max(body1, body2, 0));
      return true;
    }
  } else {
    return false;
  }
}

function min(snake1, snake2, xOrY) {
  //xOrY : x = 0, y = 1
  if (xOrY) {
    if (snake1.y < snake2.y) {
      return snake1.y;
    } else {
      return snake2.y;
    }
  } else {
    if (snake1.x < snake2.x) {
      return snake1.x;
    } else {
      return snake2.x;
    }
  }
}

function max(snake1, snake2, xOrY) {
  if (xOrY) {
    if (snake1.y < snake2.y) {
      return snake2.y;
    } else {
      return snake1.y;
    }
  } else {
    if (snake1.x < snake2.x) {
      return snake2.x;
    } else {
      return snake1.x;
    }
  }
}
