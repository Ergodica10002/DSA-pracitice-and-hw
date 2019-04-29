#include <iostream>
#include <string>
#include <map>
#define ALICE 0
#define BOB 1
#define NDEBUG
using namespace std;

bool isvalid(string card1, string card2){
	if (card1 == "pass" || card2 == "pass")
		return 1;
	return ((card1[0] == card2[0]) || (card1[1] == card2[1]));
}

string acards[20];
string bcards[20];
int acheck[20] = {0};
int bcheck[20] = {0};
int aremain;
int bremain;
string freeplay = "pass";
map<unsigned long long int, int> state;

int points(char c){
	if (c >= '2' && c <= '9')
		return c - '0';
	if (c == 'T')
		return 10;
	if (c == 'J')
		return 11;
	if (c == 'Q')
		return 12;
	if (c == 'K')
		return 13;
	if (c == 'A')
		return 1;
	else
		return 0;
}

unsigned long long int tran2state(bool nowturn, string lastcard){
	unsigned long long statenum = (unsigned long long)0;
	for (int i = 0; i < 18; i++){
		statenum = (statenum | (unsigned long long)acheck[i]);
		statenum = statenum << 1;
	}
	for (int i = 0; i < 18; i++){
		statenum = (statenum | (unsigned long long)bcheck[i]);
		statenum = statenum << 1;
	}
	statenum = (statenum | (unsigned long long)nowturn);
	statenum = statenum << 2;
	switch (lastcard[0]){
		case 'C':
			statenum = (statenum | (unsigned long long)0);
			break;
		case 'D':
			statenum = (statenum | (unsigned long long)1);
			break;
		case 'H':
			statenum = (statenum | (unsigned long long)2);
			break;
		case 'S':
			statenum = (statenum | (unsigned long long)3);
			break;
	}
	statenum = statenum << 4;
	statenum = (statenum | (unsigned long long)points(lastcard[1]));

	return statenum;
}
void remain(int player, int n){
	if (player == ALICE){
		cout << "Alice remain: ";
		for (int i = 0; i < n; i++){
			if (acheck[i] == 0)
				cout << acards[i] << ' ';
		}
	}
	else if (player == BOB){
		cout << "Bob remain: ";
		for (int i = 0; i < n; i++){
			if (bcheck[i] == 0)
				cout << bcards[i] << ' ';
		}
	}
	cout << '\n';
	return;
}
int credit(int player, int n){
	int sum = 0;
	if (player == ALICE){
		for (int i = 0; i < n; i++){
			if (acheck[i] == 0){
				sum += points(acards[i][1]);	
			}
	//		remain(ALICE, n);
		}
		return -sum;
	}
	if (player == BOB){
		for (int i = 0; i < n; i++){
			if (bcheck[i] == 0){
				sum += points(bcards[i][1]);
			}
	//		remain(BOB, n);
		}
		return sum;
	}
}
int playcard(int n, bool nowturn, string lastcard){
	if (aremain == 0)
		return credit(BOB, n);
	if (bremain == 0)
		return credit(ALICE, n);
	if (nowturn == ALICE){
		int canplay = 0;
		for (int i = 0; i < n; i++){
			if (acheck[i] == 0 && isvalid(lastcard, acards[i])){
				canplay = 1;
				break;
			}
		}
		if (canplay == 0){
		//	cout << "Alice pass\n";
			return playcard(n, BOB, freeplay);
		}
		unsigned long long int statenum = tran2state(ALICE, lastcard);
		map<unsigned long long int, int>::iterator s = state.find(statenum);
		if (s != state.end()){ 
#ifndef NDEBUG					
			cout << "memorized " << statenum << " " << s->second << '\n';
			remain(ALICE, n);
			remain(BOB, n);
			cout << "lastcard " << lastcard << '\n';
#endif
			return s->second;
		}
		int toreturn = 0;
		int smax = -250;
		for (int i = 0; i < n; i++){
			
			if (acheck[i] == 0 && isvalid(lastcard, acards[i])){
		//		cout << "Alice plays " << acards[i] << '\n';
				acheck[i] = 1;
				aremain--;
				int scredit = playcard(n, BOB, acards[i]);
		//		cout << statenum << " alice scredit: " << scredit << '\n';
				aremain++;
				acheck[i] = 0;
				if (smax < scredit)
					smax = scredit;
			}
		}
		statenum = tran2state(ALICE, lastcard);
		state[statenum] = smax;
		return smax;
	}
	if (nowturn == BOB){
		int canplay = 0;
		for (int i = 0; i < n; i++){
			if (bcheck[i] == 0 && isvalid(lastcard, bcards[i])){
				canplay = 1;
				break;
			}
		}
		if (canplay == 0){
		//	cout << "Bob pass\n";
			return playcard(n, ALICE, freeplay);
		}

		unsigned long long int statenum = tran2state(BOB, lastcard);
		map<unsigned long long int, int>::iterator s = state.find(statenum);
		if (s != state.end()){
			int scredit = s->second;
#ifndef NDEBUG					
			cout << "memorized " << statenum << " " << scredit << '\n';
			remain(ALICE, n);
			remain(BOB, n);
			cout << "lastcard " << lastcard << '\n';
#endif
			
			return scredit;
		}
		int toreturn = 0;
		int smin = 250;
		for (int i = 0; i < n; i++){
			
			if (bcheck[i] == 0 && isvalid(lastcard, bcards[i])){
				bcheck[i] = 1;
				bremain--;
				int scredit = playcard(n, ALICE, bcards[i]);
				bremain++;
				bcheck[i] = 0;
				if (smin > scredit)
					smin = scredit;
			}
		}
		statenum = tran2state(BOB, lastcard);
		state[statenum] = smin;
		return smin;
	}
}

int main(void)
{
#ifdef NDEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(0);
#endif
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> acards[i];
	for (int i = 0; i < n; i++)
		cin >> bcards[i];
#ifndef NDEBUG
	cout << "Alice\n";
	for (int i = 0; i < n; i++)
		cout << acards[i] << ' ';
	cout << "\nBob\n";
	for (int i = 0; i < n; i++)
		cout << bcards[i] << ' ';
	cout << '\n';
#endif
	aremain = bremain = n;
	bool nowturn;
	int smax = -250;
	for (int i = 0; i < n; i++){
#ifndef NDEBUG
		cout << "\nnewturn:\n";
		cout << "Alice plays " << acards[i] << '\n';
#endif	
		aremain--;
		acheck[i] = 1;
		int scredit = playcard(n, BOB, acards[i]);
#ifndef NDEBUG
		cout << "scredit = " << scredit << '\n';
#endif		
		aremain++;
		acheck[i] = 0;
		if (smax < scredit)
			smax = scredit;
	}
	if (smax > 0)
		cout << "Alice\n" << smax << '\n';
	else
		cout << "Bob\n" << -smax << '\n';
#ifndef NDEBUG
	map<unsigned long long, int> :: iterator it = state.begin();
	while (it != state.end()){
		cout << it->first << " " << it->second << '\n';
		it++;
	}
#endif

	return 0;
}

