/*
 * Chapter8 Exercise7 : 이름과 나이 pair 생성하고
 * 이름 정렬하기 
 * 
 */

#include "std_lib_facilities.h"

void prompt(vector<string>&, vector<int>&);
void printPair(const vector<string>&, const vector<int>&);
void retrieve(const vector<string>&, const vector<string>&, vector<int>&);
//
//
int main()
{
	vector<string> names, oldNames;
    vector<int> ages;

    prompt(names, ages);
    printPair(names, ages);
    oldNames.assign(names.begin(), names.end());
    sort(names.begin(), names.end());
    retrieve(oldNames, names, ages);
    printPair(names, ages);

	
	return 0;
}
//
//

// prompt user to input name and age
void prompt(vector<string>& names, vector<int>& ages)
{
    string tmpStr;
    int tmpInt;
    cout << "Please input five names divided by whitespace.\n>> ";
    for (int i = 0; i < 5; i++) {
        cin >> tmpStr;
        names.push_back(tmpStr);
    }
    cout << "Please enter five ages divided by whitespace. \n>> ";
    for (int i = 0; i < 5; i++) {
        cin >> tmpInt;
        ages.push_back(tmpInt);
    }
}
// print name and age pair
void printPair(const vector<string>& names, const vector<int>& ages)
{
    if (names.size() != ages.size()) { error("no matching array sizes!"); }
    for (int i = 0; i < names.size(); i++) {
        cout << "( " << names[i] << " , " << ages[i] << " ), ";
    }
    cout << "\b\b\n";
}
// retrieve the order of ages from difference between oldNames and newNames
void retrieve(const vector<string>& oldNames, const vector<string>& newNames, vector<int>& ages)
{
    if (oldNames.size() != newNames.size() || newNames.size() != ages.size()) { error("no matching array sizes!"); }
    auto findIndex = [] (const vector<string>& oldNames, string name) {
        for (int i = 0; i < oldNames.size(); i++) {
            if (oldNames[i] == name) return i;
        }
        return 0;
    };
    vector<int> oldOrder {ages};
    for (int i = 0; i < newNames.size(); i++) {
        ages[i] = oldOrder[findIndex(oldNames, newNames[i])];
    }
}