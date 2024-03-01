echo ""
echo "Running unit tests:"
echo "----"

for i in tests/*_tests
do
    $VALGRIND ./$i
    echo ""

done


echo ""


