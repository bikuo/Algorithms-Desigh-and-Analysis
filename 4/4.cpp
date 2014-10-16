#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <cstring>
#include <iostream>
using std::vector;
using std::set;
using std::string;
using std::cout;
using std::endl;
int const MAXN = 2003;
 
int n, m;
int longest;
int cache[MAXN][MAXN];
char a[MAXN];
char b[MAXN];
set<string> answer;
 
static inline void get_max(int& a, int b) {
    if (a < b) a = b;
}
static int max( int a, int b){
    return (a>b)? a:b;
}
static int solve(int i, int j) {
    if (i >= n || j >= m)
        return 0;
    if (cache[i][j] > -1)
        return cache[i][j];
    if (a[i] == b[j])
        cache[i][j] = solve(i + 1, j + 1) + 1;
    get_max(cache[i][j], max(solve(i + 1, j), solve(i, j + 1)));
    return cache[i][j];
}
 
static void path(int i, int j, int length, string result) {
    if (length == 0) {
        answer.insert(result);
        return;
    }
    for (int x = i + 1; x < n; ++x)
        for (int y = j + 1; y < m; ++y)
            if (a[x] == b[y] && cache[x][y] == length)
                path(x, y, length - 1, result + a[x]);
}
 
int main(int argc, char **args) {
    int TC; scanf("%d", &TC);
    while (TC-- > 0) {
        scanf("%s%s", a, b);
        n = strlen(a), m = strlen(b);
        memset(cache, -1, sizeof cache);
        longest = solve(0, 0);
        answer.clear();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (a[i] == b[j] && cache[i][j] == longest)
                    path(i, j, longest - 1, string("") + a[i]);
        
        set<string>::iterator it=answer.begin();
        string result = *it;
            printf("%s\n", result.c_str());
    }
    return 0;
}