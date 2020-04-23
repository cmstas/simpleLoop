should write filelist into List/xxx.list

##################################

runnint command example:
source setup.sh
make -j
./Task.exe List/Filelist_test.list sig

##################################
the Filelist_test.list only have 12 file (you can write a new filelist)
will save plots into sig_results.root

you can also use other words instead of "sig", the output rootfile(plots you want to draw in makeHists.h and makeHists.C are saved in this root file) will be {tag you use}_results.root

the source code are all in ./Src/xxx.C
./Src/Analysis.C is the loop func.
and pay attention: all the variables should added "R" : for example, if you want to call electron pt, use: RElectron_pt[electron index](I wrote a silly example in ./Src/Analysis.C:line54)

if you want to add variables in nanoAOD, looking at ./Include/Analysis.h line76, line 199

for drawing plots; look at ./Include/makeHists.h line 17 and ./Src/makeHists.C line 18-19 ./Src/Analysis.C line 56
(I also have a lot of drawing plot packages in /home/users/yxiang/public_html/Plot/xxx.cpp and xxx.h in case you want to use...)
