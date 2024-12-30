mkdir $1 && touch $1/main.cpp
if [[ -a $1 ]]
then
    mkdir $1/samples
fi

if [[ -a $1/main.cpp ]]
then
    # write basic code to main.cpp
    echo "#include <iostream>
using namespace std;

int main() 
{
    return 0;
}" > $1/main.cpp
fi

if (( $? == 0 ))
then
    # open main.cpp in vscode
    code $1/main.cpp
fi