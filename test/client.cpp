#include <iostream>
#include "../UdpClient.h"

int main()
{
	JNet::UDPClient client("127.0.0.1", 12098, [&](const std::string& msg) {
		std::cout << "From server: " << msg << std::endl;
		client.stop();
	});
	client.start();
	client.send("Hello server!");

	CLIENT_WAIT(client);

	return 0;
}