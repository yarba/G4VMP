#!/usr/bin/env bash
#

DIR=${1}

# --> TOOLDIR=/work1/g4v/yarba_j/Global-Fits-Tools/Go-HEP-stop-gap/yoda/bin
# --> TOOLDIR=/work1/g4v/yarba_j/Professor/gcc-7.3.0/YODA-1.6.7-install/bin
TOOLDIR=/work1/g4v/yarba_j/Global-Fits-Tools/gcc9.3.0+p3915/YODA-1.9.7-install/bin

# NOTE: the A option (capital) means don't display whatever starts with "."
list=`ls -AlF ${DIR} | grep -v total | awk '{print $NF}'`

# --> echo ${list} 

for entry in ${list}; do

if [ -d "${DIR}/${entry}"  ]; then
      # it's a dir
# -->      echo "it is a dir"
# NOTE: if it's a scan dir, entries will show as "0001/", etc.,
#       so there's no need for a "/" before "*.root"
      list_root=`ls -alF ${DIR}/${entry}*.root | awk '{print $NF}'`
# -->      echo " list_root: ${list_root}"
      for ff in ${list_root}; do
         echo "converting ${ff} --> ${ff%.*}.yoda "
# -->         ${TOOLDIR}/root2yoda-linux_amd64.exe ${ff} > ${ff%.*}.yoda
         ${TOOLDIR}/root2yoda ${ff} ${ff%.*}.yoda
         echo "deleting ${ff}"
	 rm ${ff}
      done
else
   if [ -f "${DIR}/${entry}" ]; then
      # it's a file
      echo "it is a file"
      echo ${entry##*.}
      echo ${entry%.*}
      if [ "${entry##*.}" == "root" ]; then
         echo " converting " ${entry}
# -->	 ${TOOLDIR}/root2yoda-linux_amd64.exe ${DIR}/${entry} > ${DIR}/${entry%.*}.yoda 
	 ${TOOLDIR}/root2yoda ${DIR}/${entry}  ${DIR}/${entry%.*}.yoda 
	 # rm ${DIR}/${entry}
      fi
   else
      # not valid
      # echo "not valid"
      exit 1
   fi
fi

done
