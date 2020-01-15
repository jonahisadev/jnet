#include "UdpServer.h"

namespace JNet {
#ifdef OS_UNIX
    UDPServer::UDPServer(int port, std::function<void(struct sockaddr_in& client, std::string msg)> on_receive)
            : _port(port), _on_receive(on_receive) {
        if ((_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            throw "Socket creation failed";
        }
        
        memset(&_server, 0, sizeof(_server));
        _server.sin_family = AF_INET;
        _server.sin_addr.s_addr = INADDR_ANY;
        _server.sin_port = htons(port);
        
        if (bind(_sock, (const struct sockaddr*)&_server, sizeof(_server)) < 0) {
            throw "Bind failed";
        }
    }

    UDPServer::~UDPServer() {
        stop();
        close(_sock);
    }

    void UDPServer::start() {
        _running = true;
        auto th = std::thread([&]() {
            while (_running) {
                struct sockaddr_in client;
                size_t len = sizeof(client);
                memset(&client, 0, len);
                int n = recvfrom(_sock, (char*)_buffer, MAX_BUFFER, MSG_WAITALL,
                        (struct sockaddr*)&client, (socklen_t*)&len);
                _buffer[n] = '\0';
                _on_receive(client, std::string(_buffer));
            }
        });
        th.detach();
    }

    void UDPServer::stop() {
        _running = false;
    }

    void UDPServer::send(struct sockaddr_in& client, std::string msg) {
        socklen_t len = sizeof(client);
        sendto(_sock, msg.c_str(), msg.length(), MSG_CONFIRM | MSG_DONTWAIT, (const struct sockaddr*)&client, len);
    }

#endif
}