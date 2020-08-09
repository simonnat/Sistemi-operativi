#!/bin/sh

if [ $# -gt 2 ]
then
	echo $0: toomany arguments
	echo usage: $0 '[month [year]]'
	exit 1
elif [ $# -eq 0 ]
then 
	cal
	exit 0
elif [ $# -eq 1 ]
then
	month=$(echo $1 | tr 'A-Z' 'a-z')
	case $1 in
	gen|gennaio ) cal -m 1;;
	feb|febbraio) cal -m 2;;
	mar|marzo ) cal -m 3;;
	apr|aprile ) cal -m 4;;
	mag|maggio ) cal -m 5;;
	giu|giugno ) cal -m 6;;
	lug|luglio ) cal -m 7;;
	ago|agosto ) cal -m 8;;
	sett|settembre ) cal -m 9;;
	ott|ottobre ) cal -m 10;;
	nov| novembre ) cal -m 11;;
	dic|dicembre ) cal -m 12;;
	* ) echo "Ignorante non conosci neanche i mesi dell'anno";;
	esac

	exit 0
elif [ $# -eq 2 ]
then

	month=$(echo $1 | tr 'A-Z' 'a-z')
        case $1 in
        gen|gennaio ) cal -m 1 $2;;
        feb|febbraio) cal -m 2 $2;;
        mar|marzo ) cal -m 3 $2;;
        apr|aprile ) cal -m 4 $2;;
        mag|maggio ) cal -m 5 $2;;
        giu|giugno ) cal -m 6 $2;;
        lug|luglio ) cal -m 7 $2;;
        ago|agosto ) cal -m 8 $2;;
        sett|settembre ) cal -m 9 $2;;
        ott|ottobre ) cal -m 10 $2;;
        nov| novembre ) cal -m 11 $2;;
        dic|dicembre ) cal -m 12 $2;;
        * ) echo "Ignorante non conosci neanche i mesi dell'anno";;
        esac
	exit 0
fi
