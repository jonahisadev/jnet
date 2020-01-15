#include "UdpClient.h"

namespace JNet {

    UDPClient::UDPClient(const std::string &ip, int port, std::function<void(const std::string &msg)> on_receive) 
        : _on_receive(on_receive)
    {
        struct hostent* he;
        he = gethostbyname(ip.c_str());
        
        if ((_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            throw "Bind failed";
        }
        
        memset(&_server, 0, sizeof(_server));
        _server.sin_family = AF_INET;
        _server.sin_port = htons(port);
        _server.sin_addr = *((struct in_addr*)he->h_addr);
        
        _running = false;
    }

    UDPClient::~UDPClient() {
        stop();
        close(_sock);
    }

    void UDPClient::start() {
        _running = true;
        char buffer[MAX_BUFFER];
        auto th = std::thread([&]() {
            while (_running) {
                socklen_t len;
                int n = recvfrom(_sock, (char*)buffer, MAX_BUFFER, MSG_WAITALL, 
                        (struct sockaddr*)&_server, &len);
                buffer[n] = '\0';
                _on_receive(std::string(buffer));
            }
        });
        th.detach();
    }

    void UDPClient::stop() {
        _running = false;
    }

    void UDPClient::send(const std::string &msg) {
        socklen_t len = sizeof(_server);
        sendto(_sock, msg.c_str(), msg.length(), MSG_CONFIRM | MSG_DONTWAIT, (const struct sockaddr*)&_server, len);
    }

}