/*
혜윤이는 자신의 노트북에 이 스티커들을 붙이기로 했다. 혜윤이의 노트북은 마침 직사각형 모양이고, 스티커가 인쇄된 모눈종이와 같은 간격으로 격자가 그려져 있다. 혜윤이는 스티커들을 먼저 받았던 것부터 차례대로 격자에 맞춰서 붙이려고 한다.

혜윤이가 스티커를 붙이는 방법은 다음과 같다.

스티커를 회전시키지 않고 모눈종이에서 떼어낸다.
다른 스티커와 겹치거나 노트북을 벗어나지 않으면서 스티커를 붙일 수 있는 위치를 찾는다. 혜윤이는 노트북의 위쪽부터 스티커를 채워 나가려고 해서, 스티커를 붙일 수 있는 위치가 여러 곳 있다면 가장 위쪽의 위치를 선택한다. 가장 위쪽에 해당하는 위치도 여러 곳이 있다면 그중에서 가장 왼쪽의 위치를 선택한다.
선택한 위치에 스티커를 붙인다. 만약 스티커를 붙일 수 있는 위치가 전혀 없어서 스티커를 붙이지 못했다면, 스티커를 시계 방향으로 90도 회전한 뒤 2번 과정을 반복한다.
위의 과정을 네 번 반복해서 스티커를 0도, 90도, 180도, 270도 회전시켜 봤음에도 스티커를 붙이지 못했다면 해당 스티커를 붙이지 않고 버린다.
아래의 예시를 통해 스티커를 붙이는 과정을 이해해보자. 노트북은 세로 5칸, 가로 4칸 크기이고, 혜윤이가 가지고 있는 스티커들은 아래와 같다. 왼쪽에서 오른쪽 순으로 스티커를 붙일 것이다.

<입력>
첫째 줄에 노트북의 세로와 가로 길이를 나타내는 N(1 ≤ N ≤ 40)과 M(1 ≤ M ≤ 40), 그리고 스티커의 개수 K(1 ≤ K ≤ 100)이 한 칸의 빈칸을 사이에 두고 주어진다.

그 다음 줄부터는 K개의 스티커들에 대한 정보가 주어진다. 각 스티커는 아래와 같은 형식으로 주어진다.

먼저 i번째 스티커가 인쇄된 모눈종이의 행의 개수와 열의 개수를 나타내는 Ri(1 ≤ Ri ≤ 10)와 Ci(1 ≤ Ci ≤ 10)가 한 칸의 빈칸을 사이에 두고 주어진다.

다음 Ri개의 줄에는 각 줄마다 모눈종이의 각 행을 나타내는 Ci개의 정수가 한 개의 빈칸을 사이에 두고 주어진다. 각 칸에 들어가는 값은 0, 1이다. 0은 스티커가 붙지 않은 칸을, 1은 스티커가 붙은 칸을 의미한다.

문제에서 설명한 것과 같이 스티커는 모두 올바른 모눈종이에 인쇄되어 있다. 구체적으로 스티커의 각 칸은 상하좌우로 모두 연결되어 있고, 모눈종이의 크기는 스티커의 크기에 꼭 맞아서 상하좌우에 스티커에 전혀 포함되지 않는 불필요한 행이나 열이 존재하지 않는다.

예제 입력 1 
5 4 4
3 3
1 0 1
1 1 1
1 0 1
2 5
1 1 1 1 1
0 0 0 1 0
2 3
1 1 1
1 0 1
3 3
1 0 0
1 1 1
1 0 0
예제 출력 1 
18
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
  } else {
    input.push(line);
  }
});
r.on("close", function () {
  let notebook;
  let n, m, k; //노트북의 세로와 가로, 스티커의 개수
  let s; //"s"ticker array
  let tmp = input.shift().split(" ");
  let cnt = 0;
  n = Number(tmp.shift());
  m = Number(tmp.shift());
  k = Number(tmp.shift());
  s = new Array(k);
  notebook = arrInit(n + 2, m + 2); //notebook의 바깥을 1로 도배해서 일종의 벽을 만들 것이다. notebook은 [1][1]부터 세야 한다.
  notebook[0].fill(1);
  notebook[n + 1].fill(1);
  notebook = rotate(notebook);
  notebook[0].fill(1);
  notebook[m + 1].fill(1);
  notebook = rotate(notebook);

  for (let i = 0; i < s.length; i++) {
    tmp = input.shift().split(" "); //스티커의 길이
    let tmpX = Number(tmp.shift());
    let tmpY = Number(tmp.shift());
    s[i] = arrInit(tmpX, tmpY);
    for (let j = 0; j < tmpX; j++) {
      tmp = input.shift().split(" ");
      for (let o = 0; o < tmpY; o++) {
        s[i][j][o] = Number(tmp.shift());
      }
    }
  }

  //스티커 붙이기
  for (let i = 0; i < k; i++) {
    for (let j = 0; j < 4; j++) {
      let tmpN = stick(notebook, s[i]);
      if (tmpN) {
        notebook = tmpN;
        break;
      }
      s[i] = rotate(s[i]);
    }
  }

  //안쪽 1의 개수 세기
  for (let i = 1; i <= n; i++){
    for (let j = 1; j <= m; j++){
      if (notebook[i][j]){
        cnt++;
      }
    }
  }
  console.log(cnt);

  process.exit();
});

function arrInit(x, y) {
  let out = new Array(x);
  for (let i = 0; i < x; i++) {
    out[i] = new Array(y);
    for (let j = 0; j < y; j++) {
      out[i][j] = 0;
    }
  }
  return out;
}

//rotate()는 손바닥 뒤집기로 쉽게 이해가 가능하다. 직접 실험해보자.
//1. i j 뒤바꾸기
//2. 열 번호를 뒤집기
function rotate(arr_s) {
  let rowLeng = arr_s.length;
  let colLeng = arr_s[0].length;
  let outArr = arrInit(colLeng, rowLeng);
  for (let i = 0; i < colLeng; i++) {
    for (let j = 0; j < rowLeng; j++) {
      outArr[i][rowLeng - 1 - j] = arr_s[j][i];
    }
  }
  return outArr;
}

function printS(arr_s) {
  let rowLeng = arr_s.length;
  let colLeng = arr_s[0].length;
  let printLine = new String();
  console.log("");
  for (let i = 0; i < rowLeng; i++) {
    for (let j = 0; j < colLeng; j++) {
      printLine += arr_s[i][j] + " ";
    }
    console.log(printLine);
    printLine = new String();
  }
}

function stick(note, arr_s) {
  if (note.length < arr_s.length || note[0].length < arr_s[0].length) {
    return 0; //note를 리턴해야하나?
  }
  //주의: note는 현재 n+2, m+2의 배열이다.
  let isOverwrap = false;
  for (let i = 1; i < note.length - arr_s.length; i++) {
    for (let j = 1; j < note[0].length - arr_s[0].length; j++) {
      let note_ = clone(note);
      for (let si = 0; si < arr_s.length; si++) {
        for (let sj = 0; sj < arr_s[0].length; sj++) {
          let tmp = note[i + si][j + sj] + arr_s[si][sj];
          if (tmp > 1) {
            isOverwrap = true;
            break;
          } else {
            note_[i + si][j + sj] = tmp;
          }
        }
        if (isOverwrap) {
          break;
        }
      }
      if (!isOverwrap) {
        //printS(note_);
        return note_;
      }
      isOverwrap = false;
    }
  }
  //console.log("no match");
  return false;
}

function clone(arr_s) {
  let outArr = arrInit(arr_s.length, arr_s[0].length);
  for (let i = 0; i < arr_s.length; i++) {
    for (let j = 0; j < arr_s[0].length; j++) {
      outArr[i][j] = arr_s[i][j];
    }
  }
  return outArr;
}
