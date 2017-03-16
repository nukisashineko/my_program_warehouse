#!/bin/bash

comand_name=`basename $0`

while getopts ab:c: OPT
do
		case $OPT in
				"a" ) flagA="true" ;;
				"b" ) flagB="true" ; valueB="$OPTARG" ;;
				"c" ) flagC="true" ; valueC="$OPTARG" ;;
				  * ) echo "Usage : $comand_name [-a] [-b VALUE] [-c VALUE]" 1>&2
					   exit 1 ;;
		esac
done


if [ $flagA = "true" ]; then
		echo 'you order -a option.'
fi

if [ $flagB = "true" ]; then
		echo 'you order -b option.'
		echo "value is $valueB"
fi

if [ $flagC = "true" ]; then
		echo 'you order -c option.'
		echo "value is $valueC"
fi

echo "\$1==$1"
shift `expr $OPTIND - 1`
echo "\$1==$1"

exit 0
