#!/bin/bash

# =============================================================================
# TEST MANUEL SIMPLE DE L'EXPANDER
# =============================================================================

# Variables d'environnement pour les tests
export TEST_VAR="hello"
export USER="testuser"
export HOME="/home/testuser"

echo "🔧 Compilation du projet..."
make > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "❌ ERREUR: Échec de la compilation"
    exit 1
fi

echo "✅ Compilation réussie !"
echo ""

echo "📝 TESTS MANUELS DE L'EXPANDER"
echo "=============================="
echo ""

# Fonction pour tester et afficher
test_input() {
    echo "Input: '$1'"
    echo "$1" | ./minishell 2>/dev/null
    echo ""
}

echo "--- Tests basiques ---"
test_input "echo \$TEST_VAR"
test_input "echo \$USER"
test_input "echo \$HOME"
test_input "echo \$NONEXISTENT"

echo "--- Tests avec quotes ---"
test_input 'echo "$TEST_VAR"'
test_input "echo '\$TEST_VAR'"
test_input 'echo "Hello $USER"'

echo "--- Tests paramètres spéciaux ---"
test_input "echo \$?"
test_input "echo \$\$"

echo "--- Tests complexes ---"
test_input "echo \$USER \$HOME"
test_input "echo Hello_\$USER_World"
test_input 'echo "User: $USER, Home: $HOME"'

echo "🎯 Tests terminés !" 