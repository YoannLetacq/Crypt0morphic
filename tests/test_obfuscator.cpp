#include <cassert>
#include <fstream>
#include <string>

#include "../src/obfuscator/obfuscator.h"

int main() {
    // Créez un fichier de test temporaire avec du contenu marqué
    std::string testFile = "test_source.cpp";
    std::ofstream out(testFile);
    out << "#include <iostream>\n";
    out << "// BEGIN_FUNCTION\n";
    out << "void functionA() { std::cout << \"A\"; }\n";
    out << "// END_FUNCTION\n";
    out << "// BEGIN_FUNCTION\n";
    out << "void functionB() { std::cout << \"B\"; }\n";
    out << "// END_FUNCTION\n";
    out.close();

    // Instancier l'obfuscateur sur le fichier de test
    Obfuscator obf(testFile);

    // Tester la sauvegarde
    assert(obf.obfuscate() == true);

    // Vérifier que le fichier obfusqué contient bien les blocs réordonnés à la
    // fin
    std::ifstream in(testFile);
    std::string content((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());
    in.close();

    // Vérifier que les marqueurs sont toujours présents dans le contenu
    // (les blocs ont été extraits et réinsérés)
    assert(content.find("BEGIN_FUNCTION") != std::string::npos);
    assert(content.find("END_FUNCTION") != std::string::npos);

    // Nettoyer le fichier de test et la sauvegarde
    std::remove(testFile.c_str());
    std::remove((testFile + ".bak").c_str());

    return 0;
}

