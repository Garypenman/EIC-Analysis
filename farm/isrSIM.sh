#!/bin/bash

#export JUGGLER_N_EVENTS=-1

#export DETECTOR_PATH=
#export DETECTOR_CONFIG=

#export JUGGLER_MC_FILE=/w/work5/home/garyp/eic/SimInputFiles/M3/June_2022/HepMC/eA-5x41-M3-Ph.hepmc
#export JUGGLER_SIM_FILE="/w/work5/home/garyp/eic/ddsim/test_all.root"

#export JUGGLER_MC_FILE="/scratch/garyp/data/18.t.1000.hepmc"
#export JUGGLER_SIM_FILE="/scratch/garyp/ddsimOUT.edm4hep.root"

nohup ddsim --runType batch \
    --filter.tracker edep0 \
    --part.minimalKineticEnergy 1000*GeV  \
    --numberOfEvents ${JUGGLER_N_EVENTS} \
    --compactFile ${DETECTOR_PATH}/${DETECTOR_CONFIG}.xml \
    --inputFiles "${JUGGLER_MC_FILE}" \
    --outputFile  ${JUGGLER_SIM_FILE} \
    -v ERROR \
    >> $LOGFILE 2>&1

echo "Simulation job $RUN_NUMBER complete!"

    
