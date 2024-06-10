# Rate Monotonic Scheduler Analysis (Feasibility Test) Script

from math import ceil

tasks = [(0.001, 1), (0.04, 3), (0.001, 1), (0.2, 21), (4.5, 12), (0.02, 3), (400, 861), (60, 474)]                       # Task set: (execution_time, period)
n = len(tasks)                                                  # Number of tasks

U = sum((task[0] / task[1]) for task in tasks)                  # Compute utilization U

if(U > 1):
       
       print("U = " + str(U) + " > 1 -> NON FEASIBLE - EOE")
       
elif(U <= 1):

       LUB = {                                                  # Least Upper Bound
           1 : 1.00,
           2 : 0.828,
           3 : 0.779,
           4 : 0.756,
           5 : 0.743,
           6 : 0.734,
           7 : 0.728,
           8 : 0.724
       }
       
       if(U >= 0 and U <= LUB[n]):

           print("0 <= U = " + str(U) + " <= LUB(" + str(n) + ") = " + str(LUB[n]) + " -> FEASIBLE - EOE")

       elif(U > LUB[n] and U <= 1):

           RT = sum(task[0] for task in tasks)                                     # Calculate Initial Worst Case Response Time

           lowest_priority_task = max(tasks, key=lambda x: x[1])                   # Find the task with the greatest period / lowest priority
           lowest_priority_task_index = tasks.index(lowest_priority_task) + 1      # Index of the lowest priority task
           tasks.remove(lowest_priority_task)                                      # Remove the task with the lowest priority from the list

           RT_tmp = 0
           iteration = 0

           while(True):    

               print("RT" + str(lowest_priority_task_index) + '_' + str(iteration) + " = " + str(RT))

               if(RT > lowest_priority_task[1]):
                   print("RT" + str(lowest_priority_task_index) + '_' + str(iteration) + " = " + str(RT) + " > PT" + str(lowest_priority_task_index) + " = " + str(lowest_priority_task[1]) + " -> NON FEASIBLE - EOE")
                   break
               elif(RT_tmp == RT and RT <= lowest_priority_task[1]):
                   print("RT" + str(lowest_priority_task_index) + '_' + str(iteration) + " = RT" + str(lowest_priority_task_index) + '_' + str(iteration - 1) + " = " + str(RT) + " <= PT" + str(lowest_priority_task_index) + " = " + str(lowest_priority_task[1]) + " -> FEASIBLE - EOE")
                   break

               other = 0
               for task in tasks:
                   other += ceil((RT / task[1]) * task[0])

               RT_tmp = RT
               RT = lowest_priority_task[0] + other

               iteration += 1
