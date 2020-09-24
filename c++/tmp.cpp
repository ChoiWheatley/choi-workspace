/*
 * 
 * 
 */

#include "std_lib_facilities.h"

//
//
int main()
{
	try
	{
		vector<int> v;
		for (int x; cin >> x; )
		{
			v.push_back(x);
		}
		for (int i = 0; i <= v.size(); ++i)
		{
			cout << "v[" << i << "] == " << v[i] << endl;
		}
	}
	catch(out_of_range e)
	{
		cerr << "Ooops! Range Error!!!!\n";
		cerr << e.what() << endl;
		return 1;
	}
	
	
	return 0;
}
//
//
