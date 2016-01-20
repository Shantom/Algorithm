#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>
#include <algorithm>
#include <stack>
#include <iomanip>
const int INFINITE = 65535;
using namespace std;
ifstream file("graph.txt");

struct Edge
{
	int begin;
	int end;
	int weight;
};
class M_Gragh
{
public:
	int vexnum, edgnum;
	int **Matrix;
	char *data;
	M_Gragh(int v, int e);
	~M_Gragh();
	void Input();
	void DFSTraverse();
	void BFSTraverse();
	void MiniSpanTree_Prim();
	void MiniSpanTree_Kruskal();
	void ShortestPath_Dijkstra(int v);
	void ShortestPath_Floyd();
	void TopologicalSort();
private:
	bool *visit;
	void DFS(int i);
	void BFS(int i);
	void CreateList(Edge *edges);
	//bool cmp(Edge a, Edge b) { return a.weight > b.weight; }// not used
	inline int Find(int *parent, int f) { while (parent[f] >= 0)f = parent[f]; return f; }
	int *P;// Patharray;
	int *D;// ShortPatharray;
	void PrintDij(int v);
	int **PM;// PathMatrix
	int **SPM;// ShortPathMatrix
};

M_Gragh::M_Gragh(int v, int e) :vexnum(v), edgnum(e)
{
	data = new char[v];
	for (int i = 0; i < v; ++i)
		data[i] = 'a'+i;
	Matrix = new int*[v];
	for (int i = 0; i < v; ++i)
		Matrix[i] = new int[v];
	for (int i = 0; i < v; ++i)
		for (int j = 0; j < v; ++j)
			if (i == j)
				Matrix[i][j] = 0;
			else
				Matrix[i][j] = INFINITE;
}

M_Gragh::~M_Gragh()
{
	delete data;
	for (int i = 0; i < vexnum; ++i)
		delete Matrix[i];
	delete Matrix;
}

void M_Gragh::Input()
{
	//cout << "Please input " << edgnum << " edges." << endl;
	for (int i = 0; i < edgnum; ++i)
	{
		int x, y, w;
		file >> x >> y >> w;
		Matrix[x][y] = w;
		Matrix[y][x] = w;

	}
}

void M_Gragh::DFSTraverse()
{
	cout << "DFSTraverse" << endl;
	visit = new bool[vexnum];
	for (int i = 0; i < vexnum; ++i)
		visit[i] = false;
	for (int i = 0; i < vexnum; ++i)
		if (visit[i] == false)
			DFS(i);
	delete[] visit;
}

void M_Gragh::BFSTraverse()
{
	cout << "BFSTraverse" << endl;
	visit = new bool[vexnum];
	for (int i = 0; i < vexnum; ++i)
		visit[i] = false;
	for (int i = 0; i < vexnum; ++i)
		if (visit[i] == false)
			BFS(i);
	delete[] visit;
}

void M_Gragh::MiniSpanTree_Prim()
{
	cout << "MiniSpanTree_Prim" << endl;
	int *adjvex = new int[vexnum];
	int *lowcost = new int[vexnum];
	int total = 0;

	for (int i = 0; i < vexnum; ++i)
	{
		lowcost[i] = Matrix[0][i];
		adjvex[i] = 0;
	}

	for (int i = 1; i < vexnum; ++i)//注意只有n-1条边
	{
		int min = INFINITE;
		int k = 0;
		for (int j = 1; j < vexnum; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}

		}
		cout << '(' << data[adjvex[k]] << ", " << data[k] << ") " << Matrix[adjvex[k]][k] << endl;
		total += Matrix[adjvex[k]][k];
		if (i == vexnum - 1)
		{
			cout << "Total " << total << endl;
			break;
		}
		lowcost[k] = 0;
		for (int j = 1; j < vexnum; ++j)
		{
			if (lowcost[j] != 0 && Matrix[k][j] < lowcost[j])
			{
				lowcost[j] = Matrix[k][j];
				adjvex[j] = k;
			}
		}
	}
	delete[] adjvex;
	delete[] lowcost;
}

void M_Gragh::MiniSpanTree_Kruskal()
{
	cout << "MiniSpanTree_Kruskal" << endl;

	Edge *edges = new Edge[edgnum];
	CreateList(edges);
	int *parent = new int[vexnum];
	int total = 0;
	for (int i = 0; i < vexnum; ++i)
		parent[i] = -1;
	for (int i = 0; i < edgnum; i++)
	{
		int n = Find(parent, edges[i].begin);
		int m = Find(parent, edges[i].end);
		if (n != m)
		{
			parent[n] = m;
			cout << '(' << data[edges[i].begin] << ", " << data[edges[i].end] << ") " << edges[i].weight << endl;
			total += edges[i].weight;
		}
	}
	cout << "Total " << total << endl;

}

