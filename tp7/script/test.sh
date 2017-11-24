#!/bin/bash
EXPECTED_DIR="src/test"
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`
echo "Script de test automatisé"
for filename in bin/test/*; do
  NAME=$(basename $filename)
  $filename 1> "$EXPECTED_DIR/$NAME.out" 2>&1
  if diff "$EXPECTED_DIR/$NAME.expected" "$EXPECTED_DIR/$NAME.out" > /dev/null;
  then
    echo "${green}[PASS] $NAME${reset}"
  else
    >&2 echo "${red}[FAIL] $NAME${reset}"
  fi
done
