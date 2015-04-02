# Git


# Create local copy and checkout git branch
# http://stackoverflow.com/questions/1783405/checkout-remote-git-branch
git checkout -b <branch> origin/<branch>

# See what has changed since previous commit (-1 = last commit, -2 = last last commmit ... )
git whatchanged -1

# See changes to be made on current commit
git diff
# or
git diff <file>

# pip install directly from git-repo
pip install git+https://github.com/myuser/foo.git

#Store git credentials
git config credential.helper store
# Git Address:
https://github.com/ben-albrecht/
# Bitbucket Address:
git@bitbucket.org:ben_albrecht/

# Remove untracked directories
clean -fd

# Migrating bitbucket repo to github repo
cd $HOME/repos/repository
git remote rename origin bitbucket
# MAKE A NEW GIT REPO ON GITHUB
git remote add origin https://github.com/ben-albrecht/repository.git
git push origin master
git remote rm bitbucket

# OR

git clone --mirror https://bitbucket.org/exampleuser/repository-to-mirror.git
# Make a bare mirrored clone of the repository
cd repository-to-mirror.git
git remote set-url --push origin https://github.com/exampleuser/mirrored
# Set the push location to your mirror
git push --mirror



# Drop current unstaged changes
git stash save --keep-index
git stash drop


# Recommended to use this alias for git up instead of git pull
    # Prevents nonlinearities in git history
    # See this Stack Overflow thread for details:
    # http://stackoverflow.com/questions/15316601/in-what-cases-could-git-pull-be-harmful 

git config --global alias.up 'pull --ff-only --all -p'

# Starting a new git directory
git init
# THE LINE WHERE I HAVE TO CHANGE SOMETHING:
git remote add origin git@bitbucket.org:ben_albrecht/<RepoName>.git # add repo to bitbucket
git commit -a # If there is anything in the repo yet + adds them all to repository
git push -u origin --all # pushes up the repo and its refs for the first time
git push -u origin --tags # pushes up any tags

