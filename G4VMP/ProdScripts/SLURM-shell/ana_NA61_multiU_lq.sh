#!/usr/bin/env bash
#

if [ "x" == "x$WORKDIR_TOP" ] ; then
   echo " env.var. WORKDIR_TOP is NOT set; bail out "
   exit 3
fi

# the following two will work only if launched with MPI (--mpi=pmi2)
# JobID=${PMI_RANK})
# JobID=$((1+${PMI_RANK}))
#
# this one (hopefully) works if launched as follows:
# srun -l simulate_multiU_mpi.sh
# or (hopefully) when launcehed with MPI
JobID=$((1+${SLURM_PROCID}))

SLEEP_TIME=$((${RANDOM}%60+1))
echo " JobID = ${JobID} --> will sleep ${SLEEP_TIME} seconds"
/usr/bin/sleep ${SLEEP_TIME}

# define "experiment" (exp.dataset)
#
export experiment=NA61

# in principle, we need to make sure that the number of jobs
# does not exceed the number of cores, or the jobs will
# compete for resources (as it happens in amd32_g4val_slow !)
#
target_list=( C )
momz_list=(  31.0 )

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

# more "uniform" approach as CVMFS is mounted on both Wilson & LQ1 
#

source /cvmfs/geant4-ib.opensciencegrid.org/products/setup

setup xerces_c v3_2_3 -q e20:prof
setup cmake v3_20_0
setup mrb v5_12_02

cd ${WORKDIR_TOP}
source ./localProducts*/setup

# IN THE PAST mrbsetenv was an alias for source ${MRB_DIR}/bin/mrbSetEnv
# it did NOT work if issued from a script - one has to "source" it explicitly
# BUT as of MRB v5-series, such scripts is no longer there, however, mrbsetenv
# seems to work just fine from the script
#
mrbsetenv

cd ${MRB_SOURCE}/G4VMP

node_name=`uname -n`

G4LOCATION="/work1/g4v/yarba_j/geant4-local-builds/gcc-9.3.0"
if [[ $node_name =~ "lq" ]]; then
G4LOCATION="/project/Geant4/yarba_j/geant4-local-builds/gcc-9.3.0"
fi

source ./geant4make-no-ups.sh geant4-10-07-ref-06 ${G4LOCATION}

rundirname=/scratch/analysis_${proc_level}_${beam}${momz}GeV_${target}
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
${rundirname}/HelperScripts
rsync -h --progress ${G4ParamTest}/ProdScripts/HelperScripts/art_services.sh ${rundirname}/HelperScripts
/bin/chmod +x ${rundirname}/HelperScripts/art_services.sh
${rundirname}/HelperScripts
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

# 
# NOTE: obvioulsy, it wont work if the evtfiledir is empty or doesn't exist
#       alternatively one may compose files names explicitly (e.g. from 0 to 31)
#
# ---> nfiles=`/bin/ls -alF ${rundirname}/*.root | wc -l`
# NOTE: Or maybe just as follows ???
# nfiles=`/bin/ls -alF ${rundirname}/*.root | wc -l`
nfiles=`/bin/ls -alF ${evtfiledir}/*.root | wc -l`

config_base=analysis_${proc_level}_${beam}${momz}GeV_${target}_${experiment}

config=${config_base}.fcl

ts_filename=${proc_level}_${beam}${momz}GeV_${target}-ProcL_${experiment}

/usr/bin/printf "process_name: processANALYSIS \n" >> ${config}

#input source
/usr/bin/printf " \n"  >> ${config}
/usr/bin/printf "source: { \n" >> ${config}
/usr/bin/printf "   module_type: RootInput \n" >> ${config} 
/usr/bin/printf "   maxEvents: -1 \n"  >> ${config}
/usr/bin/printf "   fileNames: [ \n " >> ${config}
icount=0
evtrootfile_list=`/bin/ls -alF ${evtfiledir}/*.root | awk '{print $NF}'`
for ff in ${evtrootfile_list}; do
/usr/bin/printf "               \"${ff}\"" >> ${config}
icount=$((${icount}+1))
if [ "${icount}" -lt "${nfiles}" ]; then
/usr/bin/printf ", \n " >> ${config}
fi
done
/usr/bin/printf " \n              ] \n"  >> ${config}
/usr/bin/printf "} \n"  >> ${config}

cfg_services_analysis >> ${config}

/usr/bin/printf " \n" >> ${config}
/usr/bin/printf "physics: { \n" >> ${config}
/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "   producers: { \n" >> ${config}
/usr/bin/printf "   } \n" >> ${config}
/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "   analyzers: { \n" >> ${config}

