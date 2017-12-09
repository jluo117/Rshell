#tests for |
#tiger: GRRR
echo grrr | tr a-z A-Z | tee tiger
#apple: MEOW, banana: meow
echo meow | tr a-z A-Z | tee apple | tr A-Z a-z | tee banana 
# total number of files in current directory and subdirectories
find . -type f -print | wc -l 
#apple: meow, mega: meow 
cat banana | tee apple | tr a-z A-Z > mega
#fileList contains contents of current directory
ls | tee fileList
# > stops piping so banana is empty
cat apple | tr a-z A-Z  | tee tiger > apple | tee banana
#append HELLO WORLD to mega
echo hello world | tr a-z A-Z | tee apple >> mega
echo wow | (tee A || tee B) | tee C > D # write wow to A, C, and D
rm tiger apple banana mega A C D