# 🧪 Scripts de Test de l'Expander - Minishell

## 📁 Fichiers de test

### `test_expander.sh` - Tests automatisés complets

**Script principal de test avec validation automatique**

- ✅ Compilation automatique du projet
- 🔍 Tests automatisés avec validation des expansions
- 📊 Comptage des réussites/échecs
- 🎨 Affichage coloré des résultats
- ⏱️ Protection contre les timeouts
- 🌍 Variables d'environnement prédéfinies pour les tests

### `test_expander_manual.sh` - Tests manuels rapides

**Script simple pour voir les outputs de l'expander**

- ⚡ Tests rapides sans validation
- 👁️ Affichage direct des expansions
- 🔧 Idéal pour le debug
- 🌍 Variables d'environnement automatiquement configurées

---

## 🚀 Utilisation

### Test automatisé complet

```bash
./test_expander.sh
```

### Test manuel rapide

```bash
./test_expander_manual.sh
```

### Test interactif

```bash
make && ./minishell
```

---

## 📋 Types de tests couverts

### ✅ Tests basiques

- Variables simples (`$VAR`)
- Variables d'environnement standard (`$USER`, `$HOME`)
- Variables inexistantes (doivent retourner chaîne vide)

### 🔤 Tests avec quotes

- Expansion dans quotes doubles (`"$VAR"`)
- Protection dans quotes simples (`'$VAR'` → littéral)
- Combinaisons mixtes

### 🔧 Tests paramètres spéciaux

- Code de retour (`$?`)
- PID du shell (`$$`)

### 🎯 Tests complexes

- Variables multiples dans une commande
- Variables mélangées avec du texte
- Expansion avec opérateurs shell

---

## 🌍 Variables d'environnement de test

Les scripts définissent automatiquement :

```bash
TEST_VAR="hello"
USER="testuser"
HOME="/home/testuser"
```

---

## 🎯 Format de sortie attendu

L'expander doit transformer les variables avant l'exécution :

```bash
# Input
echo $TEST_VAR

# Expansion attendue
echo hello

# Output final
hello
```

### Règles d'expansion

- `$VAR` → valeur de la variable
- Variable inexistante → chaîne vide
- `'$VAR'` → pas d'expansion (littéral)
- `"$VAR"` → expansion normale
- `$?` → code de retour de la dernière commande
- `$$` → PID du processus shell

---

## 🔧 Dépannage

### Problème de compilation

```bash
make clean && make
```

### Variables non expandées

- Vérifiez que l'expander est appelé après le lexer
- Vérifiez que les tokens contiennent bien les `$`
- Testez manuellement avec `./test_expander_manual.sh`

### Tests qui échouent

- Vérifiez que l'expander modifie bien les valeurs des tokens
- L'expansion doit se faire AVANT l'exécution des commandes
- Variables inexistantes doivent retourner chaîne vide (pas "undefined")

### Exemple d'intégration dans main.c

```c
// Après le lexer
tokens = lexer(prompt);
if (tokens)
{
    // Appeler l'expander
    expand_tokens(tokens, environ, last_exit_code);
    // Puis afficher ou exécuter les tokens expansés
}
```
