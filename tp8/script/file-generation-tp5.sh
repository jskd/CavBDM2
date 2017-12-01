#!/bin/bash
rep=res/demo/tp5/R
f_all=$rep/all.txt
f_shuff=$rep/shuff.txt

rm -rf $rep
mkdir -p $rep

for pre in {A..Z}; do
  for sous in {A..H}; do
    echo "$pre$sous" >> $f_all
  done
done
shuf $f_all >> $f_shuff

outname=0
i=0
while read -r line
do
  echo $line >> "$rep/R$outname.txt"
  i=$((i+1))
  if [ "$i" = "10" ]; then
    i=0
    outname=$((outname+1))
  fi
done < "$f_shuff"

rm $f_all
rm $f_shuff
