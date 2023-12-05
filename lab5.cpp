 #include <stdio.h>
 #include <unistd.h>
 #include <sys/ipc.h>
 #include <sys/shm.h>
 #include <sys/sem.h>
 #include <sys/wait.h>
 #include <iostream>
 #include <cmath>

 // | \n

 int shmid;
 int semid;
 sembuf Plus1 = {0, 1, 0}; 
 sembuf Minus1 = {0, -1, 0}; 

 bool simp(int num){
	for (int i = 2; i <= sqrt(num); i++) {
		if (num % i == 0) return false; 
	}
	return true;
 }

 void fill_matrix(int** arr, int len){
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			std::cout << "Enter number [" << i << "][" << j <<"]: ";
			std::cin >> arr[i][j];  
		}
	std::cout << std::endl;	
	}	
 }

 void print_matrix(int** arr, int len){ 
	for (int i = 0; i < len; i++){
		for (int j = 0; j < len; j++) std::cout << arr[i][j] << "\t";
	std::cout << "\n"; 
	}
 }

void delete_matrix(int** arr, int len){
	 for (int i = 0; i < len; i++) delete [] arr[i];
	delete [] arr;
 }

 int main(){

	shmid = shmget (IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); 
	if (shmid < 0){
		std::cout <<"\nError";
		return 0;
	}
	auto m = static_cast<int*>(shmat (shmid, nullptr, 0));
	 *m = 0;

	semid = semget (IPC_PRIVATE, 1, IPC_CREAT | 0666);
	if (semid < 0){
	std::cout <<"\nError";
		return 0;
	}

	int begin;
	int end;
	int run, n;
	std::cout << "Enter number n\n";
	std::cin>> n;
	int **A = new int* [n];
	for (int i = 0; i < n; i++) A[i] = new int [n]; 
	fill_matrix(A, n);
	std::cout <<"\nOrigin matrix: \n";
	print_matrix(A, n);

	run = n/4;
	semop (semid, &Plus1, 1);

	for (int i = 0; i < n; i++){
		if (fork() == 0) {
			begin = run*i;
			end = begin+run;
			for (int i = begin; i < end; i++){
				for (int j = begin; j < end; j++){
					if (A[i][j] == n*n){
						semop(semid, &Minus1, 1);
						*m = *m + 1;
						semop(semid, &Plus1, 1);
					}
				}
			}
			exit(0);
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) {
			  if (A[i][j] == n*n){
				semop (semid, &Minus1, 1); 
				*m = *m + 1;
				semop (semid, &Plus1, 1);				
			}
		}
	}
	while (wait(nullptr) > 0);
	 semctl (semid, 0, IPC_RMID);
	for (int i = 0; i < n; i++){
		for (int j = 0; j <n; j++){
			if (simp(A[i][j])) A[i][j] = *m;
		}
	}

	std::cout <<"\nResult 'm' = " << *m <<"\nResult matrix: \n";
	print_matrix(A, n);
	delete_matrix(A, n);
}