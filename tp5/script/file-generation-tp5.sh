#!/bin/bash
rm all.txt
for pre in {A..Z}; do
  for sous in {A..H}; do
    echo "$pre$sous" >> all.txt
  done
done
shuf all.txt >> shuff.txt

filename="shuff.txt"
while read -r line
do
  name="$line"
  echo "Name read from file - $name"
done < "$filename"
