#!/usr/bin/env bash
#

nuni=${1}

if [ "x" == "x$nuni" ]; then
echo " You must supply the number of universes (variants) as the 1st input argument; bail out"
exit
fi

# path2evt=/wclustre/g4p/yarba_j/g4vmp-study/12-14-21
path2evt=/wclustre/g4v/yarba_j/g4vmp-study/09-03-21

# NA61
#
# WC-IC
#
# --> LQ1 example --> sbatch -n 2 --time=23:00:00 --gres=gpu:0 -p gpu --qos=normal -A g4 --exclusive  ${my-script}
#
# --> GPU --> sbatch -N 1 -n 1 -c 1 -p gpu_gce --gres=gpu:v100:0 --nodelist=wcgpu05 --qos=regular --time=23:45:00 --exclusive -A g4p \
sbatch -N 1 -n 1 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4p  \
 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
	slurm_multiU_master.sh ana_NA61_singleU.sh Default

pattern=0000
for (( i=1; i<=${nuni}; ++i )) do
pos=$((${#pattern}-${#i}))
# echo ${pattern:0:${pos}}
univ=${pattern:0:${pos}}${i}
label_univ="Univ${univ}"
sbatch -N 1 -n 1 -c 1 -p cpu_gce --qos=regular --time=23:45:00 --exclusive -A g4p  \
 	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=${path2evt}" \
	slurm_multiU_master.sh ana_NA61_singleU.sh ${label_univ}
done


# NA49
#
# sbatch -p amd32 -N1 -t 24:00:00 \
#	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=/lfstev/g4p/yarba_j/g4studies/06-13-19,NUniv={$nuni}" \
#	-A g4p ana_NA49_multiU.sh

# SAS M6E
#
# sbatch -p amd32 -N1 -t 24:00:00 \
#	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=proton,pdgcode=2212,PATH2EVT=/lfstev/g4p/yarba_j/g4studies/06-13-19,NUniv=${nuni}" \
#	-A g4p ana_SASM6E_multiU.sh
# sbatch -p amd32 -N1 -t 24:00:00 \
#	--export="WORKDIR_TOP=${MRB_TOP},proc_level=FTFP,beam=piplus,pdgcode=211,PATH2EVT=/lfstev/g4p/yarba_j/g4studies/09-10-19-sim-combined,NUniv=${nuni}" \
#	-A g4p ana_SASM6E_multiU.sh
