# commentaar
# @ node = 1
# @ tasks_per_node = 10 
# @ notification = never
# @ input = /dev/null
# @ output = out_p10.$(jobid)
# @ error = err_p10.$(jobid)
# @ wall_clock_limit = 0:60:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p10m60/

./bspfactor2
