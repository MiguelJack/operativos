#include <stdio.h>
#define MIN_PID 300
#define MAX_PID 5000

int pidsLength = 4701;
int pids[4701];

int main(int argc, char const *argv[]){
	if (allocate_map() == 1){
		for (int i = 0; i < 20; ++i){
			newProcess();
		}
		release_pid(302);
		newProcess();
	}
	return 0;
}

int newProcess(){
	int pid = allocate_pid();
	if (pid != -1){
		printf("%d\n", pid);
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

