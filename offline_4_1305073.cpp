#include<bits/stdc++.h>
using namespace std;

vector<int> result;

void naive_string_matcher(string s,string p)
{
    int n = s.length();
    int m = p.length();

    for(int i=0;i<=n-m;i++){
        int j;
        for(j=0;j<m;j++){
            if(s[i + j] != p[j]) break;
        }
        if(j==m) result.push_back(i);
    }
}

void hashing_string_matcher(string T,string P,int d, int q)
{
    int n = T.length();
    int m = P.length();
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    //for (i=0;i<m-1;i++) h=(h*d)%q;

    h = ((int)pow(d,m-1))%q;

    for (i=0;i<m;i++){
        p = (d*p + P[i])%q;
        t = (d*t + T[i])%q;
    }

    for (i=0;i<=n-m;i++){
        if (p==t){
            for (j=0;j<m;j++){
                if(T[i+j] != P[j]) break;
            }
            if (j==m) result.push_back(i);
        }

        if (i<n-m){
            t = (d*(t - T[i]*h) + T[i+m])%q;
            if(t<0) t+=q;
        }
    }
}

void Prefix_func(string P,int *soln)
{
    int m = P.length();
    int i = 1;
    int j = 0;
    soln[0] = 0;

    while (i < m){
        if(P[i]==P[j]){
            j++;
            soln[i] = j;
            i++;
        }
        else{
            if (j != 0){
                j = soln[j-1];
            }
            else{
                soln[i] = j;
                i++;
            }
        }
    }
}

void kmp(string T,string P)
{
    int m = P.length();
    int n = T.length();

    int pi[m];
    int j = 0;

    Prefix_func(P,pi);

    int i = 0;

    while(i<n){
        if (P[j]==T[i]){
                j++;
                i++;
        }

        if (j == m){
            result.push_back(i-j);
            j = pi[j-1];
        }

        else if (i<n && P[j]!=T[i]){
            if(j!=0) j = pi[j-1];
            else i = i+1;
        }

    }
}




int main()
{
    string s,p;

    ifstream input;
    input.open("input.txt");

    input >> s >> p;
    cout << s << " " << p << endl;

    input.close();

    naive_string_matcher(s,p);
    cout << "Naive result: " << endl;
    for(int i=0;i<result.size();i++) cout << result[i] << " ";
    result.clear();
    cout << endl;

    hashing_string_matcher(s,p,256,331);
    cout << "Hashing result: " << endl;
    for(int i=0;i<result.size();i++) cout << result[i] << " ";
    result.clear();
    cout << endl;

    kmp(s,p);
    cout << "KMP result: " << endl;
    for(int i=0;i<result.size();i++) cout << result[i] << " ";
    result.clear();
}
