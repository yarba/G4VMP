#!/usr/bin/env bash
#

if [ "x" == "x$WORKDIR_TOP" ] ; then
   echo " env.var. WORKDIR_TOP is NOT set; bail out "
   exit 3
fi

NU1=${1}
NU2=${2}

# the following two will work only if launched with MPI (--mpi=pmi2)
# JobID=${PMI_RANK})
# JobID=$((1+${PMI_RANK}))
#
# this one (hopefully) works if launched as follows:
# srun -l simulate_multiU_mpi.sh
# or (hopefully) when launched with MPI
JobID=$((1+${SLURM_PROCID}))
# JobID=$((9+${SLURM_PROCID}))


echo " JobID = ${JobID} --> maxevents = ${maxevents} "

# Space jobs in time not randomly but by 15 seconds
# ... in a hope it'll be enough for mrbsetenv NOT to hiccup...
# 
SLEEP_TIME=$((${RANDOM}%60+1))
# SLEEP_TIME=$((JobID*15))
echo " JobID = ${JobID} --> will sleep ${SLEEP_TIME} seconds"
/usr/bin/sleep ${SLEEP_TIME}

# all through env.vars now via --export field of sbatch !!!
#
# proc_level=FTFP
# beam=proton
# pdgcode=2212
# NUniv=25
# maxevents=15625
# momz=5.0
# target=Pb

start_time=`date`
echo " Start job ${JobID}: ${start_time}"

# more "uniform" approach as CVMFS is mounted on both Wilson & LQ1 
#
source /cvmfs/geant4-ib.opensciencegrid.org/products/setup

setup xerces_c v3_2_3e -q e26
setup critic v2_12_04 -q e26:prof
setup cmake v3_25_2
setup mrb v6_08_01


cd ${WORKDIR_TOP}
source ./localProducts*/setup

# IN THE PAST mrbsetenv was an alias for source ${MRB_DIR}/bin/mrbSetEnv
# it did NOT work if issued from a script - one has to "source" it explicitly
# BUT as of MRB v5-series, such scripts is no longer there, however, mrbsetenv
# seems to work just fine from the script
# ... OK, the script seems to have moved to ${MRB_DIR}/libexec which doesn't
# seem to be in the PATH...
#
# ---> mrbsetenv
#
# if the local modules are installed (in a UPS-ish way) to localProducts* area,
# ona can do the following instead of mrbsetenv
#
mrbslp

# needed if using local G4 build !
# in lieu of UPS build of geant4 v4_10_4-whatever...
#
cd ${MRB_SOURCE}/G4VMP

node_name=`uname -n`

G4LOCATION="/work1/g4v/yarba_j/geant4-local-builds/gcc-12.1.0"
if [[ $node_name =~ "lq" ]]; then
G4LOCATION="/project/Geant4/yarba_j/geant4-local-builds/gcc-12.1.0"
fi

source ./geant4make-no-ups.sh geant4-11-01-ref-07 ${G4LOCATION}
echo " G4INSTALL = ${G4INSTALL} "

# setup output destiation dir
#
DATE=`date +"%m-%d-%y"`

G4VMP_OUT_BASE="/wclustre/g4v/yarba_j"
# G4VMP_OUT_BASE="/wclustre/g4p/yarba_j"
if [[ $node_name =~ "lq" ]]; then
G4VMP_OUT_BASE="/lustre1/g4/yarba_j"
fi

if [ ! -d "${G4VMP_OUT_BASE}" ]; then
mkdir ${G4VMP_OUT_BASE}
fi

G4VMP_OUT="${G4VMP_OUT_BASE}/g4vmp-study"

if [ ! -d "${G4VMP_OUT}" ]; then
mkdir ${G4VMP_OUT}
fi

if [ ! -d "${G4VMP_OUT}/${DATE}" ]; then
mkdir ${G4VMP_OUT}/${DATE}
fi
if [ ! -d "${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}" ]; then
echo " Creating ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target} "
mkdir ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}
fi

# prepare include with Universes (for the specified NUniv number of them)
# because we make jobs sleep for a random number of seconds before start,
# hopes are that the jobs will NOT "collide" over generating the FCL include
#
FCL_BASENAME=multiU_NUniv${NUniv}
FCL_INCLUDE=${FCL_BASENAME}_${proc_level}.fcl
echo " FCL_INCLUDE = ${FCL_INCLUDE} "
G4ParamTest=${MRB_SOURCE}/G4VMP/G4VMP

