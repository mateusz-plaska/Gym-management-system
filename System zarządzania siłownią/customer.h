#pragma once

#include <string>
#include <vector>

class Customer
{
public:
	Customer();
	Customer(std::string input_name, std::string input_surname, int input_age, std::string input_pesel_number,
		std::string input_phone_number, std::vector<std::string> input_packages = {});

	std::string get_name();
	std::string get_surname();
	std::string get_age();
	std::string get_pesel_number();
	std::string get_phone_number();
	std::vector<std::string> get_customer_packages();

	void edit_customer_packages();
	void edit_customer(int customer_number);
	void show_customer_details(int customer_number);
private:
	std::string name;
	std::string surname;
	int age;
	std::string pesel_number;
	std::string phone_number;
	std::vector<std::string> purchased_packages;
};