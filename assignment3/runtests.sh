#!/bin/bash

# COMP2119 Assignment 3 Automatic Testing Script
# Tasks: A, B, C
# Author: Eric15342335 and o1-mini
# Date: 2024/Oct/17
UniversityNumber=3036216734

# Exit immediately if a command exits with a non-zero status
set -e

# Function to determine the executable suffix based on the operating system
get_exe_suffix() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo ""
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo ""  # macOS also uses no suffix
    elif [[ "$OSTYPE" == "msys"* ]] || [[ "$OSTYPE" == "cygwin"* ]]; then
        echo ".exe"
    else
        echo ""
    fi
}

# Get the executable suffix
exe_suffix=$(get_exe_suffix)

# Define the list of tasks
tasks=("A" "B" "C")

# Define the number of test cases per task
num_test_cases=5  # Assuming 5 test cases per task (A-1 to A-5, etc.)

# Base directory for test cases
base_dir="sample_test_cases"

# Loop through each task
for task in "${tasks[@]}"
do
    echo "=============================="
    echo "Processing Task $task"
    echo "=============================="

    # Define the source file and executable name
    source_file="$UniversityNumber-$task.cpp"
    executable="${task}${exe_suffix}"

    # Compile the C++ source file
    echo "Compiling $source_file ..."
    g++ -pedantic-errors -std=c++11 -Wall -Wextra -o "$executable" "$source_file"
    if [ $? -ne 0 ]; then
        echo "Compilation failed for Task $task. Skipping tests for this task."
        continue
    fi
    echo "Compilation successful for Task $task."

    # Define the input and output directory for the current task
    input_dir="$base_dir/Task$task"
    output_dir="$input_dir"  # Assuming output files are in the same directory

    # Loop through each test case
    for case_num in $(seq 1 $num_test_cases)
    do
        echo "-----"
        echo "Running Test Case $task-$case_num"
        echo "Input File: $input_dir/$task-$case_num.in"
        echo "Expected Output File: $input_dir/$task-$case_num.out"

        # Define input and expected output files
        input_file="$input_dir/$task-$case_num.in"
        expected_output="$input_dir/$task-$case_num.out"

        # Define the output file generated by the executable
        my_output="myoutput${task}_${case_num}.txt"

        # Check if input and expected output files exist
        if [ ! -f "$input_file" ]; then
            echo "Input file $input_file not found. Skipping Test Case $task-$case_num."
            continue
        fi

        if [ ! -f "$expected_output" ]; then
            echo "Expected output file $expected_output not found. Skipping Test Case $task-$case_num."
            continue
        fi

        # Run the executable with the input file and capture the output
        ./"$executable" < "$input_file" > "$my_output"

        # Compare the generated output with the expected output
        if diff -Bw "$my_output" "$expected_output" > /dev/null; then
            echo "Result: PASS"
        else
            echo "Result: FAIL"
            echo "Differences:"
            diff -Bw "$my_output" "$expected_output"
        fi

        echo ""
    done

    # Remove the executable after testing
    rm "$executable"
    echo "Completed testing for Task $task."
    echo ""
done

# Cleanup all generated output files
echo "Cleaning up generated output files..."
rm -f myoutput*.txt
echo "Cleanup complete."

echo "All tasks have been processed."
