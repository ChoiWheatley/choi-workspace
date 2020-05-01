/*
이 문제는 아주 평범한 배낭에 관한 문제이다.

한 달 후면 국가의 부름을 받게 되는 준서는 여행을 가려고 한다. 
세상과의 단절을 슬퍼하며 최대한 즐기기 위한 여행이기 때문에, 
가지고 다닐 배낭 또한 최대한 가치 있게 싸려고 한다.

준서가 여행에 필요하다고 생각하는 N개의 물건이 있다. 
각 물건은 무게 W와 가치 V를 가지는데, 해당 물건을 배낭에 넣어서 가면 
준서가 V만큼 즐길 수 있다. 아직 행군을 해본 적이 없는 준서는 
최대 K무게까지의 배낭만 들고 다닐 수 있다. 준서가 최대한 즐거운 
여행을 하기 위해 배낭에 넣을 수 있는 물건들의 가치의 최댓값을 알려주자.

입력
첫 줄에 물품의 수 N(1 ≤ N ≤ 100)과 준서가 버틸 수 있는 무게
K(1 ≤ K ≤ 100,000)가 주어진다. 두 번째 줄부터 N개의 줄에 거쳐 
각 물건의 무게 W(1 ≤ W ≤ 100,000)와 해당 물건의 가치 
V(0 ≤ V ≤ 1,000)가 주어진다.

입력으로 주어지는 모든 수는 정수이다.

출력
한 줄에 배낭에 넣을 수 있는 물건들의 가치합의 최댓값을 출력한다.

예제 입력 1 
4 7
6 13
4 8
3 6
5 12
예제 출력 1 
14
예제 입력 2
5 5
1 1
1 2
1 3
1 4
1 5
예제 출력 2
15
예제입력 3
5 104
3 90
103 89
2 87
99 86
98 85
예제출력 3
263
*/

let n, k, nitem, stack, visit, ans_v;

let input = [];
let rl = require("readline");
let r = rl.createInterface({
    input: process.stdin,
    output: process.stdout
});
r.on("line", (line) => {
    if (line === "exit"){ r.close(); }
    else { input.push(line); }
});
r.on("close", () => {
    let tmp, max;
    tmp = input[0].split(" ");
    n = Number(tmp[0]);
    k = Number(tmp[1]);
    nitem = new Array(n);
    stack = new Nitem(0, 0);
    max = new Nitem(0, 0);
    visit = new Array(n);

    //nitem initialize
    for (let i = 0; i < n; i++){
        tmp = input[i+1].split(" ");
        nitem[i] = new Nitem(Number(tmp[0]), Number(tmp[1]));
    }
    //console.log(nitem);
    DFS(0);

   
    console.log(ans_v);
    

    
    process.exit();
});


class Nitem {
    constructor(w, v) {
        this.w = w;
        this.v = v;
    }
    add(item){
        this.w += item.w;
        this.v += item.v;
        return this;
    }
    change(item){
        this.w = item.w;
        this.v = item.v;
        return this;
    }
    show(){
        return `{${this.w}, ${this.v}}`;
    }
}

function DFS(x){
    for (let i = x; i < n; i++){
        if (!visit[i] && stack.w + nitem[i].w <= k){
            visit[i] = true;
            stack.w += nitem[i].w;
            stack.v += nitem[i].v;
            console.log(`stack = {${stack.w}, ${stack.v}} /// nitem[${i}] = {${nitem[i].w}, ${nitem[i].v}}`);
            DFS(i);
            //초기화
            stack.w -= nitem[i].w;
            stack.v -= nitem[i].v;
        }
    }
    ans_v = max(ans_v, stack.v);
}   

function max(a, b){
    if (a > b){ return a; }
    else { return b; }
}