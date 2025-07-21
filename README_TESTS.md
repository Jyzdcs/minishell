# 🧪 Scripts de Test du Lexer - Minishell

## 📁 Fichiers de test

### `test_lexer.sh` - Tests automatisés complets

**Script principal de test avec validation automatique**

- ✅ Compilation automatique du projet
- 🔍 Tests automatisés avec validation
- 📊 Comptage des réussites/échecs
- 🎨 Affichage coloré des résultats
- ⏱️ Protection contre les timeouts

### `test_lexer_manual.sh` - Tests manuels rapides

**Script simple pour voir les outputs du lexer**

- ⚡ Tests rapides sans validation
- 👁️ Affichage direct des tokens
- 🔧 Idéal pour le debug

---

## 🚀 Utilisation

### Test automatisé complet

```bash
./test_lexer.sh
```

### Test manuel rapide

```bash
./test_lexer_manual.sh
```

### Test interactif

```bash
make && ./minishell
```

---

## 📋 Types de tests couverts

### ✅ Tests basiques

- Commandes simples (`ls`)
- Commandes avec arguments (`ls -l -a`)
- Gestion des espaces multiples

### ⚙️ Tests avec opérateurs

- Pipes (`|`)
- Redirections (`<`, `>`, `>>`, `<<`)
- Combinaisons complexes

### 🔤 Tests avec quotes

- Quotes simples (`'...'`)
- Quotes doubles (`"..."`)
- Gestion des espaces dans les quotes

### ❌ Tests d'erreurs

- Quotes non fermées
- Syntax errors

---

## 🎯 Format de sortie attendu

Le lexer doit produire des sorties du format :

```
Token: 'ls' (type: 0)
Token: '-l' (type: 1)
Token: '|' (type: 2)
Token: 'wc' (type: 0)
```

### Types de tokens

- `0` : TOKEN_CMD (Commande)
- `1` : TOKEN_ARG (Argument)
- `2` : TOKEN_PIPE (Pipe |)
- `3` : TOKEN_REDIR_IN (<)
- `4` : TOKEN_REDIR_OUT (>)
- `5` : TOKEN_REDIR_APPEND (>>)
- `6` : TOKEN_HEREDOC (<<)

---

## 🔧 Dépannage

### Problème de compilation

```bash
make clean && make
```

### Timeout des tests

- Vérifiez les boucles infinies dans le lexer
- Testez manuellement avec `./test_lexer_manual.sh`

### Tests qui échouent

- Vérifiez le format des outputs dans `main.c`
- Le lexer doit afficher : `Token: 'value' (type: X)`