if [ ! -e ${G4ParamTest}/ProdScripts/HelperScripts/${FCL_INCLUDE} ]; then
echo " regenerating ${FCL_INCLUDE} "
cd ${G4ParamTest}/ProdScripts/HelperScripts
root -b -p -q ${G4ParamTest}/ProdScripts/HelperScripts/generate_universes.C\(\"${FCL_BASENAME}\"\,${NUniv}\,\"${proc_level}\"\)
else
echo " ${FCL_INCLUDE} exists; do NOT regenerate "
fi

rundirname=/scratch/${proc_level}_${beam}${momz}GeV_${target}_${JobID}
if [ ! -d "${rundirname}" ]; then
/bin/mkdir ${rundirname}
fi

cd ${rundirname}
echo " I am in $PWD "

echo " Copying over ${FCL_INCLUDE} from ${G4ParamTest}/ProdScripts/HelperScripts to ${rundirname}"
rsync -h --progress ${G4ParamTest}/ProdScripts/HelperScripts/${FCL_INCLUDE} ${rundirname}

#
# FIXME !!! Maybe copy them over to each rundir ???
#
. ${G4ParamTest}/ProdScripts/HelperScripts/art_input_sources.sh
. ${G4ParamTest}/ProdScripts/HelperScripts/art_services.sh
. ${G4ParamTest}/ProdScripts/HelperScripts/art_outputs.sh
. ${G4ParamTest}/ProdScripts/HelperScripts/art_producers.sh

config_base=${proc_level}_${beam}${momz}GeV_${target}

config=${config_base}_Default.fcl

if [ -e ${config} ]; then
/bin/rm ${config}
fi

process=G4SIM
#
# ATTENTION !!!
# ONE and the same rndm seed (number) for all GEN fragments !!!
# And it MUST be set in order to be part of GEN fragment;
# otherwise it'll be ommitted, and assumed to be -1 which means
# that the seed will be generated from the timestamp
#
GEN_RNDM=12345
#
seed=1234
outlabel=out${process}

LOGDIR=${G4ParamTest}/ProdScripts/SLURM-shell

# --> export LD_LIBRARY_PATH=${MRB_BUILDDIR}/artg4tk/lib:$LD_LIBRARY_PATH
echo " CET_SUBDIR = ${CET_SUBDIR} "
export LD_LIBRARY_PATH=${MRB_BUILDDIR}/G4VMP/${CET_SUBDIR}.e20.prof/lib:$LD_LIBRARY_PATH

echo " ***** ===== ***** "
echo "LD_LIBRARY_PATH = ${LD_LIBRARY_PATH}"
echo " ***** ===== ***** "

# Do Default only if NU1=1
#
if [ "1" == "$NU1" ]; then

outfile=Evt-${config_base}-Default
if [ ! "x" == "x$JobID" ]; then
# ---> seed=$((${seed}+${JobID}))
seed=$((1234+${JobID}))
config=${config_base}_Default-${JobID}.fcl
outfile=Evt-${config_base}-Default-${JobID}
fi

# NOTE: For SLURM jobs/runs, it's essential to format the include 
#       as "./<your-include>.fcl"
#       If you do "<your-include.fcl>", it's NOT guatanteed to work
#
/usr/bin/printf "#include \"./${FCL_INCLUDE}\" \n" >> ${config}

/usr/bin/printf "process_name: process${process} \n" >> ${config}
cfg_empty_source >> ${config}
cfg_services >> ${config}
cfg_outputs >> ${config}

/usr/bin/printf "physics: { \n" >> ${config}
/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "   producers: { \n" >> ${config}

cfg_generator >> ${config}

/usr/bin/printf "      ${proc_level}Default : @local::${proc_level}Default \n" >> ${config}


/usr/bin/printf "   } \n" >> ${config}

/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "   analyzers: { \n" >> ${config}
/usr/bin/printf " \n" >> ${config}
/usr/bin/printf "   } \n" >> ${config}
/usr/bin/printf " \n" >> ${config}
/usr/bin/printf "   path1: [ PrimaryGenerator,  ${proc_level}Default ] \n" >> ${config} 

/usr/bin/printf "   stream1: [ ${outlabel} ] \n" >> ${config}
/usr/bin/printf "   trigger_paths: [ path1 ] \n" >> ${config}
/usr/bin/printf "   end_paths: [ stream1 ] \n" >> ${config}

/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "} \n" >> ${config}

LOGFILE=${LOGDIR}/LOG_SIM_${SLURM_JOB_ID}_${proc_level}_${beam}${momz}GeV_${target}-Default-${JobID}.log

art -c ${config} >& ${LOGFILE}
# --> /bin/rm ${config}

# ---> rsync -z ${rundirname}/${config} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target} 

#
# Do NOT tar and transfer; 
# instead copy/transfer root files directly
# 
#TARFILE=${rundirname}/${proc_level}_${beam}${momz}GeV_${target}_Default_${JobID}.tgz
#tar zcf ${TARFILE} *.root
## ---> rsync -h -z --progress ${TARFILE} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}
#rsync -z ${TARFILE} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}

evt_root_file_list=`/bin/ls -alF ${rundirname}/*.root | awk '{print $NF}'`
for erf in ${evt_root_file_list}; do
rsync -z ${erf} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}
done

