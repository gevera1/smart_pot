#include <chrono>
#include <thread>
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

void water( int w, int w_f ) {
	std::chrono::seconds interval( 10 - w_f );
	system("echo 'Begin Watering...\n'");
	for (int i = 0; i < 2; i++) {
		softPwmWrite(pump, 100); delay(w);
		softPwmWrite(pump, 0); delay(20);
		std::this_thread::sleep_for( interval );
	}
	std::cout << "Done watering.\n\n";
}

void light( int l, int l_f ) {
	std::chrono::seconds interval( 10 - l_f);
	system("echo 'Adjusting LEDs...\n'");
	for (int j = 0; j < 2; j++) {
		softPwmWrite(led, 100); delay(l);
		softPwmWrite(led, 0); delay(20);
		std::this_thread::sleep_for( interval );
	}
	system("echo 'LEDs Adjusted.\n\n'");
}

int main(int argc, char* argv[]) {
	setup();

	int id  = std::stoi(argv[1]);
	int water_int = std::stoi(argv[2])*100;
	int light_int = std::stoi(argv[3])*100;
	int water_freq = std::stoi(argv[4]);
	int light_freq = std::stoi(argv[5]);

	std::string fname = std::to_string(id) + ".txt";
	std::string command = "cat " + fname;

	// Output display
	system("echo 'Making adjustments...\n\n'");
	system(command.c_str());
	
	// Multi-threading
	std::thread first(water, water_int, water_freq);
	std::thread second(light, light_int, light_freq);

	// Begin timing
	auto start = std::chrono::high_resolution_clock::now();	

	// Watering
	// Adjusting lights
	
	// Synchronize threads
	first.join();
	second.join();

	// Finish timing
	auto finish = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Process duration: " << elapsed.count() << " sec.\n";
	
	return 0;
}
