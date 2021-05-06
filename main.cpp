using size_t = unsigned long long;

static inline size_t my_strlen(const char* str) {
    size_t i = 0;
    for (; str[i]; ++i)
        ;
    return i;
}

static void print(const char* str) {
    int syscall = 1;
    int fd = 1;
    asm volatile(R"(
        syscall
    )"
                 :
                 : "a"(syscall), "D"(fd), "S"(str), "d"(my_strlen(str))
                 :);
}

int main() {
    for (int i = 1; i <= 15; ++i) {
        bool print_num = true;
        if (i % 3 == 0) {
            // fizz
            print("fizz");
            print_num = false;
        }
        if (i % 5 == 0) {
            // buzz
            print("buzz");
            print_num = false;
        }
        if (print_num) {
            // i
            char buf[3];
            if (i > 9) {
                buf[0] = '0' + (i / 10);
                buf[1] = '0' + (i % 10);
                buf[2] = '\0';
            } else {
                buf[0] = '0' + i;
                buf[1] = '\0';
            }
            print(buf);
        }
        print("\n");
        // \n
    }
    return 0;
}
