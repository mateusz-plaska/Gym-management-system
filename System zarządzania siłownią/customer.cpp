// Nie sprawdzam poprawnosci wprowadzanego numeru pesel, choc mozna byloby dodac takie funckje systemu
#include <iostream>
#include <vector>

#include "customer.h"
using namespace std;

Customer::Customer() : name(""), surname(""), age(0), pesel_number(""), phone_number(""), purchased_packages({})
{}

Customer::Customer(string input_name, string input_surname, int input_age, string input_pesel_number,
	string input_phone_number, vector<string> input_packages) : name(input_name), surname(input_surname),
	age(input_age), pesel_number(input_pesel_number), phone_number(input_phone_number), purchased_packages(input_packages)
{}

string Customer::get_name()
{
    return this->name;  // return name
}

string Customer::get_surname()
{
    return this->surname;
}

string Customer::get_age()
{
    return to_string(this->age);
}

string Customer::get_pesel_number()
{
    return this->pesel_number;
}

string Customer::get_phone_number()
{
    return this->phone_number;
}

vector<string> Customer::get_customer_packages()
{
    return this->purchased_packages;
}

void Customer::edit_customer_packages()
{
    int choice = 10;
    
    while (choice != 0)
    {
        cout << R"(
        Wybierz:
        1. Dodaj pakiet
        2. Usun pakiet
        0. Wyjdz z opcji edycji pakietow klienta)" << endl << endl;

        cout << "Twoj wybor : ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string package_name;
                
                cout << endl << "Podaj nazwe pakietu : ";
                cin.ignore();
                getline(cin, package_name);

                purchased_packages.push_back(package_name);
                cout << endl << endl << "Poprawnie dodano pakiet!" << endl << endl;

                break;
            }
            case 2:
            {
                int index_of_package_to_delete;

                cout << endl << "Podaj numer pakietu do usuniecia (Podaj 0 aby wyjsc z opcji usuwania pakietu) : "; // od 1 do ilosc pakietow
                cin >> index_of_package_to_delete;

                if (!index_of_package_to_delete)
                    break;

                purchased_packages.erase(purchased_packages.begin() + index_of_package_to_delete - 1);
                cout << endl << endl << "Usunieto pakiet!" << endl << endl;

                break;
            }
        }
    }
}

void Customer::edit_customer(int customer_number)
{
    int choice = 10;
    
    while (choice != 0)
    {
        show_customer_details(customer_number);

        cout << endl << "\t" << "0. Wyjdz z opcji edycji klienta" << endl << endl;

        cout << endl << "Twoj wybor : ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                string new_name;
                cout << endl << "Podaj nowe imie : ";
                cin.ignore();
                getline(cin, new_name);

                name = new_name;  // this->name = new_name

                cout << endl << "Imie klienta zostalo edytowane poprawnie!" << endl;

                break;
            }
            case 2:
            {
                string new_surname;
                cout << endl << "Podaj nowe nazwisko : ";
                cin.ignore();
                getline(cin, new_surname);

                surname = new_surname;

                cout << endl << "Nazwisko klienta zostalo edytowane poprawnie!" << endl;

                break;
            }
            case 3:
            {
                int new_age;
                cout << endl << "Podaj nowy wiek : ";
                cin >> new_age;

                age = new_age;

                cout << endl << "Wiek klienta zostal edytowany poprawnie!" << endl;

                break;
            }
            case 4:
            {
                string new_pesel;
                cout << endl << "Podaj nowy numer PESEL : ";
                cin >> new_pesel;

                pesel_number = new_pesel;

                cout << endl << "Numer PESEL klienta zostal edytowany poprawnie!" << endl;

                break;
            }
            case 5:
            {
                string new_phone_number;
                cout << endl << "Podaj nowy numer telefonu : ";
                cin.ignore();
                getline(cin, new_phone_number);

                phone_number = new_phone_number;

                cout << endl << "Numer telefonu klienta zostal edytowany poprawnie!" << endl;

                break;
            }
            case 6:
            {
                cout << endl << "**** Edycja pakietow klienta ****" << endl << endl;

                edit_customer_packages();

                break;
            }
        }
    } 
}

void Customer::show_customer_details(int customer_number)
{
	cout << endl << "\t" << "Klient nr. " << customer_number << " : " << endl << endl;

    cout <<
        "\t" << "1. Imie : " << name << endl <<
        "\t" << "2. Nazwisko : " << surname << endl <<
        "\t" << "3. Wiek : " << age << endl <<
        "\t" << "4. Numer PESEL : " << pesel_number << endl <<
        "\t" << "5. Numer telefonu : " << phone_number << endl <<
        "\t" << "6. Wykupione pakiety : " << endl;

    int it = 1;
    for (auto elem : purchased_packages)
    {
        cout << "\t" << "\t" << it << ". " << elem << endl;
        it++;
    }
}