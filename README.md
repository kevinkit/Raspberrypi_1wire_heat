This was testet with a BSDS120. Make sure that your connections are working, you need a PULLUP !
Furthermore you need to add the kernel-modules


Add:

w1-gpio pullup=1


w1-therm


to

/etc/modules




or run the 1_wireactive.sh before starting.








   Settings
   ./read 0

   Reads out whole data package

   ./read 1

   Read out the temperatue only

   ./read [0/1] SECS
   SECS stands for the seconds waited in the loop


   /.read [0/1] SECS file.cvs
   Write temperatures into cvs file in 123,3123 format 
The values will be in the secomd column.

   ./read [0/1] SECS file.cvs NUMBEr

NUMBER says how many data you want to collect - leave it out and there will be an infinite loop which can onle be borken by SIGKILL (strg+c) atm, which leads to the bug that no data will be written into the cvs file

