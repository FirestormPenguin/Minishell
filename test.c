int funzione(int *n)
{
    printf(*n);
    *n = 15;
    printf(*n);
    reutrn(*n);
}

int main ()
{
    int n = 5;
    funzione(&n);
    printf(n);
}