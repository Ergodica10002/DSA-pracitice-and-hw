#include <iostream>
#include <string>
#include <map>
#define MAXLEN 100000
#define mod 11
#define NDEBUG
using namespace std;
 
unsigned long long hashtable[MAXLEN] = {0};
unsigned long long modtable[MAXLEN] = {0};
 
void fillmod(int tomod, int len){
    modtable[0] = 1;
    for (int i = 1; i < len; i++){
        modtable[i] = modtable[i - 1] * tomod;
    }
    return;
}
void filltable(string s){
    unsigned long long hashnum = 0;
    for (int i = 0; s[i] != '\0'; i++){
        hashnum = hashnum * mod + (s[i] - 'a');
        hashtable[i + 1] = hashnum;
    }
    return;
}
 
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    fillmod(mod, MAXLEN);
    string s;
    int m;
    while (cin >> m){
        cin >> s;
        if (m == 0)
            break;
        filltable(s);
        int slen = s.size();
#ifndef NDEBUG
        for (int i = 0; i <= slen; i++)
            cout << hashtable[i] << '\n';
        cout << '\n';
#endif
        bool answer_find = 0;
 
        //first task
        int result[2] = {0};
        int lowbound = 1, upbound = slen + 1;
        int mid = (lowbound + upbound) / 2;
        while(upbound - lowbound >= 1){
            map<unsigned long long, int> count;
            map<unsigned long long, int>::iterator it;
            for (int j = mid; j <= slen; j++){
                unsigned long long hr = hashtable[j] - hashtable[j - mid] * modtable[mid];
                if ((it = count.find(hr)) != count.end()){
                    it->second++;
                    if (it->second >= m){
                        answer_find = 1;
                        result[0] = mid;
                        result[1] = j - mid;
                    }
                }
                else{
                    count[hr] = 1;
                    if (m == 1){
                        answer_find = 1;
                        result[0] = mid;
                        result[1] = j - mid;
                    }
                }
            }
            if (answer_find == 1){
                lowbound = mid + 1;
                answer_find = 0;
            }
            else{
                upbound = mid;
            }
            mid = (lowbound + upbound) / 2;
        }
        if (result[0] == 0)
            cout << "none\n";
        else
            cout << result[0] << ' ' << result[1] << '\n';
 
        //second task
        answer_find = 0;
        result[0] = 0;
        int possible[MAXLEN] = {0};
        int pnum = 0;
        if (slen <= 2)
            cout << "Just a legend\n";
        else{
            for (int i = 1; i < slen; i++){
                if (hashtable[i] == hashtable[slen] - hashtable[slen - i] * modtable[i]){
                    possible[pnum] = i;
                    pnum++;
                }
            }
            if (pnum == 0)
                cout << "Just a legend\n";
            else{
                lowbound = 0;
                upbound = pnum;
                mid = (lowbound + upbound) / 2;
                while (upbound - lowbound >= 1){
                    for (int j = 1; j + possible[mid] < slen; j++){
                        unsigned long long hr = hashtable[j + possible[mid]] - hashtable[j] * modtable[possible[mid]];
                        if (hr == hashtable[possible[mid]]){
                            result[0] = possible[mid];
                            answer_find = 1;
                            break;
                        }
                    }
                    if (answer_find == 1){
                        lowbound = mid + 1;
                    }
                    else{
                        upbound = mid;
                    }
                    answer_find = 0;
                    mid = (lowbound + upbound) / 2;
                }
                if (result[0] == 0)
                    cout << "Just a legend\n";
                else{
                    for (int i = 0; i < result[0]; i++)
                        cout << s[i];
                    cout << '\n';
                }
            }
        }
    }
 
 
    return 0;
}
