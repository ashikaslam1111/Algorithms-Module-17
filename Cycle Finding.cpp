//problem link -> https://cses.fi/problemset/task/1197/
#include<bits/stdc++.h>
using namespace std;
class edge
{
public:
    int u,v,w;
};
int n,m;
int last_updated_node=-1;
vector<edge>edg;
const long long int infinity=1e18;
const int N=1e4;
int parent[N];
long long int dist[N];
void bellMan_ford(int src);
bool negate_cycle=false;
void path_printer(int src,int node);
void negative_cycle_printer();
int main()
{
    cin>>n>>m;
    for(int i=0; i<m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        edg.push_back({u,v,w});
    }
    for(int i=0; i<N; i++)dist[i]=infinity;
    int src=1;
    dist[src]=0;
    bellMan_ford(src);
    if(negate_cycle)
    {
        cout<<"YES";
        cout<<endl;
        negative_cycle_printer();
        return 0;

    }
    cout<<"NO";
    return 0;
}
void bellMan_ford(int src)
{
    for(int i=1; i<=n; i++)
    {
        for(auto j:edg)
        {
            if(dist[j.v]>dist[j.u]+j.w)// this is the relaxation part and if the condition is true at step n then the negative cycle exists
            {
                dist[j.v]=dist[j.u]+j.w;
                parent[j.v]=j.u;
                if(i==n)
                {
                    negate_cycle=true;
                    last_updated_node=j.v;
                }
            }
        }
    }
}
void path_printer(int src,int node)
{
    stack<int>a;
    a.push(node);
    while(a.top()!=src)
    {
        int pr =parent[a.top()];
        a.push(pr);
    }
    while(!a.empty())
    {
        cout<<a.top()<<" ";
        a.pop();
    }
}
void negative_cycle_printer()
{
    for(int i=1; i<n; i++)
    {
        last_updated_node  = parent[last_updated_node];
    }
    path_printer( last_updated_node,parent[last_updated_node]);
    cout<<last_updated_node;
}

