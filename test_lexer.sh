#!/bin/bash

# =============================================================================
# SCRIPT DE TEST DU LEXER - MINISHELL
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

# Fonction pour afficher les résultats
print_header() {
    echo -e "${BLUE}=================================================${NC}"
    echo -e "${BLUE}            TEST DU LEXER - MINISHELL${NC}"
    echo -e "${BLUE}=================================================${NC}"
    echo ""
}

print_test_category() {
    echo -e "${YELLOW}--- $1 ---${NC}"
}

test_lexer() {
    local test_name="$1"
    local input="$2"
    local expected_tokens="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -n "Test: $test_name... "
    
    # Exécuter le test et capturer la sortie
    result=$(echo "$input" | timeout 5s ./minishell 2>/dev/null | grep "Token:" | wc -l)
    
    if [ $? -eq 124 ]; then
        echo -e "${RED}TIMEOUT${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        return
    fi
    
    # Comparer avec le nombre de tokens attendu
    if [ "$result" -eq "$expected_tokens" ]; then
        echo -e "${GREEN}PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}FAIL${NC} (attendu: $expected_tokens, obtenu: $result)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
}

test_lexer_output() {
    local test_name="$1"
    local input="$2"
    
    echo -e "${BLUE}Test détaillé: $test_name${NC}"
    echo "Input: '$input'"
    echo "Output:"
    echo "$input" | timeout 5s ./minishell 2>/dev/null | grep "Token:" | sed 's/^/  /'
    echo ""
}

# Fonction pour tester les erreurs (quotes non fermées)
test_lexer_error() {
    local test_name="$1"
    local input="$2"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -n "Test: $test_name... "
    
    # Tester que le lexer retourne une erreur
    result=$(echo "$input" | timeout 5s ./minishell 2>/dev/null | grep "Erreur" | wc -l)
    
    if [ "$result" -gt 0 ]; then
        echo -e "${GREEN}PASS${NC} (erreur détectée)"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}FAIL${NC} (erreur non détectée)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
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

test_lexer "Commande simple" "ls" 1
test_lexer "Commande avec argument" "ls -l" 2
test_lexer "Commande avec plusieurs arguments" "ls -l -a" 3
test_lexer "Commande avec espaces multiples" "ls    -l     -a" 3

# =============================================================================
# TESTS AVEC OPÉRATEURS
# =============================================================================

print_test_category "TESTS AVEC OPÉRATEURS"

test_lexer "Pipe simple" "ls | wc" 3
test_lexer "Redirection entrée" "cat < file.txt" 3
test_lexer "Redirection sortie" "echo hello > output.txt" 4
test_lexer "Redirection append" "echo hello >> output.txt" 4
test_lexer "Heredoc" "cat << EOF" 3
test_lexer "Opérateurs multiples" "ls -l | grep test > result.txt" 7

# =============================================================================
# TESTS AVEC QUOTES
# =============================================================================

print_test_category "TESTS AVEC QUOTES"

test_lexer "Quotes simples" "echo 'hello world'" 2
test_lexer "Quotes doubles" 'echo "hello world"' 2
test_lexer "Quotes simples avec espaces" "echo 'hello    world'" 2
test_lexer "Quotes doubles avec variable" 'echo "hello $USER"' 2

# =============================================================================
# TESTS D'ERREURS
# =============================================================================

print_test_category "TESTS D'ERREURS"

test_lexer_error "Quote simple non fermée" "echo 'hello"
test_lexer_error "Quote double non fermée" 'echo "hello'
test_lexer_error "Quote simple ouverte non fermée" "echo 'hello world"

# =============================================================================
# TESTS DÉTAILLÉS (AFFICHAGE COMPLET)
# =============================================================================

print_test_category "TESTS DÉTAILLÉS"

test_lexer_output "Commande complexe" "ls -la | grep test > results.txt"
test_lexer_output "Avec redirections multiples" "cat < input.txt > output.txt"
test_lexer_output "Avec quotes et opérateurs" 'echo "hello world" | cat > "output file.txt"'

# Nettoyage et résumé
echo "exit" | ./minishell > /dev/null 2>&1

print_summary

# Code de sortie basé sur les résultats
if [ $FAILED_TESTS -eq 0 ]; then
    exit 0
else
    exit 1
fi 