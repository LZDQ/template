template <int T> struct fast_io {
    char p[T], q[T], *p1, *p2, *q1, *q2;
    fast_io() {
        p1 = p2 = p;
        q1 = q, q2 = q + T;
    }
    inline char gc() {
        return p1 == p2 && (p2 = (p1 = p) + fread(p, 1, T, stdin)), p1 == p2 ? EOF : *p1++;
    }
    inline void pc(char c) {
        if (q1 == q2)
            q2 = (q1 = q) + fwrite(q, 1, T, stdout);
        *q1++ = c;
    }
    ~fast_io() { fwrite(q, 1, q1 - q, stdout); }
};
fast_io<1 << 20> io;

ll get_ll() {
    ll res = 0, sgn = 1;
    char ch;
    do {
        ch = io.gc();
        if (ch == '-')
            sgn = -1;
    } while (ch < '0' || ch > '9');
    do {
        res = res * 10 + (ch & 15);
		ch = io.gc();
    } while (ch >= '0' && ch <= '9');
    return res * sgn;
}

void get_str(char *s){
	char ch;
	do ch = io.gc();
	while (ch == ' ' || ch == '\n');
	do {
		*(s++) = ch;
		ch = io.gc();
	} while (ch != ' ' && ch != '\n');
	*s = 0;
}

template <typename T> void _put(T x) {
    if (x >= 10)
        _put(x / 10);
    io.pc(48 ^ (x % 10));
}

template <typename T> void _put(T x, char ch) {
    _put(x);
    io.pc(ch);
}