/bin/rm *.root

fi   # end doing Default

pattern=0000

# --> for (( i=1; i<=${NUniv}; ++i )) do
for (( i=${NU1}; i<=${NU2}; ++i )) do

RUN_NUMBER=${i}

# ---> the construct works but it'll do as 1234, 1235, 1237, etc. ---> seed=$((${seed}+${i}))
seed=$((1234+${i}))
pos=$((${#pattern}-${#i}))
# echo ${pattern:0:${pos}}
univ=${pattern:0:${pos}}${i}
#
outfile=Evt-${config_base}-add-Univ${univ}
outlabel=out${process}Univ${univ}
config=${config_base}_Univ${univ}.fcl
if [ ! "x" == "x$JobID" ]; then
# ---> see earlier comment --->  seed=$((${seed}+${JobID}))
offset=$((${JobID}*${JobID}))
seed=$((1234+${i}+${offset}))
config=${config_base}_Univ${univ}-${JobID}.fcl
outfile=Evt-${config_base}-add-Univ${univ}-${JobID}
fi
#
/usr/bin/printf "#include \"./${FCL_INCLUDE}\" \n" >> ${config}

/usr/bin/printf "process_name: process${process}${univ} \n" >> ${config}

cfg_empty_source >> ${config}

cfg_services >> ${config}

# FIXME !!! Maybe it's better to pass it in as env.vars...
# --> SPLIT_OUTPUT=yes
# --> NEVTSPLIT=2500
cfg_outputs >> ${config}

/usr/bin/printf "physics: { \n" >> ${config}
/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "   producers: { \n" >> ${config}

cfg_generator >> ${config}

/usr/bin/printf "      ${proc_level}RandomUniv${univ} : @local::${proc_level}RandomUniv${univ} \n" >> ${config}

/usr/bin/printf "   } \n" >> ${config}

/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "   analyzers: { \n" >> ${config}
/usr/bin/printf " \n" >> ${config}
/usr/bin/printf "   } \n" >> ${config}
/usr/bin/printf " \n" >> ${config}
/usr/bin/printf "   path1: [ PrimaryGenerator, ${proc_level}RandomUniv${univ} ] \n" >> ${config} 

/usr/bin/printf "   stream1: [ ${outlabel} ] \n" >> ${config}
/usr/bin/printf "   trigger_paths: [ path1 ] \n" >> ${config}
/usr/bin/printf "   end_paths: [ stream1 ] \n" >> ${config}

/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "} \n" >> ${config}

LOGFILE=${LOGDIR}/LOG_SIM_${SLURM_JOB_ID}_${proc_level}_${beam}${momz}GeV_${target}-Univ${univ}-${JobID}.log
# NOTE: art == ${ART_FQ_DIR}/bin/art
#
art -c ${config} >& ${LOGFILE}
# --> /bin/rm ${config}

# ---> rsync -z ${rundirname}/${config} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target} 

#
# Do NOT tar and transfer; 
# instead copy/transfer root files directly
# 
#TARFILE=${rundirname}/${proc_level}_${beam}${momz}GeV_${target}_Univ${univ}_${JobID}.tgz
#tar zcf ${TARFILE} *.root
## ---> rsync -h -z --progress ${TARFILE} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}
#rsync -z ${TARFILE} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}

evt_root_file_list=`/bin/ls -alF ${rundirname}/*.root | awk '{print $NF}'`
for erf in ${evt_root_file_list}; do
rsync -z ${erf} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}
done

/bin/rm *.root

#
done

end_sim_time=`date`
echo "End simulation job ${JobID}: ${end_sim_time} "

# --> TARFILE=${rundirname}/${proc_level}_${beam}${momz}GeV_${target}_${JobID}.tgz
# --> tar zcf ${TARFILE} *.root *.fcl 

# --> rsync -h -z --progress ${TARFILE} ${G4VMP_OUT}/${DATE}/${proc_level}_${beam}${momz}GeV_${target}
# --> end_transfer_time=`date`
# --> echo "End transfer output for job ${JobID}: ${end_transfer_time} "

# --> later --> /bin/rm -rf ${rundirname}

