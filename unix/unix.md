###############################
###############################
#General UNIX Environment Commands

#Starting compile over
make clean
#############################
#Decompression Variations
tar -xzf FILE.tar.gz
gunzip -c FILE.tgz | tar -xvf -
tar -xf  FILE.tar
tar jxf FILE.tar.bz2
unzip FILE.zip
#Tarball compression
tar cvzf TARBALL.tar FILES
#############################
#Job Control
#(Run in background)
<command> &
#if command already running:
#(suspend foreground process)
[ctrl + z] 
#(Run foreground process in background)
bg
#(Run background process in foreground)
fg
##############################
#Text Editing Tricks
#Remove files with grepped line in them
grep -l <search> <file> | xargs rm

###############################
###############################
#CSH

#csh input 
set whatever = $<

###############################
###############################
#OSX-specific

#change screen shot locations:
defaults write com.apple.screencapture location /Users/albrecht/Pictures/ScreenShots/
#Restore default SS location:
defaults write com.apple.screencapture location ~/Desktop/
#For system changes to take effect:
killall SystemUIServer
#Hidden files visible on OS x
defaults write com.apple.finder AppleShowAllFiles TRUE

###############################
###############################
