ans_file="ans.txt"
if [ -f "ans_file" ]; then
  read -r ANS < ans_file
else
    ANS=0
fi
# declare an array to store the history
declare -a hist=()
# loop forever until the user types "EXIT"
while true;
do
    clear # clear the screen
    read -p ">> " a b c # read the input
    if [ "$a" == "ANS" ]; then # a can compare with EXIT, ANS, HIST
        a=$ANS
    fi
    if [ "$c" == "ANS" ]; then # c can compare with ANS
        c=$ANS
    fi
    if [ "$a" == "EXIT" ];
    then
        break
    elif [ "$a" == "HIST" ]
    then
        for ((i=0; i<${#hist[@]}; i++)); do # loop through the history array
          echo "${hist[$i]}"
        done
        read -n 1 -s -r -p "" # wait for any key press
        continue
    fi
    if ! [[ "$a" =~ ^[0-9]+(\.[0-9]+)?$ ]] || ! [[ "$c" =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
        echo "SYNTAX ERROR" # check if a and c are numbers
        read -n 1 -s -r -p ""
        continue
    fi
    if ! [ "$b" == "+" ] && ! [ "$b" == "-" ] && ! [ "$b" == "*" ] && ! [ "$b" == "/" ] && ! [ "$b" == "%" ]; then
        echo "SYNTAX ERROR" # check if b is a valid operator
        read -n 1 -s -r -p ""
        continue
    fi
    case $b in # perform the calculation based on the operator b
        +) res=$(echo "$a + $c" | bc)
        ;;
        -) res=$(echo "$a - $c" | bc)
        ;;
        \*) res=$(echo "$a * $c" | bc) # escape the * operator
        ;;
        %)
        if [ "$c" -eq "0" ]; then
          echo "MATH ERROR" # check if c is not zero in the modulo operation
          read -n 1 -s -r -p ""
          continue
        fi
        if [ "$a" -lt "$c" ]; then
          res=$a
        else
        res=$(echo "$a % $c" | bc)
        fi
        ;;
        /)
        if [ "$c" -eq "0" ]; then
          echo "MATH ERROR" # check if c is not zero in the division operation
          read -n 1 -s -r -p ""
          continue
        fi
        if [ "$a" -lt "$c" ]; then # check if a is less than c
          echo -n "0"
        fi
        res=$(echo "scale=2; $a / $c" | bc) # perform the division operation
        ;;
    esac
    hist+=("$a $b $c = $res") # add the calculation to the history
    echo "$res" # print the result
    ANS=$res # store the result in ANS
    echo $ANS > ans_file # store the ANS in the file
    read -n 1 -s -r -p ""
done

