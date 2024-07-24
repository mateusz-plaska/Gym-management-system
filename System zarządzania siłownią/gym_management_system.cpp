#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "gym_management_system.h"

using namespace std;

Gym_management_system::Gym_management_system()
{
    load_data();
}

Gym_management_system::~Gym_management_system()
{
    save_data();
}

void Gym_management_system::print_headline()
{
    cout << R"(
    ***************************************
    System zarzadzania silownia
    ***************************************
                                           )" << endl;
}

void Gym_management_system::print_menu()
{
    cout << R"(
    Wybierz:
    1. Pokaz liste klientow
    2. Dodanie klienta
    3. Edytuj klienta
    4. Usun klienta
    5. Pokaz szczegolowe informacje klienta
    0. Zakoncz dzialanie systemu
        Twoj wybor : )";
}

void Gym_management_system::add_customer()
{
    string name, surname, pesel_numb, phone_numb, package_name = " ";
    int age;
    bool if_package_purchased;
    vector<string> customer_packages{};

    cout << "\t" << "***** DODAWANIE KLIENTA *****" << endl << endl;
    
    cout << "Podaj imie klienta : ";
    cin.ignore();
    getline(cin, name);

    cout << "Podaj nazwisko klienta : ";
    getline(cin, surname);

    cout << "Podaj wiek : ";
    cin >> age;

    cout << "Podaj numer PESEL : ";
    cin >> pesel_numb;

    cout << "Podaj numer telefonu : ";
    cin.ignore();
    getline(cin, phone_numb);

    while (1)
    {
        cout << endl << "Dodac pakiet? (Podaj 1-tak, 0-nie) : ";
        cin >> if_package_purchased;

        if (!if_package_purchased)
            break;

        cout << endl << "Podaj nazwe pakietu : ";
        cin.ignore();
        getline(cin, package_name);

        customer_packages.push_back(package_name);
    }

    Customer new_client(name, surname, age, pesel_numb, phone_numb, customer_packages);

    gyms_customers.push_back(new_client);

    cout << endl << endl << "Dodano nowego klienta!" << endl << endl;
}

void Gym_management_system::delete_selected_customer()
{
    int selected_customer;

    cout << "\t" << "***** USUWANIE KLIENTA *****" << endl << endl;

    show_customer_list();

    cout << endl << "Podaj numer klienta do usuniecia (Podaj 0 aby wyjsc z tej opcji) : ";
    cin >> selected_customer;

    if (!selected_customer)
        return;

    gyms_customers.erase(gyms_customers.begin() + selected_customer - 1);

    cout << endl << endl << "Usunieto klienta" << endl << endl;
}

void Gym_management_system::edit_selected_customer()
{
    int selected_customer;

    cout << "\t" << "***** EDYCJA KLIENTA *****" << endl << endl;

    show_customer_list();

    cout << endl << "Podaj numer klienta do edycji (Podaj 0 aby wyjsc z tej opcji) : ";
    cin >> selected_customer;

    if (!selected_customer)
        return;

    gyms_customers[selected_customer - 1].edit_customer(selected_customer);
}

string create_output_text_to_table(string name, string surname, string phone_number, int index) 
{
    // imie : 20, nazwisko : 25, nr_tel : 11(ze spacjami), index : 5 (4 + spacja) (3 cyfrowa mozliwa liczba potem kropka i spacja)
    string result = "";

    if (index)
    {
        result += to_string(index);
        result += '. ';
    }

    int amount_of_spaces_to_add = 5 - result.length();
    result += string(amount_of_spaces_to_add, ' ');

    amount_of_spaces_to_add = 20 - name.length();
    result += name;
    result += string(amount_of_spaces_to_add, ' ');

    amount_of_spaces_to_add = 25 - surname.length();
    result += surname;
    result += string(amount_of_spaces_to_add, ' ');

    result += phone_number;

    return result;
}

void Gym_management_system::show_customer_list()
{
    cout << endl << endl << "\t" << "*** Lista klientow ***" << endl << endl;

    cout << "\t" << create_output_text_to_table("Imie", "Nazwisko", "Numer telefonu") << endl << endl;

    int it = 1;
    for (auto elem : gyms_customers)
    {
        cout << "\t" << create_output_text_to_table(elem.get_name(), elem.get_surname(), elem.get_phone_number(), it) << endl;
        it++;
    }
}

void Gym_management_system::show_details_of_selected_customer()
{
    int selected_customer;

    show_customer_list();

    cout << endl << "Podaj numer wybranego klienta (Podaj 0 aby wyjsc z tej opcji) : ";
    cin >> selected_customer;

    if (!selected_customer)
        return;

    gyms_customers[selected_customer - 1].show_customer_details(selected_customer);
}

void Gym_management_system::load_data()
{
    ifstream load_data_from_file("database.txt");
    if (!load_data_from_file)                       // nie istnieje taki plik
        return;                                     // w przypadku pierwszego odpalenia plik nie istnieje nie ma co wczytywac

    while (!load_data_from_file.eof())
    {
        string row;

        getline(load_data_from_file, row);

        if (row == "")          // ostatnia linia z pliku jest wcztywana choc jest pusta
            break;

        string data[6]{};
        string name, surname, pesel_numb, phone_numb;
        int age;
        vector<string> packages;

        int data_index = 0;

        for (int i = 0; i < row.length(); ++i)
        {
            if (row[i] == '|') // separator danych
            {
                data_index++;
                continue;
            }
            data[data_index] += row[i];
        }

        name = data[0];
        surname = data[1];
        age = stoi(data[2]);
        pesel_numb = data[3];
        phone_numb = data[4];

        string temp = "";

        for (int i = 0; i < data[5].length(); ++i)
        {
            if (data[5][i] == ';') // separator pakietow
            {
                packages.push_back(temp);
                temp = "";
                continue;
            }
            temp += data[5][i];
        }

        Customer client(name, surname, age, pesel_numb, phone_numb, packages);

        gyms_customers.push_back(client); 
    }
}

void Gym_management_system::save_data()
{
    ofstream save_data_to_file("database.txt", ios::out | ios::trunc);

    for (auto client : gyms_customers)
    {
        string row, packages_as_string = "";

        for (auto package : client.get_customer_packages())
        {
            packages_as_string += package + ';';
        }

        row = client.get_name() + '|' + client.get_surname() + '|' + client.get_age() + '|' + client.get_pesel_number() + '|' +
            client.get_phone_number() + '|' + packages_as_string;

        save_data_to_file << row << endl;
    }
}