#!/bin/bash
#SBATCH --account=ec54
#SBATCH --job-name=simple
#SBATCH --nodes=1 --ntasks-per-node=8
#SBATCH --mem-per-cpu=2G
#SBATCH --time=0-00:05:00
set -o errexit # Exit the script on any error
set -o nounset # Treat any unset variables as an error
module --quiet purge # Reset the modules to the system default
srun ./a.out