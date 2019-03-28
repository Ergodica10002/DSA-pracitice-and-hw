#include <iostream>
#define MAXN 420000
#define NDEBUG
using namespace std;

typedef struct node{
	struct node* children[26];
	struct node* parent;
	int index;
	int epos;
	int deep;
}node;

typedef struct segnode{
	struct segnode* left;
	struct segnode* right;
	int leftbound, rightbound;
	int min;
}segnode;

int level[MAXN];
int firstoccur[MAXN];
int count = 0;
int equalindex[MAXN];

void dfs(node* root){
	level[count] = root -> deep;
	root -> epos = count;
	firstoccur[root -> index] = count;
	count++;
	for (int i = 0; i < 26; i++){
		if (root -> children[i] != NULL){
			dfs(root -> children[i]);
			level[count] = root -> deep;
			count++;
		}
	}
	return;
}

segnode* ConstructSegmentTree(segnode*& root, int leftend, int rightend){
	if (root == NULL){
		root = new segnode;
		root -> left = root -> right = NULL;
	}
	if (leftend == rightend){
		root -> leftbound = root -> rightbound = leftend;
		root -> min = level[leftend];
		return root;
	}
	root -> leftbound = leftend;
	root -> rightbound = rightend;
	root -> left = ConstructSegmentTree(root -> left, leftend, (leftend + rightend) / 2);
	root -> right = ConstructSegmentTree(root -> right, (leftend + rightend) / 2 + 1, rightend);
	root -> min = min((root -> left) -> min, (root -> right) -> min);
	return root;
}

void printtree(segnode* root){
	if (root == NULL)
		return;
	printtree(root -> left);
	cout << "left: " << root -> leftbound << " right: " << root -> rightbound << " min: " << root -> min << '\n';
	printtree(root -> right);
	return;
}

int RMQ(segnode* root, int start, int end){
	if (root -> leftbound == start && root -> rightbound == end)
		return root -> min;
	int mid = (root -> leftbound + root -> rightbound) / 2;
	if (end <= mid)
		return RMQ(root -> left, start, end);
	if (start > mid)
		return RMQ(root ->right, start, end);
	return min(RMQ(root -> left, start, mid), RMQ(root -> right, mid + 1, end));
}
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	node* string[n + 1];
	string[0] = new node;
	string[0]->parent = NULL;
	for (int i = 0; i < 26; i++)
		string[0] -> children[i] = NULL;
	string[0] -> deep = 0;
	string[0] -> index = 0;
	equalindex[0] = 0;
	int parentindex;
	char toappend;
	for (int i = 1; i <= n; i++){
		string[i] = new node;
		cin >> parentindex >> toappend;
		string[i] = string[parentindex];
		if (string[i] -> children[toappend - 'a'] == NULL){
			string[i] -> children[toappend - 'a'] = new node;
			string[i] = string[i] -> children[toappend - 'a'];
			string[i] -> parent = string[parentindex];
			for (int j = 0; j < 26; j++)
				string[i]->children[j] = NULL;
			string[i] -> deep = (string[parentindex] -> deep) + 1;
			equalindex[i] = i;
			string[i] -> index = i;
		}
		else{
			string[i] = string[i] -> children[toappend - 'a'];
			equalindex[i] = string[i] -> index;
		}
	}
	dfs(string[0]);
	segnode* root = NULL;
	root = ConstructSegmentTree(root, 0, count - 1);

#ifndef NDEBUG	
	printtree(root);
#endif

	int q, index1, index2;
	cin >> q;
	for (int i = 0; i < q; i++){
		cin >> index1 >> index2;
		index1 = equalindex[index1];
		index2 = equalindex[index2];
		int p1 = firstoccur[index1];
		int p2 = firstoccur[index2];
		if (p1 > p2){
			int temp = p1;
			p1 = p2;
			p2 = temp;
		}
		cout << RMQ(root, p1, p2) << '\n';
	}

}
