struct TrieNode
{
    TrieNode *children[2];
    bool hay[2] = {0, 0};
    bool flag = false;
    int cont = 0;

    void setEnd()
    {
        flag = true;
    }
    void sumCont()
    {
        cont = cont + 1;
    }
    void resCont()
    {
        cont = cont - 1;
    }
    bool isEnd()
    {
        return flag;
    }
};
TrieNode *node, *next;
void insert(TrieNode *root, int &numero)
{
    node = root;
    int pot = (1 << 30);
    for (int i = 0; i < 31; ++i)
    {
        if (!node->hay[(numero & pot) > 0])
        {
            // no hay nadie con este bit, lo creamos
            node->children[(numero & pot) > 0] = new TrieNode();
            node->hay[(numero & pot) > 0] = 1;
        }
        // nos movemos
        (node->children[(numero & pot) > 0])->cont++;
        node = node->children[(numero & pot) > 0];
        pot >>= 1;
    }
    node->setEnd();
}

void elimina(TrieNode *root, int numero)
{
    node = root;
    int pot = (1 << 30);

    for (int i = 0; i < 31; i++)
    {
        int bit = (numero & pot) > 0;

        // next = node.children[bit];
        if (!node->hay[bit])
        {
            return;
        }
        node = (node->children[bit]);
        node->cont--;
        pot >>= 1;
    }
}

void calcula(TrieNode *root, int &numero, int &res)
{
    // busca el numero que minimiza el xor con numero
    node = root;
    int pot = (1 << 30);
    for (int i = 0; i < 31; ++i)
    {
        int bit = (numero & pot) > 0;

        // si puedo seguir el mismo bit, no sumo nada al XOR
        if (node->hay[bit] && (node->children[bit])->cont > 0)
        {
            node = node->children[bit];
        }
        else
        {
            // tengo que ir al opuesto → este bit del XOR vale 1
            res += pot;
            node = node->children[!bit];
        }

        pot >>= 1;
    }
}

// pre=0
// insert(&root, pre);
// for i in range n
// cin >> val;
// pre ^= val;
// cant = 0;
// calcula(&root, pre, k, cant);
// insert(&root, pre);
// res += cant;
void calcula_menoresk(TrieNode *root, int numero, int k, ll &res)
{
    // cuantos subarreglos tienen xor menor que k
    node = root;
    int pot = (1 << 30);
    int sig;
    for (int i = 0; i < 31; ++i)
    {
        int bit = (numero & pot) > 0;
        int bitk = (k & pot) > 0;
        // cout << "el bit " << pot << " es " << bit << endl;
        if (bitk && bit)
        {
            if (node->hay[1])
            {
                res += (node->children[1])->cont;
            }
            sig = 0;
        }
        if (!bitk && bit)
        {
            sig = 1;
        }
        if (bitk && !bit)
        {
            if (node->hay[0])
            {
                res += (node->children[0])->cont;
            }
            sig = 1;
        }
        if (!bitk && !bit)
        {
            sig = 0;
        }
        // node->children[sig]->cont
        if (node->hay[sig] && (node->children[sig])->cont > 0)
        {
            node = node->children[sig];
        }
        else
        {
            return;
        }

        pot >>= 1;
    }
    return;
}
