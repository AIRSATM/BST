#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class SearchTree {
private:
    Node* root;
    
    Node* addNode(Node* current, int v) {
        if (current == nullptr) {
            return new Node(v);
        }
        
        if (v < current->value) {
            current->left = addNode(current->left, v);
        } else if (v > current->value) {
            current->right = addNode(current->right, v);
        }
        
        return current;
    }
    
    bool findNode(Node* current, int v) {
        if (current == nullptr) {
            return false;
        }
        
        if (v == current->value) {
            return true;
        } else if (v < current->value) {
            return findNode(current->left, v);
        } else {
            return findNode(current->right, v);
        }
    }
    
    Node* getMin(Node* current) {
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    
    Node* getMax(Node* current) {
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }
    
    Node* deleteNode(Node* current, int v) {
        if (current == nullptr) {
            return nullptr;
        }
        
        if (v < current->value) {
            current->left = deleteNode(current->left, v);
        } else if (v > current->value) {
            current->right = deleteNode(current->right, v);
        } else {
            if (current->left == nullptr && current->right == nullptr) {
                delete current;
                return nullptr;
            } else if (current->left == nullptr) {
                Node* temp = current->right;
                delete current;
                return temp;
            } else if (current->right == nullptr) {
                Node* temp = current->left;
                delete current;
                return temp;
            } else {
                Node* successor = getMin(current->right);
                current->value = successor->value;
                current->right = deleteNode(current->right, successor->value);
            }
        }
        return current;
    }
    
    void deleteTree(Node* current) {
        if (current != nullptr) {
            deleteTree(current->left);
            deleteTree(current->right);
            delete current;
        }
    }
    
    Node* copyTree(Node* current) {
        if (current == nullptr) {
            return nullptr;
        }
        
        Node* newNode = new Node(current->value);
        newNode->left = copyTree(current->left);
        newNode->right = copyTree(current->right);
        
        return newNode;
    }
    
    // ЛКП - левый, корень, правый (симметричный)
    void inOrderTraversal(Node* current) {
        if (current != nullptr) {
            inOrderTraversal(current->left);
            cout << current->value << " ";
            inOrderTraversal(current->right);
        }
    }
    
    // КЛП - корень, левый, правый (прямой)
    void preOrderTraversal(Node* current) {
        if (current != nullptr) {
            cout << current->value << " ";
            preOrderTraversal(current->left);
            preOrderTraversal(current->right);
        }
    }
    
    // ЛПК - левый, правый, корень (обратный)
    void postOrderTraversal(Node* current) {
        if (current != nullptr) {
            postOrderTraversal(current->left);
            postOrderTraversal(current->right);
            cout << current->value << " ";
        }
    }
    
    // КПЛ - корень, правый, левый
    void reversePreOrderTraversal(Node* current) {
        if (current != nullptr) {
            cout << current->value << " ";
            reversePreOrderTraversal(current->right);
            reversePreOrderTraversal(current->left);
        }
    }
    
    void showTree(Node* current, int space) {
        if (current == nullptr) return;
        
        space += 3;
        showTree(current->right, space);
        
        for (int i = 3; i < space; i++) {
            cout << " ";
        }
        cout << current->value << endl;
        
        showTree(current->left, space);
    }
    
public:
    // 1. Конструктор по умолчанию
    SearchTree() : root(nullptr) {}
    
    // 2. Конструктор копирования
    SearchTree(const SearchTree& other) : root(nullptr) {
        root = copyTree(other.root);
    }
    
    // 3. Оператор присваивания
    SearchTree& operator=(const SearchTree& other) {
        if (this != &other) {
            deleteTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }
    
    // 4. Деструктор
    ~SearchTree() {
        deleteTree(root);
    }
    
    void insert(int v) {
        root = addNode(root, v);
    }
    
    bool contains(int v) {
        return findNode(root, v);
    }
    
    void remove(int v) {
        root = deleteNode(root, v);
    }
    
    int getMinValue() {
        Node* minNode = getMin(root);
        return minNode ? minNode->value : -1;
    }
    
    int getMaxValue() {
        Node* maxNode = getMax(root);
        return maxNode ? maxNode->value : -1;
    }
    
    // ЛКП (симметричный)
    void inOrder() {
        cout << "ЛКП: ";
        inOrderTraversal(root);
        cout << endl;
    }
    
    // КЛП (прямой)
    void preOrder() {
        cout << "КЛП: ";
        preOrderTraversal(root);
        cout << endl;
    }
    
    // ЛПК (обратный)
    void postOrder() {
        cout << "ЛПК: ";
        postOrderTraversal(root);
        cout << endl;
    }
    
    // КПЛ
    void reversePreOrder() {
        cout << "КПЛ: ";
        reversePreOrderTraversal(root);
        cout << endl;
    }
    
    // Обход в ширину (по уровням)
    void levelOrder() {
        if (root == nullptr) return;
        
        cout << "По уровням: ";
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            
            cout << node->value << " ";
            
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        cout << endl;
    }
    
    void display() {
        if (root == nullptr) {
            cout << "пустое" << endl;
            return;
        }
        showTree(root, 0);
    }
    
    bool isEmpty() {
        return root == nullptr;
    }
};

int main() {
    SearchTree tree;
    int choice, value;
    
    do {
        cout << "\n1.добавить 2.найти 3.удалить 4.мин 5.макс 6.показать";
        cout << "\n7.ЛКП 8.КЛП 9.ЛПК 10.КПЛ 11.по_уровням 12.копия 0.выход\n";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "число: ";
                cin >> value;
                tree.insert(value);
                tree.display();
                break;
                
            case 2:
                cout << "найти: ";
                cin >> value;
                cout << (tree.contains(value) ? "есть" : "нет") << endl;
                break;
                
            case 3:
                cout << "удалить: ";
                cin >> value;
                tree.remove(value);
                tree.display();
                break;
                
            case 4:
                cout << "мин: " << tree.getMinValue() << endl;
                break;
                
            case 5:
                cout << "макс: " << tree.getMaxValue() << endl;
                break;
                
            case 6:
                tree.display();
                break;
                
            case 7:
                tree.inOrder();
                break;
                
            case 8:
                tree.preOrder();
                break;
                
            case 9:
                tree.postOrder();
                break;
                
            case 10:
                tree.reversePreOrder();
                break;
                
            case 11:
                tree.levelOrder();
                break;
                
            case 12: {
                SearchTree copy = tree;
                cout << "создана копия:" << endl;
                copy.display();
                break;
            }
                
            case 0:
                break;
                
            default:
                cout << "неверно" << endl;
        }
        
    } while(choice != 0);
    
    return 0;
}
