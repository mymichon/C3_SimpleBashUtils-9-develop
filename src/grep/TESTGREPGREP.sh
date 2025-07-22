#!/bin/bash
i=0
suc=0
fail=0
PATTERN=HELLo
#For test -e -e
PATTERN1=Hello
TXT=*.txt
# For -f pattern.txt
PATTERNTXT=123.txt
COUNTER=0
#*.txt

testing()
{
i=$((i+1))
grep $var $PATTERN $TXT > 1
./s21_grep $var $PATTERN $TXT > 2

diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. $var: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. $var: FAIL"
    fail=$((fail+1))
fi
}

# 1 параметр
for var1 in v c l n h o
do
    var="-$var1"
    testing $i
done

# 2 параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        if [ $var1 != $var2 ]
        then
        
            var="-$var1 -$var2"
            testing $i
        
        fi
    done
done

for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        for var3 in v c l n h o
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
               
                var="-$var1 -$var2 -$var3"
                testing $i
                
            fi
        done
    done
done

# Test -e pattern1 -e pattern2 

i=$((i+1))

grep -e $PATTERN -e $PATTERN1 $TXT > 1
./s21_grep -e $PATTERN -e $PATTERN1 $TXT > 2

diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flags -e -e: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flags -e -e: FAIL"
    fail=$((fail+1))
fi



# Tests for -f pattern.txt TXT.txt
i=$((i+1))

grep -f $PATTERNTXT $TXT > 1
./s21_grep -f $PATTERNTXT $TXT > 2

diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -f: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -f: FAIL"
    fail=$((fail+1))
fi
#Rowenaca
echo "FAIL: $fail"
echo "SUCCESS: $suc\"
echo "ALL: $i"
