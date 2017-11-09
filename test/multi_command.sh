echo beginning of multi command test; ls && echo "ls worked"
echo this should print instead of execute ls || echo fail 
echo lots ; echo of || echo silly ; echo 'commands' && echo here
echo testing '&&' && echo 1 && echo 2 && echo 3 && echo 4 && echo 5
echo testing '||'; echo alpha || echo A || echo B || echo C
ls || mkdir star && ls; exit



