#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits.h>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <array>
#include <queue>
#include <math.h>
#include <assert.h>

#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()
#define bootstrap ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define SZ(a) ((int)(a).size())
#define NG (-1)

void solve() {
    return;
}

//int main() {
//    bootstrap
//    solve();
//}

// 最大流 Dinic O(EV^2)だけど、実際もっとはやい。
class Dinic
{
public:
    Dinic(int input_maxv) : maxv(input_maxv)
    {
        G.resize(input_maxv);
        level.resize(input_maxv);
        iter.resize(input_maxv);
    }

    void add_edge_both(int from, int to, int cap)
    {
        const int rev_from  = SZ(G[from]);
        const int rev_to    = SZ(G[to]);
        G[from].push_back(edge(to,cap,rev_to));
        G[to].push_back(edge(from,cap,rev_from));
    }

    void add_edge(int from, int to, int cap)
    {
        const int rev_from  = SZ(G[from]);
        const int rev_to    = SZ(G[to]);
        G[from].push_back(edge(to,cap,rev_to));
        G[to].push_back(edge(from,0,rev_from));
    }

    // sからtへの最大流を求める
    int max_flow(int s, int t)
    {
        int flow = 0;
        for(;;)
        {
            bfs(s);
            if(level[t]<0) break;
            fill(iter.begin(),iter.end(),0);
            int f;
            while( (f=dfs(s,t,DINIC_INF))>0)
            {
                flow += f;
            }
        }

        return flow;
    }

    //  ノードsから辿れる範囲を求める（これ以上流せないところcap=0は、リンクがなくなる）
    // （流し終わったあとsourceからたどれる範囲が、最小カット時のs側。たどれない範囲がt側。その境界がカットするところ。）
    vector <bool> get_nodes_in_group(int s)
    {
        vector <bool> ret(maxv);

        queue<int> que;
        que.push(s);
        while(!que.empty())
        {
            int v = que.front();
            que.pop();
            ret[v]=true;

            for(int i=0;i<SZ(G[v]);i++)
            {
                edge &e = G[v][i];
                if(e.cap>0 && !ret[e.to])
                {
                    que.push(e.to);
                }
            }
        }
        return ret;
    }

    void disp()
    {
        for (int v = 0; v < maxv; v++)
        {
            printf("%d:",v);
            for(int i=0;i<SZ(G[v]);i++)
            {
                if(G[v][i].init_cap>0)
                {
                    printf("->%d(%d),",G[v][i].to,G[v][i].init_cap);
                }
            }
            printf("\n");
        }
    }

private:
    // sからの最短距離をBFSで計算する
    // assign every node a level from source node S.
    // In DAG, low level node->high level node is normal flow, reverse is treated residual flow.
    void bfs(int s)
    {
        fill(level.begin(),level.end(),NG);
        queue<int> que;
        level[s]=0;
        que.push(s);
        while(!que.empty())
        {
            int v = que.front();
            que.pop();
            for(int i=0;i<SZ(G[v]);i++)
            {
                edge &e = G[v][i];
                if(e.cap>0 && level[e.to]<0)
                {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    // 増加パスをDFSで探す
    // Find any path from reachable from source to terminal, and and calculate the maximum running flow(delta).
    // Once found reduce the delta from all edges on the way.(modify residual as well)
    // All can be achieved by dfs neatly.
    // @param f, is the value of running flow
    // @param v, is the node to extend from
    // @param t, is terminal of the graph
    int dfs(int v, int t, int f)
    {
        if(v==t) return f;
        for (int &i=iter[v];i<SZ(G[v]);i++)
        {
            edge& e = G[v][i];
            if(e.cap>0 && level[v]<level[e.to])
            {
                int d = dfs(e.to, t, min(f, e.cap));
                if(d>0)
                {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    static const int DINIC_INF = INT_MAX; // 容量をllにしたいときは、ここも変える

    struct edge
    {
        edge(int input_to, int input_cap, int input_rev) : to(input_to), cap(input_cap), rev(input_rev), init_cap(input_cap) {}
        int to;     // 行先
        int cap;    // 容量
        int rev;    // 逆辺
        int init_cap; // 初期容量（デバッグ用）
    };

    int maxv;
    vector < vector <edge> > G; // グラフの隣接リスト
    vector < int > level;     // sからの距離
    vector < int > iter;      // どこまで調べ終わったか

};

int main()
{
    int n;
    cin >> n;

    const int S = n;
    const int T = S+1;
    const int V = T+1;

    {
        Dinic* dinic = new Dinic(V);
        for (int i = 0; i < n; i++)
        {
            int moyasu,umeru;
            cin >> moyasu >> umeru;
            dinic->add_edge(S,i,moyasu);
            dinic->add_edge(i,T,umeru);
        }
        int answer = dinic->max_flow(S,T);
        printf("%d\n",answer);

        delete dinic;
    }

    return 0;
}