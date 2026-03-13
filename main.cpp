#include <ostream>
#include "MyString.h"

int main() {
    SetConsoleOutputCP(1251);
    ItemManager manager("Items.txt");

	MyString text1 = "Hell Maks!";
	std::cout << "(text1 == text) = "<<(text1 == text) << std::endl;
	std::cout << "(text == text1) = "<<(text == text1) << std::endl;
	std::cout <<"(text == Hello word!) = "<< (text == "Hello word!") << std::endl;

	text1 = text;
	std::cout <<"text1 = " << text1 << std::endl;
	text1 = "Hi Maks!";
	std::cout<<"text1 = " << text1 << std::endl;

	std::cout<<"text1[0] << text1[4] = " << text1[0] << text1[4] << std::endl;
	std::cout <<"text.size() = " << text.size() << std::endl;
	std::cout<< " text.c_str() = " << text.c_str() << std::endl;
	text.clear();
	std::cout<<"text.clear(); = " << text;

    return 0;
}
