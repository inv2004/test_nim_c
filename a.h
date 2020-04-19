typedef struct s{
    int val;
    int sz;
    unsigned char arr[1];
} *S;

typedef struct ss{
    int t; // 0 - just val // 1 - ref // 2 - arr
    union {
        int val;
        struct ss* ref;
        struct {
            int sz;
            unsigned char arr[1];
        };
    };
} *SS;

S mkS();
void printS(S s);

SS mkSS();
void printSS(SS ss);
