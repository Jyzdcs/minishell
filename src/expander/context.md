# 🔄 Expander - Expansion des Variables

## 📋 Rôle du Module

L'**Expander** gère l'expansion des variables d'environnement et des paramètres spéciaux dans les commandes après le parsing. Il transforme les références (`$VAR`, `$?`) en leurs valeurs réelles tout en respectant les règles de protection des quotes.

## 🎯 Objectifs

1. **Expansion des variables** : Remplacer `$VAR` par leur valeur
2. **Paramètres spéciaux** : Gérer `$?` (code de retour), `$$` (PID), etc.
3. **Respect des quotes** : Pas d'expansion dans les quotes simples
4. **Gestion des erreurs** : Variables non définies, syntaxe invalide

## 🔧 Fonctions Principales à Implémenter

### **Fonctions d'Expansion Principale**

```c
int     expand_commands(t_cmd *cmds, t_shell *shell); // Point d'entrée principal
char    *expand_string(char *str, t_shell *shell);    // Expansion d'une chaîne
char    **expand_argv(char **argv, t_shell *shell);   // Expansion d'un tableau argv
```

### **Expansion des Variables**

```c
char    *expand_variables(char *str, char **envp);    // Expansion $VAR
char    *get_var_value(char *name, char **envp);      // Récupération valeur variable
char    *extract_var_name(char *str, int *len);       // Extraction nom de variable
bool    is_valid_var_char(char c);                    // Validation caractère variable
```

### **Paramètres Spéciaux**

```c
char    *expand_exit_code(int exit_code);             // Expansion de $?
char    *expand_pid(void);                            // Expansion de $$ (PID du shell)
char    *handle_special_param(char *str, t_shell *shell); // Gestion paramètres spéciaux
```

### **Gestion des Quotes**

```c
char    *expand_with_quotes(char *str, t_shell *shell); // Expansion respectant quotes
bool    is_in_single_quotes(char *str, int pos);       // Test quote simple
bool    is_in_double_quotes(char *str, int pos);       // Test quote double
int     find_quote_end(char *str, int start, char quote); // Fin de zone quotée
```

### **Utilitaires String**

```c
char    *str_replace(char *str, char *old, char *new); // Remplacement de sous-chaîne
char    *str_insert(char *str, int pos, char *insert); // Insertion dans chaîne
size_t  calculate_expanded_len(char *str, t_shell *shell); // Calcul taille après expansion
```

## 🏗️ Algorithme d'Expansion

### **Étapes Principales**

1. **Parcours** : Scanner la chaîne caractère par caractère
2. **Détection** : Identifier les `$` et extraire le nom de variable
3. **Résolution** : Chercher la valeur dans l'environnement
4. **Remplacement** : Substituer `$VAR` par la valeur
5. **Protection** : Respecter les zones quotées

### **Exemple d'Expansion**

```bash
# Avant expansion
echo "Hello $USER, your home is $HOME"

# Après expansion (si USER=john, HOME=/home/john)
echo "Hello john, your home is /home/john"
```

## 📝 Règles d'Expansion

### **Variables d'Environnement**

- `$VAR` ou `${VAR}` → valeur de la variable
- Variable non définie → chaîne vide
- `$` seul → littéral `$`

### **Paramètres Spéciaux**

- `$?` → code de retour de la dernière commande
- `$$` → PID du processus shell
- `$0` → nom du shell (minishell)

### **Protection par Quotes**

```bash
'$VAR'     # Pas d'expansion (littéral)
"$VAR"     # Expansion normale
'$'VAR     # Expansion de VAR seulement
```

## 🧪 Tests de Validation

```bash
# Variables simples
echo $HOME              # Expansion de HOME
echo "$USER is here"    # Expansion dans quotes doubles
echo '$USER is here'    # Pas d'expansion dans quotes simples

# Paramètres spéciaux
echo $?                 # Code de retour précédent
echo $$                 # PID du shell

# Cas complexes
echo "${HOME}/bin"      # Expansion avec délimiteurs
echo "$HOME $USER"      # Multiples variables
echo "Price: $100"      # $ littéral suivi de chiffres
```

## ⚠️ Gestion d'Erreurs

### **Variables Inexistantes**

```bash
echo $UNDEFINED        # → chaîne vide (comportement bash)
```

### **Syntaxe Invalide**

```bash
echo $              # $ isolé → reste littéral
echo ${             # Accolade non fermée → erreur
```

### **Allocation Mémoire**

- Vérifier tous les `malloc()`
- Libérer les chaînes temporaires
- Gérer les expansions très longues

## 🔗 Interface avec les Autres Modules

- **Input** : Liste de commandes depuis le **Parser**
- **Output** : Commandes avec variables expandées pour l'**Executor**
- **Dépendances** :
  - **Environment** : accès aux variables d'environnement
  - **Utils** : fonctions de manipulation de chaînes
  - Fonctions système : `getenv()`, `getpid()`

## 💡 Optimisations Possibles

### **Cache de Variables**

```c
typedef struct s_var_cache {
    char    *name;
    char    *value;
    time_t  last_access;
} t_var_cache;
```

### **Expansion Incrémentale**

- Éviter la réallocation pour chaque variable
- Pré-calculer la taille finale nécessaire
- Utiliser un buffer de travail réutilisable

### **Détection Précoce**

- Scanner d'abord pour détecter la présence de `$`
- Éviter le traitement si aucune expansion nécessaire

## 🔍 Structure de Données Utiles

```c
typedef struct s_expansion_context {
    char    **envp;           // Variables d'environnement
    int     last_exit_code;   // Code de retour précédent
    pid_t   shell_pid;        // PID du shell
    bool    in_single_quotes; // État des quotes simples
    bool    in_double_quotes; // État des quotes doubles
} t_expansion_context;
```
