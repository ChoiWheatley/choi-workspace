/*
 * 
 * 
 */

#include "std_lib_facilities.h"

class Friend;
int longest_string(vector<string> str);

//
//
int main()
{
	// Drill1 ~ 7
	int birth_year = 1997;
	cout << setw(30) << "birth year in decimal :" << showbase << dec << birth_year << "\n";
	cout << setw(30) << "birth year in hexadecimal :" << hex << birth_year << "\n";
	cout << setw(30) << "birth year in octal :" << oct << birth_year << "\n";
	cout << setw(30) << "age :" << dec << 2021 - birth_year << "\n";

	// Drill9
	constexpr double number = 1234567.89;
	cout << "\n" << defaultfloat << number << "\t" << fixed << number << "\t" << scientific << number << "\n";

	// Drill10
	class Friend {
	public:
		Friend(string first_name, string last_name, long telephone_num, string email_addr)
			: first_name_{first_name}, last_name_{last_name}, telephone_num_{telephone_num}, email_addr_{email_addr} {}
		string first_name() const {return first_name_;}
		string last_name() const {return last_name_;}
		string email_addr() const {return email_addr_;}
		long telephone_num() const {return telephone_num_;}
	private:
		string first_name_;
		string last_name_;
		long telephone_num_;
		string email_addr_;
	};
	Friend choi{"choi", "seunghyeon", 1087524037, "chltmdgus604@naver.com"};
	Friend kang{"kang", "minseok", 1022437691, "idontknow"};
	Friend park{"park", "sangeun", 1090986576, "psangeun97@gmail.com"};
	Friend bjarne{"Bjarne", "Stroustrup", 1877463321, "idontknowbutiwanttorwritethemostlongestemailaddress@gmail.com"};
	vector<Friend> friends{choi, kang, park, bjarne};
	int longest_first_name = 0, longest_last_name = 0, longest_email_addr = 0;
	for (auto i : friends) {
		if (longest_first_name < i.first_name().size()) longest_first_name = i.first_name().size();
		if (longest_last_name < i.last_name().size()) longest_last_name = i.last_name().size();
		if (longest_email_addr < i.email_addr().size()) longest_email_addr = i.email_addr().size();
	}
	for (auto i : friends) {
		cout << setw(longest_first_name + 3) << i.first_name() << " |" << 
			setw(longest_last_name + 3) << i.last_name() << " |" <<
			setw(to_string(i.telephone_num()).size() + 3) << i.telephone_num() << " |" <<
			setw(longest_email_addr + 3) << i.email_addr() << " |\n";
	}

	return 0;
}
//
//

int longest_string(vector<string> str)
{
	int ret = 0;
	for (auto i : str) if (ret < i.size()) ret = i.size();
	return ret;
}