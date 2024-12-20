errMessage=$(g++ $1/main.cpp -o $1/main.out 2>&1); 

if (( $?==1 )) 
then
    echo "Compilation failed";
    echo $errMessage | grep --color -E 'main.cpp.* error|warning:'
else
    ./$1/main.out < $1/samples/$2.in
fi