#include<bits/stdc++.h>
using namespace std;

#define MAX 256


int distinct_substr_naive(string s){
    int n = s.length();
    int dp[n+1];
    vector<int> prev;

    prev.assign(MAX,-1);
    dp[0] = 1;

    for(int i=1;i<=n;i++){
        dp[i] = 2*dp[i-1];

        if(prev[s[i-1]]!=-1){
            dp[i] -= dp[prev[s[i-1]]];
        }

        prev[s[i-1]] = i-1;
        //cout << dp[i] << " ";
    }
    //cout << endl;

    return dp[n];

}


struct suffix{
    int index,rank[2];
};

int cmp(struct suffix a, struct suffix b){
    return (a.rank[0] == b.rank[0])?(a.rank[1] < b.rank[1] ?1: 0):(a.rank[0] < b.rank[0] ?1: 0);
}

vector<int> lcp_func(vector<int> SA,string s){
    vector<int> ISA(SA.size(),-1);
    int n = SA.size();
    vector<int> LCP(SA.size(),-1);

    for(int i=0;i<SA.size();i++){
        ISA[SA[i]] = i;
    }

    //for(int i=0;i<SA.size();i++){
    //    cout << ISA[i] << " ";
    //}
    //cout << endl;

    int l = 0;
    for(int i=0;i<n;i++){
        //cout << "Here\n";
        int k = ISA[i];
        int j = SA[k-1];

        while(i+l<n && j+l<n && s[i+l]==s[j+l]) {
            l++;
        }
        LCP[k] = l;
        //cout << LCP[k] << " ";
        if(l>0) l--;
    }
    //cout << endl;

    //for(int i=0;i<LCP.size();i++){
      //  cout << LCP[i] << " ";
    //}
    //cout << endl;

    return LCP;
}

vector<int> init_suffix(string s){
    int n = s.length();
    suffix suffixes[n];
    vector<int> suffix_arr;

    for(int i=0;i<n;i++){
        suffixes[i].index = i;
        suffixes[i].rank[0] = s[i]-'a';
        suffixes[i].rank[1] = ((i+1)<n)?(s[i+1]-'a'):-1;
    }

    sort(suffixes,suffixes+n,cmp);

    //for(int i=0;i<n;i++) cout << suffixes[i].index << " ";
    //cout << endl;
    int index[n];

    for(int k=4;k<2*n;k*=2){
        int r = 0;
        int pr = suffixes[0].rank[0];
        suffixes[0].rank[0] = r;
        index[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++){
            if (suffixes[i].rank[0] == pr && suffixes[i].rank[1] == suffixes[i-1].rank[1]){
                pr = suffixes[i].rank[0];
                suffixes[i].rank[0] = r;
            }

            else{
                pr = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++r;
            }
            index[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++){
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)?suffixes[index[nextindex]].rank[0]:-1;
        }
         sort(suffixes, suffixes+n, cmp);
    }

    for(int i=0;i<n;i++){
        //cout << suffixes[i].index << " ";
        suffix_arr.push_back(suffixes[i].index);
    }
    //cout << endl;
    //lcp_func(suffix_arr,s);

    return suffix_arr;
}

int distinct_substr_lcp(string s)
{
    int n = s.length();

    vector<int> suffix_arr = init_suffix(s);
    vector<int> lcp = lcp_func(suffix_arr,s);

    int result = n - suffix_arr[0];

    for (int i=1;i<lcp.size();i++)
         result += (n - suffix_arr[i]) - lcp[i - 1];

    return result+1;
}




int main()
{
    string s,p;

    ifstream input;
    input.open("input.txt");

    input >> s >> p;
    cout << s << " " << p << endl;

    cout << distinct_substr_naive(p) << endl;
    cout << distinct_substr_lcp(p) << endl;

    //init_suffix(p);

    input.close();
}
