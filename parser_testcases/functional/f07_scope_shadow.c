int main() {
    int x = 23;
    {
        int x = 2;
        x = x + 1;
    }
    return x;
}
