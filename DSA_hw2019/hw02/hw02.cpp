#include <iostream>

using namespace std;

typedef struct node{
	struct node* children[26];
	struct node* parent;
	char value;
	int deep;
}node;

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
		}
		else{
			string[i] = string[i] -> children[toappend - 'a'];
		}
	}
	int q, index1, index2;
	cin >> q;
	for (int i = 0; i < q; i++){
		cin >> index1 >> index2;
		node* str1 = string[index1];
		node* str2 = string[index2];
		int lcp;
		if (str1 -> deep == str2 -> deep){
			lcp = str1 -> deep;
			while (str1 != str2 && lcp != 0){
				str1 = str1 -> parent;
				str2 = str2 -> parent;
				lcp--;
			}
		}
		else if (str1 -> deep > str2 -> deep){
			while (str1 -> deep != str2 -> deep)
				str1 = str1 -> parent;
			lcp = str1 -> deep;
			while (str1 != str2 && lcp != 0){
				str1 = str1 -> parent;
				str2 = str2 -> parent;
				lcp--;
			}
		}	
		else{
			while (str1 -> deep != str2 -> deep)
				str2 = str2 -> parent;
			lcp = str1 -> deep;
			while (str1 != str2 && lcp != 0){
				str1 = str1 -> parent;
				str2 = str2 -> parent;
				lcp--;
			}
		}	
		cout << lcp << '\n';
	}

}
