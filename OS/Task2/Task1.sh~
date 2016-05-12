#!/bin/bash    
number=$RANDOM   
a="a"
b="b"
c="c"
txt=".txt"
one="1"


echo $number   
echo $(($number % 3))
for i in `seq 1 100`;
        do
            if [ "$(($number % 3))" = 0 ]; then
	       number=$RANDOM  
               the_file=$a$txt
               echo $a > $the_file
               a=$a$one
            else
               if [ "$(($number % 3))" = 1 ]; then
		   number=$RANDOM  
                   the_file=$b$txt
                   echo $b > $the_file
                   b=$b$one
	       else
	           number=$RANDOM  
		   the_file=$c$txt
		   echo $c > $the_file
	           c=$c$one
               fi
            fi
        done     
