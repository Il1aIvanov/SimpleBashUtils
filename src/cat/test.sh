#!/bin/bash

echo "----------"
echo "FLAG CHECK"

SUCCESS=0
FAIL=0
VERDICT=""

for flag in -b -n -e -s -t -v
do
    ./s21_cat $flag test.txt > s21_cat.txt
    cat $flag  test.txt > cat.txt
    VERDICT="$(diff -s s21_cat.txt cat.txt)"
    if [ "$VERDICT" == "Files s21_cat.txt and cat.txt are identical" ]
        then
            ((SUCCESS++))
        else
          echo "Flag $flag no passed"
            ((FAIL++))
    fi
rm -rf cat.txt s21_cat.txt
done

echo "-------"
echo "VERDICT"

echo "Passed $SUCCESS tests"
echo "Failed $FAIL tests"
