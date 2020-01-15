#include <iostream>
#include "../UdpServer.h"

std::string to_upper(std::string str) {
	std::string res = "";
	for (int i = 0; i < str.length(); i++) {
		char c = str.at(i);
		if (c >= 'a' && c <= 'z')
			res += c - 32;
		else
			res += c;
	}
	return std::string(res);
}

int main()
{
	JNet::UDPServer server(12098, [&](struct sockaddr_in& client, std::string msg) {
		std::cout << msg << std::endl;
		server.send(client, to_upper(msg));
	});
	server.start();

	std::cout << "Started server on port " << server.getPort() << std::endl;
	
	std::string line;
	while (true) {
		std::cout << "> ";
		std::getline(std::cin, line);
		if (line == "exit") {
			server.stop();
			break;
		}

		std::cout << "[SERVER] " << line << std::endl;
	}

	return 0;
}