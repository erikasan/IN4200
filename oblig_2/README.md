To compile, change directory to serial_code/ or parallel_code/ respectively and run

`make clean`

`make all`

in the terminal.

To run the serial implementation, execute with

`./serial_main [kappa] [iters] [input_jpeg] [output_jpeg]`

To run the parallel implementation, execute with

`mpirun -np [number of processes] ./parallel_main [kappa] [iters] [input_jpeg] [output_jpeg]`

The number of processes must be greater than 1.

---

I didn't use the slurm queing system in Fox out of convenience during development. To run the programs as described above, first log into Fox as usual (as described here: https://www.uio.no/english/services/it/research/platforms/edu-research/help/login-fox.html). Then once logged into Fox, write in the terminal

`ssh int-[n]`

where `[n]` is 1, 2, 3 or 4. Example:

`ssh int-3`

You will then be asked for a two factor code and your educloud research password, just like when logging in to Fox initially.

Then load OpenMPI using

`module load OpenMPI/3.1.4-GCC-8.3.0`

and compile/run as described above.

