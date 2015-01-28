# commentaar
# @ node = 1
# @ tasks_per_node = 8 
# @ notification = never
# @ input = /dev/null
# @ output = out_p8.$(jobid)
# @ error = err_p8.$(jobid)
# @ wall_clock_limit = 0:80:00
# @ job_type = shared
# 
# @ queue
#
cd $HOME/nela/p8m80/

./bspfactor2
