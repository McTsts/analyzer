// PARAM: --enable ana.int.interval_set --set ana.context.gas_value 0

int f(int x, int y)
{
    if (x == 0)
    {
        return y;
    }
    return f(x - 1, y - 1);
}

int main()
{
    // is analyzed context-insensitive
    __goblint_check(f(1000, 1000) == 0); // UNKNOWN
}