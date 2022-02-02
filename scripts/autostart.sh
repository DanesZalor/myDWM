#!/bin/bash
xrandr --otput eDP-1 --mode 1920x1080 --gamma 1.0:1.0:1.0 &
feh --bg-fill ~/.local/share/dwm/dwmbinbo.png &
nm-applet &
blueberry-tray &
wmname LG3D &
picom &
while [ true ]
do
	/.aur/suckless/dwm/scripts/status
	sleep 5
done
exit
