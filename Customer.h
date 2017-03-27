#include <string>
#include <vector>
#include <map>
#include "omp.h"
#pragma once

using namespace std;

float sumOfvector(vector<float> tosum);

class Customer {
private: 
	string Fname, Lname;
	int ID;
	map<int, int> ratings;
	struct Similar{
		int booksimilar;
		float totalweight;
		Customer* sim;
		Similar() {
			booksimilar = 0;
			totalweight = 0.0;
			sim = new Customer();
		}
	};
	map<int, Similar> similarcustomers;
public:
	Customer() { Fname = ""; Lname = ""; ID = NULL; };
	Customer(string First, string Last, int id) {
		Fname = First; 
		Lname = Last;
		ID = id;
	}
	void addRating(int ISBN, int rating) {
		ratings[ISBN] = rating;
	}
	int findRating(int ISBN) {
		if (ratings.find(ISBN) != ratings.end()) {
			return ratings[ISBN];
		}
	}
	bool findIfrated(int ISBN) {
		if (ratings.find(ISBN) != ratings.end()) {
			return true;
		}
		else {
			return false;
		}
	}
	void findSimilar(map<int, Customer> similar) {
		int counter = 0;
		map<int, Customer>::iterator itr;
		map<int, int>::iterator ratingItr;
		for (itr = similar.begin(); itr != similar.end(); itr++) {
			vector<float> weightList;
			if (itr->second.getID() != ID) {
				for (ratingItr = ratings.begin(); ratingItr != ratings.end(); ratingItr++) {
					if (itr->second.findIfrated(ratingItr->first)) {
						counter += 1;
						float weight = (itr->second.findRating(ratingItr->first));
						weightList.push_back(weight/5);
					}
				}
				Similar temp;
				temp.booksimilar = counter;
				Customer ref = itr->second;
				*temp.sim = ref;
				temp.totalweight = sumOfvector(weightList);
				similarcustomers[itr->first] = temp;
				counter = 0;
			}
		}
	};
	string getFname() { return Fname; };
	string getLname() { return Lname; };
	int getID() { return ID; };
};

float sumOfvector(vector<float> tosum) {
	float sum = 0;
	for (int i = 0; i < tosum.size(); i++) {
		sum += tosum[i];
	}
	return sum;
}