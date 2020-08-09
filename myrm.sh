#!/bin/bash

trashdir="$HOME/.local/share/Trash/files"

if [ $# -eq 0 ]
then	
	echo "No argument"
	exit 1

elif [ $# -eq 1 ]
then


	if [[ $1 =~ ^-. ]]
	then
		if [ "$1" = "-e" ]
			    then
				cd $trashdir
                                                ls | while read fname
                                                        do
                                                          rm -r $fname
                                                        done
                                                        exit 0

                fi

		echo "Incorrect entry"
		exit 1
	elif [ -e $1 ]
		then	
		mv $1 $trashdir
		exit 0
	else
		echo "No file"
		exit 1
	fi
elif [ $# -eq 2 ]
then

	if [[ $1 =~ ^-. ]]
	then
	del_dir=$(pwd)/$2
		if [ -e $2 ]
		then
		case $1 in
			-r|-R|--recursive ) if [ -d $2 ] 
						then
						cd $del_dir 
						ls | while read fname
							do
							  mv $fname $trashdir
			 				done
							cd ..
							mv $del_dir $trashdir
							exit 0
						else
							echo "No directory"
							exit 1	
			 			fi;;
			                           
			
				
								
			-* ) echo "Non supportato" ; exit 0 ;;
		esac
		else
			echo "No file"
			exit 1
		
	fi
	elif [[ $2 =~ ^-* ]]
	then
		if [ -e $1 ]
                then
		del_dir=$(pwd)/$1
                case $2 in
                        -r|-R|--recursive ) 
					if [ -d $1 ]
						then
						cd $del_dir
                                                ls | while read fname
                                                        do
                                                          mv $fname $trashdir
                                                        done
                                                        cd ..
                                                        mv $del_dir $trashdir
                                                        exit 0
 						else    
                                                        echo "No directory"
                                                        exit 1
                                                fi;;

     

                        -* ) echo "Non supportato" ; exit 0 ;;
                esac
	else 
		echo "No file"
		exit 1
                fi

	
	fi
elif [ $# > 2 ]
	then
	echo "Too much argument"
fi

