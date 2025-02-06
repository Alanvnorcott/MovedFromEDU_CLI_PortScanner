#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

void scanPort(const std::string &ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed.\n";
        return;
    }

    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &target.sin_addr);

    if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
        std::cout << "Port " << port << " is open.\n";
    }

    close(sock);
}

int main() {
    std::string ip;
    int startPort, endPort;

    std::cout << "Enter target IP: ";
    std::cin >> ip;
    std::cout << "Enter start port: ";
    std::cin >> startPort;
    std::cout << "Enter end port: ";
    std::cin >> endPort;

    for (int port = startPort; port <= endPort; ++port) {
        scanPort(ip, port);
    }

    return 0;
}
