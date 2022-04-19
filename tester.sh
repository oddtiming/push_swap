# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/17 17:32:33 by iyahoui-          #+#    #+#              #
#    Updated: 2022/04/19 17:44:39 by iyahoui-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#! /bin/bash

RED="\033[31m"
GREEN="\033[32m"
ENDCOLOR="\033[0m"

NB_VALS=7
MAX_NB_MOVES=0
MAX_TEST_ID=0
# N=1.38
# LIMIT=$(bc -l <<< "e($N*l($NB_VALS))")
LIMIT=3800
INT_LIMIT=${LIMIT%.1}
NB_CASES_ABOVE_LIMIT=0
ITERATIONS=1
SUM=0
LOG_FILE=sore_thumbs_$NB_VALS.log
PS_TEMPFILE=tester_temp.log

echo "${GREEN}Testing for ${NB_VALS} values ${ENDCOLOR}"

for i in {1..100}
do
	export ARG=`ruby -e "puts (1..$NB_VALS).to_a.shuffle.join(' ')"`
	# echo $ARG
	./push_swap $ARG > $PS_TEMPFILE
	NB_MOVES=$(< $PS_TEMPFILE wc -l | sed 's/ //g');
	if [ $(< $PS_TEMPFILE ./checker_Mac $ARG | grep KO) ];
	then
		echo "${RED}KO!${ENDCOLOR}"
		echo "KO!" >> $LOG_FILE
		echo $ARG >> $LOG_FILE
		echo "nb_moves:" >> $LOG_FILE
		echo $NB_MOVES >> $LOG_FILE
		break
	fi
	if [ $(echo "$NB_MOVES > $LIMIT" | bc) -eq 1 ];
	then
		echo "Test #"$i":" $NB_MOVES "[$(cat $PS_TEMPFILE | ./checker_Mac $ARG)]" >> $LOG_FILE
		echo $ARG >> $LOG_FILE
		echo "" >> $LOG_FILE
		let NB_CASES_ABOVE_LIMIT+=1;
	fi
	if [ $(echo $NB_MOVES ">" $MAX_NB_MOVES | bc) -eq 1 ];
		then
			echo "Test #"$i":" $NB_MOVES "[$(cat $PS_TEMPFILE | ./checker_Mac $ARG)]" >> $LOG_FILE
			echo "$ARG" >> $LOG_FILE
			echo "" >> $LOG_FILE
			MAX_NB_MOVES=$NB_MOVES;
			MAX_TEST_ID=$i;
	fi

	if [ $(echo $NB_MOVES "<" $LIMIT | bc) -eq 1 ];
	then
		echo "${i} : ${GREEN}${NB_MOVES}${ENDCOLOR}"
	else
		echo "${i} : ${RED}${NB_MOVES}${ENDCOLOR}"
	fi
	let SUM+=$NB_MOVES;
	let ITERATIONS+=1;
	let i+=1;
done

rm $PS_TEMPFILE
echo "Nb tests done:" $(($ITERATIONS - 1))
if [ $(echo "$(($SUM / ($ITERATIONS - 1))) < ${LIMIT}" | bc) -eq 1 ];
then
	echo "${GREEN}Average nb of moves: $(($SUM / ($ITERATIONS - 1)))${ENDCOLOR}"
else
	echo "${RED}Average nb of moves: $(($SUM / ($ITERATIONS - 1)))${ENDCOLOR}"
fi

if [ $(echo $MAX_NB_MOVES "<" $LIMIT | bc) -eq 1 ];
then
	echo "${GREEN}Worst nb of moves: ${MAX_NB_MOVES}${ENDCOLOR}"
else
	echo "${RED}Worst nb of moves: ${MAX_NB_MOVES}${ENDCOLOR}"
fi

if [ $NB_CASES_ABOVE_LIMIT -eq 0 ];
then
	printf "${GREEN}%s %.0f %s %d\n${ENDCOLOR}" "Nb of moves above" $LIMIT ":" $NB_CASES_ABOVE_LIMIT
else
	printf "${RED}%s %.0f %s %d\n${ENDCOLOR}" "Nb of moves above" $LIMIT ":" $NB_CASES_ABOVE_LIMIT
fi

echo "Nb tests done:" $ITERATIONS >> $LOG_FILE
echo "Average nb of moves: $(($SUM / ($ITERATIONS - 1)))" >> $LOG_FILE
echo "(Test #"$MAX_TEST_ID") Worst nb of moves:" $MAX_NB_MOVES >> $LOG_FILE
printf "%s %.0f %s %d\n" "Nb of moves above" $LIMIT ":" $NB_CASES_ABOVE_LIMIT >> $LOG_FILE
