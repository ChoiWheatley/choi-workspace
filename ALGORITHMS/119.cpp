/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> Answer(2, 0);

vector<int> street_forward(vector<vector<int>> &sn);
string street_show(vector<vector<int>> s, string argv);

vector<int> street_forward(vector<vector<int>> &sn) {
	int h = 1, w = 1;
	vector<int> out(2, 1);
	while (h < sn.size() - 1 && w < sn[0].size() - 1) {
		if(sn[h][w]) {
			//오
			sn[h][w] = 0;
			w++;
		} else {
			//아
			sn[h][w] = 1;
			h++;
		}
	}

	out[0] = h;
	out[1] = w;

	return out;
}
string street_show(vector<vector<int>> s, string argv) {
	string out_string = "";
	vector<vector<int>> tmp;
	vector<int> tmp_forward;
	if (argv.find("m") != string::npos) {
		for (int i = 1; i < s.size() - 1; i++) {
			for (int j = 1; j < s[0].size() - 1; j++) {
				out_string += to_string(s[i][j]) + " ";
			}
			out_string += "\n";
		}
	} 
	if (argv.find("f") != string::npos) {
		tmp.assign(s.begin(), s.end());
		tmp_forward = street_forward(tmp);
		out_string += to_string(tmp_forward[0]) + "\t" + to_string(tmp_forward[1]);
	}
	
	cout << out_string << "\n";
	return out_string;
}

int main(int argc, char** argv)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */	

	freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer[0] = 0;
		Answer[1] = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		int h, w, n;
		int input_int;
		vector<int> _s;
		vector<vector<int>> s;


		cin >> h >> w >> n;
		_s.assign(w + 2, 0);
		s.assign(h + 2, _s);
		for (int i = 1; i < s.size() - 1; i++) {
			cin.ignore(1, '\n');
			for (int j = 1; j < s[i].size() - 1; j++) {
				cin >> input_int;
				s[i][j] = input_int;
			}
		}
		//street_show(s, "mf");
		for (int i = 0; i < n; i++) {
			Answer = street_forward(s);
			//street_show(s, "f");
		}

		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer[0] << " " << Answer[1] << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}