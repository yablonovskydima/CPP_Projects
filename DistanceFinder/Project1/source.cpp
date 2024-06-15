#include <iostream>
#include <limits.h>
#include <Windows.h>

#define MAX_VERTICES 6
#define INF INT_MAX

using namespace std;

typedef struct {
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
	int numVertices;
} Graph;

void initializeGraph(Graph* graph, int n) {
	graph->numVertices = n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			graph->adjMatrix[i][j] = (i == j) ? 0 : INF;
		}
	}
}

void addEdge(Graph* graph, int start, int end, int weight)
{
	graph->adjMatrix[start][end] = weight;
	graph->adjMatrix[end][start] = weight;
}

void dijkstra(Graph* graph, int startVertex) {
	int dist[MAX_VERTICES];
	bool visited[MAX_VERTICES] = { 0 };

	for (int i = 0; i < graph->numVertices; i++) {
		dist[i] = INF;
	}
	dist[startVertex] = 0;

	for (int i = 0; i < graph->numVertices - 1; i++) {
		int minDist = INF, minIndex = -1;
		for (int v = 0; v < graph->numVertices; v++) {
			if (!visited[v] && dist[v] <= minDist) {
				minDist = dist[v];
				minIndex = v;
			}
		}

		if (minIndex == -1) break;

		visited[minIndex] = true;

		for (int v = 0; v < graph->numVertices; v++) {
			if (!visited[v] && graph->adjMatrix[minIndex][v] != INF && dist[minIndex] != INF &&
				dist[minIndex] + graph->adjMatrix[minIndex][v] < dist[v]) {
				dist[v] = dist[minIndex] + graph->adjMatrix[minIndex][v];
			}
		}
	}

	cout << "Vertex\tDistance from Source\n";
	for (int i = 0; i < graph->numVertices; i++) {
		if (dist[i] == INF) {
			cout << i << "\tINF\n";
		}
		else {
			cout << i << "\t" << dist[i] << "\n";
		}
	}
}

void floydWarshall(Graph* graph) {
	int dist[MAX_VERTICES][MAX_VERTICES];

	for (int i = 0; i < graph->numVertices; i++) {
		for (int j = 0; j < graph->numVertices; j++) {
			dist[i][j] = graph->adjMatrix[i][j];
		}
	}

	for (int k = 0; k < graph->numVertices; k++) {
		for (int i = 0; i < graph->numVertices; i++) {
			for (int j = 0; j < graph->numVertices; j++) {
				if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	cout << "Pair\tDistance\n";
	for (int i = 0; i < graph->numVertices; i++) {
		for (int j = 0; j < graph->numVertices; j++) {
			if (dist[i][j] == INF) {
				cout << i << "-" << j << "\tINF\n";
			}
			else {
				cout << i << "-" << j << "\t" << dist[i][j] << "\n";
			}
		}
	}
}

void printRoutesWithinDistance(Graph* graph, int startVertex, int maxDistance) {
	int dist[MAX_VERTICES];
	bool visited[MAX_VERTICES] = { 0 };

	for (int i = 0; i < graph->numVertices; i++) {
		dist[i] = INF;
	}
	dist[startVertex] = 0;

	for (int i = 0; i < graph->numVertices - 1; i++) {
		int minDist = INF, minIndex = -1;
		for (int v = 0; v < graph->numVertices; v++) {
			if (!visited[v] && dist[v] <= minDist) {
				minDist = dist[v];
				minIndex = v;
			}
		}

		if (minIndex == -1) break;

		visited[minIndex] = true;

		for (int v = 0; v < graph->numVertices; v++) {
			if (!visited[v] && graph->adjMatrix[minIndex][v] != INF && dist[minIndex] != INF &&
				dist[minIndex] + graph->adjMatrix[minIndex][v] < dist[v]) {
				dist[v] = dist[minIndex] + graph->adjMatrix[minIndex][v];
			}
		}
	}

	cout << "Vertex\tDistance from Source\n";
	for (int i = 0; i < graph->numVertices; i++) {
		if (dist[i] <= maxDistance) {
			cout << i << "\t" << dist[i] << "\n";
		}
	}
}

void menu() {
	cout << "Menu:\n";
	cout << "1. Shortest paths from a given vertex (Dijkstra's algorithm)\n";
	cout << "2. Shortest paths between all pairs of vertices (Floyd's algorithm)\n";
	cout << "3. Shortest routes to cities within a given distance\n";
	cout << "4. Exit\n";
}

int main() {
	SetConsoleOutputCP(1251);
	int startVertex, maxDistance;
	Graph graph;

	initializeGraph(&graph, MAX_VERTICES);

	addEdge(&graph, 0, 1, 30);
	addEdge(&graph, 0, 2, 60);
	addEdge(&graph, 0, 3, 40);
	addEdge(&graph, 1, 4, 35);
	addEdge(&graph, 2, 3, 30);
	addEdge(&graph, 2, 5, 50);
	addEdge(&graph, 3, 5, 20);
	addEdge(&graph, 5, 0, 15);

	int choice;

	while (true) {
		menu();
		cout << "Choose an option: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter start vertex (0-Ivano-Frankivsk, 1-Kalush, 2-Kolomyia, 3-Nadvirna, 4-Dolyna, 5-Tysmenytsia): ";
			cin >> startVertex;
			if (startVertex >= 0 && startVertex < MAX_VERTICES) {
				dijkstra(&graph, startVertex);
				system("pause");
				system("cls");
			}
			else {
				cout << "Invalid vertex choice. Try again.\n";
				system("pause");
				system("cls");
			}
			break;
		case 2:
			floydWarshall(&graph);
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "Enter start vertex (0-Ivano-Frankivsk, 1-Kalush, 2-Kolomyia, 3-Nadvirna, 4-Dolyna, 5-Tysmenytsia): ";
			cin >> startVertex;
			if (startVertex >= 0 && startVertex < MAX_VERTICES) {
				cout << "Enter maximum distance: ";
				cin >> maxDistance;
				printRoutesWithinDistance(&graph, startVertex, maxDistance);
				system("pause");
				system("cls");
			}
			else {
				cout << "Invalid vertex choice. Try again.\n";
				system("pause");
				system("cls");
			}
			break;
		case 4:
			exit(0);
		default:
			cout << "Invalid choice, try again.\n";
			system("pause");
			system("cls");
		}

		cout << "\n";
	}

	return 0;
}
