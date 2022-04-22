#!/bin/bash

sudo cp /.aur/suckless/dwm/scripts/win95rofi.rasi /usr/share/rofi/themes/win95rofi.rasi
xrandr --otput eDP-1 --mode 1920x1080 --gamma 1.0:1.0:0.8 &
feh --bg-fill ~/.local/share/dwm/dwmbinbo.png &
nm-applet & pasystray &
blueberry-tray &
wmname LG3D &
picom &
while [ true ]
do
	/.aur/suckless/dwm/scripts/status
	sleep 5
done
exit
