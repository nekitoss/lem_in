#!/bin/sh

COL="\033[;35m";
COL2="\033[;92m";
ESC="\033[33;0m";

echo "-------------------------------------------"
echo "${COL2}OK${ESC} 1_m.txt"
./lem-in < maps/1_m.txt
echo "-------------------------------------------"

echo "${COL2}OK${ESC}\n #comment at the beginning 10_m.txt"
./lem-in < maps/10_m.txt
echo "-------------------------------------------"

echo "${COL2}OK${ESC}\n ##bullshit before ants 15_m.txt"
./lem-in < maps/15_m.txt
echo "-------------------------------------------"

echo "${COL2}OK${ESC}\n qwerty name of the room 26_m.txt"
./lem-in < maps/26_m.txt
echo "-------------------------------------------"

echo "${COL2}OK${ESC}\n strange room names 34_m.txt"
./lem-in < maps/34_m.txt
echo "-------------------------------------------"

echo "${COL2}OK${ESC}\n hell of a lot of comments and commands 35_comments.txt"
#./lem-in < maps/35_comments.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n no ants 2_m.txt" 
cat maps/2_m.txt
./lem-in < maps/2_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n no ##start 3_m.txt"
cat maps/3_m.txt
./lem-in < maps/3_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n no ##end 4_m.txt"
cat maps/4_m.txt
./lem-in < maps/4_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n no ##start ##end ##bullshit instead 5_m.txt" 
cat maps/5_m.txt
./lem-in < maps/5_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n room instead of N of ants 6_m.txt" 
cat maps/6_m.txt
./lem-in < maps/6_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n zero ants 7_m.txt"
cat maps/7_m.txt
./lem-in < maps/7_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n comment after ##start 8_m.txt"
cat maps/8_m.txt
./lem-in < maps/8_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n comment after ##end 9_m.txt"
cat maps/9_m.txt
./lem-in < maps/9_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n ##start before ants 11_m.txt"
cat maps/11_m.txt
./lem-in < maps/11_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n ##end before ants 12_m.txt"
cat maps/12_m.txt
./lem-in < maps/12_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n 2 ##start 13_m.txt" 
cat maps/13_m.txt
./lem-in < maps/13_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n 2 ##end 14_m.txt"
cat maps/14_m.txt
./lem-in < maps/14_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n empty line after ants 16_m.txt"
cat maps/16_m.txt
./lem-in < maps/16_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n empty line after rooms 17_m.txt"
cat maps/17_m.txt
./lem-in < maps/17_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n empty line first 18_m.txt"
cat maps/18_m.txt
./lem-in < maps/18_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n ##end right after ##start 19_m.txt" 
cat maps/19_m.txt
./lem-in < maps/19_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n no rooms 20_m.txt"
cat maps/20_m.txt
./lem-in < maps/20_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n no connections 21_m.txt"
cat maps/21_m.txt
./lem-in < maps/21_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n no room that in connection 22_m.txt"
cat maps/22_m.txt
./lem-in < maps/22_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n connection with non-existing room 23_m.txt"
cat maps/23_m.txt
./lem-in < maps/23_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n room start with L 24_m.txt"
cat maps/24_m.txt
./lem-in < maps/24_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n bullshit without # 25_m.txt"
cat maps/25_m.txt
./lem-in < maps/25_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n room without coordinates 27_m.txt"
cat maps/27_m.txt
./lem-in < maps/27_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n connections with spaces 28_m.txt"
cat  maps/28_m.txt
./lem-in < maps/28_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n room doesn't connected to end 29_m.txt"
cat maps/29_m.txt
./lem-in < maps/29_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n room doesn't connected to start 30_m.txt"
cat maps/30_m.txt
./lem-in < maps/30_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n dublicats room names 31_m.txt"
cat maps/31_m.txt
./lem-in < maps/31_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n dublicates room coordinates 32_m.txt"
cat maps/32_m.txt
./lem-in < maps/32_m.txt
echo "-------------------------------------------"

echo "${COL}WRONG${ESC}\n empty file 33_m.txt"
cat maps/33_m.txt
./lem-in < maps/33_m.txt
echo "-------------------------------------------"

echo "${COL2}OK${ESC}\n just so you know I can do max int of ants algo_gen13_maxint.txt"
#./lem-in < maps/algo_gen13_maxint.txt
echo "-------------------------------------------"