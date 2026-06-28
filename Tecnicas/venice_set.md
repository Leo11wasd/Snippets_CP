# Venice technique (version set)
Whenever we want to answer queries of the form:

- Add an element to a multiset
- Delete an element from the multiset
- Add v to all elements currently in the set
- Get the maximum/minimum from the set

Instead of using a complex data structure or another one with some workarounds, we can use a simple multiset and think of the following analogy: Instead of adding or deleting numbers, think of building and demolishing buildings. The add v to all elements operation turns into add/remove v floors from all buildings. Instead of going building by building removing the floors, we can remove building floors by flooding (thus the "Venice" name of the technique) v floors. We maintain a simple multiset and a variable water_level to emulate the same idea with the members of our set.
## Complexity
### add
- Time: $O(\log{N})$
### remove
- Time: $O(\log{N})$
### updateAll
- Time: $O(1)$

## Notes

- https://codeforces.com/blog/entry/58316

## Code

```cpp
struct vset
{
    multiset<ll> S;
    ll water_level = 0;
    void add(ll v)
    {
        S.insert(v + water_level);
    }
    void remove(ll v)
    {
        // error si v+water_level no esta en el set.
        S.erase(S.find(v + water_level));
    }
    void updateAll(ll v)
    {
        water_level += v;
    }
    ll getMin()
    {
        return *S.begin() - water_level;
    }
    ll size()
    {
        return S.size();
    }
};
```