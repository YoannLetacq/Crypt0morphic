#ifndef REVERSE_SHELL_H
#define REVERSE_SHELL_H

#include <string>

class ReverseShell {
   public:
    // Initialise le constructeur avec l'addresse IP et le PORT
    ReverseShell(const std::string &ip, int port);

    // lance le reverse shell
    bool launch();

    // retourne le commande construite
    std ::string getCommand() const;

   private:
    std::string ipAddress;
    int port;
};

#endif  // REVERSE_SHELL_H

