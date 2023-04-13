from DDSim.DD4hepSimulation import DD4hepSimulation
from g4units import mm, GeV, MeV
SIM = DD4hepSimulation()

SIM.runType = "batch"
SIM.part.minimalKineticEnergy = 1.0
SIM.filter.tracker = "edep0"
#SIM.printLevel = "ERROR"
