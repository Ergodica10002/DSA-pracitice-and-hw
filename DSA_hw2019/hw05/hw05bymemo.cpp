#include <iostream>
#define modnum 1000000007 
#define NDEBUG
using namespace std;
int grid[11][11] = {{0}};
unsigned long long combin[100][100] = {{0}};
unsigned long long waysfound[10000000] = {0};
bool isfound[10000000] = {0};
unsigned int transfer(int l1, int r1, int l2, int r2, int k){
	int num = (((l1 * 11 + r1) * 11 + l2) * 11 + r2) * 200 + k;
	return num;
}
void fillcombin(void){
	for (int i = 0; i < 100; i++){
		combin[i][0] = combin[i][i] = 1;
	}
	for (int i = 1; i < 100; i++){
		for (int j = 1; j < i; j++){
			combin[i][j] = (combin[i - 1][j] + combin[i - 1][j - 1]) % modnum;
		}
	}
}
int findcut(int type, int l1, int r1, int l2, int r2, int array[12]){
	int c = 0;
	if (type == 0){
		if (l1 + 1 >= r1)
			return 0;
		for (int i = l1; i < r1; i++){
			bool tocut = 1;
			for (int j = l2; j < r2; j++){
				if (grid[i][j] == 0){
					tocut = 0;
					break;
				}
			}
			if (tocut == 1){
				array[c] = i;
				c++;
			}
		}
	}
	else{
		if (l2 + 1 >= r2)
			return 0;
		for (int i = l2; i < r2; i++){
			bool tocut = 1;
			for (int j = l1; j < r1; j++){
				if (grid[j][i] == 0){
					tocut = 0;
					break;
				}
			}
			if (tocut == 1){
				array[c] = i;
				c++;
			}
		}
	}
	return c;
}

unsigned long long countways(int l1, int r1, int l2, int r2, int k){
	if (k > 0 && (l1 >= r1 || l2 >= r2)){
#ifndef NDEBUG
		cout << "state " << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << ' ' << k << " ways: " << 0 << '\n';
#endif		
		return 0;
	}
	if (k == 0){
#ifndef NDEBUG
		cout << "state " << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << ' ' << k << " ways: " << 1 << '\n';
#endif	
		return 1;
	}
	int cutrow[12] = {0};
	int cutcol[12] = {0};
	int cx = findcut(0, l1, r1, l2, r2, cutrow);
	int cy = findcut(1, l1, r1, l2, r2, cutcol);
	unsigned long long aways = 0, bways = 0, totalways = 0;
	for (int i = 0; i < cx; i++){
#ifndef NDEBUG
		cout << "cut row " << cutrow[i] << '\n';
#endif
		for (int ka = 0; ka < k; ka++){
			unsigned int t = transfer(l1, cutrow[i], l2, r2, ka);
			if (isfound[t] == 1)
				aways = waysfound[t];
			else{
				aways = countways(l1, cutrow[i], l2, r2, ka) % modnum;
				waysfound[t] = aways;
				isfound[t] = 1;
			}
			t = transfer(cutrow[i] + 1, r1, l2, r2, k - 1 - ka);
			if (isfound[t] == 1)
				bways = waysfound[t];
			else{
				bways = countways(cutrow[i] + 1, r1, l2, r2, k - 1 - ka) % modnum;
				waysfound[t] = bways;
				isfound[t] = 1;
			} 
			totalways += ((combin[k - 1][ka] * aways) % modnum) * bways;
			totalways = totalways % modnum;
			
		}	
	}
	for (int i = 0; i < cy; i++){
#ifndef NDEBUG
		cout << "cut col " << cutcol[i] << '\n';
#endif
		for (int ka = 0; ka < k; ka++){
			unsigned int t = transfer(l1, r1, l2, cutcol[i], ka);
			if (isfound[t] == 1)
				aways = waysfound[t];
			else{
				aways = countways(l1, r1, l2, cutcol[i], ka) % modnum;
				waysfound[t] = aways;
				isfound[t] = 1;
			}
			t = transfer(l1, r1, cutcol[i] + 1, r2, k - 1 - ka);
			if (isfound[t] == 1)
				bways = waysfound[t];
			else{
				bways = countways(l1, r1, cutcol[i] + 1, r2, k - 1 - ka) % modnum;
				waysfound[t] = bways;
				isfound[t] = 1;
			}
			totalways += ((combin[k - 1][ka] * aways) % modnum) * bways;
			totalways = totalways % modnum;
		}	
	}
#ifndef NDEBUG
	cout << "state " << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << ' ' << k << " ways: " << totalways <<'\n';
#endif
	
	
	return totalways;
}
int main(void)
{
	int N, M;
	char c;
	cin >> N >> M;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			cin >> c;
			if (c == 'O')
				grid[i][j] = 1;
		}
	}

	fillcombin();
	int k = 0;
	unsigned long long result = 0;
	unsigned long long toadd;
	while (1){
#ifndef NDEBUG
		cout << "new k = " << k << '\n';
#endif
		toadd = countways(0, N, 0, M, k);
		if (toadd == 0)
			break;
		result += toadd;
		result = result % modnum;
		k++;
	}
	cout << result << '\n';
	
	

	return 0;
}

