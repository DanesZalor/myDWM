#!/bin/bash

if [ 65536 -gt $(pactl get-sink-volume @DEFAULT_SINK@ | cut -f3 -d " ") ]
then
	pactl set-sink-volume @DEFAULT_SINK@ +5%
fi
exit
