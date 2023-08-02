#!/bin/bash

# Define the folder structure
folder_structure="a/b/c/"

# Create the folder structure
mkdir -p "$folder_structure"

# Navigate to the last folder in the structure using xdotool
sleep 1
xdotool type "cd $(realpath "$folder_structure")"
xdotool key Return
sleep 1

# Type pwd using xdotool
xdotool type "pwd"
xdotool key Return
sleep 0.5

# Remove the first folder and its subfolders
rm -rf "$(realpath "${folder_structure%%/*}")"

# Type pwd using xdotool
xdotool type "pwd"
xdotool key Return
sleep 0.5

# Navigate back using cd ..
xdotool type "cd .."
xdotool key Return
