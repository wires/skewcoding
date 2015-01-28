# commentaar
# @ node = 1
# @ tasks_per_node = 14
# @ notification = never
# @ input = /dev/null
# @ output = out_p14.$(jobid)
# @ error = err_p14.$(jobid)
# @ wall_clock_limit = 0:40:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p14m40/

./bspfactor2
