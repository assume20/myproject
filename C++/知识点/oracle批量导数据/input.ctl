load data
infile 'C:\Users\Administrator\Desktop\zhenghe.csv' 
append into table TEST fields terminated by ','
trailing nullcols(WRTUID,STRNAME,BYRTUADDRESS,STRMAINCHIPADDR,WMAINCHPORTNUM)