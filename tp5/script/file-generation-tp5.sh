#!/bin/bash
rep=res/disk/R

rm all.txt
rm shuff.txt
rm -rf $rep

mkdir -p $rep

for pre in {A..Z}; do
  for sous in {A..H}; do
    echo "$pre$sous" >> all.txt
  done
done
shuf all.txt >> shuff.txt


outname=0
i=0
filename="shuff.txt"
while read -r line
do
  echo $line >> "$rep/$outname.txt"
  i=$((i+1))
  if [ "$i" = "10" ]; then
    i=0
    outname=$((outname+1))
  fi
done < "$filename"

rm all.txt
rm shuff.txt
