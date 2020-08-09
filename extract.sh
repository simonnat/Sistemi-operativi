#!/bin/sh

if [ $# = 2 ]
then
	cat $1 | egrep -v '\<'$2'+[^0-9a-zA-Z]' ;         #cat opera riga per riga, nessun ciclo necessario
	exit 0;
else
	echo "inserisci due argomenti";
	exit 1;
fi
 
