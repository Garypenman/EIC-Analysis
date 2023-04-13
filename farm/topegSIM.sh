#!/bin/bash

#export JUGGLER_N_EVENTS=-1

#export DETECTOR_PATH=
#export DETECTOR_CONFIG=

#export JUGGLER_MC_FILE="/scratch/garyp/topegsim/data/eA-5x41-M3-Ph.hepmc"
#export JUGGLER_SIM_FILE="/scratch/garyp/topegsim/rootfiles/eA-5x41-M3-Ph_$SEG.edm4hep.root"

ddsim --steeringFile minimal.py \
    --numberOfEvents ${JUGGLER_N_EVENTS} \
    --compactFile ${DETECTOR_PATH}/${DETECTOR_CONFIG}.xml \
    --inputFiles ${JUGGLER_MC_FILE}  \
    --outputFile  ${JUGGLER_SIM_FILE} \
    --skipNEvents ${NSKIP} \
    >> $LOGFILE 2>&1

#--runType batch \
#--part.minimalKineticEnergy 1000*GeV  \
#--filter.tracker edep0 \
#-v ERROR \

mv $JUGGLER_SIM_FILE $WORK_OUT_DIR
mv $LOGFILE $WORK_LOG_DIR
echo "Simulation $RUN $SEG complete!"
