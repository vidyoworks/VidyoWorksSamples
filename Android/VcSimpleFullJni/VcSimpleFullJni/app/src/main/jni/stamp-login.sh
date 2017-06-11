if [[ -e "$1" ]]
then
rm -f 1.txt
sed s/\"raz\"/\"\"/ $1 > 1.txt
sed s/\"qa9.vidyo.com\"/\"\"/ 1.txt > $1
fi