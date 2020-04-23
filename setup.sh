# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
        . /etc/bashrc
fi
alias tmux='/home/users/phchang/local/bin/tmux'
export PATH=/home/users/yxiang/local/bin/:$PATH
source /cvmfs/cms.cern.ch/cmsset_default.sh > /dev/null 2>&1
export SCRAM_ARCH=slc6_amd64_gcc700
export CMSSW_VERSION=CMSSW_9_2_0
alias tmux='/home/users/phchang/local/bin/tmux'
alias tmux='TERM=xterm-256color /home/users/phchang/local/bin/tmux -2'
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc700/cms/cmssw/CMSSW_9_2_0/src
eval `scramv1 runtime -sh`
cd -

alias pch='/home/users/phchang/local/bin/wemux'


#if [ -f /etc/bashrc ]; then
#        . /etc/bashrc
#fi
# User specific aliases and functions
#alias tmux='/home/users/phchang/local/bin/tmux'
#source /cvmfs/cms.cern.ch/cmsset_default.sh > /dev/null 2>&1
#export SCRAM_ARCH=slc6_amd64_gcc520
#export CMSSW_VERSION=CMSSW_9_2_0
#echo Setting up CMSSW for CMSSW_9_2_0 for slc6_amd64_gcc530
#alias tmux='/home/users/phchang/local/bin/tmux'
#cd /cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_9_2_0/src
#eval `scramv1 runtime -sh`
#cd -

# ROOT SYSTEM PATH DEFINITIONS
#export ROOTSYS=/root
#export PATH=$ROOTSYS/bin:$PATH
#export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH
# CERNLIB PATH DEFINITIONS
#export CERN=/cern
#export CERN_LEVEL=2006
#export CERN_ROOT=$CERN/$CERN_LEVEL
#export PATH=$CERN_ROOT/bin:$PATH
# LHAPDF PATH DEFINITIONS
#export LHAPDF=/usr/local/lib
#export LD_LIBRARY_PATH=$LHAPDF:$LD_LIBRARY_PATH
#export LANG=en_US
