#!/bin/bash

# =============================================================================
# TEST MANUEL SIMPLE DU LEXER
# =============================================================================

echo "🔧 Compilation du projet..."
make > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "❌ ERREUR: Échec de la compilation"
    exit 1
fi

echo "✅ Compilation réussie !"
echo ""

echo "📝 TESTS MANUELS DU LEXER"
echo "=========================="
echo ""

# Fonction pour tester et afficher
test_input() {
    echo "Input: '$1'"
    echo "$1" | ./minishell 2>/dev/null
    echo ""
}

echo "--- Tests basiques ---"
test_input "ls"
test_input "ls -l"
test_input "ls -l -a"

echo "--- Tests avec opérateurs ---"
test_input "ls | wc"
test_input "cat < file.txt"
test_input "echo hello > output.txt"
test_input "echo hello >> output.txt"
test_input "cat << EOF"

echo "--- Tests avec quotes ---"
test_input "echo 'hello world'"
test_input 'echo "hello world"'

echo "--- Tests d'erreurs ---"
test_input "echo 'hello"
test_input 'echo "hello'

echo "--- Test complexe ---"
test_input "ls -la | grep test > results.txt"

echo "🎯 Tests terminés !" 