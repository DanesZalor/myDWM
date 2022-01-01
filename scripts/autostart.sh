#!/bin/bash
#place this in .local/share/dwm/
xrandr --otput eDP-1 --mode 1920x1080 --gamma 1.0:1.0:1.0 &
feh --bg-fill ~/.local/share/dwm/dwmbinbo.png &
/.aur/dwm/scripts/statusLoop &
wmname LG3D &
picom &
exit
