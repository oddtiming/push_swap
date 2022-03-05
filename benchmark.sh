# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    benchmark.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/29 17:15:18 by vbrazhni          #+#    #+#              #
#    Updated: 2022/03/05 00:20:50 by iyahoui-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

MAX=0
MAX_MOVES=5500
NB_ABOVE=0
ITERATIONS=1
LIMIT=5500
FILE=problem_100
SUM=0

for i in {1..1000}
do
		export ARG=`ruby -e "puts (1..500).to_a.shuffle.join(' ')"`
		if ./push_swap $ARG | ./checker_Mac $ARG | grep -q KO
		then
			echo "Error!"
			echo $ARG
			break
		fi
		NUMBER="$(./push_swap $ARG | wc -l | sed 's/ //g')"
		if [ "$NUMBER" -gt "$LIMIT" ]
			then
			echo $NUMBER >> $FILE
			echo $ARG >> $FILE
		fi
		if [ "$NUMBER" -gt "$MAX_MOVES" ]
			then
			let NB_ABOVE+=1;
			echo $ARG
		fi
		if [ "$NUMBER" -gt "$MAX" ]
			then
			MAX=$NUMBER;
		fi
		echo $i ":" $NUMBER
		let SUM+=$NUMBER;
		let ITERATIONS+=1
done

echo "AVG: $(($SUM / $ITERATIONS))"
echo "MAX: "$MAX
echo "NB_ABOVE" $MAX_MOVES ":" $NB_ABOVE
