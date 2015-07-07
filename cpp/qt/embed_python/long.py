import time

counter = 0
while counter < 5:
    print "Thread 1"
    time.sleep(5)
    counter += 1

print "done 1"
