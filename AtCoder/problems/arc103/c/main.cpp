#include <bits/stdc++.h>
using namespace std;

int A[100005];
int cntEven[100005];
int cntOdd[100005];
int main() {
    int n;
    cin >> n;
    for (int i=0; i<n; i++)
        cin >> A[i];
    A[n]=0;

    int evenMaxId = n;
    int evenPrevId = n;
    for (int i=0; i<n; i+=2)
    {
        cntEven[A[i]]++;
        if ( cntEven[evenMaxId] < cntEven[A[i]] )
        {
            evenPrevId = evenMaxId;
            evenMaxId = A[i];
        }
        else if ( cntEven[evenPrevId] < cntEven[A[i]] && evenMaxId != A[i] ) {
                evenPrevId = A[i];
        }
    }
    int oddMaxId = n;
    int oddPrevId = n;
    for (int i=1; i<n; i+=2)
    {
        cntOdd[A[i]]++;
        if ( cntOdd[oddMaxId] < cntOdd[A[i]] )
        {
            oddPrevId = oddMaxId;
            oddMaxId = A[i];
        }
        else if ( cntOdd[oddPrevId] < cntOdd[A[i]] && oddMaxId != A[i] ) {
                oddPrevId = A[i];
        }
    }
    if ( oddMaxId != evenMaxId )
        cout << n/2-cntOdd[oddMaxId] + n/2-cntEven[evenMaxId] << endl;
    else if ( cntOdd[oddPrevId] > cntEven[evenPrevId] )
        cout << n/2-cntOdd[oddPrevId] + n/2-cntEven[evenMaxId] << endl;
    else
        cout << n/2-cntOdd[oddMaxId] + n/2-cntEven[evenPrevId] << endl;

    return 0;
}
