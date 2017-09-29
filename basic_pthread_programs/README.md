The test_mutex.c program essentially has a few basic pthread and mutex calls using the POSIX API.

The test_cond.c program has a few basic calls to the pthread conditional variables.

Invocation example: $gcc test_mutex.c -pthread -o test_mutex
		    $./test_mutex
