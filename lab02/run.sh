mainFile="main"

if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Usage: ./run.sh <lab-folder> <sample-number>"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "Error: Folder $1 does not exist"
    exit 1
fi

if [ ! -z "$3" ]; then
    mainFile=$3
fi

errMessage=$(g++ $1/$mainFile.cpp -o $1/$mainFile.out 2>&1); 

if (( $?==1 )) 
then
    echo "Compilation failed";
    # string format
    echo $errMessage | grep --color -E '${mainFile}.* error|warning:'
else
    ./$1/$mainFile.out < $1/samples/$2.in

    if (( $?==0 )) 
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
fi