#!/usr/bin/env bash
#

if [ "x" == "x$WORKDIR_TOP" ] ; then
   echo " env.var. WORKDIR_TOP is NOT set; bail out "
   exit 3
fi

nuni1=${1}
nuni2=${2}

JobID=$((1+${SLURM_PROCID}))

SLEEP_TIME=$((${RANDOM}%60+1))
echo " JobID = ${JobID} --> will sleep ${SLEEP_TIME} seconds"
/usr/bin/sleep ${SLEEP_TIME}

# define "experiment" (exp.dataset)
#
export experiment=IAEA

# in principle, we need to make sure that the number of jobs
# does not exceed the number of cores, or the jobs will
# compete for resources (as it happens in amd32_g4val_slow !)
#
target_list=( C Fe Pb )
momz_list=(  3.824 )

ntgts=${#target_list[@]}
nmoms=${#momz_list[@]}

njobsmax=$((${ntgts}*${nmoms}))

if [ ${JobID} -gt ${njobsmax} ]; then
echo " JobID ${JobID} exceeds max number of needed jobs (${njobsmax}) " 
exit
fi

# Note: see earlier that JobID = SLURM_PROCID + 1
#
itgt=$((${SLURM_PROCID}/${nmoms}))
imom=$((${SLURM_PROCID} % ${nmoms}))
target=${target_list[$itgt]}
momz=${momz_list[$imom]}

#
# beam and momz "env.vars" are visible throughout; no need to pass them in, etc.
#
echo " beam = ${beam} "
echo " pdgcode = ${pdgcode} "
echo " momentum(z) = ${momz} "

source /cvmfs/geant4-ib.opensciencegrid.org/products/setup

setup critic v2_09_00 -q e20:prof
setup xerces_c v3_2_3 -q e20:prof
setup cmake v3_22_0
setup mrb v5_19_05


cd ${WORKDIR_TOP}
source ./localProducts*/setup

# IN THE PAST mrbsetenv was an alias for source ${MRB_DIR}/bin/mrbSetEnv
# it did NOT work if issued from a script - one has to "source" it explicitly
# BUT as of MRB v5-series, such scripts is no longer there, however, mrbsetenv
# seems to work just fine from the script
# NOTE: mrbSetEnv moved to ${MRB_DIR}/libexec
#
# Since v5_19_05, problematic if used multiple times
#
# ---> mrbsetenv
#
mrbslp

# needed if using local G4 build !
# in lieu of UPS build of geant4 v4_10_4-whatever...
#
cd ${MRB_SOURCE}/G4VMP

G4LOCATION="/work1/g4v/yarba_j/geant4-local-builds/gcc-9.3.0"
if [[ $node_name =~ "lq" ]]; then
G4LOCATION="/project/Geant4/yarba_j/geant4-local-builds/gcc-9.3.0"
fi

source ./geant4make-no-ups.sh geant4-11-00 ${G4LOCATION}

# --> rundirname=/scratch/analysis_${proc_level}_${beam}${momz}GeV_${target}
rundirname=/dev/shm/analysis_${proc_level}_${beam}${momz}GeV_${target}
if [ ! -d "${rundirname}" ]; then
/bin/mkdir ${rundirname}
fi


cd ${rundirname}
echo " I am in $PWD "

#
# Copy over common-use scripts
#
G4ParamTest=${MRB_SOURCE}/G4VMP/G4VMP
/bin/mkdir ${rundirname}/HelperScripts
rsync -h --progress ${G4ParamTest}/ProdScripts/HelperScripts/art_services.sh ${rundirname}/HelperScripts
/bin/chmod +x ${rundirname}/HelperScripts/art_services.sh
# ---> ??? ${rundirname}/HelperScripts
rsync -h --progress ${G4ParamTest}/ProdScripts/exp_data_includes/exp_data.sh ${rundirname}/HelperScripts
/bin/chmod +x ${rundirname}/HelperScripts/exp_data.sh

#
# Now copy over JSON files (exp.data)
#
JSONDIR=${rundirname}/json
if [ ! -d "${JSONDIR}" ]; then
/bin/mkdir ${JSONDIR}
fi 

ExpDataLOCATION="/work1/g4v/yarba_j/dossier-json"
if [[ $node_name =~ "lq" ]]; then
ExpDataLOCATION="/home/yarba_j/dossier-json"
fi

rsync -h --progress ${ExpDataLOCATION}/ExpDataJSON.tgz ${JSONDIR}

cd ${JSONDIR}
tar -xzf ${JSONDIR}/ExpDataJSON.tgz
cd ${rundirname}

. ${rundirname}/HelperScripts/art_services.sh
. ${rundirname}//HelperScripts/exp_data.sh

# define path to input simulated event files
# Note: PATH2EVT is set via env.var. on input to sbatch
#
evtfiledir=${PATH2EVT}/${proc_level}_${beam}${momz}GeV_${target}

nfiles=0

evtrootfile_list=""

pattern=0000
for (( iu=nuni1; iu<=nuni2; ++iu )) do
pos=$((${#pattern}-${#i}))
# echo ${pattern:0:${pos}}
univ=${pattern:0:${pos}}${i}
nf=`/bin/ls -alF ${evtfiledir}/*Univ${univ}*.root | wc -l`
nfiles=$(( nfiles + nf ))
uni_list=`/bin/ls -alF ${evtfiledir}/*Univ${univ}*.root | awk '{print $NF}'`
evtrootfile_list=${evtrootfile_list}" 
${uni_list}"
done

