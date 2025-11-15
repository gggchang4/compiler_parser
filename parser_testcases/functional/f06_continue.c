int main() {
    int x = 0;
    int y = 1000;
    while (x < 5) {
        x = x + 1;
        if (x == 3) {
            continue;
        }
        y = y + 1;
    }
    return y;
}
