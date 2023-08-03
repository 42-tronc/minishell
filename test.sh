#!/bin/bash

# Define the folder structure
folder_structure="a/b/c/"

# Wait for 1 second
sleep 1

# Create the folder structure
mkdir -p "$folder_structure"

# Navigate to the last folder in the structure using xdotool
xdotool type "cd $(realpath "$folder_structure")"
xdotool key Return
sleep 0.5

# Type pwd using xdotool
xdotool type "pwd"
xdotool key Return
sleep 0.5

# Change the Home
# xdotool type "export HOME=\"$(realpath "$folder_structure")\""
# xdotool key Return
# sleep 0.5

# Remove the first folder and its subfolders
rm -rf "$(realpath "${folder_structure%%/*}")"

# Type pwd using xdotool
xdotool type "pwd"
xdotool key Return
sleep 0.5

# Navigate back using cd ..
xdotool type "cd .."
xdotool key Return
sleep 0.5

# Type pwd using xdotool
xdotool type "pwd"
xdotool key Return
sleep 0.5

# Type echo $OLDPWD
xdotool type "echo \$OLDPWD"
xdotool key Return
sleep 0.5

# Type cd
xdotool type "cd"
xdotool key Return
sleep 0.5

# Type pwd using xdotool
xdotool type "pwd"
xdotool key Return
sleep 0.5

# Type echo $OLDPWD
xdotool type "echo \$OLDPWD"
xdotool key Return
sleep 0.5