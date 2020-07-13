
#include "../src/ngsd.h"

#include <iostream>
#include <iomanip>
#include <fstream>

void addJSON() {
	ngsd::json j;
	//ngsd::Material m;
	//ngsd::to_json(j, m);

	ngsd::Sampler s;

	j = s;

	std::string str = j.dump();

	std::cout << str << std::endl;

	std::ofstream o("test.ngsd");
	o << std::setw(4) << j << std::endl;
}



int main() {
	addJSON();
}