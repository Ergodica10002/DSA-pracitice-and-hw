#include <iostream>
#define MAXN 210000
#define MAXV MAXN * 2
#define NDEBUG

using namespace std;

typedef struct trienode{
	struct trienode* children[26];
	struct trienode* parent;
	int index;
	int deep;
}trienode;

int level[MAXV];
int firstoccur[MAXN];
int count = 0;
int equalindex[MAXN];

int log2(int n){
	int i = 1, result = 0;
	while ((i << 1) <= n){
		i <<= 1;
		result++;
	}
	return result;
}
void dfs(trienode* root){
	level[count] = root -> deep;
	firstoccur[root -> index] = count;
	count++;
	for (int i = 0; i < 26; i++){
		if (root->children[i] != NULL){
			dfs(root->children[i]);
			level[count] = root->deep;
			count++;
		}
	}
	return;
}

int sparse[MAXV][30];
void filltable(int n = count){
	for (int i = 0; i < n; i++)
		sparse[i][0] = level[i];
	for (int i = 1; (1 << i) < n; i++){
		for (int j = 0; j + (1 << i) < n; j++)
			sparse[j][i] = min(sparse[j][i - 1], sparse[j + (1 << (i - 1))][i - 1]);
	}
	return;
}

int RMQ(int pos1, int pos2){
	if (pos1 == pos2)
		return sparse[pos1][0];
	int len = log2(pos2 - pos1);
	return min(sparse[pos1][len], sparse[pos2 - (1 << len)][len]);
}
int main(void)
{	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	trienode* string[n + 1];
	string[0] = new trienode;
	string[0]->parent = string[0];
	for (int i = 0; i < 26; i++)		//init string[0]
		string[0]->children[i] = NULL;
	string[0]->deep = 0;
	string[0]->index = 0;
	equalindex[0] = 0;
	int parentindex;
	char toappend;
	for (int i = 1; i <= n; i++){
		cin >> parentindex >> toappend;
		string[i] = string[parentindex];
		if (string[i]->children[toappend - 'a'] == NULL){
			string[i]->children[toappend - 'a'] = new trienode;
			string[i] = string[i]->children[toappend - 'a'];
			string[i]->parent = string[parentindex];
			for (int j = 0; j < 26; j++)		//init all children
				string[i]->children[j] = NULL;
			string[i]->deep = (string[parentindex]->deep) + 1;
			equalindex[i] = i;
			string[i]->index = i;
		}
		else{
			string[i] = string[i]->children[toappend - 'a'];
			equalindex[i] = string[i]->index;
		}
	}
	dfs(string[0]);
	filltable();
		
	int q, index1, index2;
	cin >> q;
	for (int i = 0; i < q; i++){
		cin >> index1 >> index2;
		index1 = equalindex[index1];
		index2 = equalindex[index2];
		int pos1 = firstoccur[index1];	//where string[index1] first occur at array level 
		int pos2 = firstoccur[index2];	//where string[index2] first occur at array level i
		if (pos1 > pos2)
			swap(pos1, pos2);
		cout << RMQ(pos1, pos2) << '\n';
	}

}