void M_Gragh::ShortestPath_Dijkstra(int v)
{
	cout << "ShortestPath_Dijkstra, start vertex: " << v << endl;

	int *final = new int[vexnum];
	D = new int[vexnum];
	P = new int[vexnum];
	for (int i = 0; i < vexnum; i++)
	{
		final[i] = 0;
		D[i] = Matrix[v][i];
		P[i] = v;
	}
	final[v] = 1;

	for (int i = 0; i < vexnum; i++)
	{
		int min = INFINITE;
		int k = 0;
		for (int j = 0; j < vexnum; j++)
		{
			if (!final[j] && D[j] < min)
			{
				min = D[j];
				k = j;
			}
		}
		final[k] = 1;

		for (int j = 0; j < vexnum; j++)
		{
			if (!final[j] && D[k] + Matrix[k][j] < D[j])
			{
				D[j] = D[k] + Matrix[k][j];
				P[j] = k;
			}
		}
	}

	PrintDij(v);

	delete[] final;
	delete[] D;
	delete[] P;
}

void M_Gragh::ShortestPath_Floyd()
{
	PM = new int*[vexnum];
	for (int i = 0; i < vexnum; i++)
		PM[i] = new int[vexnum];
	SPM = new int*[vexnum];
	for (int i = 0; i < vexnum; i++)
		SPM[i] = new int[vexnum];

	for (int i = 0; i < vexnum; i++)
	{
		for (int j = 0; j < vexnum; j++)
		{
			SPM[i][j] = Matrix[i][j];
			PM[i][j] = j;
		}
	}

	for (int k = 0; k < vexnum; k++)
	{
		for (int i = 0; i < vexnum; i++)
		{
			for (int j = 0; j < vexnum; j++)
			{
				if (SPM[i][j]>SPM[i][k] + SPM[k][j])
				{
					SPM[i][j] = SPM[i][k] + SPM[k][j];
					PM[i][j] = PM[i][k];
				}

			}
		}
	}



	for (int i = 0; i < vexnum; i++)
		delete[] PM[i];
	delete[] PM;
	for (int i = 0; i < vexnum; i++)
		delete[] SPM[i];
	delete[] SPM;
}

void M_Gragh::TopologicalSort()
{
	cout << "TopologicalSort: " << endl;
	int *in_degree = new int[vexnum];
	memset(in_degree, 0, sizeof(int)*vexnum);
	stack<int> S;
	for (int i = 0; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
			if (Matrix[i][j]>0 && Matrix[i][j] < INFINITE)
				++in_degree[j];
	for (int i = 0; i < vexnum; i++)
		if (in_degree[i] == 0)
			S.push(i);
	while (!S.empty())
	{
		int gettop = S.top();
		S.pop();
		cout << gettop << ' ';
		for (int i = 0; i < vexnum; i++)
			if (Matrix[gettop][i]>0 && Matrix[gettop][i] < INFINITE)
				if (0 == (--in_degree[i]))
					S.push(i);
	}


	delete[]in_degree;

}

void M_Gragh::DFS(int i)
{
	visit[i] = true;
	cout << i << ' ';
	for (int j = 0; j < vexnum; ++j)
		if (Matrix[i][j] != INFINITE && i != j && visit[j] == false)
			DFS(j);

}

void M_Gragh::BFS(int i)
{
	queue<int> Q;
	Q.push(i);
	visit[i] = true;
	while (!Q.empty())
	{
		i = Q.front();
		Q.pop();
		cout << i << ' ';
		for (int j = 0; j < vexnum; ++j)
			if (Matrix[i][j] != INFINITE && i != j && visit[j] == false)
			{
				Q.push(j);
				visit[j] = true;
			}
	}
}

void M_Gragh::CreateList(Edge *edges)
{
	int k = 0;
	for (int i = 1; i < vexnum; i++)
	{
		for (int j = 0; j < i; ++j)
		{
			if (Matrix[i][j] != 0 && Matrix[i][j] != INFINITE)
			{
				edges[k].begin = j;
				edges[k].end = i;
				edges[k].weight = Matrix[i][j];
				++k;
			}
		}
	}
	sort(edges, edges + edgnum, [](const Edge &a, const Edge &b) {return a.weight < b.weight; });
}

void M_Gragh::PrintDij(int v)
{
	for (int i = 0; i < vexnum; i++)
	{
		if (i != v) {
			cout << "From " << v << " to " << i << ": ";
			if(D[i]==INFINITE)
				cout << "\n\t\t\t\t\t\tDisconnected." << endl;
			else
			{
				stack<int> path;
				int tmp = i;
				do {
					path.push(tmp);
					tmp = P[tmp];
				} while (tmp != v);
				cout << v << " -> ";
				while (!path.empty())
				{
					cout << path.top();
					path.pop();
					if (!path.empty())
						cout << " -> ";
				}
				cout << "\n\t\t\t\t\t\tTotal " << D[i] << '.' << endl;
			}
		}
	}
}

int main()
{
	if (!file)
	{
		puts("open failed.");
		exit(0);
	}

	M_Gragh M(16, 28);
	M.Input();
	M.MiniSpanTree_Kruskal();
}