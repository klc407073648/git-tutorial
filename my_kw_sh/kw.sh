#!/bin/bash
record=""
num=0

cat kw.txt | while read line
do
  if [ "${line:0:1}" == "#" ];then     
     if [ $num != 0 ];then
     echo $record 
	   ID=`echo $record | cut -d ':' -f 1 | cut -d '#' -f 2 `
	   PROBLEM=`echo $record | cut -d '/' -f 1 | cut -d ':' -f 2 `
	   CODEPATH=`echo $record | cut -d '/' -f 2- | cut -d 'C' -f 1 `
	   CODE=`echo ${record##*CODE} | cut -d '|' -f 1 | cut -d ':' -f 2`
	   SERVERITY=`echo ${record##*severity} | cut -d '|' -f 1 | cut -d ':' -f 2`
	   echo "$ID $PROBLEM $CODEPATH $CODE $SERVERITY" >> b.txt
     record=""   
     fi
     record=${record}${line}
     num=$num+1
  elif  [ "${line:0:1}" != "#" ];then
     record=${record}${line}
  fi 
done

