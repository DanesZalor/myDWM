#!/bin/bash

if [ 85000 -gt $(pactl get-sink-volume @DEFAULT_SINK@ | cut -f3 -d " ") ]
then
	pactl set-sink-volume @DEFAULT_SINK@ +1%
fi
exit
