#include <iostream>
#define MAXN 100000
using namespace std;
int a[MAXN], b[MAXN], c[MAXN];

/*b[i]�O���q�Ĥ@�Ӽƨ��i�Ӽƨ��Y�ǼƦr(�ܤ֨��@��)���̤j�ȬO�h�֡A(��i�Ӥ��@�w�n��)�A
b[0]=a[0]�Ai=1~N-1�ɡAb[i]=max(a[i], b[i-1], a[i]+b[i-1])*/
/*c[i]�O���H��i�Ӭ��̫�@�Ӫ��̤j���s��M�O�h�֡A(��i�Ӥ@�w�n��)
c[2]=a[0]+a[2]�Ai=3~N�ɡAc[i]=max(c[i-1], b[i-2])+a[i]*/
/*ans = max(c[2], c[3], ... , c[n - 1]*/

int main(void)
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	b[0] = a[0];
	for (int i = 1; i < n; i++){
		int s1 = b[i - 1];
		int s2 = b[i - 1] + a[i];
		int s3 = a[i];
		if (s1 > s2 && s1 > s3)
			b[i] = s1;
		else if (s2 > s1 && s2 > s3)
			b[i] = s2;
		else
			b[i] = s3;
	}
	c[0] = c[1] = -1000000;
	c[2] = a[0] + a[2];
	for (int i = 3; i < n; i++){
		int s1 = b[i - 2] + a[i];
		int s2 = c[i - 1] + a[i];
		if (s1 > s2)
			c[i] = s1;
		else
			c[i] = s2;
	}
	int ans = -1000000;
	for (int i = 0; i < n; i++)
		cout << c[i] << ' ';
	cout << '\n';
	for (int i = 0; i < n; i++)
		if (ans < c[i])
			ans = c[i];
	cout << ans;
	

	return 0;
}

