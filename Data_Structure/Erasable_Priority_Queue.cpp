template <class T, class C = vector<T>, class O = less<T>>
struct PQSet {
    PQSet() = default;
    explicit PQSet(const O& o) : pq(o), del(o) {}
    const T& top() const { return pq.top(); }
    int size() const { return int(pq.size() - del.size()); }
    bool empty() const { return !size(); }
    void insert(const T& x) { pq.push(x); }
    void pop() { pq.pop(); flush(); }
    void erase(const T& x) { del.push(x); flush(); }
    void flush() { while (ssize(del) && pq.top() == del.top()) pq.pop(), del.pop(); }

    priority_queue<T, C, O> pq, del;
};
