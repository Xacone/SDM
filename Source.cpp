#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int ContactIpAddresses(string ip_addr, string port) {

	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct addrinfo* result = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	ret = getaddrinfo(ip_addr.c_str(), port.c_str(), &hints, &result);
	ret = connect(sockfd, result->ai_addr, (int)result->ai_addrlen);

	freeaddrinfo(result);
	closesocket(sockfd);
	WSACleanup();

	return 0;
}


int main() {

	vector<string> tor_nodes_5_5_23 {"161.97.166.49", "162.19.171.180", "162.19.230.56", "162.212.158.82", "162.250.191.15", "162.250.191.15", "163.172.94.144", "163.172.94.144", "167.114.36.23", "167.114.36.23", "167.114.36.23"};
	const int tor_nodes_5_5_23_s = 11;
	thread threads[tor_nodes_5_5_23_s];
	
	for (int i = 0; i < tor_nodes_5_5_23_s; i++) {
		threads[i] = thread(ContactIpAddresses, tor_nodes_5_5_23[i], to_string(7777));
	}

	for (int i = 0; i < tor_nodes_5_5_23_s; i++) {
		threads[i].join();
	}


	return 0;
}