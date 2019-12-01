/*平衡二叉树*/
#include <iostream>

using namespace std;
typedef struct BiTNode {
    int data;
    int bf;
    struct BiTNode *lchild, *rchild;

    BiTNode() : data(0), lchild(nullptr), rchild(nullptr) {}
} BiTNode, *BiTree;

void r_rotate(BiTree *T) {
    BiTree L;
    L = (*T)->lchild;
    (*T)->lchild = L->rchild;
    L->rchild = (*T);
    *T = L;
}

void l_rotate(BiTree *T) {
    BiTree R;
    R = (*T)->rchild;
    (*T)->rchild = R->lchild;
    R->lchild = (*T);
    *T = R;
}

const int LH = 1;
const int EH = 0;
const int RH = -1;

void leftBalance(BiTree *T) {
    BiTree L, Lr;
    L = (*T)->lchild;
    switch (L->bf) {
        case LH://LL type
        {
            (*T)->bf = L->bf = EH;
            r_rotate(T);
            break;
        }
        case RH://LR type
        {
            Lr = L->rchild;
            switch (Lr->bf) {
                case LH: {
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                }
                case EH: {
                    (*T)->bf = EH;
                    break;
                }
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            l_rotate(&(*T)->lchild);
            r_rotate(T);
        }
    }
}

void rightBalance(BiTree *T) {
    BiTree R, Rl;
    R = (*T)->rchild;
    switch (R->bf) {
        case LH: {
            Rl = R->lchild;
            switch (Rl->bf) {
                case LH: {
                    (*T)->bf = EH;
                    break;
                }
                case EH: {
                    (*T)->bf = R->bf = EH;
                    break;
                }
                case RH: {
                    (*T)->bf = LH;
                    R->bf = EH;
                }
            }
            Rl->bf = EH;
            r_rotate(&(*T)->rchild);// why not R?
            l_rotate(T);
        }
        case RH: {
            (*T)->bf = R->bf = EH;
            l_rotate(T);
            break;
        }
    }
}

bool AVL_insert(BiTree *T, int e, bool *taller) {
    if (!*T) {
        (*T) = (BiTree) new BiTNode;
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = nullptr;
        (*T)->bf = EH;
    } else {
        if (e == (*T)->data) {
            *taller = false;
            return false;
        }
        if (e < (*T)->data) {
            if (!AVL_insert(&(*T)->lchild, e, taller)) {
                return false;
            }
            if (*taller) {
                switch ((*T)->bf) {
                    case LH: {
                        leftBalance(T);
                        *taller = false;
                        break;
                    }
                    case EH: {
                        (*T)->bf = LH;
                        *taller = true;
                        break;
                    }
                    case RH: {
                        (*T)->bf = EH;
                        *taller = false;
                        break;
                    }
                }
            }
        } else {
            if (!AVL_insert(&(*T)->rchild, e, taller)) {
                return false;
            }
            if (*taller) {
                switch ((*T)->bf) {
                    case LH: {
                        (*T)->bf = EH;
                        *taller = false;
                        break;
                    }
                    case EH: {
                        (*T)->bf = RH;
                        *taller = true;
                        break;
                    }
                    case RH: {
                        rightBalance(T);
                        *taller = false;
                        break;
                    }
                }
            }
        }
    }
    return true;
}

void midTraverse(BiTree *T) {
    if (!*T) {
        return;
    } else {
        midTraverse(&(*T)->lchild);
        cout << (*T)->data << ' ';
        midTraverse(&(*T)->rchild);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, e;
        cin >> n;
        BiTree *T = new BiTree;
        while (n--) {
            cin >> e;
            bool b = false;
        }
        midTraverse(T);
        cout << endl;
        cin >> n;
        while (n--) {
            cin >> e;
            bool b = false;
            midTraverse(T);
            cout << endl;
        }
    }

}
