/*
 * 
 * 
 */

#include "std_lib_facilities.h"

//
//
int main()
{
	vector<double> temps;
	for (double temp; cin >> temp; )
		temps.push_back(temp);
	try
	{
		double sum = 0;
		double high_temp = temps[0];
		double low_temp = temps[0];

		for (auto x : temps)
		{
			if (x > high_temp)
				high_temp = x;
			if (x < low_temp)
				low_temp = x;
			sum += x;
		}
		cout << "High temperature : " << high_temp << endl;
		cout << "Low temperature : " << low_temp << endl;
		cout << "Average temperature : " << sum / temps.size() << endl;
	}
	catch (runtime_error &e)
	{
		cerr << "hiiiiiiiiiiiii " << e.what() << endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "WARNING\nyou should input more than 0 value ::: " << e.what() << '\n';
	}


	return 0;
}
//
//
