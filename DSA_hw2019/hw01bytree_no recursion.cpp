#include <iostream>
#define MAXLEN 200000
#define DEBUG 0
using namespace std;
typedef struct treenode{
	int data;
	treenode* left;
	treenode* right;
	int leftnum;
}treenode;
void print(treenode* root){
	if (root == NULL)
		return;
	print(root->left);
	cout << "data" << root->data << " leftnum " << root->leftnum << '\n';
	print(root->right);
}
void insert(int element, treenode* root){
	treenode* current = root;
	treenode* upcurrent;
	while (current != NULL){
		upcurrent = current;
		if (element > current->data){
			current = current->right;
		}else{
			current->leftnum++;
			current = current->left;
		}
	}
	current = new treenode;
	current->left = current->right = NULL;
	current->leftnum = 0;
	current->data = element;
	if (element > upcurrent->data)
		upcurrent->right = current;
	else
		upcurrent->left = current;
	return;
}
int search(int pos, treenode* root){
	treenode* current = root;
	while (current != NULL && (current->leftnum) != pos){
		if (pos == 0){
			while (current->left != NULL)
				current= current->left;
			return current->data;
		}
		if (current->leftnum < pos){
			pos = pos - current->leftnum - 1;
			current = current->right;
		}
		else{
			current = current->left;
		}
	}
	return (current == NULL)? -1 : current->data;
}
void del(int element, treenode* root){
	if (root == NULL)
		return;
	treenode* uproot = root;
	while (root->data != element){
		if (element > root->data){
			uproot = root;
			root = root->right;
		}
		else{
			root->leftnum--;
			uproot = root;
			root = root->left;
		}
	}
	if (root->left == NULL){
		treenode* rootright = root->right;
		root->left = rootright->left;
		root->right = rootright->right;
		root->data = rootright->data;
		root->leftnum = rootright->leftnum;
		return;
	}
	else if (root->right == NULL){
		treenode* rootleft = root->left;
		root->left = rootleft->left;
		root->right = rootleft->right;
		root->data = rootleft->data;
		root->leftnum = rootleft->leftnum;
		return;
	}
	treenode* leftmax = root->left; //find the max element in left
	treenode* upleftmax = root; //record the parent of the max element in left
	if (leftmax->right == NULL){  
		root->left = leftmax->left;
		root->data = leftmax->data;
		root->leftnum = leftmax->leftnum;
		return;
	}
	while (leftmax->right != NULL){
		upleftmax = leftmax;
		leftmax = leftmax->right;
	}
	root->data = leftmax->data;
	root->leftnum--;
	upleftmax->right = leftmax->left;
	delete leftmax;
	return;
}
void insertionSort(int* buffer, int size)
{
	for (int i = 1; i < size; i++){
		int j = i;
		int temp = buffer[i];
		while (j > 0 && buffer[j - 1] > temp){
			buffer[j] = buffer[j - 1];
			j--;
		}
		buffer[j] = temp;
	}
	cout << "insertionSort result:\n";
	for (int i = 0; i < size; i++)
		cout << buffer[i] << ' ';
	cout << endl;
	return;
}
using namespace std;
int main()
{
//	ios_base::sync_with_stdio(false);
//	cin.tie(0);
	int N, M, K;
	cin >> N >> M >> K;
	int window[MAXLEN];
	if (M == 1){
		for (int i = 0; i < N; i++){
			cin >> window[0];
			cout << window[0] << '\n';
		}
	}
	else{
		for (int i = 0; i < M; i++){
			cin >> window[i];
		}
		treenode* root = new treenode;
		root->left = root->right = NULL;
		root->leftnum = 0;
		root->data = window[0];
		for (int i = 1; i < M; i++)
			insert(window[i], root);
		cout << search(K - 1, root) << '\n';
		for (int i = M; i < N; i++){
			del(window[i % M], root);
#if DEBUG
			cout << "afterdel root:\n";
			print(root);
			cout << '\n';
#endif
			cin >> window[i % M];
			int element = window[i % M];
			insert(element, root);
#if DEBUG
			cout << "now root:\n";
			print(root);
			cout << '\n';
#endif
			cout << search(K - 1, root) << '\n';
		}
	}
	return 0;
}
