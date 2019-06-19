#include <iostream>
#define MAXN 100000 

using namespace std;
char food[MAXN];
int toadd(int s, int f){
	int l2dayf = s / 4, ldayf = s % 4;
	if (ldayf == 0){
		return 1;
	}
	if (l2dayf == 0){
		return (ldayf == f)? 1 : 2;
	}
	if (l2dayf != ldayf && l2dayf != f && ldayf != f)
		return 3;
	else if (l2dayf == ldayf && l2dayf == f)
		return 1;
	else
		return 2;
}
int mine(int n, int day, int s1, int s2){
	if (n == day)
		return 0;
	int f;
	if (food[day] == 'M')
		f = 1;
	else if (food[day] == 'F')
		f = 2;
	else
		f = 3;
	int add1 , add2;
	add1 = toadd(s1, f);
	add2 = toadd(s2, f);
	int news1 = (s1 % 4) * 4 + f;
	int news2 = (s2 % 4) * 4 + f;
	return max(add1 + mine(n, day + 1, news1, s2), add2 + mine(n, day + 1, s1, news2));
	
}
int main(void)
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> food[i];
	int s1 = 0, s2 = 0;//m 1 f 2 b 3
	cout << mine(n, 0, s1, s2);

	return 0;
}

