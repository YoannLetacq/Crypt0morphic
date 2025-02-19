#include <cassert>
#include <fstream>
#include <string>

#include "../src/obfuscator/obfuscator.h"
int main() {
    // --- Partie 1 : Test de la fonction XOR ---
    {
        Obfuscator obf("dummy");  // Le nom de fichier n'est pas utilisé ici.
        std::string original = "Test XOR encryption";
        char key = 'K';
        std::string encrypted = obf.xorEncryptDecrypt(original, key);
        std::string decrypted = obf.xorEncryptDecrypt(encrypted, key);
        assert(decrypted == original);
    }

    // --- Partie 2 : Test de l'obfuscation avec chiffrement ---
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

    // Appliquer l'obfuscation
    assert(obf.obfuscate() == true);

    // Vérifier que le fichier obfusqué contient bien le marqueur des blocs
    // encryptés
    std::ifstream in(testFile);
    std::string content((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());
    in.close();

    // Vérification de la présence du marqueur
    assert(content.find("ENCRYPTED_BLOCK_START") != std::string::npos);
    assert(content.find("ENCRYPTED_BLOCK_END") != std::string::npos);

    // Nettoyer le fichier de test et la sauvegarde
    std::remove(testFile.c_str());
    std::remove((testFile + ".bak").c_str());

    return 0;
}