# now the chain of analyzers...
#
# first of all, default
#
/usr/bin/printf "      ${proc_level}Default${experiment}: \n" >> ${config}
/usr/bin/printf "      { \n" >> ${config}
/usr/bin/printf "         module_type: Analyzer${experiment} \n" >> ${config}
/usr/bin/printf "         ProductLabel: \"${proc_level}Default\" \n" >> ${config}
/usr/bin/printf "         IncludeExpData: \n" >> ${config}
/usr/bin/printf "         { \n" >> ${config}
/usr/bin/printf "            UseASCIIRecords: true \n " >> ${config}
/usr/bin/printf "            Path2Records : \"${JSONDIR}\" \n " >>  ${config}
exp_data_${beam}${momz}GeV_${target}_${experiment} >> ${config} 
/usr/bin/printf "\n         } \n" >> ${config}
/usr/bin/printf "      } \n" >> ${config}
#
# now variants
#
pattern=0000
for (( i=1; i<=${NUniv}; ++i )) do
pos=$((${#pattern}-${#i}))
# echo ${pattern:0:${pos}}
univ=${pattern:0:${pos}}${i}
/usr/bin/printf "      ${proc_level}Univ${univ}${experiment}: \n" >> ${config}
/usr/bin/printf "      { \n" >> ${config}
/usr/bin/printf "         module_type: Analyzer${experiment} \n" >> ${config}
/usr/bin/printf "         ProductLabel: \"${proc_level}RandomUniv${univ}\" \n" >> ${config}
/usr/bin/printf "         IncludeExpData: \n" >> ${config}
/usr/bin/printf "         { \n" >> ${config}
/usr/bin/printf "            UseASCIIRecords: true \n " >> ${config}
/usr/bin/printf "            Path2Records : \"${JSONDIR}\" \n " >>  ${config}
exp_data_${beam}${momz}GeV_${target}_${experiment} >> ${config}
/usr/bin/printf "\n         } \n" >> ${config}
/usr/bin/printf "      } \n" >> ${config}
done

/usr/bin/printf " \n" >> ${config}
/usr/bin/printf "   } \n" >> ${config} # this is the end of analyzers-block

/usr/bin/printf " \n" >> ${config}

# schedule analyzers for the run
/usr/bin/printf "   path2: [ \n" >> ${config}
/usr/bin/printf "            ${proc_level}Default${experiment} \n" >> ${config}
pattern=0000
for (( i=1; i<=${NUniv}; ++i )) do
pos=$((${#pattern}-${#i}))
# echo ${pattern:0:${pos}}
univ=${pattern:0:${pos}}${i}
/usr/bin/printf "          , ${proc_level}Univ${univ}${experiment} \n" >> ${config}
done
/usr/bin/printf "          ] \n" >> ${config} 

/usr/bin/printf "   end_paths: [ path2 ] \n" >> ${config}

/usr/bin/printf " \n" >> ${config}

/usr/bin/printf "} \n" >> ${config}

LOGDIR=${G4ParamTest}/ProdScripts/SLURM-shell
LOGFILE=${LOGDIR}/LOG_ANA_${SLURM_JOB_ID}_${proc_level}_${beam}${momz}GeV_${target}.log
art -c ${config} >& ${LOGFILE}

# NOW NEED TO 
# --> TAR OUTPUT
# --> TRANSFERE OUTPUT TO /lfstev
# --> CLEANUP

TARFILE=${rundirname}/analysis_${proc_level}_${beam}${momz}GeV_${target}.tgz
tar zcf ${TARFILE} ${ts_filename}.root *.fcl


DATE=`date +"%m-%d-%y"`


G4VMP_OUT_BASE="/wclustre/g4p/yarba_j"
if [[ $node_name =~ "lq" ]]; then
G4VMP_OUT_BASE="/lustre1/g4/yarba_j"
fi

if [ ! -d "${G4VMP_OUT_BASE}" ]; then
mkdir ${G4VMP_OUT_BASE}
fi

G4VMP_OUT="${G4VMP_OUT_BASE}/g4vmp-study"

if [ ! -d "${G4VMP_OUT}/${DATE}" ]; then
mkdir ${G4VMP_OUT}/${DATE}
fi
if [ ! -d "${G4VMP_OUT}/${DATE}/analysis_${proc_level}_${target}" ]; then
mkdir ${G4VMP_OUT}/${DATE}/analysis_${proc_level}_${beam}_${experiment}
fi

rsync -h -z --progress ${TARFILE} ${G4VMP_OUT}/${DATE}/analysis_${proc_level}_${beam}_${experiment}

/bin/rm -rf ${rundirname}

exit


