#include <iostream>
#include <string>
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
}
int credit(int player, int n){
    int sum = 0;
    if (player == ALICE){
        for (int i = 0; i < n; i++){
            if (acheck[i] == 0){
                sum += points(acards[i][1]);
            }
        }
        return -sum;
    }
    if (player == BOB){
        for (int i = 0; i < n; i++){
            if (bcheck[i] == 0){
                sum += points(bcards[i][1]);
            }
        }
        return sum;
    }
}
int playcard(int n, bool nowturn, string lastcard, int a, int b){
    if (aremain == 0)
        return credit(BOB, n);
    if (bremain == 0)
        return credit(ALICE, n);
    if (nowturn == ALICE){
        int canplay = 0;
        for (int i = 0; i < n; i++){
            if (acheck[i] == 0 && isvalid(lastcard, acards[i])){
                canplay = 1;
            }
        }
        if (canplay == 0){
            //cout << "Alice pass\n";
            return playcard(n, BOB, freeplay, a, b);
        }
        for (int i = 0; i < n; i++){
            if (acheck[i] == 0 && isvalid(lastcard, acards[i])){
            //    cout << "Alice plays " << acards[i] << '\n';
                acheck[i] = 1;
                aremain--;
                int scredit = playcard(n, BOB, acards[i], a, b);
                aremain++;
                acheck[i] = 0;
                if (scredit > a && scredit < b)
                    a = scredit;
                if (scredit >= b){
                    return b;
                }
            }
        }
        return a;
    }
    if (nowturn == BOB){
        int canplay = 0;
        for (int i = 0; i < n; i++){
            if (bcheck[i] == 0 && isvalid(lastcard, bcards[i])){
                canplay = 1;
            }
        }
        if (canplay == 0){
            //cout << "Bob pass\n";
            return playcard(n, ALICE, freeplay, a, b);
        }
        for (int i = 0; i < n; i++){
            if (bcheck[i] == 0 && isvalid(lastcard, bcards[i])){
            //    cout << "Bob plays " << bcards[i] << '\n';
                bcheck[i] = 1;
                bremain--;
                int scredit = playcard(n, ALICE, bcards[i], a, b);
                bremain++;
                bcheck[i] = 0;
                if (scredit > a && scredit < b)
                    b = scredit;
                if (scredit <= a){
                    return a;
                }
            }
        }
        return b;
    }
}
 
int main(void)
{
#ifndef NDEBUG
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
    int a = -300;
    for (int i = 0; i < n; i++){
#ifndef NDEBUG
        cout << "\nnewturn:\n";
        cout << "Alice plays " << acards[i] << '\n';
#endif    
        aremain--;
        acheck[i] = 1;
        nowturn = BOB;
        int scredit = playcard(n, BOB, acards[i], a, 300);
#ifndef NDEBUG
        cout << "scredit = " << scredit << '\n';
#endif        
        if (scredit > a)
            a = scredit;
        aremain++;
        acheck[i] = 0;
    }
    if (a > 0)
        cout << "Alice\n" << a << '\n';
    else
        cout << "Bob\n" << -a << '\n';
 
 
 
    return 0;
}
