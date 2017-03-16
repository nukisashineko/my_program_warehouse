#/bin/sh
FILE_NAME=$1
FILE_2=$2
if [ $# -eq 1 ]
then
	if [ -d $FILE_NAME ]
	then
		 echo "-d is true"
	else
		 echo "-d is false"
	fi
	if [ -f $FILE_NAME ]
	then
		 echo "-f is true"
	else
		 echo "-f is false"
	fi
	if [ -l $FILE_NAME ]
	then
		 echo "-l is true"
	else
		 echo "-l is false"
	fi
	if [ -r $FILE_NAME ]
	then
		 echo "-r is true"
	else
		 echo "-r is false"
	fi
	if [ -w $FILE_NAME ]
	then
		 echo "-w is true"
	else
		 echo "-w is false"
	fi
	if [ -x $FILE_NAME ]
	then
		 echo "-x is true"
	else
		 echo "-x is false"
	fi
	if [ -s $FILE_NAME ]
	then
		 echo "-s is true"
	else
		 echo "-s is false"
	fi
elif [ $# -eq 2 ]
then
	if [  $FILE_NAME -nt $FILE_2 ]
	then
		 echo "-nt is true "
	else
		 echo "-nt is false"
	fi
	if [  $FILE_NAME -ot $FILE_2 ]
	then
		 echo "-ot is true "
	else
		 echo "-ot is false"
	fi
else
	echo "arg is false ..."
	echo "$0 is one or two args read !!"
fi
