// 斐波那契数列计算（递归实现）
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

// 最大公约数（辗转相除法）
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// 判断素数
int isPrime(int num) {
    if (num <= 1) {
        return 0;
    }

    if (num <= 3) {
        return 1;
    }

    if (num % 2 == 0 || num % 3 == 0) {
        return 0;
    }

    int i = 5;
    while (i * i <= num) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return 0;
        }
        i = i + 6;
    }

    return 1;
}

// 阶乘计算
int factorial(int n) {
    int result = 1;
    while (n > 0) {
        result = result * n;
        n = n - 1;
    }
    return result;
}

// 计算组合数 C(n,k)
int combination(int n, int k) {
    if (k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }

    // 使用公式 C(n,k) = n!/(k!*(n-k)!)
    return factorial(n) / (factorial(k) * factorial(n - k));
}

// 快速幂算法
int power(int base, int exponent) {
    int result = 1;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        exponent = exponent / 2;
    }

    return result;
}

// 复杂的嵌套控制流和表达式计算
int complexFunction(int a, int b, int c) {
    int result = 0;

    if (!(a > b && b > c)) {
        result = a * b - -(c + -1);
    } else if (!(a < c) || c < b) {
        result = a * (c - +b - -2);
    } else if (b >= a && a >= c || b <= c) {
        result = b * a - -(c + -3);
    } else if (b > c || c > a && a <= b) {
        result = b * (c - +a - -4);
    } else if (!(c > a || b != a) && a == b) {
        result = c * a - +(b + -5);
    } else {
        result = c * (b - -a - -6);
    }

    int i = 0;
    while (i < 10) {
        i = i + 1;
        {
            int i = 0;
        }

        if (i % 3 == 0) {
            result = result + i;
        } else if (i % 3 == 1) {
            result = result - i;
        } else {
            result = result * 2;

            if (result < 50) {
                continue;
            }

            result = result + 1;

            if (result > 100) {
                break;
            }
        }
    }

    return result;
}

// 测试短路逻辑
int shortCircuit(int a, int b) {
    int result = 0;

    // 测试逻辑与的短路
        if (a > 0 && b / a > 2) {
            result = result + 42;
    }

    // 测试逻辑或的短路
        if (a < 0 || b / (a - a + 1) < 0) {
            result = result + 17;
    }

    return result;
}

// 嵌套循环和条件语句
int nestedLoopsAndConditions(int n) {
    int sum = 0;
    int i = 0;

    while (i < n) {
        int j = 0;
        while (j < i) {
            if ((i + j) % 2 == 0) {
                sum = sum - i * j;
            } else {
                sum = sum + i * j;

                if (sum < 0) {
                    sum = 0;
                    continue;
                }
            }

                if (sum > 1000) {
                    break;
            }

            j = j + 1;
        }

            if (sum > 1000) {
                break;
        }

        i = i + 1;
    }

    return sum;
}

int func1(int x, int y, int z) {
    if (z == 0) {
        return +x * y;
    } else {
        return func1(x, y - z, 0);
    }
}

int func2(int x, int y) {
    if (y) {
        return func2(x % +y, 0);
    } else {
        return x;
    }
}

int func3(int x, int y) {
    if (y == 0) {
        return x + 1;
    } else {
        return func3(x + y, 0);
    }
}

int func4(int x, int y, int z) {
    if (x) {
        return y;
    } else {
        return z;
    }
}

int func5(int x) {
    return -x;
}

int func6(int x, int y) {
    if (x && y) {
        return 1;
    } else {
        return 0;
    }
}

int func7(int x) {
    if (!x) {
        return 1;
    } else {
        return 0;
    }
}

int nestedCalls(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9) {
    int i1 = 7;
    int i2 = 8;
    int i3 = 9;
    int i4 = 10;
    int a = func1(
        // this
        func2(
            // is
            func1(
                // comment
                func3(func4(func5(func3(func2(func6(func7(i1), func5(i2)), i3),
                                        // this
                                        i4)),
                            // is
                            a0,
                            // function
                            func1(func2(func3(func4(func5(a1),
                                                    // call
                                                    func6(a2, func7(a3)),
                                                    func2(a4, func7(a5))),
                                              a6),
                                        a7),
                                  func3(a8, func7(a9)), i1)),
                      func2(i2, func3(func7(i3), i4))),
                a0, a1),
            a2),
        a3,
        func3(func2(func1(func2(func3(a4, func5(a5)), func5(a6)),
                          a7, func7(a8)),
                    func5(a9)),
              i1));
    return a;
}

// 主函数
int main() {
    int result = 0;

    // EXEC 宏已移除，直接使用 C 代码实现

    // 测试斐波那契数列
    int x_fib = 13;
    int fib = fibonacci(x_fib);
    if (fib != 233) {
        return 0;
    }

    // 测试最大公约数
    int x_gcd = 36, y_gcd = 60;
    int gcd_result = gcd(x_gcd, y_gcd);
    if (gcd_result != 12) {
        return 0;
    }

    // 测试素数判断
    int x_prime = 17;
    int prime_check = isPrime(x_prime);
    if (prime_check != 1) {
        return 0;
    }

    // 测试阶乘
    int x_fact = 7;
    int fact = factorial(x_fact);
    if (fact != 5040) {
        return 0;
    }

    // 测试组合数
    int x_comb = 6, y_comb = 2;
    int comb = combination(x_comb, y_comb);
    if (comb != 15) {
        return 0;
    }

    // 测试快速幂
    int x_pow = 2, y_pow = 11;
    int pow_result = power(x_pow, y_pow);
    if (pow_result != 2048) {
        return 0;
    }

    // 测试复杂函数
    int complex_result = complexFunction(3, 4, 5);

    // 测试短路逻辑
    int short_circuit = shortCircuit(-7, 10);

    // 测试嵌套循环和条件
    int nested_loops_conds_result = nestedLoopsAndConditions(10);

    // 测试嵌套调用
    int nested_calls_result = nestedCalls(11, 22, 33, 44, 55, 66, 77, 88, 99, 101);

    // 综合所有结果
    result = 1 + (fib * 2 % 37633 + gcd_result * 2 % 37633 - prime_check * 2 % 37633 + fact * 2 % 37633 - comb * 2 % 37633 + pow_result * 2 % 37633 - nested_loops_conds_result * 2) % 254;

    return result;
}
