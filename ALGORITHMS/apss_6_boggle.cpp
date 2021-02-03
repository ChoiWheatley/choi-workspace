/* <APSS> Chapter6 무식하게 풀기 <ID: BOGGLE / p.150>
 * https://algospot.com/judge/problem/read/BOGGLE

보글(Boggle) 게임은 5x5 크기의 알파벳 격자인 게임판의 한 글자에서 시작해서 펜을 움직이면서 만나는 글자를 그 순서대로 나열하여 만들어지는 영어 단어를 찾아내는 게임입니다. 
펜은 상하좌우, 혹은 대각선으로 인접한 칸으로 이동할 수 있으며 글자를 건너뛸 수는 없습니다. 지나간 글자를 다시 지나가는 것은 가능하지만, 펜을 이동하지않고 같은 글자를 여러번 쓸 수는 없습니다.
보글 게임판과 알고 있는 단어들의 목록이 주어질 때, 보글 게임판에서 각 단어를 찾을 수 있는지 여부를 출력하는 프로그램을 작성하세요.

<입력>
입력의 첫 줄에는 테스트 케이스의 수 C(C <= 50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 각 5줄에 5글자로 보글 게임판이 주어집니다. 게임판의 모든 칸은 알파벳 대문자입니다.
그 다음 줄에는 우리가 알고 있는 단어의 수 N(1 <= N <= 10)이 주어집니다. 그 후 N줄에는 한 줄에 하나씩 우리가 알고 있는 단어들이 주어집니다. 각 단어는 알파벳 대문자 1글자 이상 10글자 이하로 구성됩니다.

<출력>
각 테스트 케이스마다 N줄을 출력합니다. 각 줄에는 알고 있는 단어를 입력에 주어진 순서대로 출력하고, 해당 단어를 찾을 수 있을 경우 YES, 아닐 경우 NO를 출력합니다.



예제 입력
1
URLPM
XPRET
GIAET
XTNZY
XOQRS
6
PRETTY
GIRL
REPEAT
KARA
PANDORA
ururur

예제 출력

PRETTY YES
GIRL YES
REPEAT YES
KARA NO
PANDORA NO
GIAZAPX YES

<History>
21. 02. 02
	-- 어젠 Input만 끙끙대다 끝났네.
21. 02. 01
    -- 백준 온라인 강의 대비를 위한 알고리즘 공부! 목표는 강의시작일인 2월 10일까지 하루에 두 문제씩만 푸는거다.
    -- 백준 온라인 강의 수강기간이 45일밖에 되지 않는다. 해당기간동안 알고리즘 기초를 다져놓는다고 생각하고 그 뒤부터 다시 APSS로 돌아와 문제를 접근하자.
20. 10. 03

 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


// f("PRETTY") --> true
// f("UUUUU") --> false
bool f(const vector<string>& case_, string& word);
// Can you find word_ after (x, y) position?
// word_ = word - word[0]
// BASE_CASE1 check x, y range 
// BASE_CASE2 check word_ 's size (if 0, return true)
bool next(const vector<string>& case_, int y, int x, string& word_);
// input control (is >> case_ , is >> words)
void input(istream& is, vector<string>& case_, vector<string>& words);

// helper functions
inline bool isRange(int x, int y) {return (0 <= x && x < 5) &&
										  (0 <= y && y < 5);}

int main(void) 
{
    vector<string> case_;
    vector<string> words;
	ifstream is{"sample.txt"};
	if (!is) std::runtime_error("wrong input file");
    int c;
    is >> c;
    for (; c > 0; c--) {
        input (is, case_, words);
// debugging
		cout << "case_ : \n";
		for (auto i : case_)
			cout << i << '\n';
// end debug
		for (auto i : words){
			cout << i << " \n" << (f(case_, i) ? "YES" : "NO") << '\n';
		}
	}
    return 0;
}
bool f(const vector<string>& case_, string& word)
{
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			if (case_[i][j] == word[0] && 
				next(case_, j, i, word.erase(0, 1)))
				return true;
		}
	}
	return false;
}
bool next(const vector<string>& case_, int y, int x, string& word_)
{
// dx, dy are starting at 3o'clock to clockwise
	static const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
	static const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
// BASE CONDITIONS
	if (!isRange(x, y)) return false;
	if (word_.size() < 1) return true;

//debug
	cerr << "word_ = " << word_ << '\n';
	cerr << "(x, y) = (" << x << ", " << y << ")\n";
//end debug

	for (int i = 0; i < 8; i++){
		int x_ = x + dx[i];
		int y_ = y + dy[i];
		if (case_[x_][y_] == word_[0] &&
			next(case_, y_, x_, word_.erase(0, 1))
		)  return true;
	}
	return false;
}

void input(istream& is, vector<string>& case_, vector<string>& words)
{
    case_ = vector<string>();
    words = vector<string>();
	string tmpstr;
	int n;
// case_
    for (int i = 0; i < 5; i++){
		is >> tmpstr;
        for (char& j : tmpstr) {
            if (!isalpha(j)) throw std::runtime_error("not alphabet");
            j = toupper(j);
        }
		case_.push_back(tmpstr);
    }

    is >> n;
// words
    for (int i = 0; i < n; i++){
		is >> tmpstr;
        if (is.eof()) return;
        if (is.fail()) {is.clear(); continue;}
        if (is.bad()) std::runtime_error("cin object badbit error");
        for (char& j : tmpstr){
            if (!isalpha(j)) throw std::runtime_error("not alphabet");
            j = toupper(j);
        }
		words.push_back(tmpstr);
    }
}
