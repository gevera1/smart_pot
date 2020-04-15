#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	wiringPiSetup(); //
	softPwmCreate(0, 0, 255);
	for (int i = 0; i < 25; i++) {
		softPwmWrite(0, 100); delay(500);
		softPwmWrite(0, 0); delay(500);
		printf("loop %d\n",i+1);
	}
	digitalWrite(0, LOW);
	return 0;
}
