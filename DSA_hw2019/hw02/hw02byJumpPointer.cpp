#include <iostream>
#define MAXN 210000
using namespace std;

typedef struct node{
	struct node* children[26];
	struct node* parent;
	int deep;
}node;

inline void init(node* str){
	for (int i = 0; i < 26; i++)
		str->children[i] = NULL;
	return;
}

inline int log2(int n){
	int i = 0;
	int a = 1;
	while ((a << i) <= n)
		i++;
	return i - 1;
}

int grand[MAXN][40] = {{0}};

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	node* string[MAXN];
	string[0] = new node;
	string[0] -> parent = string[0];
	init(string[0]);
	string[0]->deep = 0;
	int parentindex;
	char toappend;
	for (int i = 1; i <= n; i++){
		cin >> parentindex >> toappend;
		string[i] = string[parentindex];
		if (string[i] -> children[toappend - 'a'] == NULL){
			string[i] -> children[toappend - 'a'] = new node;
			string[i] = string[i] -> children[toappend - 'a'];
			string[i] -> parent = string[parentindex];
			init(string[i]);
			string[i] -> deep = (string[parentindex] -> deep) + 1;
		}
		else{
			string[i] = string[i] -> children[toappend - 'a'];
		}
		grand[i][0] = parentindex;
	}

	for (int i = 1; i <= n; i++){
		int level = log2(string[i] -> deep);
		for (int j = 1; j <= level; j++)
			grand[i][j] = grand[grand[i][j - 1]][j - 1];
	}
	int q, index1, index2;
	cin >> q;
	for (int i = 0; i < q; i++){
		cin >> index1 >> index2;
		if (string[index1] -> deep == string[index2] -> deep){
			if (string[index1] == string[index2])
				cout << string[index1] -> deep << '\n';
			else{
				int level = log2(string[index1] -> deep);
				while (level >= 0){
					if (string[grand[index1][level]] != string[grand[index2][level]]){
						index1 = grand[index1][level];
						index2 = grand[index2][level];
					}
					level--;
				}
				cout << string[index1] -> deep - 1 << '\n';
			}
		}
		else if (string[index1] -> deep > string[index2] -> deep){
			int diff = string[index1] -> deep - string[index2] -> deep;
			while (diff > 0){
				index1 = grand[index1][log2(diff)];
				diff = string[index1] -> deep - string[index2] -> deep;
			}
			if (string[index1] == string[index2])
				cout << string[index1] -> deep << '\n';
			else{
				int level = log2(string[index1] -> deep);
				while (level >= 0){
					if (string[grand[index1][level]] != string[grand[index2][level]]){
						index1 = grand[index1][level];
						index2 = grand[index2][level];
					}
					level--;
				}
				cout << string[index1] -> deep - 1 << '\n';
			}
		}	
		else{
			int diff = string[index2] -> deep - string[index1] -> deep;
			while (diff > 0){
				index2 = grand[index2][log2(diff)];
				diff = string[index2] -> deep - string[index1] -> deep;
			}
			if (string[index1] == string[index2])
				cout << string[index1] -> deep << '\n';
			else{
				int level = log2(string[index1] -> deep);
				while (level >= 0){
					if (string[grand[index1][level]] != string[grand[index2][level]]){
						index1 = grand[index1][level];
						index2 = grand[index2][level];
					}
					level--;
				}
				cout << string[index1] -> deep - 1 << '\n';
			}
			
		}	
	}

}
