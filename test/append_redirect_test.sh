#tests for >>
echo water >> elements
echo fire >> elements >> hotStuff #fire written to hotStuff, not elements (FAIL)
cat hotStuff
echo sun >> elements >> hotStuff #sun added to hotStuff
cat hotStuff
echo pancakes >> food
cat elements hotStuff food >> things
cat things # water fire sun pancakes
echo waffles | tr a-z A-Z | tee yum >> food # food has pancakes and WAFFLES
rm elements hotStuff food yum 