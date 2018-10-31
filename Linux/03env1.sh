#!/bin/bash
#export cadmesh_DIR=/home/nuclearresearch/MyPrograms/CADMesh/install/lib/cmake/cadmesh-.
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/nuclearresearch/MyPrograms/CADMesh/install/lib

#for root setting
#!/bin/bash
#export ROOTSYS=$PACKAGES_PATH/root
source  /home/gfh16/Packages/root/bin/thisroot.sh

#######################################
##for xerces-c-3.1.1
export XERCESC_LIBRARY=/usr/local/lib
export XERCESC_INCLUDE_DIR=/usr/local/include/xercesc
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

#################################################
##for Geant4.9.6.p03
#export Geant4_9_6_path=/home/gfh16/Packages/Geant4/geant4.9.6.p03-install
#source $Geant4_9_6_path/bin/geant4.sh
#source $Geant4_9_6_path/share/Geant4-9.6.3/geant4make/geant4make.sh


####for data
#export  G4ABLA3=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4ABLA3.0
#export  G4EMLOW=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4EMLOW6.50
#export  G4ENSDFSTATE=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4ENSDFSTATE2.1
#export  G4NDL=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4NDL4.5
#export  G4PII=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4PII1.3
#export  G4NEUTRONXS=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4NEUTRONXS1.4
#export  G4SAIDDATA=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4SAIDDAT1.1
#export  G4TENDL=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4TENDL1.3
#export  PhotonEvaporation=/home/gfh16/Geant4/geant4.9.6.p03-install/data/G4PhotonEvaporation4.3.2
#export  RadioactiveDecay=/home/gfh16/Geant4/geant4.9.6.p03-install/data/RadioactiveDecay5.1.1
#export  RealSurface=/home/gfh16/Geant4/geant4.9.6.p03-install/data/RealSurface1.0

##for Geant4.9.6.p03// for /home/gfh16/Geant4
#export Geant4_9_6_path=/home/gfh16/Packages/geant4/geant4.9.6.p03-install
#source $Geant4_9_6_path/bin/geant4.sh
#source $Geant4_9_6_path/share/Geant4-9.6.3/geant4make/geant4make.sh

##for Geant4.9.6.p03// for /home/gfh16/Geant4
export Geant4_9_6_path=/home/gfh16/Packages/GEANT4/geant4.10.03.p01-install
source $Geant4_9_6_path/bin/geant4.sh
source $Geant4_9_6_path/share/Geant4-10.3.1/geant4make/geant4make.sh
