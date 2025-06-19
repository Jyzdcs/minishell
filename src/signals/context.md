# 🔔 Signals - Gestion des Signaux

## 📋 Rôle du Module

Le module **Signals** gère les signaux système (SIGINT, SIGQUIT, etc.) pour que le shell réagisse correctement aux interruptions clavier et autres événements. Il assure la compatibilité avec le comportement de Bash.

## 🎯 Objectifs

1. **Interruptions clavier** : Ctrl+C (SIGINT), Ctrl+\ (SIGQUIT), Ctrl+D (EOF)
2. **Gestion des processus** : Signaux vers les processus enfants
3. **Restauration du prompt** : Affichage propre après interruption
4. **Codes de retour** : Gestion des codes d'erreur spéciaux

## 🔧 Fonctions Principales à Implémenter

### **Configuration des Signaux**

```c
void    setup_signals(void);                           // Configuration initiale
void    setup_child_signals(void);                     // Configuration enfants
void    restore_signals(void);                         // Restauration par défaut
void    ignore_signals(void);                          // Ignorer temporairement
```

### **Handlers de Signaux**

```c
void    sigint_handler(int sig);                       // Handler SIGINT (Ctrl+C)
void    sigquit_handler(int sig);                      // Handler SIGQUIT (Ctrl+\)
void    sigchld_handler(int sig);                      // Handler SIGCHLD (enfant mort)
```

### **Gestion des États**

```c
void    set_interactive_mode(void);                    // Mode interactif (prompt)
void    set_executing_mode(void);                      // Mode exécution
void    set_heredoc_mode(void);                        // Mode heredoc
```

### **Utilitaires**

```c
int     get_signal_exit_code(int sig);                 // Code sortie pour signal
void    propagate_signal(pid_t pid, int sig);          // Propagation vers enfant
bool    is_signal_pending(void);                       // Test signal en attente
```

## 🏗️ Architecture de Gestion

### **Variable Globale (Contrainte Sujet)**

```c
// UNE SEULE variable globale autorisée
volatile sig_atomic_t g_signal_received = 0;
```

### **États du Shell**

```c
typedef enum e_shell_state {
    STATE_INTERACTIVE,      // Attente commande (prompt)
    STATE_EXECUTING,        // Exécution commande
    STATE_HEREDOC,         // Mode heredoc
    STATE_EXITING          // Sortie en cours
} t_shell_state;
```

## 📝 Comportements Spécifiques

### **Mode Interactif (Prompt)**

- **Ctrl+C** : Afficher nouveau prompt sur nouvelle ligne
- \*\*Ctrl+\*\* : Ignorer (ne rien faire)
- **Ctrl+D** : Quitter le shell si ligne vide

### **Mode Exécution**

- **Ctrl+C** : Interrompre commande (SIGINT → enfant)
- \*\*Ctrl+\*\* : Quit avec core dump (SIGQUIT → enfant)
- **Signaux** : Laisser les enfants gérer

### **Mode Heredoc**

- **Ctrl+C** : Interrompre saisie heredoc
- **Ctrl+D** : Terminer heredoc si délimiteur trouvé

## 🎯 Implémentation des Handlers

### **Handler SIGINT (Ctrl+C)**

```c
void sigint_handler(int sig) {
    g_signal_received = sig;

    if (get_shell_state() == STATE_INTERACTIVE) {
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    // En mode exécution : laisser l'enfant gérer
}
```

### **Handler SIGQUIT (Ctrl+\)**

```c
void sigquit_handler(int sig) {
    if (get_shell_state() == STATE_INTERACTIVE) {
        // Ne rien faire en mode interactif
        return;
    }

    g_signal_received = sig;
    // En mode exécution : propager aux enfants
}
```

## 🧪 Tests de Validation

### **Mode Interactif**

```bash
# Dans le shell
^C                    # Nouveau prompt
^C^C^C               # Multiples Ctrl+C
^\                   # Ctrl+\ ignoré
^D                   # Sortie du shell
```

### **Mode Exécution**

```bash
sleep 10             # Commande longue
^C                   # Interruption → code 130
sleep 10
^\                   # Quit → code 131
```

### **Heredoc**

```bash
cat << EOF
line 1
^C                   # Interruption heredoc
```

## ⚠️ Gestion d'Erreurs

### **Codes de Sortie Standards**

```c
#define EXIT_SIGINT     130     // Ctrl+C
#define EXIT_SIGQUIT    131     // Ctrl+\
#define EXIT_SIGTERM    143     // Terminaison
```

### **Sécurité**

- Handlers async-signal-safe uniquement
- Pas de `malloc()` dans les handlers
- Utiliser `write()` au lieu de `printf()`

## 🔗 Interface avec les Autres Modules

- **Input** : État global du shell
- **Interactions** :
  - **Main** : Configuration initiale
  - **Executor** : Propagation vers enfants
  - **Readline** : Interruption saisie
- **System calls** : `signal()`, `sigaction()`, `kill()`
