#pragma once
#include <iostream>
#include <locale>  // Passt UTF an Sprache des Systems an
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Database {
public:
	void menu();
	void toGet();
	void choosefile();
	void save();
	void load();
	void show();
	int search(const string&);
	void remove();

private:
	vector < vector < string >> data; // Wird nur hier gesetzt und ist dann überall als "data" verfügbar
	string filename;
};