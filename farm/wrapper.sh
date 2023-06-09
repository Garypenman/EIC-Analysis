#!/bin/bash

run=0

for file in /scratch/garyp/data/18.t.*.hepmc;
do
    base=${file%.hepmc}
    base=${file##*/}
    outfile=/scratch/garyp/rootfiles/$base.edm4hep.root
    logfile=/scratch/garyp/logs/$base.log
    export RUN_NUMBER=$run
    export JUGGLER_N_EVENTS=-1
    export JUGGLER_MC_FILE=$file
    export JUGGLER_SIM_FILE=$outfile
    export LOGFILE=$logfile
    echo "Submitting simulation job $RUN_NUMBER. File: $base"
    ./isrSIM.sh &
    run=$(( $run+1 ))
    sleep 5
done
