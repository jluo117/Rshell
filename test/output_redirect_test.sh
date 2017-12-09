#test for >
echo hello world > sampleFile
echo "write > out"
cat sampleFile > file1 > file2 > file3 #doesn't add hello world to other files
echo TACO | tr A-Z a-z > file2 | tee file3 # > stops pipe, doens't write to file3
cat file2 sampleFile file2 > destFile # combines files into destFile
ls > fileList #puts list of contents of directory in fileList
ls > file1 | tee wind # doesn't write to wind
rm sampleFile file1 file2 file3 fileList destFile
