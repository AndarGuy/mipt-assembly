# variables
1000 2 # x = 2
1001 0 # sinx
1002 1 # counter
1003 F # precision
1004 1 # factorial
1005 0 # temp
1006 1 # power
100A 1 # increment
100B 186A0 # precision value
100C -1 # modifier

# beginning of the program
0 80 2000 0 0

# program
# 2000 20 1000 0 0 # input target
2003 00 1000 0 1001 # sinx = x
2004 13 1001 100B 1001 # sinx = precision value * x
2005 00 1000 0 1006 # power = x

2006 94 1002 1003 20AA # if counter >= precision -> ouput result
2007 13 1006 1000 1006 # x *= x
2008 13 1006 1000 1006 # x *= x
2009 13 1006 100C 1006 # x^n *= -1
200A 01 1002 100A 1002 # couter++
200B 13 1004 1002 1004 # factorial *= coutner
200C 01 1002 100A 1002 # couter++
200D 13 1004 1002 1004 # factorial *= coutner
200E 13 1006 100B 1005 # temp = x^n * precision value
200F 04 1005 1004 1005 # temp = x^n/!n
2010 01 1001 1005 1001 # sinx += temp
2011 80 2006 0 0 # return to start of for

20AA 21 1001 0 0 # output the result
20AB 99 0 0 0 # end program
