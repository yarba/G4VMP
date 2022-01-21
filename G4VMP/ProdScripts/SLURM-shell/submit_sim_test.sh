#!/usr/bin/env bash

nuni=${1}

nu1=${2}
nu2=${3}

if [ "x" == "x$nuni" ]; then
echo " You must supply the number of universes (variants) as the 1st input argument; bail out"
exit
fi

# NA61
#
# 31GeV/c proton on C
#
sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular --exclusive -A g4p \
 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=C,momz=31.0,NUniv=${nuni},maxevents=10000" \
	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
