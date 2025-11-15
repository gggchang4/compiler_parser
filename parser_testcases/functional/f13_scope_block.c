int main() {
    int x = 123;
    {
        int y = 456;
        x = x + y;
    }
    return x;

