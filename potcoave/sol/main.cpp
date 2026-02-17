#include <fstream>
#include <climits>

using namespace std;
ifstream in("potcoave.in");
ofstream out("potcoave.out");
typedef long long ll;
typedef ll NrMare[205];
const int N = 1e4 + 5;

ll m, n, a[N], b[N];

void aduna(NrMare x, NrMare y) {
    ll t = 0;
    x[0] = max(x[0], y[0]);
    for(int i=1; i<=x[0]; i++, t /= 10) {
        t += x[i] + y[i];
        x[i] = t % 10;
    }

    while(t) {
        x[++x[0]] = t % 10;
        t /= 10;
    }
}
void prod(NrMare x, ll p) {
    ll t = 0;
    for(int i=1; i<=x[0]; i++, t /= 10) {
        t += x[i] * p;
        x[i] = t % 10;
    }

    while(t) {
        x[++x[0]] = t % 10;
        t /= 10;
    }
}
void atrib(NrMare x, ll y) {
    for(int i=1; i<=x[0]; i++)
        x[i] = 0;
    x[0] = 0;

    while(y) {
        x[++x[0]] = y % 10;
        y /= 10;
    }
}
void rst(NrMare x) {
    for(int i=0; i<=200; i++)
        x[i] = 0;
}
bool cmp(NrMare x, NrMare y) {
    if(x[0] != y[0])
        return x[0] > y[0];

    for(int i=x[0]; i>=1; i--)
        if(x[i] != y[i])
            return x[i] > y[i];

    return 1;
}

int main()
{
    in >> m;
    in >> n;
    for(int i=1; i<=n; i++)
        in >> a[i] >> b[i];

    NrMare target;
    rst(target);
    atrib(target, m);
    ll st = 1, dr = 4e18, lst = 0;
    while(st <= dr) {
        ll mij = (st + dr) / 2;

        NrMare facute, x;
        rst(x);
        rst(facute);
        atrib(facute, 0);
        for(int i=1; i<=n; i++) {
            ll p = mij - mij / b[i];
            atrib(x, a[i]);
            prod(x, p);
            aduna(facute, x);
        }

        if(cmp(facute, target)) {
            lst = mij;
            dr = mij - 1;
        }
        else st = mij + 1;
    }

    out << lst;
    return 0;
}