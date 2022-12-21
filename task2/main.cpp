#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void task1() {
	FILE *fp;
	char line[1024];

	fp = popen("sysctl -a", "r");
	if (fp == NULL) {
		std::cerr << "Failed to run command" << std::endl;
		return;
	}

	while (fgets(line, sizeof(line)-1, fp)) {
		if (strstr(line, "hw.l1dcachesize")) {
			std::cout << line;
		}
		if (strstr(line, "hw.l2cachesize")) {
			std::cout << line;
		}
	}

	pclose(fp);
}

void time(std::string str, std::function<void()> f) {
	struct timespec start, stop;

	clock_gettime(CLOCK_REALTIME, &start);
	f();
	clock_gettime(CLOCK_REALTIME, &stop);

	auto time = (stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec ) / 1000000000.;
	std::cout << str << ": " << time << std::endl;
}

void task2(volatile int k) {
	time("Basic sleep", []() {
		sleep(1);
	});
	
	time("Linear array", [k]() {
		int a[k];
		for (int i = 0; i < k; i++)
			++a[i];
	});

	time("Cache line array", [k]() {
		int a[k];
		
	});
}

int main( int argc, char *argv[] ) {
	task2(227);
	return 0;
}
