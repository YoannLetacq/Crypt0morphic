#ifndef OBFUSCATOR_H
#define OBFUSCATOR_H

#include <string>
#include <vector>

class Obfuscator {
   public:
    // Constrcteur recevant la source à obfusquer
    Obfuscator(const std::string &sourceFile);

    // Applique l'obfuscation
    bool obfuscate();

    // Methode pour tester le chiffrement XOR
    std::string xorEncryptDecrypt(const std::string &input, char key);

    // Restaure le fichier depuis la sauvegarde
    // pulbic to restore main file after obfuscation (educational purpose)
    bool restoreBackup();

   private:
    // Chemin du fichier source
    std::string sourceFilePath;
    // Sauvegarde le fichier original dans un sourceFilePath + ".bak"
    bool backupOriginal();

    // Lit le contenu du fichier source et le retourne sous forme de string
    bool readSource(std::string &content);

    // Analyse le contenu et retourne les blocs de fonction delimiter par les
    // marqueurs
    std::vector<std::string> extractFunctionsBlocks(
        const std::string &fileContent);

    // Reordonne aléatoirement les blocs extraits
    std::vector<std::string> reorderBlocks(
        const std::vector<std::string> &blocks);

    // Reecrit le fichier source avec les blocs reordonnés
    bool writeObfuscatedFile(const std::vector<std::string> &blocks,
                             const std::string &originalContent);
};

#endif  // OBFUSCATOR_H

