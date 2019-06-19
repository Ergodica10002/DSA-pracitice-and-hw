#include <iostream>
#define MAXE 1000000
#define MAXV 10000
using namespace std;

typedef struct edge{
	int node1, node2;
	int weight;
}edge;
bool isused[MAXV + 1] = {0};
int group[MAXV + 1] = {0};

edge edgelist[MAXE];
void echange(int e1, int e2){
	edge temp = edgelist[e1];
	edgelist[e1] = edgelist[e2];
	edgelist[e2] = temp;
	return;
}

int main(void)
{
	int vnum, edgenum;
	while (1){
		cin >> vnum >> edgenum;
		if (vnum == 0)
			break;
		for (int i = 1; i <= vnum; i++){
			isused[i] = 0;
			group[i] = 0;
		}
		for (int i = 1; i <= edgenum; i++){
			cin >> edgelist[i].node1 >> edgelist[i].node2 >> edgelist[i].weight;
			int current = i;
			while (edgelist[current].weight < edgelist[current / 2].weight){
				edge temp = edgelist[current];
				edgelist[current] = edgelist[current / 2];
				edgelist[current / 2] = temp;
				current = current / 2;
			}
		}
		for (int i = 1; i <= edgenum; i++){
			cout << edgelist[i].weight << ' ';
		}
		cout << '\n';
		int edgecount = 0, mstw = 0;
		int newgroup = 1;
		while (edgecount < vnum - 1 && edgenum != 0){
			if (group[edgelist[1].node1] != group[edgelist[1].node2] 
					|| group[edgelist[1].node1] == 0 || group[edgelist[1].node2] == 0){
				if (group[edgelist[1].node1] == 0 && group[edgelist[1].node2] == 0){
					group[edgelist[1].node1] = group[edgelist[1].node2] = newgroup;
					newgroup++;
				}
				else if (group[edgelist[1].node1] == 0)
					group[edgelist[1].node1] = group[edgelist[1].node2];
				else if (group[edgelist[1].node2] == 0)
					group[edgelist[1].node2] = group[edgelist[1].node1];
				if (group[edgelist[1].node1] < group[edgelist[1].node2]){
					int g1 = group[edgelist[1].node1];
					int g2 = group[edgelist[1].node2];
					for (int i = 1; i <= vnum; i++){
						if (group[i] == g2)
							group[i] = g1;
					}
				}
				if (group[edgelist[1].node2] < group[edgelist[1].node1]){
					int g1 = group[edgelist[1].node1];
					int g2 = group[edgelist[1].node2];
					for (int i = 1; i <= vnum; i++){
						if (group[i] == g1)
							group[i] = g2;
					}
				}
				edgecount++;
				mstw += edgelist[1].weight;
				cout << "add edge " << edgelist[1].node1 << ' ' << edgelist[1].node2 << ' ' << edgelist[1].weight << '\n'; 
				cout << "groupmatrix\n";
				for (int i = 1; i <= vnum; i++){
						cout << group[i] << ' ';	
				}
				cout << '\n';
			}
			int current = 1;
			edgelist[current] = edgelist[edgenum];
			while (2 * current <= edgenum){
				int left = 2 * current;
				int right = 2 * current + 1;
				if (right > edgenum){
					if (edgelist[current].weight > edgelist[left].weight){
						echange(current, left);
					}
					break;
				}
				if (edgelist[left].weight < edgelist[right].weight){
					if (edgelist[current].weight > edgelist[left].weight){
						echange(current, left);
						current = left;
					}
					else
						break;
				} else{
					if (edgelist[current].weight > edgelist[right].weight){
						echange(current, right);
						current = right;
					}
					else
						break;
				}
			}
			edgenum--;	
		}
		if (edgecount != vnum - 1)
			mstw = -1;
		cout << "mstw = " << mstw << '\n';
		cout << "groupmatrix\n";
		for (int i = 1; i <= vnum; i++){
				cout << group[i] << ' ';	
		}
		cout << '\n';
	}
	

	return 0;
}

