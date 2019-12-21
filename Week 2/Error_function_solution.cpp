#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) int((x).size())
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

template<class T>
ostream& operator<<(ostream& out, vector<T> V){
    for(auto &i:V)out << i << " ";
    return out;
}

vector<int> getErrorVector(string needle, string haystack){
    needle = needle+'$'+haystack;
    vector<int> errorVector(sz(needle)+1,0);
    for(int i = 1, j = 0; i < sz(needle); ){
        if(needle[i] == needle[j]) errorVector[++i]=++j;
        else if(j == 0)errorVector[++i] = 0;
        else j = errorVector[j];
    }
    return errorVector;
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    string needle = "aba";
    string haystack = "ababba";
    cout << needle+'$'+haystack << endl;
    cout << getErrorVector(needle,haystack) << endl;
}