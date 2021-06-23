#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// For input
#include <SFML/Graphics.hpp>


#include <iostream>
#include <fstream>

using namespace std;

#define PORT 8080

bool codes[1000];

int send_int(int fd, int value)
{
	static int x;

	x = value;

	return send(fd, &x, sizeof(int), 0);
}

using namespace sf;

int main()
{
	string ip;
	int port;

	cout << "Enter IP address (of PI): ";
	cin >> ip;

	// cout << "Enter port"

	int sock = 0, valread;
	sockaddr_in serv_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0)  {
		printf("Error: Invalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Error: Connection Failed \n");
		return -1;
	}

	// TODO: display statistics
	cout << "Connected." << endl;

	// Main loop
	while (true) {
		int sig = 0;

		// Checking input (splitting into mutually exclusive pairs of control)
		if (Keyboard::isKeyPressed(Keyboard::Space))
			sig |= 0b10000;
		else if (Keyboard::isKeyPressed(Keyboard::Up))
			sig |= 0b1;
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			sig |= 0b10;
		
		if (Keyboard::isKeyPressed(Keyboard::Right))
			sig |= 0b100;
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			sig |= 0b1000;
		
		// Check quit
		if (Keyboard::isKeyPressed(Keyboard::Q))
			break;

		// TODO: add brake
		if (sig) {
			cout << "sig = " << sig << endl;
			send_int(sock, sig);
		}

		// Some delay
		usleep(100);
	}

	send_int(sock, -1);

	// Ending
	return 0;
}
