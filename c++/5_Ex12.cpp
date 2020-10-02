/*
 * <Chapter 5 Example 12> : Bulls And Cows (= 숫자야구)
 * Bull : right digit & right position
 * Cow : only right digit
 * eg) 
 * answer > 1234
 * estima > 1359
 * return > 1 Bull 1 Cow
 * 
 * <Example 13> : improve this program the answer is 
 * the Random value
 */

#include "std_lib_facilities.h"
#include <random>

typedef struct BULLCOW
{
    int Bull = 0;
    int Cow = 0;
}BULLCOW;


void input_estima(vector<int> & estima);
BULLCOW evaluate(const vector<int> & ans, const vector<int> & esti);
inline int ctoi(char x) { return x - 48; }
vector<int> init_answer();
void show(const vector<int> & v);
inline bool is_dupl(const vector<int> & t, int i);
inline void init_seq(vector<int> & t);

// ********************************************************************************** //
// ********************************************************************************** //
// ********************************************************************************** //
int main()
{
    BULLCOW ret;
	vector<int> answer = init_answer();
    vector<int> estima(4);
    for (int i = 0; i < 10 && ret.Bull < 4; i++)
    {
        input_estima(estima);
        ret = evaluate(answer, estima);
        cout << ret.Bull << "Bull " << ret.Cow << "Cow" << endl;
    }
    cout << "The answer is ";
    show(answer);

    return 0;
}
// ********************************************************************************** //
// ********************************************************************************** //
// ********************************************************************************** //

void input_estima(vector<int> & estima)
/*
 * 입력 시, 중복된 숫자가 있는지도 판별해야 한다.
 */ 
{
    init_seq(estima);
    cout << "Please input four digits between 0 to 9 $ ";
    for (int i = 0; i < 4; i++)
    {
        char tmp = cin.get();
        estima[i] = ctoi(tmp);
        if ( !(tmp >= 48 && tmp <= 57) ) throw runtime_error("ERROR : no 0 to 9 value\n");
        if ( is_dupl(estima, i) ) throw runtime_error("ERROR : duplicated number\n");
    }
    cin.ignore(10, '\n');
}
BULLCOW evaluate(const vector<int> & ans, const vector<int> & est)
/*
 *  i) ans와 est의 BULL을 비교
 *  ii) ans와 est의 COW를 비교
 */
{
    BULLCOW ret;
    for (int i = 0; i < 4; i++)
    {
        if (ans[i] == est[i])
        // i) ans와 est의 BULL을 비교
        {
            ret.Bull++;
            continue;
        }
        for (int j = 0; j < 4; j++)
        {
            if (ans[i] == est[j])
            // ii) ans와 est의 COW를 비교
            {
                ret.Cow++;
                continue;
            }
        }
    }
    return ret;
}


/*
 *
 *
 *
 *
 *
 *
 *
 *
 * 
*/



int get_randint(int min, int max)
{
    random_device rn;
    mt19937_64 rng (rn());
    uniform_int_distribution<int64_t> dist(min, max);
    return dist( rng );
}
vector<int> init_answer()
{
    vector<int> ret(4);
    seed_randint(time(NULL));
    for (int i = 0; i < 4; i++)
    {
        ret[i] = get_randint(0,9);
        if (is_dupl(ret, i)) i--;
    }
    return ret;
}
void show(const vector<int> & v)
{
    for (auto i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}
inline bool is_dupl(const vector<int> & t, int i)
{
    if (i < 1) return false;
    for (int j = 0; j < i; j++)
        if (t[i] == t[j]) return true;
    return false;
}
inline void init_seq(vector<int> & t)
{
    for (int i = 0; i < t.size(); i++)
        t[i] = 0;
}