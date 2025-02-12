struct TrieNode
{
    TrieNode *children[2];
    bool hay[2] = {0, 0};
    bool flag = false;
    ll cont = 0;
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
void insert(TrieNode *root, int &numero)
{
    TrieNode *node = root;
    int pot = (1 << 30);
    for (int i = 0; i < 31; ++i)
    {
        if (!node->hay[(numero & pot) > 0])
        {
            node->children[(numero & pot) > 0] = new TrieNode();
            node->hay[(numero & pot) > 0] = 1;
        }
        node->children[(numero & pot) > 0]->cont++;
        node = node->children[(numero & pot) > 0];
        pot >>= 1;
    }
    node->setEnd();
}

void elimina(TrieNode *root, int &numero)
{
    TrieNode *node = root;
    int pot = (1 << 30);
    for (int i = 0; i < 31; i++)
    {

        node->cont--;
        // cout << "en la potencia " << pot << " ahora hay " << node->cont << endl;
        node = node->children[(numero & pot) > 0];
        pot >>= 1;
    }
    node->cont--;
}

void calcula(TrieNode *root, int &numero, int &res)
{
    //devuelve (y xor numero) donde y es el valor en el trie que minimiza el xor con numero
    TrieNode *node = root;
    int pot = (1 << 30);
    for (int i = 0; i < 31; ++i)
    {
        // cout << "veamos si hay " << !(numero & pot) << " en la potencia " << pot << endl;

        if (node->hay[!((numero & pot) > 0)] > 0 && node->children[!((numero & pot) > 0)]->cont > 0)
        {
            // cout << "si hubo y hay " << node->children[!(numero & pot)]->cont << endl;
            // esta el q ocupo
            res += pot;
        }
        if (node->hay[!((numero & pot) > 0)] == 0 || node->children[!((numero & pot) > 0)]->cont == 0)
        {
            node = node->children[(numero & pot) > 0];
        }
        else
        {
            node = node->children[!((numero & pot) > 0)];
        }
        pot >>= 1;
    }
}
