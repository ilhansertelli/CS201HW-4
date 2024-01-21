#include <iostream>
#include <vector>
#include <string>
#include "randgen.h"
#include "strutils.h"
using namespace std;
/*
struct filmGroup {
	string group, film, gen, year;
	 int years;
};

void sorter(vector<int> & a, vector<string> & b, vector<string> & c) { //year, film, genre

	// 1000, 1000, 1000, 1001, 1002
	//AMovie, BMovie, CMovie, DMovie, EMovie
	//Genre, Genre, Genre, Genre, Genre, Genre


	int swap, min;  
	string swap1;
	for (unsigned int i = 0; i < a.size(); i++) {
		min = i;
		for (int j = i + 1; j < a.size(); j++) {
			if (a[j] <= a[min]) {
				min = j;
			}
		}
		swap = a[i];
		a[i] = a[min];
		a[min] = swap;
		swap1 = b[i];
		b[i] = b[min];
		b[min] = swap1;
		swap1 = c[i];
		c[i] = c[min];
		c[min] = swap1;
	}
	for (int p = 0; p < a.size(); p++) {
		for (int k = 0; k < a.size() - 1; k++) {
			if (a[k] == a[k+1]) {
				for (int m = 0; m < b[k].length(); m++) {
					if (char(b[k][m]) < char(b[k+1][m])) {
						swap1 = b[k+1];
						b[k+1] = b[k];
						b[k] = swap1;
						swap1 = c[k+1];
						c[k+1] = c[k];
						c[k] = swap1;
						break;
					}
					else {
						break;
					}
				} 
			}
		}
	}
}

void group(vector<filmGroup> & a, string data) {
	int idx = 0;

	for (int i = 0; i < a.size(); i++) {
		a[i].group = data.substr(idx, data.find("|", idx + 1) - idx);
		idx = data.find("|", idx + 1) + 1;
	}
	for (int j = 0; j < a.size(); j++) {
		a[j].film = a[j].group.substr(0, a[j].group.find(";"));
	}
	for (int k = 0; k < a.size(); k++) {
		a[k].year = a[k].group.substr(a[k].group.find(";") + 1, a[k].group.rfind(";") - a[k].group.find(";") - 1);
	}
	for (int c = 0; c < a.size(); c++) {
		a[c].gen = a[c].group.substr(a[c].group.rfind(";") + 1);
	}
	for (int x = 0; x < a.size(); x++) {
		a[x].years = atoi(a[x].year);
	}
}

void choice1(vector<filmGroup> a, string genre) {
	vector<string> available_f;
	vector<string> available_g;
	vector<int> available_y;
	int count = 0;
	string genre1 = genre;
	ToLower(genre);
	for (int i = 0; i < a.size(); i++) {
		ToLower(a[i].gen);
		if (genre == a[i].gen) {
			available_f.push_back(a[i].film);
			available_y.push_back(a[i].years);
			available_g.push_back(a[i].gen);
			count++;
		}
	}
	if (count != 0) {
		sorter(available_y, available_f, available_g);

		cout << endl;
		cout << genre1 << " movies from newest to oldest:" << endl;
		for (int j = available_y.size() - 1; j >= 0; j--) {
			cout << "Movie name: " << available_f[j] << " Release Year: " << available_y[j] << endl;
		}
	}
	else {
		cout << endl;
		cout << "There are no " << genre1 << " movies!" << endl;
	}
} 

void choice2(vector<filmGroup> a, string range) {
	int year, year1, year2, count = 0, counter = 0;
	vector<string> available_f;
	vector<string> available_g;
	vector<int> available_y;

	for (int i = 0; i < range.size(); i++) {
		if (range.at(i) == '-') {
			count++;
		}
	}
	if (count == 1) {
		year1 = atoi(range.substr(0, range.find("-")));
		year2 = atoi(range.substr(range.find("-") + 1));
		for (int i = 0; i < a.size(); i++) {
			if (year1 <= a[i].years && a[i].years <= year2) {
				available_f.push_back(a[i].film);
				available_y.push_back(a[i].years);
				available_g.push_back(a[i].gen);
				counter++;
			}
		} 
		if (counter != 0) {
			sorter(available_y, available_f, available_g);
			cout << "Movies released between the years " << range << " from A to Z with decreasing year ordering:" << endl;
			for (int j = available_y.size() - 1; j >= 0; j--) {
				cout << "Movie name: " << available_f[j] << " Release Year: " << available_y[j] << " Genre: " << available_g[j] << endl;
			}	
		}
		else {
			cout << "There are no movies released between " << range << "!" << endl;
		}
	}
	else if (count == 0) {
		year = atoi(range);
		for (int i = 0; i < a.size(); i++) {
			if (year == a[i].years) {
				available_f.push_back(a[i].film);
				available_g.push_back(a[i].gen);
				available_y.push_back(a[i].years);
				counter++;
			}
		} 
		if (counter != 0) {
			sorter(available_y, available_f, available_g);
			cout << "Movies released in " << range << " from A to Z:" << endl;
			for (int j = available_y.size() - 1; j >= 0; j--) {
				cout << "Movie name: " << available_f[j] << " Genre: " << available_g[j] << endl;
			}
		}
		else {
			cout << "There are no movies released in " << range << "!" << endl;
		}
	} 
}	

void choice3(vector<filmGroup> a, int & b) {
	RandGen number;
	b = number.RandInt(0, a.size() - 1);
}

int main() {
	string database, genre, range;
	int choice, randnum = 0, count = 0;

	cout << "Welcome to the movie recommender program!" << endl << endl;
	cout << "Please enter the movie, year and genre list:" << endl;
	cin >> database;
	cout << endl;

	for (int i = 0; i < database.length(); i++) {
		if (database.at(i) == '|') {
			count++;
		}
	}

	vector<filmGroup> films(count + 1);
	group(films, database);

	cout << "Please select your action:" << endl;
	cout << "1. Select the genre of the movie that you want to watch" << endl;
	cout << "2. Select the year of the movie that you want to watch" << endl;
	cout << "3. Choose a random movie" << endl;
	cout << "4. Exit program" << endl << endl;
	cout << "Enter your choice: ";
	cin >> choice;

    while ((choice < 1) || (choice > 4)) {
		cout << "Invalid action!" << endl << endl;
		cout << "Enter your choice: ";
		cin >> choice;
	} 
	while (choice != 4) {
		while ((choice < 1) || (choice > 4)) {
			cout << "Invalid action!" << endl << endl;
			cout << "Enter your choice:	";
			cin >> choice;
		} 
		if (choice == 1) {
			cout << "Please enter the genre of the movie you want to watch: ";
			cin >> genre;
			choice1(films, genre);
			cout << endl;
		}
		else if (choice == 2) {
			cout << "Please enter the year of the movie you want to watch: ";
			cin >> range;
			choice2(films, range);
			cout << endl;
		}
		else if (choice == 3) {
			choice3(films, randnum);
			cout << "Movie name: " << films[randnum].film << " Release Year: " << films[randnum].years << " Genre: " << films[randnum].gen << endl << endl;
		}
		else if (choice == 4) {
			break;
		}
		cout << "Enter your choice: ";
		cin >> choice;
	}
	cout << "Thank you..." << endl;

	return 0;
} */


int main() {
	vector<int> steps(4);
	steps = {1, 1, 1, 1};

    RandGen rnd;
    int step = rnd.RandInt(1,4);
    int count = 0;

    while (count != 4) {
        bool check = false;
        for (int i = 0; i < steps.size(); i++) {
            if (steps[i] == step) {
                check = true;
                break;
            }
        }
        if (!check) {
            steps.push_back(step);
            count++;
        }
    }

    cout << steps[0] << " " << steps[1] << " " << steps[2] << " " << steps[3];

    return 0;
}