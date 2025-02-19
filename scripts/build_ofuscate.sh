#!/bin/bash
# build_ofuscate.sh - Script d'automatisation pour compiler, tester et lancer crypt0morphic

# Arrêter le script en cas d'erreur
set -e

# Nettoyage des anciens builds
echo "Nettoyage des anciens builds..."
rm -f crypt0morphic
rm -f tests/builds/test_reverse_shell tests/builds/test_obfuscator

# Compilation du programme principal
echo "Compilation de crypt0morphic..."
g++ -std=c++17 -I./src -o crypt0morphic src/main.cpp src/obfuscator/obfuscator.cpp src/reverse_shell/reverse_shell.cpp

# Compilation des tests unitaires

# Test pour ReverseShell
echo "Compilation du test: test_reverse_shell..."
g++ -std=c++17 -I./src -o tests/builds/test_reverse_shell src/reverse_shell/reverse_shell.cpp tests/test_ReverseShell.cpp

# Test pour Obfuscator
echo "Compilation du test: test_obfuscator..."
g++ -std=c++17 -I./src -o tests/builds/test_obfuscator src/obfuscator/obfuscator.cpp tests/test_obfuscator.cpp

# Exécution des tests unitaires

echo "Exécution du test_reverse_shell..."
./tests/builds/test_reverse_shell

echo "Exécution du test_obfuscator..."
./tests/builds/test_obfuscator

# Lancement du programme principal
echo "Lancement de crypt0morphic..."
./crypt0morphic

echo "Processus terminé avec succès."
