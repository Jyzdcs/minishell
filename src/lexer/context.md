# 🔤 Lexer - Analyseur Lexical

## 📋 Rôle du Module

Le **Lexer** (ou analyseur lexical) est la première étape du pipeline de traitement d'une commande shell. Il transforme une chaîne de caractères brute en une séquence de **tokens** (lexèmes) typés et structurés.

## 🎯 Objectifs

1. **Tokenisation** : Découper l'input en unités lexicales distinctes
2. **Classification** : Assigner un type à chaque token (CMD, ARG, PIPE, REDIR, etc.)
3. **Gestion des quotes** : Respecter les règles de protection des caractères spéciaux
4. **Validation syntaxique** : Détecter les erreurs de syntaxe de base

## 🔧 Fonctions Principales à Implémenter

### **Fonctions de Tokenisation**

```c
t_token *lexer(char *input);                    // Point d'entrée principal
t_token *create_token(char *value, t_type type); // Création d'un token
void    add_token(t_token **list, t_token *new); // Ajout à la liste
```

### **Gestion des Quotes**

```c
char    *handle_quotes(char *input, int *i);    // Extraction du contenu entre quotes
bool    is_quote_closed(char *input);           // Vérification fermeture quotes
char    *remove_quotes(char *str);              // Suppression des quotes externes
```

### **Reconnaissance des Opérateurs**

```c
bool    is_operator(char c);                    // Détection caractères spéciaux
t_type  get_operator_type(char *str);           // Type d'opérateur (|, <, >, etc.)
int     get_operator_len(char *str);            // Longueur de l'opérateur (>> = 2)
```

### **Utilitaires**

```c
void    skip_whitespace(char *str, int *i);     // Ignorer les espaces
bool    is_whitespace(char c);                  // Test caractère d'espacement
void    free_tokens(t_token *tokens);           // Libération mémoire
```

## 🏗️ Structure de Données

```c
typedef enum e_token_type {
    TOKEN_CMD,          // Commande (premier mot)
    TOKEN_ARG,          // Argument
    TOKEN_PIPE,         // |
    TOKEN_REDIR_IN,     // <
    TOKEN_REDIR_OUT,    // >
    TOKEN_REDIR_APPEND, // >>
    TOKEN_HEREDOC,      // <<
    TOKEN_EOF           // Fin de chaîne
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;
```

## 📝 Règles de Gestion

### **Quotes Simples (`'`)**

- Tout caractère est littéral (pas d'expansion)
- Exemple : `'echo $HOME | ls'` → un seul token ARG

### **Quotes Doubles (`"`)**

- Variables expandées (`$VAR` → valeur)
- Opérateurs protégés (`"|"` reste littéral)
- Exemple : `"echo $HOME"` → expansion de `$HOME`

### **Caractères Spéciaux**

- `|` : séparateur de pipe
- `<`, `>`, `>>`, `<<` : redirections
- ` ` (espace) : séparateur de tokens

## 🧪 Tests de Validation

```bash
# Tests basiques
echo hello world        # 3 tokens: CMD, ARG, ARG
ls | wc -l              # 4 tokens: CMD, PIPE, CMD, ARG

# Tests avec quotes
echo "hello world"      # 2 tokens: CMD, ARG
echo 'no $expansion'    # 2 tokens: CMD, ARG

# Tests redirections
cat < input.txt         # 3 tokens: CMD, REDIR_IN, ARG
echo hi > output.txt    # 4 tokens: CMD, ARG, REDIR_OUT, ARG
```

## ⚠️ Gestion d'Erreurs

- **Quotes non fermées** : Retourner NULL ou token d'erreur
- **Opérateurs en fin de ligne** : `ls |` → erreur syntaxique
- **Séquences invalides** : `< >` → erreur de redirection

## 🔗 Interface avec les Autres Modules

- **Input** : Chaîne brute depuis `readline()`
- **Output** : Liste chaînée de tokens pour le **Parser**
- **Dépendances** : Module **Utils** pour les fonctions auxiliaires
