#pragma once

#include <vector>
#include <string>

#include "customer.h"

std::string create_output_text_to_table(std::string name, std::string surname, std::string phone_number, int index = 0);

class Gym_management_system
{
public:
	Gym_management_system();
	~Gym_management_system();

	void print_headline();
	void print_menu();

	void add_customer();
	void delete_selected_customer();
	void edit_selected_customer();
	void show_customer_list();
	void show_details_of_selected_customer();

	void load_data(); // wczytac dane z pliku txt do vectora gyms_customers
	void save_data();
private:
	std::vector<Customer> gyms_customers;
};