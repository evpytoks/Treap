#include <iostream>
#include <chrono>
#include <random>
#include <string>
using namespace std;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 g(seed);
struct Treap {
    Treap *l = nullptr, *r = nullptr;
    long long x;
    long long y;


    Treap(long long x) : x(x) {
        y = g();
    }
};


void Split(Treap *tr, Treap *&left, Treap *&right, long long x) {
    if (tr == nullptr) {
        left = nullptr;
        right = nullptr;
        return;
    }
    if (tr->x < x) {
        Split(tr->r, tr->r, right, x);
        left = tr;
    } else {
        Split(tr->l, left, tr->l, x);
        right = tr;
    }
}


void Merge(Treap *&tr, Treap *left, Treap *right) {
    if (left == nullptr) {
        tr = right;
        return;
    }
    if (right == nullptr) {
        tr = left;
        return;
    }
    if (left->y >= right->y) {
        Merge(left->r, left->r, right);
        tr = left;
    } else {
        Merge(right->l, left, right->l);
        tr = right;
    }
}


void Insert(Treap *&tr, Treap *other) {
    if (tr == nullptr) {
        tr = other;
    } else if (other->y > tr->y) {
        Split(tr, other->l, other->r, other->x);
        tr = other;
    } else {
        if (other->x < tr->x) {
            Insert(tr->l, other);
        } else if (other->x > tr->x) {
            Insert(tr->r, other);
        }
    }
}


void Next(Treap *&tr, long long elem, long long &ans) {
    if (tr == nullptr) {
        return;
    } else if (elem < tr->x) {
        ans = tr->x;
        Next(tr->l, elem, ans);
    } else {
        Next(tr->r, elem, ans);
    }
}


void Delete(Treap *&tr, long long x) {
    if (tr->x == x) {
        Merge(tr, tr->l, tr->r);
    } else {
        if (x < tr->x) {
            Delete(tr->l, x);
        } else {
            Delete(tr->r, x);
        }
    }
}

void Exists(Treap *&tr, long long x, bool &ans) {
    if (tr == nullptr) {
        return;
    }
    if (tr->x == x) {
        ans = true;
    } else {
        if (x < tr->x) {
            Exists(tr->l, x, ans);
        } else {
            Exists(tr->r, x, ans);
        }
    }
}


void Prev(Treap *&tr, long long elem, long long &ans) {
    if (tr == nullptr) {
        return;
    } else if (elem <= tr->x) {
        Prev(tr->l, elem, ans);
    } else {
        ans = tr->x;
        Prev(tr->r, elem, ans);
    }
}



int main() {
    string command;
    long long x;
    Treap *root = nullptr;
    while (cin >> command) {
        cin >> x;
        if (command == "insert") {
            bool ans = false;
            Exists(root, x, ans);
            if (!ans) {
                Treap *tr = new Treap(x);
                Insert(root, tr);
            }
        } else if (command == "delete") {
            bool ans = false;
            Exists(root, x, ans);
            if (ans) {
                Delete(root, x);
            }
        } else if (command == "exists") {
            bool ans = false;
            Exists(root, x, ans);
            if (ans) {
                cout << "true" << endl;
            } else {
                cout << "false" << endl;
            }
        } else if (command == "next") {
            long long ans = -1000000001;
            Next(root, x, ans);
            if (ans == -1000000001) {
                cout << "none" << endl;
            } else {
                cout << ans << endl;
            }
        } else {
            long long ans = -1000000001;
            Prev(root, x, ans);
            if (ans == -1000000001) {
                cout << "none" << endl;
            } else {
                cout << ans << endl;
            }
        }
    }
    return 0;
}
