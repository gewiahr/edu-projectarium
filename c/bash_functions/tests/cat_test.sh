#!/bin/bash

SUCCESSFUL_TESTS=0
FAILED_TESTS=0
COUNTER=0
DIFF_SYSTEM_MESSAGE=" "
RED_COL="$(tput setaf 1)"
BLUE_COL="$(tput setaf 4)"
WHITE_COL="$(tput setaf 7)"

declare -a flags=(
    "b"
    "e"
    "n"
    "s"
    "t"
    "v"
)


declare -a files=(
    "tests\/test1.txt"
    "tests\/test2.txt"
    "tests\/test3.txt"
    "tests\/test1.txt tests\/test2.txt"
    "tests\/test1.txt tests\/test3.txt"
    "tests\/test1.txt tests\/test2.txt tests\/test3.txt"
)

input="OPTIONS FILE"

test_cat() {
    args=$(echo "$@" | sed -e "s/OPTIONS/$opt/")
    args=$(echo "$args" | sed -e "s/FILE/$file/")
    ./cat $args > my_cat.log
    cat $args > cat.log
    DIFF="$(diff -s my_cat.log cat.log)"
    let "COUNTER++"
    if [ "$DIFF" == "Files my_cat.log and cat.log are identical" ]
    then
        let "SUCCESSFUL_TESTS++"
        echo "$COUNTER - ${BLUE_COL}SUCCESS${WHITE_COL} $args"
    else
        let "FAILED_TESTS++"
        echo "$COUNTER - ${RED_COL}FAIL${WHITE_COL} $args"
    fi
    rm *.log
}

for flag1 in "${flags[@]}"
do
    opt="-$flag1"
    file=${files[ $RANDOM % ${#files[@]} ]}
    test_cat $input
done

for flag1 in "${flags[@]}"
do
    for flag2 in "${flags[@]}"
    do
        if [ $flag1 != $flag2 ]
        then
            opt="-$flag1 -$flag2"
            file=${files[ $RANDOM % ${#files[@]} ]}
            test_cat $input
        fi
    done
done

for flag1 in "${flags[@]}"
do
    for flag2 in "${flags[@]}"
    do
        for flag3 in "${flags[@]}"
        do
            if [ $flag1 != $flag2 ] && [ $flag3 != $flag2 ] && [ $flag1 != $flag3 ]
            then
                opt="-$flag1 -$flag2 -$flag3"
                file=${files[ $RANDOM % ${#files[@]} ]}
                test_cat $input
            fi
        done
    done
done

for flag1 in "${flags[@]}"
do
    for flag2 in "${flags[@]}"
    do
        for flag3 in "${flags[@]}"
        do
            for flag4 in "${flags[@]}"
            do
                if [ $flag1 != $flag2 ] && [ $flag2 != $flag3 ] \
                && [ $flag1 != $flag3 ] && [ $flag1 != $flag4 ] \
                && [ $flag2 != $flag4 ] && [ $flag3 != $flag4 ]
                then
                    opt="-$flag1 -$flag2 -$flag3 -$flag4"
                    file=${files[ $RANDOM % ${#files[@]} ]}
                    test_cat $input
                fi
            done
        done
    done
done

echo "============================="
echo "${BLUE_COL}SUCCESSFUL${WHITE_COL}: $SUCCESSFUL_TESTS"
echo "${RED_COL}FAILED${WHITE_COL}: $FAILED_TESTS"
echo "ALL: $COUNTER"
