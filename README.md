This was testet with a BSDS120. Make sure that your connections are working, you need a PULLUP !
Furthermore you need to add the kernel-modules


Add:

w1-gpio pullup=1


w1-therm


to

/etc/modules
