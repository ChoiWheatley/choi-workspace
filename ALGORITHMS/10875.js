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
    let head, trace;
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
    tail = new Array(new Snake(0, 0, RIGHT)); //tail에 모든 경로를 집어넣지 말고 꺾인점만 넣는다.
    let i = 0; //뱀의 생존시간
    let ti = t.shift() + 1; //다음 회전까지 남은 시간

    while (!die) {
        //head ~ head+ti 사이에 tail직선이나 boundary가 닿는지 확인
        let tmpHead = head;
        head.moveForward(ti);
        let headTi = head;
        head = tmpHead;

        console.log(head);
        i += isSuicide(head, headTi, tail)
        if (i) {
            console.log("bumped into itself");
            die = true;
        } else if (Math.abs(headTi.x) > l) {
            console.log("bumped into boundary");
            die = true;
            i += ti - Math.abs(headTi.x) - l;
        } else if (Math.abs(headTi.y) > l) {
            console.log("bumped into boundary");
            die = true;
            i += ti - Math.abs(headTi.y) - l;
        }

        ti = t.shift();
        headTi.turn(dir.shift());
        head = headTi;

        console.log(head);
        console.log(tail);
    }
    console.log(i);

    process.exit();
});

function isSuicide(head, headTi, tail) {
    //여기에서 시간초과가 발생하는 듯 하다.
    //바뀐 tail에 따르면 두 꺾인점 A와 B 사이에 head와 headTi가 지나가는지 조사하면 된다.

    if (head.y === headTi.y) {
        //가로
        for (let i = 0; i < tail.length - 1; i++) {
            if (tail[i].x === tail[i + 1].x) {
                let tmpTail1 = min(
                    tail[i],
                    tail[i + 1],
                    tail[i].x === tail[i + 1].x
                );
                let tmpTail2 = max(
                    tail[i],
                    tail[i + 1],
                    tail[i].x === tail[i + 1].x
                );
                if (head.y <= tmpTail2.y && head.y >= tmpTail1.y) {
                    return Math.abs(tail[i].x - head.x);
                }
            }
        }
    } else {
        //세로
        for (let i = 0; i < tail.length - 1; i++) {
            if (tail[i].y === tail[i + 1].y) {
                let tmpTail1 = min(
                    tail[i],
                    tail[i + 1],
                    tail[i].x === tail[i + 1].y
                );
                let tmpTail2 = max(
                    tail[i],
                    tail[i + 1],
                    tail[i].x === tail[i + 1].y
                );
                if (head.x <= tmpTail2.x && head.x >= tmpTail1.x) {
                    return Math.abs(tail[i].x - head.x);
                }
            }
        }
    }
    return 0;

    function max(snk1, snk2, isHori) {
        if (isHori) {
            if (snk1.x > snk2.x) {
                return snk2;
            } else {
                return snk1;
            }
        } else {
            if (snk1.y > snk2.y) {
                return snk2;
            } else {
                return snk1;
            }
        }
    }
    function min(snk1, snk2, isHori) {
        if (isHori) {
            if (snk1.x < snk2.x) {
                return snk2;
            } else {
                return snk1;
            }
        } else {
            if (snk1.y < snk2.y) {
                return snk2;
            } else {
                return snk1;
            }
        }
    }
}

function isTouch(head, a, b) {
    //가로방향일 경우
    if (a.x === b.x) {
        if (a.x > b.x) {
            let tmp = a.x;
            a = b;
            b = tmp;
        }
        if (head.x >= a.x && head.x <= b.x) {
            return true;
        } else {
            return false;
        }
    }
    //세로방향일 경우
    else {
        if (a.y > b.y) {
            let tmp = a.y;
            a = b;
            b = tmp;
        }
        if (head.y >= a.y && head.y <= b.y) {
            return true;
        } else {
            return false;
        }
    }
}
