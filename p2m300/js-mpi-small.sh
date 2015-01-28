# commentaar
# @ node = 1
# @ tasks_per_node = 2 
# @ notification = never
# @ input = /dev/null
# @ output = out_p2.$(jobid)
# @ error = err_p2.$(jobid)
# @ wall_clock_limit = 0:300:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p2m300/

./bspfactor2
