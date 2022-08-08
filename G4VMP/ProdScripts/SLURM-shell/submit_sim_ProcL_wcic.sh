#!/usr/bin/env bash

nuni=${1}

nu1=${2}
nu2=${3}

if [ "x" == "x$nuni" ]; then
echo " You must supply the number of universes (variants) as the 1st input argument; bail out"
exit
fi

# IAEA
#
# 3.824 GeV/c (3 GeV ekin) proton on C, Fe, Pb
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=C,momz=3.824,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=Fe,momz=3.824,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
# --> sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v \
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=Pb,momz=3.824,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}

# HARP and/or ITEP771
#
# 5 GeV/c proton on C, Cu, Pb
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=C,momz=5.0,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=Cu,momz=5.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=Pb,momz=5.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#
# 5 GeV/c pi+ on C, Cu, Pb
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piplus,pdgcode=211,target=C,momz=5.0,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piplus,pdgcode=211,target=Cu,momz=5.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v \
 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piplus,pdgcode=211,target=Pb,momz=5.0,NUniv=${nuni},maxevents=50000" \
	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#
# 5 GeV/c pi- on C, Cu, Pb
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piminus,pdgcode=-211,target=C,momz=5.0,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piminus,pdgcode=-211,target=Cu,momz=5.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piminus,pdgcode=-211,target=Pb,momz=5.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}


#
# 7.5 GeV/c proton on C, Cu, Pb
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=C,momz=7.5,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=12:00:00 --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=Cu,momz=7.5,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=Pb,momz=7.5,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#
# 8 GeV/c proton on Ta
#
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=Ta,momz=8.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}

# 12 GeV/c pi+ on C, Cu, Pb
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piplus,pdgcode=211,target=C,momz=12.0,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piplus,pdgcode=211,target=Cu,momz=12.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piplus,pdgcode=211,target=Pb,momz=12.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#
# 12 GeV/c pi- on C, Cu, Pb
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piminus,pdgcode=-211,target=C,momz=12.0,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piminus,pdgcode=-211,target=Cu,momz=12.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
#sbatch -N 1 -n 15 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piminus,pdgcode=-211,target=Pb,momz=12.0,NUniv=${nuni},maxevents=50000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}




# NA61
#
# 31GeV/c proton on C
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=C,momz=31.0,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
	
# NA49
#
# 158 GeV/c proton on C
#
#sbatch -N 1 -n 10 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,target=C,momz=158.0,NUniv=${nuni},maxevents=100000" \
#	slurm_multiU_master.sh sim_multiU_wcic.sh ${nu1} ${nu2}
