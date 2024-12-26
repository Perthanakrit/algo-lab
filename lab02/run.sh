#!/bin/bash

# Default values
mainFile="main"
sampleFile=""

# Usage message
usage() {
    echo "Usage: ./run.sh -l <lab-folder> [-m <main-file>] [-s <sample-number>]"
    echo "  -l, --lab       Lab folder (required)"
    echo "  -m, --main      Main file name (default: 'main')"
    echo "  -s, --sample    Sample number (optional)"
    exit 1
}

# Progress bar function
progress_bar() {
    local duration=$1
    local increment=0.1
    local progress=0
    local bar=""

    if (( duration <= 0 )); then
        duration=1 # Prevent division by zero or negative duration
    fi

    while (( $(echo "$progress < 1" | bc -l) )); do
        bar="${bar}#"
        printf "\r%-0s %d%%" "$bar" "$(echo "$progress * 100" | bc | awk '{print int($1)}')"
        sleep $increment
        progress=$(echo "$progress + $increment / $duration" | bc -l)
    done
    printf "\r%-0s 100%% in %fs\n" "$bar" "$duration"
}

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -l|--lab)
            folder="$2"
            shift 2
            ;;
        -m|--main)
            mainFile="$2"
            shift 2
            ;;
        -s|--sample)
            sampleFile="$2"
            shift 2
            ;;
        -h|--help)
            usage
            ;;
        *)
            echo "Unknown option: $1"
            usage
            ;;
    esac
done

# Validate required arguments
if [[ -z "$folder" ]]; then
    echo "Error: Lab folder is required."
    usage
fi

if [[ ! -d "$folder" ]]; then
    echo "Error: Folder '$folder' does not exist."
    exit 1
fi

# Compile the program
echo "Compiling the program..."
start_time=$(date +%s)
errMessage=$(g++ "$folder/$mainFile.cpp" -o "$folder/$mainFile.out" 2>&1)
end_time=$(date +%s)
compilation_time=$(( end_time - start_time ))

# Show progress bar for compilation
progress_bar $compilation_time

if (( $? != 0 )); then
    echo "Compilation failed"
    echo "$errMessage" | grep --color -E "${mainFile}.* error|warning:"
    exit 1
else
    echo "Compilation succeeded"
fi

# Run the program
echo "Running the program..."

output=""

start_time=$(date +%s)
if [[ -z "$sampleFile" ]]; then
    "$folder/$mainFile.out"
else
    if [[ ! -f "$folder/samples/$sampleFile.in" ]]; then
        echo "Error: Sample file '$folder/samples/$sampleFile.in' does not exist."
        exit 1
    fi
    # redirect input from sample file and output to variable
    output=$("$folder/$mainFile.out" < "$folder/samples/$sampleFile.in" 1>&1)
fi
end_time=$(date +%s)
running_time=$(( end_time - start_time ))

# Show progress bar for running
progress_bar $running_time

echo "$output"
