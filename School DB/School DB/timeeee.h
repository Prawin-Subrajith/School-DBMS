#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;
time_t my_time = time(NULL);

class timer {
public:
	string time = ctime(&my_time);
};

void time() {
	fstream file("log.dat", ios::binary || ios::out);
	timer X;

	while (!file.eof()) {
		file.write((char*)&X, sizeof(X));
	}

	file.close();
}