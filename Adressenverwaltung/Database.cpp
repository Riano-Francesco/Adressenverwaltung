#include "Database.h"

void Database::menu() {
	if (data.empty()) {
		cout << "Welche Datei soll geöffnet werden? -> ";
		choosefile();
	}

	cout << "1. Neue Adresse hinzufügen -> " << endl;
	cout << "2. Adresse Suchen          -> " << endl;
	cout << "3. Adresse Löschen         -> " << endl;

	int choose = 0;
	cin >> choose;

	switch (choose) {
	case 1:
		toGet();
		break;

	case 2:
		show();
		break;

	case 3:
		remove();
		break;

	default:
		menu();
	}
}

void Database::choosefile() {
	cout << "Bitte geben sie den Namen der Datei ein: ";
	cin >> filename;

	filename += ".csv";

	ifstream file(filename);
	if (file.good()) { // checkt ob datei existiert
		cout << "Datei gefunden.\n\n";
		load();    // zeiger auf ein Objekt
	}
	else {
		ofstream file(filename);
	}
	
}

void Database::toGet() {

	int anzahl = 0;
	cout << "Wie viele Personen sollen gespeichert werden? -> ";
	cin >> anzahl;

	for (int i = 1; i < anzahl + 1; i++) {

		vector < string > temp;
		string vname;
		string nname;
		string strasse;
		string ort;
		string plz;

		cout << "Bitte Vornamen eingeben: ";
		cin >> vname;
		vname = vname;
		temp.push_back(vname);

		cout << "Bitte Nachnamen eingeben: ";
		cin >> nname;
		nname = nname;
		temp.push_back(nname);

		cout << "Bitte Strasse eingeben: ";
		cin >> strasse;
		strasse = strasse;
		temp.push_back(strasse);

		cout << "Bitte Ort eingeben: ";
		cin >> ort;
		ort = ort;
		temp.push_back(ort);

		cout << "Bitte Postleitzahl eingeben: ";
		cin >> plz;
		plz = plz;
		temp.push_back(plz);
		cout << "Daten wurden hinzugefügt.\n\n";

		data.push_back(temp);
	}
	save();
}

void Database::save() {
	ofstream file(filename);
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size(); j++) {
			file << data[i][j];
			if (j < data[0].size() - 1) {
				file << ",";
			}
		}
		file << "\n";
	}
}

void Database::load() {
	ifstream file(filename);
	string zeile;

	while (getline(file, zeile)) {
		vector < string > temp;
		string item;

		for (int i = 0; i < zeile.size(); i++) {
			if (zeile[i] != ',') {
				item += zeile[i];
			}
			else {
				temp.push_back(item); // Speichert hier zelle für zelle
				item = "";
			}
		}
		temp.push_back(item);
		data.push_back(temp);
		// getter.erase(getter.begin(), getter.end());
	}
}

void Database::show() {
	string search;
	cout << "Bitte geben Sie den Nachnamen ein: ";
	cin >> search;

	this->search(search);
}

int Database::search(const string& search) {
	vector < int > matches;

	for (int i = 0; i < data.size(); i++) {
		if (search.substr(0, 2) == data[i][1].substr(0, 2)) {  // substr(0, 2) -> 0 beginnt er, 2 ist die zweite stelle == data[i][1] -> i = durchlauf & 1 gleiche zweite stelle 
			matches.push_back(i);
		}
	}
	if (matches.empty()) {
		cout << "Kein Eintrag gefunden.";
		return -1;
	}
	if (matches.size() == 1) {
		int i = matches[0];
		cout << "Eintrag wurde gefunden.";
		cout << "Vorname: " << data[i][0] << endl;
		cout << "Nachname: " << data[i][1] << endl;
		cout << "Strasse: " << data[i][2] << endl;
		cout << "Ort: " << data[i][3] << endl;
		cout << "Postleitzahl: " << data[i][4] << endl;
		return i;
	}
	else {
		cout << matches.size() << " Einträge gefunden!" << endl << endl;
		for (int i = 0; i < matches.size(); i++) {
			int j = matches[i];
			cout << i + 1 << " Ausgabe: " << data[j][0] << " " << data[j][1] << endl;
		}
		int option = 0;
		cout << "\nWelchen Eintrag wollen Sie einsehen? -> ";
		cin >> option;
		cout << endl;

		int i = matches[option - 1]; // um bei postition 0 zu beginnen 
		cout << "Gewählte Ausgabe:" << endl;
		cout << "Vorname: " << data[i][0] << endl;
		cout << "Nachname: " << data[i][1] << endl;
		cout << "Strasse: " << data[i][2] << endl;
		cout << "Ort: " << data[i][3] << endl;
		cout << "Postleitzahl: " << data[i][4] << endl;
		return i;
	}
}


void Database::remove() {
	string search;
	cout << "Geben Sie einen Nachnamen ein. -> ";
	cin >> search;

	int i = this->search(search);  // In dem Fall wichtig zeiger auf methode mit gleichnamigen Rückgabewert. so lange man im Objekt ist, ist der zeiger nicht notwendig!

	data.erase(data.begin() + i); // Löscht den Eintrag der gewählt wurde
	cout << "Eintrag wurde gelöscht.\n";
	save();
}