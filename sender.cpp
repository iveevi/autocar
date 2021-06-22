#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

#include <iostream>
#include <fstream>

using namespace std;

#define PORT 8080

int send_int(int fd, int value)
{
	static int x;

	x = value;

	return send(fd, &x, sizeof(int), 0);
}

int main()
{
	// Setup ncurses
	initscr();
	clear();
	noecho();
	cbreak();

	keypad(stdscr, TRUE);

	int sock = 0, valread;
	sockaddr_in serv_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)  {
		endwin();

		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		endwin();

		printf("\nConnection Failed \n");
		return -1;
	}

	// Entry message
	printw("Type input: ");

	int c;
	bool quit = false;
	do {
		c = getch();
		switch (c) {
		case KEY_UP:
			send_int(sock, 1);
			break;
		case KEY_DOWN:
			send_int(sock, 2);
			break;
		case KEY_LEFT:
			send_int(sock, 3);
			break;
		case KEY_RIGHT:
			send_int(sock, 4);
			break;
		case 'q':
			quit = true;
			break;
		}
	} while (!quit);

	send_int(sock, -1);
	endwin();

	return 0;
}
