int main(int ac , char **argv)
{
    static char *toto[512];
    int i =0;
    int value_hash = 0;
    
    while (i < strlen(argv[1]))
    {
        value_hash = value_hash << 8;
        value_hash += argv[1][i];
        i++;
    }
    value_hash %= 512;
    toto[value_hash] = 1;
    printf("%d", value_hash);
}