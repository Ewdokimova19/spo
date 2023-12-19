#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>
 
 #include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector> 

#define MSGKEY 75

// | \n

 using namespace std; 

size_t COUNT_THREAD;

 struct mymsg //структура для сообщений
 {
	int x = 0; 
	int y = 0; 
 } m ;

int n;
int buf_sqr;
int** fill_Matrix(int** arr){
	ifstream in("in.txt"); 
	in >> n;
	arr = new int* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int [n]; 
 	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			in >> arr[i][j];
		}
	 }
	in.close(); 
	return (arr);
 }
void print_Matrix(int** arr){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) {
 			cout << setw(4) << arr[i][j] << " ";
		}
	cout << "\n";
	 }
  }

 vector<int> matrixto_Vector(int **arr){
	vector<int> outVec;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			outVec.push_back(arr[i][j]);
		}
	}
	return outVec;
 }

 vector<vector<int>> splitVector(const vector<int>& vec, size_t num){
	vector<vector<int>> outVec (num);
	for (size_t i = 0; i < num; i++){
		outVec[i].resize(num);
		for (size_t j = 0; j < num; j++){
			outVec[i][j] = vec[j + num*i];
		}
	}
	return outVec;
}

int my_Task(vector<int> &arr, int msgid, int z, int buf){ 
	int bufX = 0; 
	int bufY = 0; 
	for (int i = 0; i < arr.size(); i++){ 
		int isPowerOfTwo = 1; 
 		while (isPowerOfTwo < (i+z)){
			isPowerOfTwo*=2;
		}	
		if (isPowerOfTwo == (i+z)){
			cout << arr[i] << " ";
			if (buf < arr[i]){
				buf = arr[i];
				bufX = i;
				bufY = Z;
			}
		}
	}										
	msgctl(msgid,IPC_RMID,0);
	m.x = bufX;
	m.y = bufY;
	msgsnd(msgid, &m, sizeof(int), 0); 
	return buf;
}

void delete_Matrix(int** arr){
	cout <<"\n";
	for (int i = 0; i < n; i++){
		delete [] arr[i];
            for (j=0; j<n; j++){
                cout << setw(4) << arr[i][j] <<" ";
                cout << endl;
            }
	}
	delete [] arr;
}

int main(){

srand(time(NULL));
COUNT_THREAD = 4;
pthread_t threads[COUNT_THREAD];
int **matrix;
fill_Matrix(&matrix);
print_Matrix(matrix);
for(int i = 0; i<n; ++i)
buf_sqr += matrix[rand() % n][i] * matrix[rand() % n][i];
m.x = rand() % n;
m.y = rand() % n;

int buf = 0;
cout <<"\norigin matrix: \n";
print_Matrix(A);
cout << "\nElements with ID sum = power of 2:" << endl;

vector<int> vector_Matrix = matrixto_Vector(A);
COUNT_THREAD = n;

vector<vector<int>> sum_Id2 = splitVector(vector_Matrix, COUNT_THREAD); 

int msgid = msgget (IPC_PRIVATE, IPC_CREAT | 0666);
if (msgid < 0) {
	cout << "Error:"
	return 0;
}
for (int i = 0; i < COUNT_THREAD-1; i++){
	if (fork() == 0){
		buf = my_Task(sum_Id2[i], msgid, i, buf); 
		return 1;
	}
}
buf = my_Task(sum_Id2[COUNT_THREAD-1], msgid, COUNT_THREAD-1, buf); 
while (wait(nullptr) > 0);

for (int i=0 ; i<COUNT_THREAD ; 1++){
	msgrcv(msgid, &m, sizeof(int), 0, 0);
}
cout <<"\nindex 'x' of max element = "<< m.x << index "y" of max element = : << m.y << and MAX element = << buf;
delete_Matrix(A);
return 1;
}

