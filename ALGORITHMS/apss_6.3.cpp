/*
 * 2020 10 03
 * https://algospot.com/judge/problem/read/BOGGLE
 * 예제 : 보글게임 p.150
입력의 첫 줄에는 테스트 케이스의 수 C(C <= 50)가 주어집니다. 
각 테스트 케이스의 첫 줄에는 각 5줄에 5글자로 보글 게임판이 주어집니다. 
게임판의 모든 칸은 알파벳 대문자입니다.
그 다음 줄에는 우리가 알고 있는 단어의 수 N(1 <= N <= 10)이 주어집니다. 
그 후 N줄에는 한 줄에 하나씩 우리가 알고 있는 단어들이 주어집니다. 
각 단어는 알파벳 대문자 1글자 이상 10글자 이하로 구성됩니다.

각 테스트 케이스마다 N줄을 출력합니다. 각 줄에는 알고 있는 단어를 
입력에 주어진 순서대로 출력하고, 해당 단어를 찾을 수 있을 
경우 YES, 아닐 경우 NO를 출력합니다.

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

 * 
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// (dx, dy)
const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

// 대문자로 변환
void capitalize(string &str);
void init_board(vector<string> &str);
// 보드, 워드 초기화 및 입력 프롬프트
void input_prompt(vector<string> &board, vector<string> &words);
void dbg_print_strings(vector<string> &strs);

// x,y 좌표에서부터 해당 str가 있는지 검사
bool has_word(int x, int y, const vector<string> &board, const string &str);
bool in_range(int x, int y);

/*

███    ███      █████      ██     ███    ██ 
████  ████     ██   ██     ██     ████   ██ 
██ ████ ██     ███████     ██     ██ ██  ██ 
██  ██  ██     ██   ██     ██     ██  ██ ██ 
██      ██     ██   ██     ██     ██   ████ 
                                            
 */
int main(void)
{
    int c = 0;
    cin >> c;
    for (int test_case_i = 0; test_case_i < c; test_case_i++)
    {
        vector<string> board(5);
        vector<string> words;
        input_prompt(board, words);
        for (auto w : words)
        {
            bool has_word_flag = false;
            for (int i = 0; i < 5 && !has_word_flag; i++)
                for (int j = 0; j < 5 && !has_word_flag; j++)
                    if (has_word(i, j, board, w))
                        has_word_flag = true;
            if (has_word_flag)
                cout << w << " YES\n";
            else
                cout << w << " NO\n";
        }
    }
    return 0;
}
void input_prompt(vector<string> &board, vector<string> &words)
{
    int n = 0;
    for (int i = 0; i < 5; i++)
    {
        cin >> board[i];
        capitalize(board[i]);
        if (board[i].size() != 5)
            throw runtime_error("ERROR: wrong input board\n");
    }
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        capitalize(tmp);
        words.push_back(tmp);
    }
}

void dbg_print_strings(vector<string> &strs)
{
    cout << "\n><><>< DEBUGGING ><><><" << endl;
    for (auto i : strs)
        cout << i << endl;
}
void capitalize(string &str)
{
    for (int i = 0; i < str.size(); i++)
        str[i] = toupper(str[i]);
}

/*

██   ██  █████  ███████     ██     ██  ██████  ██████  ██████  
██   ██ ██   ██ ██          ██     ██ ██    ██ ██   ██ ██   ██ 
███████ ███████ ███████     ██  █  ██ ██    ██ ██████  ██   ██ 
██   ██ ██   ██      ██     ██ ███ ██ ██    ██ ██   ██ ██   ██ 
██   ██ ██   ██ ███████      ███ ███   ██████  ██   ██ ██████  

5 * 5의 보글 게임 판의 해당 위치에서 주어진 단어가 시작하는지를 반환하는 프로그램
                                                               
base case #1 시작 위치가 범위 밖이면 무조건 false
base case #2 시작 위치가 str의 첫 글자가 아니면 false
base case #3 str.size() == 1 이면 return true

TODOLIST
-- 첫 글자를 제외한 새 str을 만들어야 한다.
-- (x + dir_x[i], y + dir_y[i]) 부터 탐색하게 만들어야 한다.
-- 만약 재탐색 검색결과가 true 이면 그대로 true를 리턴하여도 좋다.
*/
bool has_word(int x, int y, const vector<string> &board, const string &str)
{
    if (!in_range(x, y))
        return false;
    if (board[y][x] != str[0])
        return false;
    if (str.size() == 1)
        return true;

    for (int i = 0; i < 8; i++)
    {
        if (has_word(x + dx[i], y + dy[i], board, str.substr(1)))
            return true;
    }
    return false;
}
bool in_range(int x, int y)
{
    if (x < 0 || x > 4 ||
        y < 0 || y > 4)
        return false;
    return true;
}