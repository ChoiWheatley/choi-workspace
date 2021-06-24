/*
	https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/

	You have n boxes. You are given a binary string boxes of length n, where boxes[i] is '0' if the ith box is empty, and '1' if it contains one ball.

	In one operation, you can move one ball from a box to an adjacent box. Box i is adjacent to box j if abs(i - j) == 1. Note that after doing so, there may be more than one ball in some boxes.

	Return an array answer of size n, where answer[i] is the minimum number of operations needed to move all the balls to the ith box.

	Each answer[i] is calculated considering the initial state of the boxes.
*/


#include <iostream>
using namespace std;

int abs(int x)
{
	return (x < 0 ? x * (-1) : x);
}

int main(void)
{
	string boxes;
	vector<int> answer;
	cin >> boxes;
	
	for (int i = 0; i < boxes.size; i++)
	{
		int sum = 0;
		for (int j = 0; j < boxes.size; j++)
		{
			if (i == j) continue;
			sum += abs(i - j);
		}
		answer.add(sum);
	}

	for (auto i : sum)
	{
	}

	return 0;
}
