#PSG:
## Prompt Source Generator (Beta, wont work unless your username is ted)

#####because fuck bashrc, its slow and has shit manipulation of data.
#####because fuck zsh, it is bloat.
#####It's really late now an I have work in the morning.


## Using PSG

make a file ~/.config/psg/psgrc
````
$userhost
10
233

$path
18
6

$git
3
8
````

the $variables are module names, they correlate directly to C functions.
the numbers are the forground and background respectivey. they are
8 bit colors. look here for more info: http://misc.flogisoft.com/bash/tip_colors_and_formatting

also add the file https://github.com/tmathmeyer/dotfiles/blob/master/.config/psg/git.sh
to the ~/.config/psg/ directory. 


##SCREENSHOTS
![everything](screenshots/tree.png)

![git](screenshots/git_info.png)

![shell](screenshots/terminal.png)