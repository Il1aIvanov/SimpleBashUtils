#!/bin/bash

echo "----------"
echo "FLAG CHECK"

SUCCESS=0
FAIL=0
VERDICT=""

for flag1 in -e -i -v -c -l -n -h -s -o
do
  ./s21_grep $flag1 "he" test.txt > s21_grep.txt
  grep $flag1 "he" test.txt > grep.txt
  VERDICT="$(diff -s s21_grep.txt grep.txt)"
  if [ "$VERDICT" == "Files s21_grep.txt and grep.txt are identical" ]
          then
            (( SUCCESS++ ))
          else
            echo "Flag $flag1 not passed"
            (( FAIL++ ))
        fi
rm -rf grep.txt s21_grep.txt
done

echo "-----------------"
echo "DOUBLE FLAG CHECK"

for flag1 in -i -v -c -l -n -h -s -o
do
  for flag2 in -i -v -c -l -n -h -s -o
  do
  if [ $flag1 != $flag2 ] && [ $flag2 != $flag1 ]
     then
      ./s21_grep $flag1 $flag2 "he" test.txt > s21_grep.txt
      grep $flag1 $flag2 "he" test.txt > grep.txt
      VERDICT="$(diff -s s21_grep.txt grep.txt)"
      if [ "$VERDICT" == "Files s21_grep.txt and grep.txt are identical" ]
              then
                (( SUCCESS++ ))
              else
                echo "Flags $flag1 $flag2 not passed"
                (( FAIL++ ))
      fi
      rm -rf grep.txt s21_grep.txt
      fi
    done
done
echo "-------"
echo "VERDICT"

echo "Passed $SUCCESS tests"
echo "Failed $FAIL tests"
