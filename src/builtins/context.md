# 🏠 Builtins - Commandes Intégrées

## 📋 Rôle du Module

Les **Builtins** sont les commandes intégrées du shell qui s'exécutent directement dans le processus principal (sans `fork()`). Elles modifient l'état interne du shell : répertoire courant, variables d'environnement, ou contrôlent le shell lui-même.

## 🎯 Objectifs

1. **Commandes système** : `cd`, `pwd`, `exit`
2. **Gestion environnement** : `export`, `unset`, `env`
3. **Affichage** : `echo`
4. **Cohérence avec Bash** : Comportement identique et codes de retour

## 🔧 Fonctions Principales à Implémenter

### **Dispatcher Principal**

```c
bool    is_builtin(char *cmd);                         // Test si commande builtin
int     execute_builtin(char **argv, t_shell *shell);  // Exécution dispatcher
```

### **Commandes de Navigation**

```c
int     builtin_cd(char **argv, t_shell *shell);       // Change directory
int     builtin_pwd(char **argv, t_shell *shell);      // Print working directory
```

### **Gestion de l'Environnement**

```c
int     builtin_export(char **argv, t_shell *shell);   // Export variables
int     builtin_unset(char **argv, t_shell *shell);    // Unset variables
int     builtin_env(char **argv, t_shell *shell);      // Print environment
```

### **Affichage et Contrôle**

```c
int     builtin_echo(char **argv, t_shell *shell);     // Echo avec option -n
int     builtin_exit(char **argv, t_shell *shell);     // Exit shell
```

### **Utilitaires Internes**

```c
bool    is_valid_identifier(char *name);               // Validation nom variable
char    *get_env_value(char *name, t_shell *shell);    // Récupération valeur env
int     set_env_var(char *name, char *value, t_shell *shell); // Définition variable
int     unset_env_var(char *name, t_shell *shell);     // Suppression variable
```

## 📋 Spécifications des Builtins

### **`echo` - Affichage**

```c
// Usage: echo [-n] [string ...]
// -n : pas de saut de ligne final
int builtin_echo(char **argv, t_shell *shell) {
    bool no_newline = false;
    int i = 1;

    // Vérifier option -n
    if (argv[1] && strcmp(argv[1], "-n") == 0) {
        no_newline = true;
        i = 2;
    }

    // Afficher arguments séparés par espaces
    while (argv[i]) {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }

    if (!no_newline)
        printf("\n");

    return EXIT_SUCCESS;
}
```

### **`cd` - Change Directory**

```c
// Usage: cd [directory]
// cd sans argument → $HOME
// cd - → $OLDPWD
// Mise à jour PWD et OLDPWD
```

**Comportements spéciaux :**

- `cd` seul → aller à `$HOME`
- `cd -` → aller à `$OLDPWD` et l'afficher
- `cd ~` → aller à `$HOME`
- Mise à jour automatique de `PWD` et `OLDPWD`

### **`pwd` - Print Working Directory**

```c
// Usage: pwd (pas d'options)
// Affiche le répertoire courant absolu
char *cwd = getcwd(NULL, 0);
printf("%s\n", cwd);
free(cwd);
```

### **`export` - Export Variables**

```c
// Usage: export [name[=value] ...]
// Sans argument : affiche toutes les variables exportées (format declare -x)
// Avec arguments : exporte les variables dans l'environnement
```

**Formats :**

- `export VAR=value` → définit et exporte
- `export VAR` → exporte variable existante
- `export` seul → liste triée de toutes les variables

### **`unset` - Unset Variables**

```c
// Usage: unset [name ...]
// Supprime les variables de l'environnement
// Ignore les variables inexistantes (pas d'erreur)
```

### **`env` - Environment**

```c
// Usage: env (pas d'arguments ni options)
// Affiche toutes les variables d'environnement format "NAME=value"
// Une variable par ligne, pas de tri particulier
```

### **`exit` - Exit Shell**

