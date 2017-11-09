echo start of comment test || echo rip
echo only 1 should print; echo 1 #; echo 2
echo '#hello' &&  echo world # comment with space after #
echo "comment without space after #" #fail
echo end of test; exit
