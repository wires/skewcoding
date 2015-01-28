# commentaar
# @ node = 1
# @ tasks_per_node = 32 
# @ notification = never
# @ input = /dev/null
# @ output = out_p32.$(jobid)
# @ error = err_p32.$(jobid)
# @ wall_clock_limit = 0:15:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p32m15/

./bspfactor2
