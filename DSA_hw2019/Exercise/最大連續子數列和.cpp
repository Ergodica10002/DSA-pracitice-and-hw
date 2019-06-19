#include <stdio.h>

int N, num[134217];

int main()
{
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
        scanf("%d", &num[i]);
    
    num[0] = 0;
    int ans = num[1];
    for(int i = 1; i <= N; i++) {
        if(num[i - 1] > 0) num[i] += num[i - 1];
        else num[i] += 0;
        if(num[i] > ans) ans = num[i];
    }

    printf("%d\n", ans);

    return 0;
}
