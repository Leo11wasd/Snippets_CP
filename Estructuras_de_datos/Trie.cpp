struct TrieNode
{
    map<char, TrieNode *> children;
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
void insert(TrieNode *root, const string &word)
{
    TrieNode *node = root;
    for (int i = 0; i < word.length(); ++i)
    {
        if (!node->children.count(word[i]))
        {
            node->children[word[i]] = new TrieNode();
        }
        node->children[word[i]]->sumCont();
        node = node->children[word[i]];
    }
    node->setEnd();
}

ll search(TrieNode *root, string &word)
{
    TrieNode *node = root;
    for (int i = 0; i < word.length(); ++i)
    {
        if (!node->children.count(word[i]))
        {
            return 0;
        }
        node = node->children[word[i]];
    }
    if (node->isEnd())
    {
        return node->cont;
    }
    else
    {
        return 0;
    }
}

bool startsWith(TrieNode *root, string &prefix)
{
    TrieNode *node = root;
    for (int i = 0; i < prefix.length(); ++i)
    {
        if (!node->children.count(prefix[i]))
        {
            return false;
        }
        node = node->children[prefix[i]];
    }
    return true;
}
