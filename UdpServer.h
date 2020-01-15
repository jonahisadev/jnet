#pragma once

#include "os.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <functional>

#ifdef OS_UNIX
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

#define MAX_BUFFER 65355

namespace JNet {
    class UDPServer {
#ifdef OS_UNIX
    private:
        int _sock;
        const int _port;
        char _buffer[MAX_BUFFER];
        struct sockaddr_in _server;
        bool _running = false;
        std::function<void(struct sockaddr_in& client, std::string msg)> _on_receive;

    public:
        UDPServer(int port, std::function<void(struct sockaddr_in& client, std::string msg)> on_receive);
        ~UDPServer();
        
        void start();
        void stop();
        void send(struct sockaddr_in& client, std::string msg);
        
        inline int getPort() { return _port; }

#endif
    };
}