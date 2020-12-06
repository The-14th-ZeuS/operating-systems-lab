echo "Program to print fibbonacci series"                                                                              
echo "Enter how many numbers you want to print"                                                                         
read n                                                                                                                  
count=1                                                                                                                 
first=0                                                                                                                 
second=1                                                                                                                
while [ $count -le $n ]                                                                                                 
do                                                                                                                              
	echo "$first"                                                                                                           
	second=$(($second+first))                                                                                               
	first=$(($second-$first))                                                                                               
	count=$(($count+1))                                                                                            
done
