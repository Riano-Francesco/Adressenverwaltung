#include "Funktionen.h"
#include "Database.h"

using namespace std;

bool abbruch = false;
bool wiederholung()
{
	cout << "Wiederholen ? 0 = Abbruch | 1 = Wiederholen" << endl;
	cin >> abbruch;

	return abbruch;
}

void run()
{
	cout << "Willkommen in der Adressverwaltung\n";
	cout << "Bitte geben sie das Passwort ein: ";

	string password;
	cin >> password;

	Database DB;

	for (int i = 1; i >= 0; i--) {
		if (password == "123") {
			cout << "Passwort korrekt!\n\n";
			DB.menu();
			break;
		}
		else {
			cout << "Passwort falsch - bitte erneut Versuchen: ";
			cin >> password;
		}
		while (i == 0) {
			cout << "Passwort wurde 3 mal Falsch eingegeben!\n";
			exit(0);
		}
	}
}