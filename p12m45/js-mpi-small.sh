# commentaar
# @ node = 1
# @ tasks_per_node = 12 
# @ notification = never
# @ input = /dev/null
# @ output = out_p12.$(jobid)
# @ error = err_p12.$(jobid)
# @ wall_clock_limit = 0:45:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p12m45/

./bspfactor2
