#include <iostream>
#include <vector>
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
	printf("data %d leftnum %d\n", root->data, root->leftnum);
	print(root->right);
}
treenode* insert(int element, treenode*& root){
	treenode* current = root;
	treenode* upcurrent;
	if (root == NULL){
		root = new treenode;
		root->left = root->right = NULL;
		root->leftnum = 0;
		root->data = element;
		return root;
	} 
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
	return root;
}
int search(int pos, treenode*& root){
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
treenode* del(int element, treenode*& root){
	if (root == NULL)
		return root;
	if (root->data == element){
		if (root->left == NULL)
			return root->right;
		else if (root->right == NULL)
			return root->left;
		treenode* leftmax = root->left; //find the max element in left
		treenode* upleftmax = root; //record the parent of the max element in left
		if (leftmax->right == NULL){  
			leftmax->right = root->right;
			delete root;
			return leftmax; 
		}
		while (leftmax->right != NULL){
			upleftmax = leftmax;
			leftmax = leftmax->right;
		}
		root->data = leftmax->data;
		root->leftnum--;
		upleftmax->right = leftmax->left;
		delete leftmax;
		return root;
	}
	if (element > root->data)
		root->right = del(element, root->right);
	else{
		root->leftnum--;
		root->left = del(element, root->left);
	}
	return root;
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
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N, M, K;
	cin >> N >> M >> K;
	int window[MAXLEN];
	cin >> window[0];
	treenode* root = new treenode;
	root->left = root->right = NULL;
	root->leftnum = 0;
	root->data = window[0];
	for (int i = 1; i < M; i++){
		cin >> window[i];
		root = insert(window[i], root);
	}
	cout << search(K - 1, root) << '\n';
	for (int i = M; i < N; i++){
		int element = window[i % M];
		cin >> window[i % M];
		if (element == window[i % M]){
			cout << search(K - 1, root) << '\n';
			continue;
		}
		root = del(element, root);
		element = window[i % M];
		root = insert(element, root);
#if DEBUG
		cout << "now root:\n";
		print(root);
#endif
		cout << search(K - 1, root) << '\n';
	}

	

	return 0;
}
