# commentaar
# @ node = 1
# @ tasks_per_node = 6 
# @ notification = never
# @ input = /dev/null
# @ output = out_p6.$(jobid)
# @ error = err_p6.$(jobid)
# @ wall_clock_limit = 0:100:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p6m100/

./bspfactor2
