#!/usr/bin/env bash
#

nuni1=${1}
nuni2=${2}

# if [ "x" == "x$nuni1" ] || [ "x" == "x$nuni2" ]; then
if [ "x" == "x$nuni1" -o "x" == "x$nuni2" ]; then
echo " You must supply the 1st and the last universes (variants) as input arguments; bail out"
exit
fi

# path2evt=/wclustre/g4p/yarba_j/g4vmp-study/12-14-21
# path2evt=/wclustre/g4v/yarba_j/g4vmp-study/sim-g4.11.0-NP500-NA61
# path2evt=/wclustre/g4v/yarba_j/g4vmp-study/04-08-22
# path2evt=/wclustre/g4v/yarba_j/g4vmp-study/05-04-22
path2evt=/wclustre/g4v/yarba_j/g4vmp-study/05-15-22

# NA61
#
# WC-IC
#
# --> LQ1 example --> sbatch -n 2 --time=23:00:00 --gres=gpu:0 -p gpu --qos=normal -A g4 --exclusive  ${my-script}
#
# --> GPU --> sbatch -N 1 -n 1 -c 1 -p gpu_gce --gres=gpu:v100:0 --nodelist=wcgpu05 --qos=regular --time=23:45:00 --exclusive -A g4p \
#if [ "1" == "$nuni1" ]; then
#sbatch -N 1 -n 1 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4v  \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
#	slurm_multiU_master.sh ana_NA61_singleU.sh Default
#fi

#pattern=0000
#for (( i=${nuni1}; i<=${nuni2}; ++i )) do
#pos=$((${#pattern}-${#i}))
## echo ${pattern:0:${pos}}
#univ=${pattern:0:${pos}}${i}
#label_univ="Univ${univ}"
#sbatch -N 1 -n 1 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v  \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
#	slurm_multiU_master.sh ana_NA61_singleU.sh ${label_univ}
#done

# IAEA
#
# path2evt=/wclustre/g4v/yarba_j/g4vmp-study/sim-g4.11.0-NP500-IAEA
path2evt=/wclustre/g4v/yarba_j/g4vmp-study/sim-g4.11.0-NucDestr-NP250-IAEA

#if [ "1" == "$nuni1" ]; then
#sbatch -N 1 -n 3 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v  \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
#	slurm_multiU_master.sh ana_IAEA_singleU.sh Default
#fi

#pattern=0000
#for (( i=${nuni1}; i<=${nuni2}; ++i )) do
#pos=$((${#pattern}-${#i}))
## echo ${pattern:0:${pos}}
#univ=${pattern:0:${pos}}${i}
#label_univ="Univ${univ}"
#sbatch -N 1 -n 3 -c 1 -p cpu_gce  --exclusive -A g4v  \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
#	slurm_multiU_master.sh ana_IAEA_singleU.sh ${label_univ}
#done

# ITEP771 & HARP
#
#path2evt=/wclustre/g4v/yarba_j/g4vmp-study/sim-g4.11.0-NP500-HARP-ITEP

# ITEP
#
# path2evt=/wclustre/g4v/yarba_j/g4vmp-study/sim-g4.11.0-NucDestr-NP250-ITEP-HARP
# path2evt=/wclustre/g4v/yarba_j/g4vmp-study/04-09-22
# path2evt=/wclustre/g4v/yarba_j/g4vmp-study/05-04-22
path2evt=/wclustre/g4v/yarba_j/g4vmp-study/05-15-22


#if [ "1" == "$nuni1" ]; then
#sbatch -N 1 -n 6 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4v  \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
#	slurm_multiU_master.sh ana_ITEP_singleU.sh Default
#fi

#pattern=0000
#for (( i=${nuni1}; i<=${nuni2}; ++i )) do
#pos=$((${#pattern}-${#i}))
## echo ${pattern:0:${pos}}
#univ=${pattern:0:${pos}}${i}
#label_univ="Univ${univ}"
#sbatch -N 1 -n 6 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v  \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
#	slurm_multiU_master.sh ana_ITEP_singleU.sh ${label_univ}
#done


# HARP
#
if [ "1" == "$nuni1" ]; then
sbatch -N 1 -n 3 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4v  \
 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
	slurm_multiU_master.sh ana_HARP_singleU.sh Default
fi

pattern=0000
for (( i=${nuni1}; i<=${nuni2}; ++i )) do
pos=$((${#pattern}-${#i}))
# echo ${pattern:0:${pos}}
univ=${pattern:0:${pos}}${i}
label_univ="Univ${univ}"
sbatch -N 1 -n 3 -c 1 -p cpu_gce --qos=regular --exclusive -A g4v  \
 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
	slurm_multiU_master.sh ana_HARP_singleU.sh ${label_univ}
done



# NA49
#
#path2evt=/wclustre/g4v/yarba_j/g4vmp-study/sim-g4.11.0-NP500-NA49
path2evt=/wclustre/g4v/yarba_j/g4vmp-study/03-23-22

#if [ "1" == "$nuni1" ]; then
#sbatch -N 1 -n 1 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4p  \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
#	slurm_multiU_master.sh ana_NA49_singleU.sh Default
#fi

#pattern=0000
#for (( i=${nuni1}; i<=${nuni2}; ++i )) do
#pos=$((${#pattern}-${#i}))
## echo ${pattern:0:${pos}}
#univ=${pattern:0:${pos}}${i}
#label_univ="Univ${univ}"
#sbatch -N 1 -n 1 -c 1 -p cpu_gce --qos=regular  --exclusive -A g4p  \
# 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
#	slurm_multiU_master.sh ana_NA49_singleU.sh ${label_univ}
#done


# SAS M6E
#
# sbatch -p amd32 -N1 -t 24:00:00 \
#	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=/lfstev/g4p/yarba_j/g4studies/06-13-19,NUniv=${nuni}" \
#	-A g4p ana_SASM6E_multiU.sh
# sbatch -p amd32 -N1 -t 24:00:00 \
#	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piplus,pdgcode=211,PATH2EVT=/lfstev/g4p/yarba_j/g4studies/09-10-19-sim-combined,NUniv=${nuni}" \
#	-A g4p ana_SASM6E_multiU.sh
