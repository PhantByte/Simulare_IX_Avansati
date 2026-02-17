#include <fstream>
#include <cmath>
#include <map>
#include <vector>
#include <array>
using namespace std;
ifstream cin("tablou.in");
ofstream cout("tablou.out");
typedef long long ll;
vector<array<int,2>> positions;
int frecv[101], sol[101][101], visited[101][101], cntVisited = 0;
int takenX[101], takenY[101];
ll sum(ll x)
{
    return x * (x + 1) / 2;
}
ll sum(ll l, ll r)
{
    return sum(r) - sum(l-1);
}
ll f(ll first, ll n)
{
    return sum(first,first + n - 1) * n;
}
int main()
{
    ll n, S ;
    cin >> n >> S;
    ll minS = f(1,n);
    if(S < minS)
    {
        cout << 0 << '\n';
        return 0;
    }
    int posI = 1, posJ = 1;
    while(cntVisited < n * n)
    {
        visited[posI][posJ] = true;
        positions.push_back({posI,posJ});
        cntVisited++; posI++; posJ++;
        if(posI > n) posI -= n;
        if(posJ > n) posJ -= n;
        if(visited[posI][posJ])
        {
            posI++;
            if(posI > n) posI -= n;
        }
    }
    ll poz = (S / (n * n) - (n-1) / 2);
    while(f(poz,n) <= S) poz++;
    while(f(poz,n) > S ) poz--;

    for(int i = 1;i<=n;i++)
        frecv[i] = n;
    ll dif = S - f(poz,n), change = n;
    while(dif != 0)
    {
        if(dif >= change)
            dif -= change, frecv[n - change + 1]--;
        else
        {
            //frecv[n - dif + 1]--;
            int badX = positions[n * (n - dif)][0];
            int badY = positions[n * (n - dif)][1];
            sol[badX][badY] = poz + n;
            takenX[badX] = true;
            takenY[badY] = true;
            dif = 0;
        }
    }
    int cnt = 0, p = 0, toFill = 0;
    for(auto it : positions)
    {
        int cx = it[0], cy = it[1];
        if(cnt % n == 0)
        {
            p++;
            toFill = n - frecv[p];
        }

        if(sol[cx][cy] != 0)
        {
            cnt++;
            continue;
        }

        if(toFill > 0 && !takenX[cx] && !takenY[cy])
        {
            sol[cx][cy] = poz + n;
            toFill--;
            takenX[cx] = true;
            takenY[cy] = true;
        }
        else
            sol[cx][cy] = (poz + p - 1);
        cnt++;

    }
    int suma = 0;
    for(int i = 1;i<=n;i++,cout << '\n')
        for(int j = 1;j<=n;j++)
            cout << sol[i][j] << ' ', suma += sol[i][j];
    //cout <<'\n' << suma << '\n';
    return 0;
}