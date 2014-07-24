#PSG:
## Prompt Source Generator

#####because bash has trash control over stuctured data
#####because zsh is hipster and bloat


## Using PSG
group tag | definition
-----------------------------------------------------------
$proc            | # of background processes (doesnt show anything if there arent any)
$userhost        | username & hostname (on my computer it's 'ted@hyperion', or 'ted@helios')
$path            | the current pwd of the shell ie, '~/git/psg' (it replaces $HOME with ~)
$git             | information about the current git repository, if the pwd is in one.
$svn (not shown) | similar to git, but only works with the custom tripadvisor SVN


make a file ~/.config/psg/psgrc
````
$proc
18
6

$userhost
2
235

$path
18
6

$git
3
8
````

note: the $proc section only works on linux machines (or anything with /proc/<id>/status)

the $variables are module names, they correlate directly to C functions.
the numbers are the forground and background respectivey. they are
8 bit colors. look here for more info: http://misc.flogisoft.com/bash/tip_colors_and_formatting

also add the file https://github.com/tmathmeyer/dotfiles/blob/master/.config/psg/git.sh
to the ~/.config/psg/ directory.




##SCREENSHOTS
![everything](screenshots/tree.png)

![git](screenshots/git_info.png)

![shell](screenshots/terminal.png)