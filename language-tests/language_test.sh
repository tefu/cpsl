for program in $(ls test-files)
do
    echo "-------------------------------------------------"
    echo "Running compiler on ${program}... "
    echo "-------------------------------------------------"
	  cat "test-files/$program" | ./cpsl
done
