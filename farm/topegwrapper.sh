#!/bin/bash

nevents=1000000
segs=10
nsegev=$(( $nevents / $segs ))

export WORK_DIR=/w/work5/home/garyp/eic
export WORK_DATA_DIR=$WORK_DIR/Generators/Topeg/HepMC/June_2022
export WORK_LOG_DIR=$WORK_DIR/ddsim/Topeg/Logs
export WORK_OUT_DIR=$WORK_DIR/ddsim/Topeg/Rootfiles

simdir="/scratch/garyp/topegsim"
mkdir -p ${simdir}

datadir=$simdir/data
mkdir -p ${datadir}

outdir=$simdir/rootfiles
mkdir -p ${outdir}

logdir=$simdir/logs
mkdir -p ${logdir}

##cant loop over all files because ->6x10=60jobs
##np-chi has 64 threads.
##2s per event, 100k events takes 2.5days
##cant clog np-chi for 2.5 days :(

for file in $WORK_DATA_DIR/eA-5x41-M3-Ph.hepmc;
do
    basename=${file##*/}
    basename=${basename%.hepmc}
    if [ ! -f $datadir/$basename.hepmc ]
    then
	echo "Copying $basename from /w/work5/... to $datadir"
	cp $file $datadir/$basename.hepmc
    fi    
    mkdir -p $outdir/$basename
    export RUN=$basename
    echo "Submitting $basename simulation"
    for (( seg=0; seg<$segs; seg++ ))
    do
	export SEG=$seg
	export NSKIP=$(( $seg * $nsegev ))
	export LOGFILE=$logdir/$basename"_"$SEG.log
	export JUGGLER_N_EVENTS=$nsegev
	export JUGGLER_MC_FILE=$datadir/$basename.hepmc
	export JUGGLER_SIM_FILE=$outdir/$basename/$basename"_"$SEG.edm4hep.root
	njob=$(( $seg + 1 ))
	echo "Skipping $NSKIP events"	    
	echo "Submitting topeg-ddsim simulation job $njob / $segs"
	./topegSIM.sh &
	sleep 5
    done
done
