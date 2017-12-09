# tests for <
echo "echo hello world" > file1
cat < file1 #outputs hello world
echo "< this should print"
cat < file1 | tr a-z A-Z #ouputs HELLO WORLD
wc -l < file1 #prints line count of file1 
echo second line >> file1 #append to file1
wc -l < file1 > length #puts 2 in length
cat length
rm file1 length