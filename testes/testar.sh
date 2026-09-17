#!/bin/bash
# uso:
#   bash testes/testar.sh parte1
#   bash testes/testar.sh missao1
#   bash testes/testar.sh missao2
#   bash testes/testar.sh missao3
set -e

ALVO="$1"
if [ -z "$ALVO" ]; then
    echo "uso: bash testes/testar.sh <parte1|missao1|missao2|missao3>"
    exit 1
fi

case "$ALVO" in
    parte1) PASTA="testes/parte1" ;;
    missao1) PASTA="testes/missao1" ;;
    missao2) PASTA="testes/missao2" ;;
    missao3) PASTA="testes/missao3" ;;
    *) echo "alvo desconhecido: $ALVO"; exit 1 ;;
esac

echo "compilando..."
g++ -std=c++11 -Wall -Wno-sign-compare src/main.cpp -o agencia
if [ $? -ne 0 ]; then
    echo "ERRO DE COMPILACAO"
    exit 1
fi

TOTAL=0
PASSOU=0

for arquivo_in in "$PASTA"/*.in; do
    [ -e "$arquivo_in" ] || continue
    nome=$(basename "$arquivo_in" .in)
    arquivo_out="$PASTA/$nome.out"
    TOTAL=$((TOTAL+1))

    saida=$(./agencia < "$arquivo_in")
    esperado=$(cat "$arquivo_out")

    if [ "$saida" == "$esperado" ]; then
        echo "PASSOU - $nome"
        PASSOU=$((PASSOU+1))
    else
        echo "FALHOU - $nome"
        diff <(echo "$esperado") <(echo "$saida")
    fi
done

echo ""
echo "$PASSOU de $TOTAL testes passaram"
