#!/bin/bash
i=0
suc=0
fail=0
TXT=catcat.txt
#TEST 1
i=$((i+1))
cat $TXT > 1
./s21_cat $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. No flags: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. No flags: FAIL"
    fail=$((fail+1))
fi

#TEST 2
i=$((i+1))

cat -b $TXT > 1
./s21_cat -b $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -b: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -b: FAIL"
    fail=$((fail+1))
fi

#TEST 3
i=$((i+1))

cat -b $TXT > 1
./s21_cat --number-nonblank $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -b GNU: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -b GNU: FAIL"
    fail=$((fail+1))
fi

#TEST 4
i=$((i+1))

cat -e $TXT > 1
./s21_cat -e $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -e: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -e: FAIL"
    fail=$((fail+1))
fi

#TEST 5
i=$((i+1))

cat -n $TXT > 1
./s21_cat -n $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -n: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -n: FAIL"
    fail=$((fail+1))
fi

#TEST 6
i=$((i+1))

cat -bn $TXT > 1
./s21_cat -bn $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flags -b -n: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flags -b -n: FAIL"
    fail=$((fail+1))
fi

#TEST 7
i=$((i+1))

cat -s $TXT > 1
./s21_cat -s $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -s: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -s: FAIL"
    fail=$((fail+1))
fi

#TEST 8
i=$((i+1))

cat -t $TXT > 1
./s21_cat -t $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -t: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -t: FAIL"
    fail=$((fail+1))
fi

#TEST 9
i=$((i+1))

cat -n $TXT > 1
./s21_cat --number $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -n GNU: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -n GNU: FAIL"
    fail=$((fail+1))
fi

#TEST 10
i=$((i+1))

cat -s $TXT > 1
./s21_cat --squeeze-blank $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -s GNU: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -s GNU: FAIL"
    fail=$((fail+1))
fi

#TEST 11
i=$((i+1))

cat -benst $TXT > 1
./s21_cat -benst $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flags -benst: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flags -benst: FAIL"
    fail=$((fail+1))
fi

#TEST 12
i=$((i+1))
cat -k $TXT > 1
./s21_cat -k $TXT > 2
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i. Flag -k: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i. Flag -k: FAIL"
    fail=$((fail+1))
fi

#Rownaca
echo "FAIL: $fail"
echo "SUCCESS: $suc"
echo "ALL: $i"
