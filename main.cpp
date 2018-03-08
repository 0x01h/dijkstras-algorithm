/*

Random Graph Generator Using 4D Array

length[a][b][c][d] = distance/weight
a: layer
b: node rank in layer
c: if (d == 0) then [a][b] has length distance to next layer's cth node.
d: if (d == 0) then distance to next layer's cth node, else if (d == 1) then total minimum distance of each node. 

*/

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <windows.h>
#define MAX 63

using namespace std;

void dijkstra(long long int [MAX][MAX][MAX][2], int, int);
static float CalculateCPULoad();
static unsigned long long FileTimeToInt64();
float GetCPULoad();

int main(){
	srand (time(NULL));
	int k, n, max_length, min_length, l;
	
	static long long int length[MAX][MAX][MAX][2];
	
	cout << "Enter the number of layers: ";
	cin >> k;
	
	while ((k > MAX) || (k < 2)){
		cout << "Enter the value between " << MAX << " and 2: ";
		cin >> k;
	}
	
	cout << "Enter the number of nodes for each layer: ";
	cin >> n;
	
	while ((n > MAX) || (n < 1)){
		cout << "Enter the value between " << MAX << " and 1: ";
		cin >> n;
	}

	cout << "Enter the maximum length between two nodes: ";
	cin >> max_length;
	
	cout << "Enter the minimum length between two nodes: ";
	cin >> min_length;
	
	while ((min_length == 0) || (min_length > max_length)){
		cout << "Enter the value that is not 1 and lower than maximum length: ";
		cin >> min_length;
	}
	
	cout << "How many times do you want the algorithm works? ";
	cin >> l;
	
	for (int x = 0; x < n; x++){
		length[0][0][x][0] = rand() % max_length + min_length;
	}
	
	length[0][0][0][1] = 0;
	
	for (int i = 1; i < k+1; i++){
		for (int x = 0; x < n; x++){
			for (int z = 0; z < n; z++){
				length[i][x][z][0] = rand() % max_length + min_length;
				length[i][x][0][1] = 0;
			}
		}
	}
	
		for (int x = 0; x < n; x++){
				length[k+1][0][x][0] = rand() % max_length + min_length;
		}
		
		length[k+1][0][0][1] = 0;
	
	cout << endl << "Started!" << endl << endl;
	cout << "Layer - 0, ";
	cout << "Node Rank - 0" << endl;
	
	for (int x = 0; x < n; x++){
		cout << "Distance to " << x << "th node: " << length[0][0][x][0] << endl ;
	}
	
	cout << endl << "---------" << endl;
	
	for (int i = 1; i < k; i++){
		for (int x = 0; x < n; x++){
			cout << endl << "Layer - " << i << ", ";
			cout << "Node Rank - " << x << endl;
			for (int z = 0; z < n; z++){
				cout << "Distance to " << z << "th node: " << length[i][x][z][0] << endl;
			}
		}
		cout << endl << "---------" << endl;
	}
	
		for (int x = 0; x < n; x++){
			cout << endl << "Layer - " << k << ", ";
			cout << "Node Rank - " << x << endl;
				cout << "Distance to final node: " << length[k][x][0][0] << endl;
		}
	
	cout << endl << "Finished!" << endl << endl;
	
	cout << endl;
	cout << "Beginning CPU Usage: %" << GetCPULoad() * 100 << endl;
	auto start_time = chrono::high_resolution_clock::now();
	
	for (int i = 0; i < l; i++)
		dijkstra(length, k, n);
	
	auto end_time = chrono::high_resolution_clock::now();
	cout << "Final CPU Usage: %" << GetCPULoad() * 100 << endl << endl;
	
	cout << "Shortest distance to final node: " << length[k+1][0][0][1] << endl <<
	"Elapsed time: " << double(chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()) / 1000000 << " seconds." << endl <<
	"Average time: " << double(chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()) / l << " microseconds." << endl << endl;
	
	system("pause");
	
	return EXIT_SUCCESS;
}

void dijkstra(long long int eval[MAX][MAX][MAX][2], int layer, int n_perlayer){
	long int smallest;
	
	for (int i = 0; i < n_perlayer; i++){
		eval[1][i][0][1] = eval[0][0][i][0];
	}
	
	for (int i = 1; i < layer+1; i++){
		for (int y = 0; y < n_perlayer; y++){

			smallest = eval[i][0][y][0] + eval[i][y][0][1];
			
			for (int z = 1; z < n_perlayer; z++){
			if (smallest > (eval[i][z][y][0] + eval[i][z][0][1])){
				smallest = eval[i][z][y][0] + eval[i][z][0][1];
				}
			}
			
			eval[i+1][y][0][1] = smallest;
		}
	}
	
	smallest = eval[layer][0][0][0] + eval[layer][0][0][1];
	
	for (int y = 1; y < n_perlayer; y++){
			if (smallest > (eval[layer][y][0][0] + eval[layer][y][0][1])){
				smallest = eval[layer][y][0][0] + eval[layer][y][0][1];
			}
	}
	
	eval[layer+1][0][0][1] = smallest;
}

static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;


    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME & ft)
{
    return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.  Returns -1.0 on error.

float GetCPULoad()
{
    FILETIME idleTime, kernelTime, userTime;
    return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
}
