# commentaar
# @ node = 1
# @ tasks_per_node = 4 
# @ notification = never
# @ input = /dev/null
# @ output = out_p4.$(jobid)
# @ error = err_p4.$(jobid)
# @ wall_clock_limit = 0:160:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p4m160/

./bspfactor2
