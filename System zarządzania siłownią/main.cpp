// System zarządzania siłownią.cpp 
// Nie zaglebialem sie w dokladne sprawdzanie poprawnosci danych wejsciowych i ewentualne w zwiazku z tym 
// komunikaty oraz rzucanie wyjatkow - wystapia bledy przy niepoprwanym podaniu danych (znaki do inta,boola)
#include <iostream>

#include "gym_management_system.h"
using namespace std;

void clear_screen()
{
	system("cls"); // Windows

	// POSIX :  system("clear");
}

int main()
{
	system("color 3a"); // pokazowo; dziala na Windows, system() nie jest dobra opcja jednak nie zaglebialem sie w zmiane kolorow outputu w konsoli

	Gym_management_system gym_system;

	int selected_action;

	while (1)
	{
		clear_screen();
		gym_system.print_headline();
		gym_system.print_menu();

		cin >> selected_action;

		if (!selected_action)
			break;

		char temp;
		switch (selected_action)
		{
			case 1:
			{
				clear_screen();
				gym_system.print_headline();

				gym_system.show_customer_list();

				cout << endl << endl << "\t" << "Wprowadz dowolny klawisz aby wrocic do menu : ";
				cin >> temp;

				break;
			}
			case 2:
			{
				clear_screen();
				gym_system.print_headline();

				gym_system.add_customer();

				cout << endl << "\t" << "Wprowadz dowolny klawisz aby wrocic do menu : ";
				cin >> temp;

				// gym_system.save_data(); mozna po kazdej dokonanej zmianie zapisywac dane

				break;
			}
			case 3:
			{
				clear_screen();
				gym_system.print_headline();

				gym_system.edit_selected_customer();

				cout << endl << "\t" << "Wprowadz dowolny klawisz aby wrocic do menu : ";
				cin >> temp;

				// gym_system.save_data(); mozna po kazdej dokonanej zmianie zapisywac dane

				break;
			}
			case 4:
			{
				clear_screen();
				gym_system.print_headline();

				gym_system.delete_selected_customer();

				cout << endl << "\t" << "Wprowadz dowolny klawisz aby wrocic do menu : ";
				cin >> temp;

				// gym_system.save_data(); mozna po kazdej dokonanej zmianie zapisywac dane

				break;
			}
			case 5:
			{
				clear_screen();
				gym_system.print_headline();

				gym_system.show_details_of_selected_customer();

				cout << endl << "\t" << "Wprowadz dowolny klawisz aby wrocic do menu : ";
				cin >> temp;

				break;
			}
		}
	}

	return 0;
}
