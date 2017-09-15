#!/bin/bash
# " . " and " source " the same 
	 . files_for_test/tests.sh
source files_for_test/print.sh

# Print when cheking stopped by ctrl + c but also work when programm ending
# trap "printf '\t%sWow you stopped it... Bye%s' '$red' '$reset'" EXIT

if [ -n "$1" ]
then
	# ft_print_head
# Check error maps directory
	ft_error_maps $1 maps/error_maps
	ft_valid_maps $1 maps/valid_maps
	# ft_print_footer
else
printf "%s\tusage:%s\n" "$red" "$reset"
printf "\t\t./unit-test.sh lem-in\n"
fi






