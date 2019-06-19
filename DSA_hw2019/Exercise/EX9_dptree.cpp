#include <iostream>
#include <vector>
#define MAXN 200000 
#define INF 2147483647
using namespace std;
int a[MAXN];
vector <int> adnode[MAXN];
int sum[MAXN];
int maxsum[MAXN];
int dfssum(int root, int parent){
	if (sum[root] == -INF){
		sum[root] = a[root];
		int size = adnode[root].size();
		for (int i = 0; i < size; i++){
			if (adnode[root][i] != parent){
				sum[root] += dfssum(adnode[root][i], root);
			}
		}
		return sum[root];
	}
	else
		return sum[root];
}
int dfsmax(int root, int parent){
	if (adnode[root].size() == 1){
		maxsum[root] = sum[root];
		printf("root %d max %d\n", root, maxsum[root]);
		return maxsum[root];
	}
	else{
		int nowmax = -INF;
		for (int i = 0; i < adnode[root].size(); i++){
			if (adnode[root][i] != parent){
				int child = dfsmax(adnode[root][i], root);
				if (nowmax < child)
					nowmax = child;
			}
		}
		maxsum[root] = max(sum[root], nowmax);
		printf("root %d max %d\n", root, maxsum[root]);
		return maxsum[root];
	}
}
int dfsans(int root, int parent){
	if (adnode[root].size() <= 2 && parent != -1){
		return maxsum[root];
	}
	int nowmax = -INF;
	for (int i = 0; i < adnode[root].size(); i++){
		if (adnode[root][i] == parent)
			continue;
		int childans = dfsans(adnode[root][i], root);
		nowmax = max(nowmax, childans);
	}
	cout << "root nowmax " << root << ' ' << nowmax << '\n';
	int max1index = -1, max2index = -1;
	for (int i = 0; i < adnode[root].size(); i++){
		if (adnode[root][i] == parent)
			continue;
		if (max1index == -1)
			max1index = i;
		if (maxsum[adnode[root][i]] > maxsum[adnode[root][max1index]]){
			max1index = i;
		}	
	}
	for (int i = 0; i < adnode[root].size(); i++){
		if (adnode[root][i] == parent || i == max1index)
			continue;
		if (max2index == -1)
			max2index = i;
		if (maxsum[adnode[root][i]] > maxsum[adnode[root][max2index]]){
			max2index = i;
		}
	}
	return (max(maxsum[adnode[root][max1index]] + maxsum[adnode[root][max2index]], nowmax));
}
int main(void)
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 0; i < n - 1; i++){
		int n1, n2;
		cin >> n1 >> n2;
		adnode[n1].push_back(n2);
		adnode[n2].push_back(n1);
	}
	for (int i = 1; i <= n; i++)
		sum[i] = -INF;
	dfssum(1, -1);
	dfsmax(1, -1);
	cout << "\nans " << dfsans(1, -1);

	return 0;
}

