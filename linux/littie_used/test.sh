#!/bin/sh
#-----LANG-------
LANG="C"
#----dainyu---
PARA1="string"
PARA2=string
PARA3=3
PARA4=`date '+%Y-%m-%d'`
#-----print------

echo "PARA1=${PARA1}"
echo "PARA2=${PARA2}"
echo "PARA3=${PARA3}"
echo "PARA4=${PARA4}"
PARA5=`date '+%d-%B-%Y'`
echo "PARA5=${PARA5}"

#------temp if--------
pwd
ret=$?
if test ${ret} -eq 0
then
	echo "pwd true"
else
	echo "pwd false"
fi
#------temp while--------
a=0
while [ $a -ne 10 ]
do
	a=`expr $a + 1`	
	echo" doing ${a} times !!"
done
#------temp for------------
for arg in $@
do
	echo ${arg}
done
