#include <iostream>
#include <queue>
#include <algorithm>
#include <sstream>
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
    
    void inOrderTraversal(Node* current) {
        if (current != nullptr) {
            inOrderTraversal(current->left);
            cout << current->value << " ";
            inOrderTraversal(current->right);
        }
    }
    
    void findLeaves(Node* current) {
        if (current == nullptr) return;
        
        if (current->left == nullptr && current->right == nullptr) {
            cout << current->value << " ";
            return;
        }
        
        findLeaves(current->left);
        findLeaves(current->right);
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
    SearchTree() : root(nullptr) {}
    
    SearchTree(const SearchTree& other) : root(nullptr) {
        root = copyTree(other.root);
    }
    
    SearchTree& operator=(const SearchTree& other) {
        if (this != &other) {
            deleteTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }
    
    ~SearchTree() {
        deleteTree(root);
    }
    
    void insert(int v) {
        root = addNode(root, v);
    }
    
    void insertMultiple() {
        cout << "Введите числа через пробел (для окончания введите 0): ";
        string line;
        cin.ignore();
        getline(cin, line);
        
        stringstream ss(line);
        int value;
        int count = 0;
        
        while (ss >> value) {
            if (value == 0) break;
            insert(value);
            count++;
            cout << "Добавлено: " << value << endl;
        }
        
        if (count > 0) {
            cout << "Всего добавлено: " << count << " элементов" << endl;
        } else {
            cout << "Ничего не добавлено" << endl;
        }
    }
    
    void insertContinuous() {
        cout << "Режим непрерывного ввода (введите 0 для выхода):" << endl;
        int value;
        int count = 0;
        
        do {
            cout << "Введите число: ";
            cin >> value;
            
            if (value != 0) {
                insert(value);
                count++;
                cout << "Добавлено: " << value << endl;
                display();
            }
        } while (value != 0);
        
        cout << "Всего добавлено: " << count << " элементов" << endl;
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
    
    void inOrder() {
        cout << "ЛКП: ";
        inOrderTraversal(root);
        cout << endl;
    }
    
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
    
    void leaves() {
        if (root == nullptr) {
            cout << "пустое";
            return;
        }
        cout << "Листья: ";
        findLeaves(root);
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
        cout << "\n1.добавить_одно 2.добавить_несколько 3.добавить_непрерывно";
        cout << "\n4.найти 5.удалить 6.мин 7.макс 8.показать";
        cout << "\n9.ЛКП 10.по_уровням 11.листья 12.копия 0.выход\n";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "число: ";
                cin >> value;
                tree.insert(value);
                tree.display();
                break;
                
            case 2:
                tree.insertMultiple();
                tree.display();
                break;
                
            case 3:
                tree.insertContinuous();
                break;
                
            case 4:
                cout << "найти: ";
                cin >> value;
                cout << (tree.contains(value) ? "есть" : "нет") << endl;
                break;
                
            case 5:
                cout << "удалить: ";
                cin >> value;
                tree.remove(value);
                tree.display();
                break;
                
            case 6:
                cout << "мин: " << tree.getMinValue() << endl;
                break;
                
            case 7:
                cout << "макс: " << tree.getMaxValue() << endl;
                break;
                
            case 8:
                tree.display();
                break;
                
            case 9:
                tree.inOrder();
                break;
                
            case 10:
                tree.levelOrder();
                break;
                
            case 11:
                tree.leaves();
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
