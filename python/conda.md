= Create conda virtualenv =
===========================
conda create -n <name> python=<version number> anaconda

= Remove conda virtualenv =
===========================
conda remove -n env --all

= List conda virtualenvs =
==========================
conda info -e


= Write/Read packages to requirements =
=======================================
conda list -e > requirements.txt
conda install --file requirements.txt


= Update conda and anaconda =
=============================
# First
conda update conda
# Second
conda update anaconda


