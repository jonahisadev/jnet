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

#ifdef OS_UNIX
typedef struct sockaddr_in NetworkDevice;
#endif

namespace JNet {
    class UDPServer {
#ifdef OS_UNIX
    private:
        int _sock;
        const int _port;
        char _buffer[MAX_BUFFER];
        NetworkDevice _server;
        bool _running = false;
        std::function<void(NetworkDevice& client, std::string msg)> _on_receive;

    public:
        UDPServer(int port, std::function<void(NetworkDevice& client, std::string msg)> on_receive);
        ~UDPServer();
        
        void start();
        void stop();
        void send(NetworkDevice& client, const std::string& msg);
        
        inline int getPort() const { return _port; }
        inline bool isRunning() const { return _running; }
#endif
    };
}