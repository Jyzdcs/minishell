# 🛠️ Utils - Fonctions Utilitaires

## 📋 Rôle du Module

Le module **Utils** contient toutes les fonctions utilitaires partagées par les autres modules : manipulation de chaînes, gestion de mémoire, validation, et fonctions helper génériques.

## 🎯 Objectifs

1. **Réutilisabilité** : Fonctions communes à plusieurs modules
2. **Sécurité** : Versions sécurisées des fonctions standard
3. **Performance** : Optimisations pour les opérations fréquentes
4. **Maintenance** : Centralisation des utilitaires

## 🔧 Fonctions Principales à Implémenter

### **Manipulation de Chaînes**

```c
char    *ft_strdup(const char *s);                     // Duplication sécurisée
char    *ft_strjoin(char const *s1, char const *s2);   // Concaténation
char    **ft_split(char const *s, char c);             // Division par délimiteur
char    *ft_strtrim(char const *s1, char const *set);  // Suppression caractères
int     ft_strcmp(const char *s1, const char *s2);     // Comparaison
size_t  ft_strlen(const char *s);                      // Longueur
```

### **Gestion de Mémoire**

```c
void    *ft_malloc(size_t size);                       // Allocation sécurisée
void    *ft_realloc(void *ptr, size_t size);           // Réallocation
void    ft_free(void **ptr);                           // Libération + NULL
void    ft_free_array(char **array);                   // Libération tableau
```

### **Validation et Tests**

```c
bool    ft_isalpha(int c);                             // Test alphabétique
bool    ft_isdigit(int c);                             // Test numérique
bool    ft_isalnum(int c);                             // Test alphanumérique
bool    ft_isspace(int c);                             // Test espace
bool    ft_isprint(int c);                             // Test imprimable
```

### **Conversion**

```c
int     ft_atoi(const char *str);                      // String vers int
char    *ft_itoa(int n);                               // Int vers string
long    ft_atol(const char *str);                      // String vers long
```

### **Manipulation de Tableaux**

```c
int     ft_arraylen(char **array);                     // Taille tableau
char    **ft_array_dup(char **array);                  // Duplication tableau
char    **ft_array_append(char **array, char *new);    // Ajout élément
char    **ft_array_remove(char **array, int index);    // Suppression élément
```

### **Utilitaires Système**

```c
bool    ft_file_exists(const char *path);              // Test existence fichier
bool    ft_is_directory(const char *path);             // Test répertoire
char    *ft_get_absolute_path(const char *path);       // Chemin absolu
int     ft_count_char(const char *str, char c);        // Comptage caractère
```

## 🏗️ Structures Utilitaires

### **Gestion d'Erreurs**

```c
typedef enum e_error_code {
    ERR_SUCCESS = 0,
    ERR_MALLOC,
    ERR_INVALID_ARG,
    ERR_FILE_NOT_FOUND,
    ERR_PERMISSION_DENIED,
    ERR_SYNTAX_ERROR
} t_error_code;

typedef struct s_error {
    t_error_code    code;
    char            *message;
    char            *context;
} t_error;
```

### **Buffer Dynamique**

```c
typedef struct s_buffer {
    char    *data;
    size_t  size;
    size_t  capacity;
} t_buffer;

// Fonctions buffer
t_buffer    *buffer_create(size_t initial_size);
int         buffer_append(t_buffer *buf, const char *str);
int         buffer_append_char(t_buffer *buf, char c);
char        *buffer_to_string(t_buffer *buf);
void        buffer_destroy(t_buffer *buf);
```

## 📝 Macros Utilitaires

### **Gestion Mémoire**

```c
#define SAFE_FREE(ptr) do { \
    if (ptr) { \
        free(ptr); \
        ptr = NULL; \
    } \
} while(0)

#define SAFE_MALLOC(size) ({ \
    void *ptr = malloc(size); \
    if (!ptr) { \
        perror("malloc"); \
        exit(EXIT_FAILURE); \
    } \
    ptr; \
})
```

### **Debug et Logging**

```c
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d: " fmt "\n", \
                __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif

#define ERROR_PRINT(fmt, ...) \
    fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__)
```

## 🧪 Tests de Validation

### **Tests de Chaînes**

```c
// Test ft_strjoin
char *result = ft_strjoin("Hello", " World");
assert(strcmp(result, "Hello World") == 0);

// Test ft_split
char **words = ft_split("one,two,three", ',');
assert(ft_arraylen(words) == 3);
assert(strcmp(words[0], "one") == 0);
```

### **Tests de Mémoire**

```c
// Test allocation/libération
char *ptr = ft_malloc(100);
assert(ptr != NULL);
ft_free((void**)&ptr);
assert(ptr == NULL);
```

## 🔗 Interface avec les Autres Modules

### **Utilisé par Tous les Modules**

- **Lexer** : Manipulation de chaînes, validation
- **Parser** : Gestion de tableaux, allocation
- **Expander** : Manipulation de chaînes, conversion
- **Executor** : Utilitaires système, gestion erreurs
- **Builtins** : Validation, conversion, système
- **Environment** : Manipulation de tableaux, chaînes
- **Signals** : Macros de debug, gestion erreurs

### **Aucune Dépendance**

- Module autonome
- Uniquement les fonctions système standard
- Pas de dépendance circulaire

## 💡 Optimisations Possibles

### **Cache de Chaînes**

```c
typedef struct s_string_cache {
    char    *original;
    char    *cached;
    size_t  hash;
} t_string_cache;
```

### **Pool de Mémoire**

```c
typedef struct s_memory_pool {
    void    *pool;
    size_t  size;
    size_t  used;
    size_t  block_size;
} t_memory_pool;
```

### **Fonctions Inline**

```c
// Fonctions courtes en inline pour performance
static inline bool ft_isspace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' ||
            c == '\r' || c == '\f' || c == '\v');
}
```
