# 🏗️ Parser - Analyseur Syntaxique

## 📋 Rôle du Module

Le **Parser** transforme la liste de tokens du lexer en une structure de commandes exécutables. Il construit l'arbre syntaxique abstrait (AST) simplifié sous forme de liste chaînée de commandes avec leurs redirections et pipes.

## 🎯 Objectifs

1. **Structuration** : Organiser les tokens en commandes logiques
2. **Validation syntaxique** : Vérifier la cohérence des séquences
3. **Gestion des pipes** : Séparer les commandes reliées par `|`
4. **Traitement des redirections** : Ouvrir les fichiers et assigner les FD

## 🔧 Fonctions Principales à Implémenter

### **Fonctions de Parsing Principal**

```c
t_cmd   *parse_tokens(t_token *tokens);         // Point d'entrée principal
t_cmd   *create_cmd(void);                      // Création d'une nouvelle commande
void    add_cmd(t_cmd **list, t_cmd *new);      // Ajout à la liste de commandes
```

### **Construction des Commandes**

```c
char    **build_argv(t_token *tokens);          // Construction du tableau argv
int     count_args(t_token *tokens);            // Comptage des arguments
void    fill_argv(char **argv, t_token *tokens); // Remplissage du tableau
```

### **Gestion des Redirections**

```c
int     handle_redirection(t_cmd *cmd, t_token *token); // Traitement d'une redirection
int     open_input_file(char *filename);        // Ouverture fichier d'entrée
int     open_output_file(char *filename, bool append); // Ouverture fichier de sortie
int     handle_heredoc(char *delimiter);        // Gestion du heredoc (<<)
```

### **Validation Syntaxique**

```c
bool    is_valid_syntax(t_token *tokens);       // Validation globale
bool    check_redirections(t_token *tokens);    // Vérification redirections
bool    check_pipes(t_token *tokens);           // Vérification pipes
```

### **Utilitaires**

```c
void    free_cmds(t_cmd *cmds);                 // Libération mémoire
void    free_argv(char **argv);                 // Libération tableau argv
t_token *skip_to_pipe(t_token *tokens);         // Navigation jusqu'au prochain pipe
```

## 🏗️ Structure de Données

```c
typedef struct s_cmd {
    char            **argv;         // Tableau d'arguments (NULL-terminated)
    int             argc;           // Nombre d'arguments
    int             infile;         // FD d'entrée (-1 si stdin)
    int             outfile;        // FD de sortie (-1 si stdout)
    bool            append_mode;    // Mode append pour >>
    char            *heredoc_delim; // Délimiteur pour heredoc
    struct s_cmd    *next;          // Commande suivante (pipe)
} t_cmd;
```

## 📝 Algorithme de Parsing

### **Étapes Principales**

1. **Validation** : Vérifier la syntaxe des tokens
2. **Segmentation** : Séparer par pipes en sous-séquences
3. **Construction** : Pour chaque segment :
   - Extraire la commande et ses arguments
   - Traiter les redirections
   - Créer la structure `t_cmd`
4. **Chaînage** : Lier les commandes en liste

### **Gestion des Pipes**

```
cmd1 | cmd2 | cmd3
└─── t_cmd ──→ t_cmd ──→ t_cmd ──→ NULL
```

## 🔄 Traitement des Redirections

### **Types de Redirections**

- `<` : Redirection d'entrée
- `>` : Redirection de sortie (écrasement)
- `>>` : Redirection de sortie (ajout)
- `<<` : Heredoc (lecture jusqu'au délimiteur)

### **Exemple de Parsing**

```bash
cat < input.txt | grep "pattern" > output.txt
```

**Résultat :**

- **cmd1** : `argv=["cat"]`, `infile=fd_input`
- **cmd2** : `argv=["grep", "pattern"]`, `outfile=fd_output`

## 🧪 Tests de Validation

```bash
# Commandes simples
ls -la                  # 1 cmd: argv=["ls", "-la"]
echo "hello"            # 1 cmd: argv=["echo", "hello"]

# Pipes
ls | wc -l              # 2 cmds: ["ls"] | ["wc", "-l"]
cat file | sort | uniq  # 3 cmds chaînées

# Redirections
cat < input > output    # 1 cmd avec infile et outfile
echo "test" >> log.txt  # 1 cmd avec outfile en mode append

# Heredoc
cat << EOF              # 1 cmd avec heredoc_delim="EOF"
```

## ⚠️ Gestion d'Erreurs

### **Erreurs Syntaxiques**

- Pipe en début/fin : `| ls` ou `ls |`
- Redirections orphelines : `cat < > file`
- Tokens manquants : `cat <` (pas de nom de fichier)

### **Erreurs d'Ouverture de Fichiers**

- Fichier inexistant pour `<`
- Permissions insuffisantes pour `>` ou `>>`
- Répertoire au lieu de fichier

### **Codes d'Erreur**

```c
#define PARSE_SUCCESS   0
#define PARSE_SYNTAX    1
#define PARSE_FILE      2
#define PARSE_MEMORY    3
```

## 🔗 Interface avec les Autres Modules

- **Input** : Liste de tokens depuis le **Lexer**
- **Output** : Liste de commandes pour l'**Executor**
- **Dépendances** :
  - **Utils** pour les utilitaires
  - Fonctions système : `open()`, `close()`, `access()`

## 💡 Optimisations Possibles

- **Réutilisation de FD** : Éviter les `open()`/`close()` multiples
- **Validation précoce** : Arrêter au premier erreur détectée
- **Cache de fichiers** : Mémoriser les FD ouverts fréquemment
