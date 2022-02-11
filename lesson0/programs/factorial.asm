# variables
1000 0 # target
1001 1 # counter
1002 1 # factorial
1003 1 # increment

# beginning of the program
0 80 2000 0 0

#program
2000 20 1000 0 0 # input target
2001 94 1001 1000 200A # if counter >= target -> ouput result
2002 01 1001 1003 1001 # couter++
2003 13 1002 1001 1002 # factorial *= coutner
2004 80 2001 0 0 # return to start of for

200A 21 1002 0 0 # output the result
200B 99 0 0 0 # end program
