# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    benchmark.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/29 17:15:18 by vbrazhni          #+#    #+#              #
#    Updated: 2022/03/04 02:24:10 by iyahoui-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

MAX=0
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
		if [ "$NUMBER" -gt "$MAX" ]
			then
			MAX=$NUMBER;
		fi
		echo $i ":" $NUMBER
		let SUM+=$NUMBER;
		let ITERATIONS+=1
done

echo "AVG: $(($SUM / $ITERATIONS))"
echo "MAX: " $MAX
