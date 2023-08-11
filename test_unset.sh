#!/bin/bash

# Wait for 1 second
sleep 1

xdotool type "unset PATH"
xdotool key Return
sleep 0.5

xdotool type "ls"
xdotool key Return
sleep 0.5

xdotool type "minishell"
xdotool key Return
sleep 0.5
