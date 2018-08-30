#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define MIN_PID 300
#define MAX_PID 5000

int pidsLength = 4701;
int pids[4701];

pthread_t threads[4701];
int threadCount = 100;

int main(int argc, char const *argv[]){
	if (allocate_map() == 1){
		for (int i = 0; i < threadCount; ++i){
			newProcess();
		}
		for (int i = 0; i < threadCount; ++i)
		{
			pthread_join(threads[i], NULL);
		}
	}
	return 0;
}

void *waiting(void *param){
	srand(time(NULL));
	int r = rand() % 100 * 1000;  
	usleep(r);
	release_pid(param);
	printf("%d %s\n", param, "liberado");
}

int newProcess(){
	int pid = allocate_pid();
	if (pid != -1){
		pthread_t tid;
		pthread_create(&tid,NULL,waiting,pid);
		threads[pid - MIN_PID] = tid;
		printf("%d %s\n", pid, "asignado al thread");
	}else{
		printf("ningun pid libre\n");
	}
}

int allocate_map(void){
	for (int i = 0; i < pidsLength; ++i){
		pids[i] = 0;
	}
	return 1;
}

int allocate_pid(void){
	int pid = -1;
	for (int i = 0; i < pidsLength; ++i){
		if (pids[i] == 0){
			pid = i+MIN_PID;
			pids[i] = 1;
			break;
		}
	}
	return pid;
}

void release_pid(int pid){
	pids[pid - MIN_PID] = 0;
}
