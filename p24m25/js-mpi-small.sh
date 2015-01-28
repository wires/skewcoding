# commentaar
# @ node = 1
# @ tasks_per_node = 24
# @ notification = never
# @ input = /dev/null
# @ output = out_p24.$(jobid)
# @ error = err_p24.$(jobid)
# @ wall_clock_limit = 0:25:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p24m25/

./bspfactor2
