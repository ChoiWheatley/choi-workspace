/*
 * each value as a distance between two cities along a given route.
 * 1. compute a total distance (the sum of all distances)
 * 2. Find and print the smallest and greatest distance between two neighboring cities.
 * 3. Find and print the mean distance between two neighboring cities.
 */

#include "std_lib_facilities.h"

inline double sum(const vector<double> & list);
inline double smallest(vector<double> list);
inline double largest(vector<double> list);
inline double mean(const vector<double> & list);

int main()
{
	vector<double> dists;
	for (double tmp; cin >> tmp; )
		dists.push_back(tmp);
	cout << "The total distance is : " << sum(dists) << endl;
	cout << "The smallest and the largest distance is : " << smallest(dists) << " and " << largest(dists) << endl;
	cout << "The mean value of distances is : " << mean(dists) << endl;

	return 0;
}

inline double sum(const vector<double> & list)
{
	double ret = 0;
	for (int i = 0; i < list.size(); i++) 
	{
		ret += list[i];
	}
	return ret;
}
inline double smallest(vector<double> list)
{
	sort(list);
	return list[0];
}
inline double largest(vector<double> list)
{
	sort(list);
	return list[list.size()-1];
}
inline double mean(const vector<double> & list)
{
	double sum = 0;
	for (int i = 0; i < list.size(); i++)
		sum += list[i];
	return sum / list.size();
}
