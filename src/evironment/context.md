# 🌐 Environment - Gestion des Variables d'Environnement

## 📋 Rôle du Module

Le module **Environment** gère toutes les variables d'environnement du shell : création, modification, suppression et accès. Il maintient une copie locale de l'environnement pour permettre les modifications sans affecter l'environnement système jusqu'à l'export.

## 🎯 Objectifs

1. **Gestion des variables** : Créer, modifier, supprimer des variables
2. **Environnement local** : Maintenir une copie modifiable de l'environnement
3. **Export/Import** : Synchroniser avec l'environnement système
4. **Recherche efficace** : Accès rapide aux variables fréquemment utilisées

## 🔧 Fonctions Principales à Implémenter

### **Gestion de Base**

```c
int     env_init(t_shell *shell, char **envp);         // Initialisation environnement
void    env_cleanup(t_shell *shell);                   // Nettoyage mémoire
char    **env_to_array(t_shell *shell);                // Conversion en tableau
int     env_size(t_shell *shell);                      // Nombre de variables
```

### **Accès aux Variables**

```c
char    *env_get(t_shell *shell, char *name);          // Récupération valeur
bool    env_exists(t_shell *shell, char *name);        // Test existence
int     env_set(t_shell *shell, char *name, char *value); // Définition
int     env_unset(t_shell *shell, char *name);         // Suppression
```

### **Manipulation Avancée**

```c
int     env_export(t_shell *shell, char *name);        // Export vers système
int     env_import(t_shell *shell, char *name);        // Import depuis système
char    **env_list_exported(t_shell *shell);           // Liste variables exportées
char    **env_list_all(t_shell *shell);                // Liste toutes variables
```

### **Utilitaires**

```c
bool    is_valid_env_name(char *name);                 // Validation nom
char    *parse_env_assignment(char *str, char **name); // Parse "NAME=value"
int     env_sort(char **envp);                         // Tri alphabétique
```

## 🏗️ Structure de Données

```c
typedef struct s_env_var {
    char                *name;      // Nom de la variable
    char                *value;     // Valeur de la variable
    bool                exported;   // Marqueur d'export
    struct s_env_var    *next;      // Variable suivante
} t_env_var;

typedef struct s_environment {
    t_env_var   *vars;              // Liste des variables
    int         count;              // Nombre de variables
    char        **cache;            // Cache tableau (pour execve)
    bool        cache_valid;        // Cache valide
} t_environment;
```

## 📝 Algorithmes Principaux

### **Recherche de Variable**

```c
char *env_get(t_shell *shell, char *name) {
    t_env_var *var = shell->env.vars;

    while (var) {
        if (strcmp(var->name, name) == 0)
            return var->value;
        var = var->next;
    }
    return NULL;
}
```

### **Définition de Variable**

```c
int env_set(t_shell *shell, char *name, char *value) {
    t_env_var *var = find_var(shell, name);

    if (var) {
        // Mise à jour existante
        free(var->value);
        var->value = strdup(value);
    } else {
        // Nouvelle variable
        var = create_var(name, value);
        add_var(&shell->env.vars, var);
        shell->env.count++;
    }

    shell->env.cache_valid = false; // Invalider cache
    return 0;
}
```

## 🧪 Tests de Validation

### **Variables de Base**

```bash
export TEST=hello       # Créer variable
echo $TEST             # → "hello"
export TEST=world      # Modifier variable
echo $TEST             # → "world"
unset TEST             # Supprimer variable
echo $TEST             # → "" (vide)
```

### **Variables Système**

```bash
echo $HOME             # Variable système
echo $PATH             # Variable PATH
echo $PWD              # Répertoire courant
```

### **Export/Import**

```bash
VAR=local             # Variable locale
export VAR            # Export vers environnement
env | grep VAR        # Doit apparaître
```

## ⚠️ Gestion d'Erreurs

### **Validation des Noms**

- Caractères valides : `[a-zA-Z_][a-zA-Z0-9_]*`
- Noms réservés : éviter les conflits système
- Longueur maximale : limiter la taille

### **Gestion Mémoire**

- Libération automatique lors de la suppression
- Détection des fuites mémoire
- Réallocation efficace du cache

## 🔗 Interface avec les Autres Modules

- **Used by** : **Expander** (résolution $VAR), **Builtins** (export/unset)
- **Dependencies** : **Utils** pour manipulation de chaînes
- **System calls** : `getenv()`, `setenv()`, `unsetenv()`
