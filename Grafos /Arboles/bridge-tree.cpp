vector<vector<pair<int, int>>> adj; // adjacency list of graph
int n, m;
vector<bool> visited, es_bridge;
vector<int> tin, low, componente;
int timer;

void dfs(int v, int p = -1)
{
   visited[v] = true;
   tin[v] = low[v] = timer++;
   bool parent_skipped = false;
   for (auto &[to, id_edge] : adj[v])
   {
       if (to == p && !parent_skipped)
       {
           parent_skipped = true;
           continue;
       }
       if (visited[to])
       {
           low[v] = min(low[v], tin[to]);
       }
       else
       {
           dfs(to, v);
           low[v] = min(low[v], low[to]);
           if (low[to] > tin[v])
               es_bridge[id_edge] = 1;
       }
   }
}

void find_bridges()
{
   timer = 0;
   es_bridge.assign(m,false);
   visited.assign(n, false);
   tin.assign(n, -1);
   low.assign(n, -1);
   for (int i = 0; i < n; ++i)
   {
       if (!visited[i])
           dfs(i);
   }
}

vector<vector<int>> build_bridge_tree()
{
   queue<int> q;
   set<pair<int, int>> s;
   find_bridges();
   componente.assign(n, 0);
   visited.assign(n, false);
   int comp = 0;
   int actual;
   for (int i = 0; i < n; i++)
   {
       if (!visited[i])
       {
           visited[i] = 1;
           q.push(i);
           componente[i] = comp;
           while (!q.empty())
           {
               actual = q.front();
               q.pop();
               for (auto &[vecino, id_edge] : adj[actual])
               {
                   if (!visited[vecino] && !es_bridge[id_edge])
                   {                       
                       visited[vecino] = 1;
                       componente[vecino] = comp;
                       q.push(vecino);
                   }
                   if (es_bridge[id_edge])
                   {
                       s.insert({min(actual, vecino), max(actual, vecino)});
                   }
               }
           }
           comp++;
       }
   }
   vector<vector<int>> tree(comp, vector<int>());
   for (auto &[a, b] : s)
   {
       tree[componente[a]].push_back(componente[b]);
       tree[componente[b]].push_back(componente[a]);
   }

   return tree;
}
