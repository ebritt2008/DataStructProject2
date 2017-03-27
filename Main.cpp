#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include "Book.h"
#include "Customer.h"

using namespace std;
map<int, Book> createUnratedBook(map<int, Book> books, map<int, Customer> customers, Customer currentUser);
bool optionFucntion(map<int, Customer> customers, map<int, Book> Books, int ID, int option);
map<int, Book> loadbooks(istream& fin, map<int, Book> bookmap);
map<int, Customer> loadcustomers(istream& fin, map<int, Customer> custmap);
void loadratings(istream& fin, map<int, Customer>& custmap);
void main() {
	map<int,Customer> custmap;
	map<int, Book> bookmap;
	int ID;
	int option;
	ifstream fin, fin2, fin3;
	fin.open("customers.txt");
	fin2.open("books.txt");
	fin3.open("ratings.txt");
	custmap = loadcustomers(fin, custmap);
	bookmap = loadbooks(fin2, bookmap);
	loadratings(fin3, custmap);
	cout << "Enter ID>>";
	cin >> ID;
	cout << " What would you like to do today? \n 1. Search a book and maybe rate it? \n 2. Rate a book that you havent rated before? \n 3. View Book recomendations by revelance \n >>";
	cin >> option;
	bool correct = optionFucntion(custmap, bookmap, ID, option);
	
	system("pause");
}

map<int, Customer> loadcustomers(istream& fin, map<int, Customer> custmap) {
	int id;
	string fname, lname;
	stringstream temps, temps1, temps2;
	string temp, line, temp1;
	int counter = 0;
	int ignore = 0;
	while (getline(fin, line))
	{
		if (ignore != 0) {
			temps.clear();
			temps << line;
			int counter = 0;
			while (getline(temps, temp, ',')) {
				if (counter == 0) {
					id = stoi(temp);
					counter += 1;
				}
				else if (counter == 1) {
					counter = 0;
					temp = temp.substr(1, temp.size());
					temps1 << temp;
					int tempnum = 0;
					while (getline(temps1, temp1, ' ')) {
						if (tempnum == 0) {
							fname = temp1;
							tempnum += 1;
						}
						else {
							lname = temp1;
						}
					}
					temps1.clear();
				}
			}
			Customer temp(fname, lname, id);
			custmap[id] = temp;
			temps.clear();
		}
		else {
			temps2 << line;
			temps2.clear();
			ignore += 1;
		}
	}
	return custmap;

}

void loadratings(istream& fin, map<int, Customer>& custmap) {
	int Id, ISBN, rating;
	string line, temp;
	stringstream temps, temps1, temps2;
	int ignore = 0;
	while (getline(fin, line)) {
		if (ignore != 0) {
			temps.clear();
			temps << line;
			int counter = 0;
			while (getline(temps, temp, ',')) {
				if (counter == 0) {
					Id = stoi(temp);
					counter += 1;
				}
				else if (counter == 1) {
					rating = stoi(temp);
					counter += 1;
				}
				else {
					ISBN = stoi(temp);
				}
			}
			custmap[Id].addRating(ISBN, rating);
		}
		else {
			temps2 << line;
			temps2.clear();
			ignore += 1;
		}
	}
}
map<int, Book> loadbooks(istream& fin, map<int, Book> bookmap) {
	int ISBN;
	string title;
	string line,temp;
	stringstream temps, temps1, temps2;
	int ignore = 0;
	map<int, Book> unrated;
	while (getline(fin, line)) {
		if (ignore != 0) {
			temps.clear();
			temps << line;
			int counter = 0;
			while (getline(temps, temp, ',')) {
				if (counter == 0) {
					ISBN = stoi(temp);
					counter += 1;
				}
				else {
					title = temp;
				}
			}
			Book temp(ISBN, title);
			bookmap[ISBN] = temp;
		}
		else {
			temps2 << line;
			temps2.clear();
			ignore += 1;
		}
		
	}
	return bookmap;
}

bool optionFucntion(map<int, Customer> customers, map<int, Book> Books, int ID, int option) {
	string response;
	bool YN = true;
	bool again = true;
	int ISBN, rating;
	map<int, Book>::iterator itr;
	map<int, Book> unrated;
	switch (option)
	{
	case 1: 
		cout << "Please enter ISBN of book you want to search \n >>";
		cin >> ISBN;
		if (Books.find(ISBN) != Books.end()) {
			cout << "Book found" << endl;
			cout << "ISBN: " << ISBN << " Title: " << Books[ISBN].getTitle();
		}	
		while (YN) {
			cout << "Would you like to rate the Book? (Y/N) \n>>";
			cin >> response;
			if (response == "Y" || response == "y") {
				while (again) {
					cout << "Please enter you rating on a scale of 1 to 5 \n>>";
					cin >> rating;
					if (rating > 5 || rating < 0) {
						cout << "you have entered an inavlid rating please try again !";
					}
					else {
						customers[ID].addRating(ISBN, rating);
						cout << "Book has been rated!" << endl;
						again = false;
						YN = false;
					}
				}
			}
			else if (response == "N" || response == "n") {
				cout << "Going back to main menu" << endl;
				YN = false;
			}
			else {
				cout << "invalid response try again" << endl;
			}
		}
		return true;
	case 2:
		for (itr = Books.begin(); itr != Books.end(); itr++) {
			if (!customers[ID].findIfrated(itr->second.getISBN())) {
				cout << "You havent rated: " << itr->second.getISBN() << " Title: " << itr->second.getTitle() << endl;
			}
		}
		while (again) {
			cout << "Please enter ISBN of book you want to rate \n >>";
			cin >> ISBN;
			if (Books.find(ISBN) != Books.end()) {
				cout << "Book found" << endl;
				cout << "ISBN: " << ISBN << " Title: " << Books[ISBN].getTitle();
				again = false;
			}
			else {
				cout << "Book was not found try again" << endl;
				again = true;
			}
		}
		while (YN) {
			cout << "Would you like to rate the Book? (Y/N) \n>>";
			cin >> response;
			if (response == "Y" || response == "y") {
				again = true;
				while (again) {
					cout << "Please enter you rating on a scale of 1 to 5 \n>>";
					cin >> rating;
					if (rating > 5 || rating < 0) {
						cout << "you have entered an inavlid rating please try again !";
					}
					else {
						customers[ID].addRating(ISBN, rating);
						cout << "Book has been rated!" << endl;
						again = false;
						YN = false;
					}
				}
			}
			else if (response == "N" || response == "n") {
				cout << "Going back to main menu" << endl;
				YN = false;
			}
			else {
				cout << "invalid response try again" << endl;
			}
		}
		return true;
	case 3:
		unrated = createUnratedBook(Books, customers, customers[ID]);
	default:
		return false;
		break;
	}
}


map<int, Book> createUnratedBook(map<int, Book> books, map<int, Customer> customers, Customer currentUser) {
	map<int, Book> unrated;
	omp_set_num_threads(3);
	#pragma omp parallel for
	{
		int ID = omp_get_thread_num();

		currentUser.findSimilar(customers);
		map<int, Book>::iterator itr;
		for (itr = books.begin(); itr != books.end(); itr++) {
			if (!currentUser.findIfrated(itr->second.getISBN())) {
				unrated[itr->second.getISBN()] = itr->second;
			}
		}
	}
	return unrated;

}