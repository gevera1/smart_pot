#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>

#define pump 0
#define led 1

void setup( void ) {
	wiringPiSetup();
	softPwmCreate(pump, 0, 100);
	softPwmCreate(led, 0, 100); 		
}

int main(int argc, char* argv[]) {
	setup();

	int id  = std::stoi(argv[1]);
	int water_int = std::stoi(argv[2]);
	int light_int = std::stoi(argv[3]);
	int water_freq = std::stoi(argv[4]);
	int light_freq = std::stoi(argv[5]);

	std::string fname = std::to_string(id) + ".txt";
	std::string command = "cat " + fname;
	system(command.c_str());
	system("echo 'Watering...\n'");
	delay(20);
	for (int i = 0; i < water_freq*5; i++) {
		softPwmWrite(pump, water_int); delay(950);
		softPwmWrite(pump, 0); delay(50);
	}
	system("echo 'Done watering.\n'");
	delay(50);
	system("echo 'Adjusting LEDs...\n'");
	delay(20);
	for (int i = 0; i < light_freq*5; i++) {
		softPwmWrite(led, light_int); delay(450);
		softPwmWrite(led, 0); delay(50);
	}
	std::cout << "LEDs adjusted.\n\n";
	
	
	return 0;
}
