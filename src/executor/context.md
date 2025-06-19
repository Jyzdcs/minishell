# ⚡ Executor - Exécuteur de Commandes

## 📋 Rôle du Module

L'**Executor** est le cœur du shell : il exécute les commandes après parsing et expansion. Il gère les processus enfants, les pipes, les redirections et coordonne l'exécution des builtins et commandes externes.

## 🎯 Objectifs

1. **Exécution** : Lancer les commandes (externes et builtins)
2. **Gestion des processus** : `fork()`, `wait()`, codes de retour
3. **Pipes** : Connecter la sortie d'une commande à l'entrée de la suivante
4. **Redirections** : Configurer les entrées/sorties avec `dup2()`

## 🔧 Fonctions Principales à Implémenter

### **Fonctions d'Exécution Principale**

```c
int     execute_commands(t_cmd *cmds, t_shell *shell); // Point d'entrée principal
int     execute_single_cmd(t_cmd *cmd, t_shell *shell); // Exécution d'une commande
int     execute_pipeline(t_cmd *cmds, t_shell *shell);  // Exécution d'un pipeline
```

### **Gestion des Processus**

```c
pid_t   create_child(t_cmd *cmd, t_shell *shell);      // Création processus enfant
int     wait_for_children(pid_t *pids, int count);     // Attente des enfants
int     handle_child_signals(int status);              // Gestion signaux enfants
void    setup_child_process(t_cmd *cmd, int *pipes);   // Configuration enfant
```

### **Gestion des Pipes**

```c
int     setup_pipes(t_cmd *cmds, int **pipes);         // Création des pipes
void    connect_pipes(t_cmd *cmd, int *pipes, int index); // Connexion pipes
void    close_pipes(int *pipes, int count);            // Fermeture pipes
int     count_commands(t_cmd *cmds);                    // Comptage commandes
```

### **Redirections**

```c
int     setup_redirections(t_cmd *cmd);                // Configuration redirections
int     redirect_input(int fd);                        // Redirection entrée
int     redirect_output(int fd);                       // Redirection sortie
void    restore_std_fds(int stdin_backup, int stdout_backup); // Restauration FD
```

### **Commandes Externes**

```c
int     execute_external(t_cmd *cmd, t_shell *shell);  // Exécution externe
char    *find_command_path(char *cmd, char **envp);    // Recherche dans PATH
bool    is_executable(char *path);                     // Test exécutabilité
char    **build_envp(t_shell *shell);                  // Construction environnement
```

## 🏗️ Architecture d'Exécution

### **Pipeline Simple**

```
cmd1 | cmd2 | cmd3
  │      │      │
fork() fork() fork()
  │      │      │
 PID1   PID2   PID3
```

### **Gestion des Pipes**

```c
// Pour n commandes, on a besoin de (n-1) pipes
int pipes[2 * (cmd_count - 1)];

// cmd1 | cmd2 | cmd3
// pipe[0,1] connecte cmd1 → cmd2
// pipe[2,3] connecte cmd2 → cmd3
```

## 📝 Algorithme d'Exécution

### **Commande Simple (sans pipe)**

1. Vérifier si c'est un builtin → exécuter directement
2. Sinon : `fork()` → dans l'enfant : `execve()`
3. Parent : `wait()` et récupérer le code de retour

### **Pipeline (avec pipes)**

1. Créer tous les pipes nécessaires
2. Pour chaque commande :
   - `fork()` un enfant
   - Dans l'enfant : configurer `dup2()` et `execve()`
   - Dans le parent : fermer les FD non utilisés
3. Fermer tous les pipes du parent
4. `wait()` tous les enfants

## 🔄 Gestion des Redirections

### **Types de Redirections**

```c
// Redirection d'entrée : cmd < file
if (cmd->infile != -1) {
    dup2(cmd->infile, STDIN_FILENO);
    close(cmd->infile);
}

// Redirection de sortie : cmd > file
if (cmd->outfile != -1) {
    dup2(cmd->outfile, STDOUT_FILENO);
    close(cmd->outfile);
}
```

### **Priorité des Redirections**

1. **Pipes** (communication inter-processus)
2. **Redirections explicites** (`<`, `>`, `>>`)
3. **Entrée/sortie standard** (par défaut)

## 🧪 Tests de Validation

```bash
# Commandes simples
echo "hello"            # Builtin simple
/bin/ls                 # Commande externe avec chemin absolu
ls                      # Commande externe via PATH

# Pipes
ls | wc -l              # Pipeline simple
cat file | sort | uniq  # Pipeline multiple

# Redirections
echo "test" > file.txt  # Redirection sortie
cat < input.txt         # Redirection entrée
ls >> log.txt           # Redirection append

# Combinaisons
cat < input | grep "pattern" > output  # Pipes + redirections
```

## ⚠️ Gestion d'Erreurs

### **Erreurs d'Exécution**

- **Commande introuvable** : `bash: cmd: command not found` (code 127)
- **Fichier non exécutable** : `bash: cmd: Permission denied` (code 126)
- **Erreur fork** : Gestion des ressources insuffisantes

### **Erreurs de Pipes**

- Échec création pipe → retourner erreur
- Processus enfant mort → SIGPIPE vers parent

### **Codes de Retour Standards**

```c
#define EXIT_SUCCESS        0   // Succès
#define EXIT_FAILURE        1   // Échec général
#define EXIT_MISUSE         2   // Mauvaise utilisation
#define EXIT_CANNOT_EXEC    126 // Ne peut pas exécuter
#define EXIT_NOT_FOUND      127 // Commande introuvable
#define EXIT_SIGINT         130 // Interruption Ctrl+C
#define EXIT_SIGQUIT        131 // Quit Ctrl+\
```

## 🔗 Interface avec les Autres Modules

- **Input** : Liste de commandes depuis l'**Expander**
- **Interactions** :
  - **Builtins** : Exécution des commandes intégrées
  - **Environment** : Variables d'environnement pour `execve()`
  - **Signals** : Gestion des interruptions
- **Fonctions système utilisées** :
  - `fork()`, `execve()`, `wait()`, `waitpid()`
  - `pipe()`, `dup2()`, `close()`
  - `access()`, `stat()`

## 💡 Optimisations Possibles

### **Réutilisation de Processus**

- Cache des commandes fréquentes
- Pool de processus pré-créés

### **Gestion Mémoire**

- Libération immédiate des ressources non utilisées
- Partage de l'environnement entre processus

### **Parallélisation**

- Exécution asynchrone des commandes indépendantes
- Optimisation des pipes pour gros volumes de données

## 🔍 Structures de Données Utiles

```c
typedef struct s_process {
    pid_t   pid;            // PID du processus
    int     status;         // Code de retour
    bool    is_builtin;     // Flag builtin
    t_cmd   *cmd;           // Commande associée
} t_process;

typedef struct s_pipeline {
    t_process   *processes; // Tableau des processus
    int         count;      // Nombre de processus
    int         *pipes;     // FD des pipes
    int         pipe_count; // Nombre de pipes
} t_pipeline;
```
