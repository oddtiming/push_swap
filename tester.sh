#! /bin/bash

RED="\033[31m"
GREEN="\033[32m"
ENDCOLOR="\033[0m"

NB_VALS=8
MAX_NB_MOVES=0
N=1.38
LIMIT=$(bc -l <<< "e($N*l($NB_VALS))")
NB_CASES_ABOVE_MAX=0
ITERATIONS=0
SUM=0
LOG_FILE=sore_thumbs_$NB_VALS.log
PS_TEMPFILE=tester_temp.log

echo -e "${GREEN}Testing for ${NB_VALS} values ${ENDCOLOR}"


for i in {1..10}
do
	export ARG=`ruby -e "puts (1..$NB_VALS).to_a.shuffle.join(' ')"`
	./push_swap $ARG > $PS_TEMPFILE
	NB_MOVES=$(< $PS_TEMPFILE wc -l | sed 's/ //g');
	if < $PS_TEMPFILE ./checker_Mac $ARG | grep -q KO
	then
		echo "Error!"
		echo "Error!" >> $LOG_FILE
		echo $ARG >> $LOG_FILE
		echo "nb_moves:" >> $LOG_FILE
		echo $NB_MOVES >> $LOG_FILE
		break
	fi
	if [ $(echo "$NB_VALS > $LIMIT" | bc) -eq 1 ];
		then
		echo $ARG >> $LOG_FILE
		cat $PS_TEMPFILE | ./checker_Mac $ARG
		echo "nb_moves:" >> $LOG_FILE
		echo $NB_MOVES >> $LOG_FILE
		let NB_CASES_ABOVE_MAX+=1;
		echo $ARG 
	fi
	if [ $(echo $NB_MOVES ">" $MAX_NB_MOVES | bc) -eq 1 ]
	then
		MAX_NB_MOVES=$NB_MOVES;
		MAX_ARGS=$ARGS;
	fi
	echo $i ":" $NB_MOVES
	let SUM+=$NB_MOVES;
	let ITERATIONS+=1;
	let i+=1;
done

rm $PS_TEMPFILE
echo "Nb tests done:" $ITERATIONS
echo "Average nb of moves: $(($SUM / $ITERATIONS))"
echo "Worst nb of moves: "$MAX_NB_MOVES
echo "Nb of moves above" $LIMIT":" $NB_CASES_ABOVE_MAX
echo "Worst nb of moves: "$MAX_NB_MOVES >> $LOG_FILE
echo "Arguments:\n "$MAX_ARGS >> $LOG_FILE
echo "Nb tests done:" $ITERATIONS >> $LOG_FILE
echo "Nb of moves above" $LIMIT":" $NB_CASES_ABOVE_MAX >> $LOG_FILE
