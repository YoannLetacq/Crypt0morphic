#include "obfuscator.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

Obfuscator::Obfuscator(const std::string &sourceFile)
    : sourceFilePath(sourceFile) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

bool Obfuscator::backupOriginal() {
    std::ifstream in(sourceFilePath);
    if (!in) {
        std::cerr << "Impossible d'ouvrir le fichier source" << std::endl;
        return false;
    }

    std::ofstream out(sourceFilePath + ".bak");
    if (!out) {
        std::cerr << "Impossible de creer le fichier de sauvegarde"
                  << std::endl;
        return false;
    }
    out << in.rdbuf();
    return true;
}

bool Obfuscator::restoreBackup() {
    std::ifstream in(sourceFilePath + ".bak");
    if (!in.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier de sauvegarde"
                  << std::endl;
        return false;
    }

    std::ofstream out(sourceFilePath);
    if (!out.is_open()) {
        std::cerr << "Impossible de restaurer le fichier original" << std::endl;
        return false;
    }
    out << in.rdbuf();
    return true;
}

bool Obfuscator::readSource(std::string &content) {
    std::ifstream in(sourceFilePath);
    if (!in.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier source" << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << in.rdbuf();
    content = buffer.str();
    return true;
}

std::vector<std::string> Obfuscator::extractFunctionsBlocks(
    const std::string &fileContent) {
    std::vector<std::string> blocks;
    std::stringstream iss(fileContent);
    std::string line;
    bool inBlock = false;
    std::string currentBlock;

    while (std::getline(iss, line)) {
        if (line.find("// BEGIN_FUNCTION") != std::string::npos) {
            inBlock = true;
            currentBlock = line + "\n";
        } else if (line.find("// END_FUNCTION") != std::string::npos &&
                   inBlock) {
            currentBlock += line + "\n";
            blocks.push_back(currentBlock);
            inBlock = false;
        } else if (inBlock) {
            currentBlock += line + "\n";
        }
    }
    return blocks;
}

std::vector<std::string> Obfuscator::reorderBlocks(
    const std::vector<std::string> &blocks) {
    std::vector<std::string> reordered = blocks;

    std::shuffle(reordered.begin(), reordered.end(),
                 std::mt19937{std::random_device{}()});
    return reordered;
}

bool Obfuscator::writeObfuscatedFile(const std::vector<std::string> &blocks,
                                     const std::string &originalContent) {
    std::string obfuscatedContent = originalContent;

    for (const auto &block : blocks) {
        size_t pos = obfuscatedContent.find(block);
        if (pos != std::string::npos) {
            obfuscatedContent.erase(pos, block.length());
        }
    }

    obfuscatedContent += "\n Block de fonctions obfusquees\n";
    for (const auto &block : blocks) {
        obfuscatedContent += block;
    }

    std::ofstream out(sourceFilePath);
    if (!out.is_open()) {
        std::cerr << "Impossible d'ecrire le fichier obfusque" << std::endl;
        return false;
    }
    out << obfuscatedContent;
    return true;
}

bool Obfuscator::obfuscate() {
    // sauvegarde le fichier original
    if (!backupOriginal()) {
        return false;
    }

    // lit le contenu du fichier source
    std::string content;
    if (!readSource(content)) {
        return false;
    }

    // extrait les blocs de fonctions
    std::vector<std::string> blocks = extractFunctionsBlocks(content);

    // reordonne les blocs
    std::vector<std::string> reorderedBlocks = reorderBlocks(blocks);

    // ecrit le fichier obfusque
    if (!writeObfuscatedFile(reorderedBlocks, content)) {
        return false;
    }

    std::cout << "Obfuscation realise avec succes !" << std::endl;
    return true;
}

std::string Obfuscator::xorEncryptDecrypt(const std::string &input, char key) {
    std::string output = input;
    for (size_t i = 0; i < input.size(); i++) {
        output[i] = input[i] ^ key;
    }

    return output;
}
