#!/bin/bash
red=$(tput bold ; tput setaf 1)
green=$(tput setaf 2)
yellow=$(tput bold ; tput setaf 3)
blue=$(tput bold ; tput setaf 4)
magenta=$(tput bold ; tput setaf 5)
cyan=$(tput bold ; tput setaf 6)
reset=$(tput sgr0)

ft_check_errors()
{
	if [[ ("$1" == *"error"* || "$1" == *"ERROR"* || "$1" == *"Error"*) && $2 -eq 1 ]]
	then
		printf "%s[OK]%s\n" "$green" "$reset"
	else
 		printf "%s[KO][KO][KO]%s\n" "$red" "$reset"
	fi
}

ft_error_maps()
{
	comm="NULL"
	len=0
	printf "\n%12sERROR_MAPS%s\n" "$cyan" "$reset"
	for directory in $2/*
	do
		printf "\t%s\n" "$yellow$(basename $directory) : $reset"
		for file in $directory/*
		do
			error=$($1 < $file)
			length=$($1 < $file | wc -l | tr -d ' ')
			printf "\t\t%-20s : " "$(basename $file)"
			ft_check_errors $error $length
		done
		printf "\n"
	done
}

ft_check_valid()
{
	if [[ $1 -eq 1 ]]
	then
		printf "%s[KO][KO][KO]%s\n" "$red" "$reset"
		
	else
 		printf "%s[OK]%s\n" "$green" "$reset"
	fi
}

ft_valid_maps()
{
	comm="NULL"
	len=0
	printf "\n%12sVALID_MAPS%s\n" "$cyan" "$reset"
	for directory in $2/*
	do
		printf "\t%s\n" "$yellow$(basename $directory) : $reset"
		for file in $directory/*
		do
			length=$($1 < $file | wc -l | tr -d ' ')
			printf "\t\t%-20s : " "$(basename $file)"
			ft_check_valid $length
		done
		printf "\n"
	done
}