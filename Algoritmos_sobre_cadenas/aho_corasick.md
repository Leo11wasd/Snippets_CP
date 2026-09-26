# Aho-Corasick

## Complexity

- Time: 
- Memory:

## Notes

-

## Code

```cpp
struct AC
{
   int N, P;
   const int A = 26;

   vector<vector<int>> next;
   vector<int> link, out_link;
   vector<vector<int>> out;

   vector<ll> cnt;
   vector<int> order;

   AC() : N(0), P(0)
   {
       node();
   }

   int node()
   {
       next.emplace_back(A, 0);
       link.emplace_back(0);
       out_link.emplace_back(0);
       out.emplace_back();
       cnt.emplace_back(0);
       return N++;
   }

   inline int get(char c)
   {
       return c - 'a';
   }

   int add_pattern(const string T)
   {
       int u = 0;

       for (char c : T)
       {
           if (!next[u][get(c)])
               next[u][get(c)] = node();

           u = next[u][get(c)];
       }

       out[u].push_back(P);
       return P++;
   }

   void compute()
   {
       queue<int> q;
       q.push(0);

       while (!q.empty())
       {
           int u = q.front();
           q.pop();

           order.push_back(u);

           for (int c = 0; c < A; ++c)
           {
               int v = next[u][c];

               if (!v)
               {
                   next[u][c] = next[link[u]][c];
               }
               else
               {
                   link[v] = u ? next[link[u]][c] : 0;

                   out_link[v] =
                       out[link[v]].empty()
                           ? out_link[link[v]]
                           : link[v];

                   q.push(v);
               }
           }
       }
   }

   void process(const string &text)
   {
       int u = 0;

       for (char c : text)
       {
           u = next[u][get(c)];
           cnt[u]++;
       }

       // Propagate occurrences through failure links.
       for (int i = N - 1; i > 0; --i)
       {
           int v = order[i];
           cnt[link[v]] += cnt[v];
       }
   }
};
/*
// Contar, para cada patron cuantas veces aparece en el string

AC ac;

ac.add_pattern("he");
ac.add_pattern("she");

ac.compute();
ac.process("ahishers");

vector<int> answer(ac.P);

for (int v = 0; v < ac.N; v++) {
   for (int id : ac.out[v]) {
       answer[id] = ac.cnt[v];
   }
}
   answer[id] = cantidad de veces que aparece en el string el patron id
   (el id se asigna en orden en que se agregó el patron)
*/

```