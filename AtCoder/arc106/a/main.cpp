#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
typedef long long int ll;

int main() {
    ull n;
    cin >> n;

    ull d = n%10;
    if ( d==8 || d==4 || d==2 || d==6 )
    {
        ull ans_a=1;
        ull left;
        if ( d==8 )
        {
            ans_a=1;
            left=3;
        }
        else if ( d==4 )
        {
            ans_a=2;
            left=9;
        }
        else if ( d==2 )
        {
            ans_a=3;
            left=27;
        }
        else if ( d==6 )
        {
            ans_a=4;
            left=81;
        }

        ull ans_b=1;
        ull right = 5;


        ull i = ans_a;
        ull tl = left;
        ull j = ans_b;
        ull tr = right;
        while( 1 )
        {
            ull i = ans_a;
            ull tl = left;

            while( 1 )
            {
                if ( tl + tr == n )
                {
                    cout << i << " " << j << endl;
                    goto END;
                }
                else if ( tl + tr > n )
                    break;

                i += 4;
                tl *= 81;
            }

            j += 1;
            tr *= 5;

            if ( tr > n )
                break;
        }
        cout << "-1" << endl;
    }
    else
        cout << "-1" << endl;
END:
    return 0;
}
