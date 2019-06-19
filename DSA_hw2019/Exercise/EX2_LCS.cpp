#include <iostream>
#define MAXN 100
using namespace std;
/*
void LCS()
{
    for (int i=0; i<=n1; i++) length[i][0] = 0;
    for (int j=0; j<=n2; j++) length[0][j] = 0;
 
    for (int i=1; i<=n1; i++)
        for (int j=1; j<=n2; j++)
            if (s1[i] == s2[j])
            {
                length[i][j] = length[i-1][j-1] + 1;
                prev[i][j] = 0; // 左上方
            }
            else
            {
                if (length[i-1][j] < length[i][j-1])
                {
                    length[i][j] = length[i][j-1];
                    prev[i][j] = 1; // 左方
                }
                else
                {
                    length[i][j] = length[i-1][j];
                    prev[i][j] = 2; // 上方
                }
            }
 
    cout << "LCS的長度是" << length[n1][n2];
    cout << "LCS是";
    print_LCS(n1, n2);
}
*/
void print_LCS(string s1, string s2, int l1, int l2, int prev[MAXN + 1][MAXN + 1]){
	if (l1 == 0 || l2 == 0)
		return;
	if (prev[l1][l2] == 0){
		print_LCS(s1, s2, l1 - 1, l2 - 1, prev);
		cout << s1[l1 - 1];
	}
	if (prev[l1][l2] == 1){
		print_LCS(s1, s2, l1, l2 - 1, prev);
	}
	if (prev[l1][l2] == 2){
		print_LCS(s1, s2, l1 - 1, l2, prev);
	}
	return;
}
int main(void)
{
	string s1, s2;
	int length[MAXN + 1][MAXN + 1];
	int prev[MAXN + 1][MAXN + 1];
	
	int T;
	cin >> T;
	while (T--){
		int l1, l2;
		cin >> l1 >> l2;
		cin >> s1 >> s2;
		for (int i = 0; i < l1; i++)
			length[i][0] = 0;
		for (int i = 0; i < l2; i++)
			length[0][l2] = 0;
		for (int i = 1; i <= l1; i++){
			for (int j = 1; j <= l2; j++){
				if (s1[i - 1] == s2[j - 1]){
					length[i][j] = length[i - 1][j - 1] + 1;
					prev[i][j] = 0;
				}
				else{
					if (length[i - 1][j] > length[i][j - 1]){
						length[i][j] = length[i - 1][j];
						prev[i][j] = 2; //上方 
					}
					else{
						length[i][j] = length[i][j - 1];
						prev[i][j] = 1; //左方 
					}
				}
			}
		}
		for (int i = 0; i <= l1; i++){
			for (int j = 0; j <= l2; j++){
				cout << length[i][j] << ' ';
			}
			cout << '\n';
		}
		if (length[l1][l2] == 0)
			cout << "*\n";
		else
			print_LCS(s1, s2, l1, l2, prev);
	}


	return 0;
}

