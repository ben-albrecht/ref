# Reload modules when they are changed
%load_ext autoreload
%autoreload 2


# access IPython notebook remotely
#   Taken from here: http://wisdomthroughknowledge.blogspot.co.uk/2012/07/accessing-ipython-notebook-remotely.html
# Remote machine:
ipython notebook --no-browser

# Local machine:
ssh -N -f -L localhost:6001:localhost:8888 user@hostname

# Go to URL in browser:
http://localhost:6001
