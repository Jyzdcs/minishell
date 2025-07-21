#!/bin/bash

# =============================================================================
# SCRIPT DE TEST DE L'EXPANDER - MINISHELL
# =============================================================================

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compteurs de tests
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Variables d'environnement pour les tests
export TEST_VAR="hello"
export USER="testuser"
export HOME="/home/testuser"

# Fonction pour afficher les résultats
print_header() {
    echo -e "${BLUE}=================================================${NC}"
    echo -e "${BLUE}           TEST DE L'EXPANDER - MINISHELL${NC}"
    echo -e "${BLUE}=================================================${NC}"
    echo ""
}

print_test_category() {
    echo -e "${YELLOW}--- $1 ---${NC}"
}

test_expander() {
    local test_name="$1"
    local input="$2"
    local expected_output="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -n "Test: $test_name... "
    
    # Exécuter le test et capturer la sortie
    result=$(echo "$input" | timeout 5s ./minishell 2>/dev/null | grep -v "Token:" | tail -n 1)
    
    if [ $? -eq 124 ]; then
        echo -e "${RED}TIMEOUT${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        return
    fi
    
    # Comparer avec le résultat attendu
    if [ "$result" = "$expected_output" ]; then
        echo -e "${GREEN}PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}FAIL${NC} (attendu: '$expected_output', obtenu: '$result')"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

test_expander_output() {
    local test_name="$1"
    local input="$2"
    
    echo -e "${BLUE}Test détaillé: $test_name${NC}"
    echo "Input: '$input'"
    echo "Output:"
    echo "$input" | timeout 5s ./minishell 2>/dev/null | grep -v "Token:" | sed 's/^/  /'
    echo ""
}

print_summary() {
    echo ""
    echo -e "${BLUE}=================================================${NC}"
    echo -e "${BLUE}                RÉSUMÉ DES TESTS${NC}"
    echo -e "${BLUE}=================================================${NC}"
    echo -e "Total des tests: $TOTAL_TESTS"
    echo -e "${GREEN}Tests réussis: $PASSED_TESTS${NC}"
    echo -e "${RED}Tests échoués: $FAILED_TESTS${NC}"
    echo ""
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "${GREEN}🎉 TOUS LES TESTS ONT RÉUSSI ! 🎉${NC}"
    else
        echo -e "${RED}❌ $FAILED_TESTS test(s) ont échoué${NC}"
    fi
}

# =============================================================================
# DÉMARRAGE DES TESTS
# =============================================================================

print_header

# Compilation du projet
echo -e "${YELLOW}Compilation du projet...${NC}"
make clean > /dev/null 2>&1
make > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo -e "${RED}ERREUR: Échec de la compilation${NC}"
    exit 1
fi

echo -e "${GREEN}Compilation réussie !${NC}"
echo ""

# =============================================================================
# TESTS BASIQUES
# =============================================================================

print_test_category "TESTS BASIQUES"

test_expander "Variable simple" "echo \$TEST_VAR" "hello"
test_expander "Variable USER" "echo \$USER" "testuser"
test_expander "Variable HOME" "echo \$HOME" "/home/testuser"
test_expander "Variable inexistante" "echo \$NONEXISTENT" ""

# =============================================================================
# TESTS AVEC QUOTES
# =============================================================================

print_test_category "TESTS AVEC QUOTES"

test_expander "Variable dans quotes doubles" 'echo "$TEST_VAR"' "hello"
test_expander "Variable dans quotes simples" "echo '\$TEST_VAR'" '\$TEST_VAR'
test_expander "Mixte quotes doubles" 'echo "Hello $USER"' "Hello testuser"

# =============================================================================
# TESTS PARAMÈTRES SPÉCIAUX
# =============================================================================

print_test_category "TESTS PARAMÈTRES SPÉCIAUX"

test_expander "Code de retour \$?" "echo \$?" "0"
test_expander "PID du shell \$\$" "echo \$\$" "[0-9]*"

# =============================================================================
# TESTS COMPLEXES
# =============================================================================

print_test_category "TESTS COMPLEXES"

test_expander "Variables multiples" "echo \$USER \$HOME" "testuser /home/testuser"
test_expander "Variable avec texte" "echo Hello_\$USER_World" "Hello_testuser_World"

# =============================================================================
# TESTS DÉTAILLÉS (AFFICHAGE COMPLET)
# =============================================================================

print_test_category "TESTS DÉTAILLÉS"

test_expander_output "Expansion complexe" 'echo "User: $USER, Home: $HOME"'
test_expander_output "Variable avec opérateurs" 'echo $USER > file.txt'

# Nettoyage et résumé
echo "exit" | ./minishell > /dev/null 2>&1

print_summary

# Code de sortie basé sur les résultats
if [ $FAILED_TESTS -eq 0 ]; then
    exit 0
else
    exit 1
fi 