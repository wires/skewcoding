# commentaar
# @ node = 1
# @ tasks_per_node = 16
# @ notification = never
# @ input = /dev/null
# @ output = out_p16.$(jobid)
# @ error = err_p16.$(jobid)
# @ wall_clock_limit = 0:30:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p16m30/

./bspfactor2
