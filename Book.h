#include <string>
#pragma once

using namespace std;

class Book {
	int ISBN;
	string Title;
public:
	Book() { ISBN = 0; Title = ""; };
	Book(int isbn, string title){
		ISBN = isbn;
		Title = title;
	};
	int getISBN() { return ISBN; };
	string getTitle() { return Title; };
};