```c
// Usage: exit [n]
// n : code de sortie (0-255)
// Sans argument : utilise le code de la dernière commande
// Avec argument non numérique : erreur
```

## 🧪 Tests de Validation

### **Tests Echo**

```bash
echo hello world        # → "hello world\n"
echo -n hello          # → "hello" (sans \n)
echo -n               # → "" (vide, sans \n)
echo                  # → "\n" (juste un saut de ligne)
```

### **Tests CD**

```bash
cd /tmp               # Change vers /tmp
pwd                   # → "/tmp"
cd                    # Retourne à $HOME
cd -                  # Retourne au précédent (/tmp) et l'affiche
cd nonexistent        # Erreur : "No such file or directory"
```

### **Tests Export/Unset/Env**

```bash
export TEST=value     # Définit TEST
env | grep TEST       # → "TEST=value"
export | grep TEST    # → "declare -x TEST=\"value\""
unset TEST           # Supprime TEST
env | grep TEST       # Aucun résultat
```

### **Tests Exit**

```bash
exit                 # Code 0 (ou dernier code)
exit 42              # Code 42
exit abc             # Erreur : argument non numérique
```

## ⚠️ Gestion d'Erreurs

### **Codes de Retour Standards**

- **Succès** : `0`
- **Erreur générale** : `1`
- **Erreur d'usage** : `2`

### **Erreurs Spécifiques**

```c
// cd
#define CD_HOME_NOT_SET     1  // $HOME non défini
#define CD_NO_SUCH_DIR      1  // Répertoire inexistant
#define CD_PERMISSION       1  // Pas de permission

// export/unset
#define INVALID_IDENTIFIER  1  // Nom de variable invalide

// exit
#define EXIT_NUMERIC_ARG    2  // Argument non numérique
```

### **Messages d'Erreur**

```c
// Respecter le format bash
fprintf(stderr, "minishell: cd: %s: No such file or directory\n", path);
fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", name);
fprintf(stderr, "minishell: exit: %s: numeric argument required\n", arg);
```

## 🔗 Interface avec les Autres Modules

- **Input** : Commandes depuis l'**Executor**
- **Interactions** :
  - **Environment** : Manipulation des variables d'environnement
  - **Utils** : Fonctions de validation et manipulation
- **Fonctions système utilisées** :
  - `chdir()`, `getcwd()` pour `cd`/`pwd`
  - `getenv()`, `setenv()`, `unsetenv()` pour l'environnement
  - `exit()` pour `exit`

## 💡 Optimisations Possibles

### **Cache des Répertoires**

```c
typedef struct s_dir_cache {
    char    *old_pwd;       // Cache OLDPWD
    char    *current_pwd;   // Cache PWD
    bool    pwd_updated;    // Flag mise à jour
} t_dir_cache;
```

### **Validation Précoce**

- Vérifier les arguments avant exécution
- Cache des validations d'identifiants
- Pré-tri des variables pour `export`

## 🔍 Structures de Données Utiles

```c
typedef struct s_builtin {
    char    *name;                              // Nom de la commande
    int     (*func)(char **, t_shell *);        // Fonction d'exécution
} t_builtin;

// Table des builtins
static t_builtin g_builtins[] = {
    {"echo", builtin_echo},
    {"cd", builtin_cd},
    {"pwd", builtin_pwd},
    {"export", builtin_export},
    {"unset", builtin_unset},
    {"env", builtin_env},
    {"exit", builtin_exit},
    {NULL, NULL}
};
```

## 📝 Règles de Validation des Identifiants

```c
// Nom de variable valide : [a-zA-Z_][a-zA-Z0-9_]*
bool is_valid_identifier(char *name) {
    if (!name || !*name)
        return false;

    // Premier caractère : lettre ou underscore
    if (!isalpha(*name) && *name != '_')
        return false;

    // Caractères suivants : alphanumérique ou underscore
    for (int i = 1; name[i]; i++) {
        if (!isalnum(name[i]) && name[i] != '_')
            return false;
    }

    return true;
}
```
