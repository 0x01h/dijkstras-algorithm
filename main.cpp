/*

@Author
Student Name: Orçun Özdemir
Student ID: 150140121
Date: 10/02/2018

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
#define MAX 63

using namespace std;

int dijkstra(long int eval[MAX][MAX][MAX][2], int layer, int n_perlayer){
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

int main(){
	srand (time(NULL));
	int k, n, max_length, l;

	long int length[MAX][MAX][MAX][2];

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

	while (max_length < 1){
		cout << "Enter the value that is greater than 1: ";
		cin >> max_length;
	}

	cout << "How many times do you want the algorithm works? ";
	cin >> l;

	while (l < 1){
		cout << "Enter the value that is greater than 1: ";
		cin >> l;
	}

	for (int x = 0; x < n; x++){
		length[0][0][x][0] = rand() % max_length + 1;
	}

	length[0][0][0][1] = 0;

	for (int i = 1; i < k+1; i++){
		for (int x = 0; x < n; x++){
			for (int z = 0; z < n; z++){
				length[i][x][z][0] = rand() % max_length + 1;
				length[i][x][0][1] = 0;
			}
		}
	}

		for (int x = 0; x < n; x++){
				length[k+1][0][x][0] = rand() % max_length + 1;
		}

		length[k+1][0][0][1] = 0;

	auto start_time = chrono::high_resolution_clock::now();

	for (int i = 0; i < l; i++)
		dijkstra(length, k, n);

	auto end_time = chrono::high_resolution_clock::now();

	cout << "Shortest distance to final node: " << length[k+1][0][0][1] << endl <<
	"Elapsed time: " << double(chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()) / 1000000 << " seconds." << endl <<
	"Each run elapsed average time: " << double(chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()) / l << " microseconds." << endl << endl;

	return EXIT_SUCCESS;
}
