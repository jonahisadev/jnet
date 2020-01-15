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
#include <netdb.h>
#endif

#define MAX_BUFFER 65355

#ifdef OS_UNIX
typedef struct sockaddr_in NetworkDevice;
#endif

#define CLIENT_WAIT(client) while (client.isRunning())

namespace JNet {
    class UDPClient {
#ifdef OS_UNIX
    private:
        int _sock;
        bool _running;
        NetworkDevice _server;
        std::function<void(const std::string& msg)> _on_receive;
        
    public:
        UDPClient(const std::string& ip, int port, std::function<void(const std::string& msg)> on_receive);
        ~UDPClient();
        
        void start();
        void stop();
        void send(const std::string& msg);
        
        bool isRunning() const { return _running; }
#endif
    };
}