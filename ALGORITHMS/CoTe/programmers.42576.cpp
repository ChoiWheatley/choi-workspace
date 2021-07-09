#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

ostream& operator<<(ostream& os, const map<string, int>& dic)
{
	for (auto i : dic)
	{
		os << "[" << i.first << "," << i.second << "] ";
	}
	return os;
}

// Hash, Map(unordered_map), multiset(unordered_multiset) 등을 활용하여
// 문제를 풀 수 있다. 각각의 경우에 대하여 사용법과 iterator, 메커니즘을 
// 파악하자.
int main(void)
{
	// 동명이인이 있을 수 있는 참가자들
	vector<string> participant{ "mislav", "stanko", "mislav", "ana" };
	vector<string> completion{ "stanko", "ana", "mislav" };


	//
	//
	// map 을 활용한 풀이 : map은 key 값을 자동으로 자료구조에 정렬하여 
	// 집어넣는다. 정렬이 불편하다면 내부적으로 해시를 사용한 
	// unordered_map 을 활용하면 된다. 
	map<string, int> dic;
	string answer;

	for(auto i : participant)
	{
		// 사실 이 코드는 없어도 된다.
		// dic[i] 에서 i가 없는 값이면 
		// 자동으로 추가하여 ++ 해주기 때문이다.
		if (dic.find(i) != dic.end())
		{
			dic[i]++;
			continue;
		}
		dic.insert(make_pair(i, 1));
		
	}
	cout << dic << '\n';
	for (auto i : completion)
	{
		dic[i]--;
	}
	cout << dic << '\n';
	for (auto i : dic)
	{
		if (i.second > 0)
			answer = i.first;
	}
	cout << "the answer is " << answer << '\n';

	//
	//
	// 벡터를 정렬해서 순차적으로 접근하는 아주아주 간단한
	// 방법도 있다.
	answer = "";
	vector<string> p{participant};
	vector<string> c{completion};
	sort(p.begin(), p.end());
	sort(c.begin(), c.end());

	// 가장 마지막에 있는 선수의 경우
	answer = string{p.back()};
	for (int i = 0; i < c.size(); i++)
	{
		if (p[i] != c[i])
		{
			answer = p[i];
			break;
		}
	}
	cout << "the answer is " << answer << '\n';


	//
	//
	// unordered multiset을 활용하여 문제를 풀 수도 있다.
	answer = "";
	unordered_multiset<string> names;
	for (auto i : participant)
	{
		names.insert(i);
	}
	for (auto i : completion)
	{
		unordered_multiset<string>::iterator iter = names.find(i);
		names.erase(iter);
	}
	// 다 지우고 나면 딱 하나의 name만 남겠다.
	answer = *names.begin();
	cout << "the answer is " << answer << '\n';

	return 0;
}
