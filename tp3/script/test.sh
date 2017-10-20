#!/bin/bash
EXPECTED_DIR="src/test"
echo "Script de test automatisé"
for filename in bin/test/*; do
  NAME=$(basename $filename)
  $filename > "$EXPECTED_DIR/$NAME.out"
  if diff "$EXPECTED_DIR/$NAME.expected" "$EXPECTED_DIR/$NAME.out" > /dev/null;
  then
    echo "[PASS] $NAME"
  else
    echo "[FAIL] $NAME ($EXPECTED_DIR/$NAME.out != $EXPECTED_DIR/$NAME.expected)"
  fi
done
