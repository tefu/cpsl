for program in $(ls test-files)
do
    echo "-------------------------------------------------"
    echo "Running compiler on ./test-files/${program}... "
    echo "-------------------------------------------------"
	  cat "test-files/$program" | ./cpsl
done
