#include <fstream>
using namespace std;
ifstream cin("bip.in");
ofstream cout("bip.out");
int bip(int nrA,int A,int nrB,int B)
{
    int sol = 0;
    while(nrA--)
        sol = sol*10+A;
    while(nrB--)
        sol = sol*10+B;
    return sol;
}
int main()
{
    int M,S,N,T;
    bool valid = false;
    int n, sol = 0;
    cin >> n;
    for(int i = 2;i<=9;i++) /// cate cifre sunt in total
    {
        for(int j = 1;j<=9;j++) /// prima cifra
            for(int k = 0;k<=9;k++) /// a doua cifra
            {
                if(j == k) continue; /// cifrele trebuie sa fie distincte.

                for(int l = 1;l<i;l++) /// cate din cifre sa fie prima
                {
                    int cM = l, cN = i - l; /// daca folosim prima cifra de l ori , a doua trebuie in restul numarului.
                    if(bip(cM,j,cN,k) % n == 0)
                    {
                        if(valid == false)
                            valid = true, sol = bip(cM,j,cN,k), M = cM, N = cN, S = j, T = k;
                        else if(bip(cM,j,cN,k) < sol)
                                sol = bip(cM,j,cN,k), M = cM, N = cN, S = j, T = k;
                    }
                }
            }
    }
    if(valid)
        cout << M << ' ' << S <<' ' << N <<' ' << T << '\n';
    else cout << -1;
    return 0;
}
