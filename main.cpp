#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

struct Node
{
    std::string inf;
    int priority{0};
    Node *next{nullptr};

    explicit Node(const std::string& str, int prio = 0) : inf(str), next(nullptr), priority(prio) {}
};

class List {
private:
    Node* head{nullptr};
    Node* last{nullptr};
public:
    List() = default;

    ~List() {
        clear();
    }

    void add(const std::string& str) {
        Node *p = new (std::nothrow) Node(str);
        if (p == nullptr) {
            std::cout << "ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ\n";
            return;
        }
        if (head == nullptr) {
            head = p;
            last = p;
        } else {
            last->next = p;
            last = last->next;
        }
    }
    
    void review() const {
        if (head == nullptr) {
            std::cout << "список пуст\n";
        } else {
            std::cout << "список:\n";
            Node *f = head;
            while (f != nullptr) {
                std::cout << f->inf << "\n";
                f = f->next;
            }
        }
    }

    void del(const std::string &str){
        int cnt = 0;
        while (head != nullptr && head->inf == str) {
            Node *toDel = head;
            head = head->next;
            delete toDel;
            ++cnt;
        }

        if (head == nullptr) {
            last = nullptr;
            std::cout << "удалено "<< cnt << " обьектов\n";
            return;
        }

        Node *current = head->next;
        Node *prev = head; 
        while (current != nullptr){
            if (current->inf == str) {
                prev->next = current->next;
                if (current == last) last = prev;
                delete current;
                current = prev->next;
                ++cnt;
            } else {
                prev = current;
                current = current->next;
            }
        }
        std::cout << "удалено " << cnt << " обьектов\n"; 
    }
    
    void clear() {
        while (head != nullptr){
            Node *f = head->next;
            delete head;
            head = f;
        }
        last = nullptr;
    }
    List(const List&) = delete;
    List& operator=(const List&) = delete;
};


class QueuePrio {
private:
    Node *head{nullptr};
    Node *last{nullptr};
public:
    QueuePrio() = default;

    ~QueuePrio() {
        clear();   
    }

    void review() const {
        if (head == nullptr) {
            std::cout << "очередь с приоритетом пуста\n";
        } else {
            std::cout << "очередь с приоритетом:\n";
            Node *f = head;
            while (f != nullptr) {
                std::cout << f->inf << " " << f->priority <<"\n";
                f = f->next;
            }
        }
    }
        
    bool containsPriority(int prio) const{
        Node *f = head;
        while (f != nullptr) {
            if (f->priority == prio) return true;
            f = f->next;
        }    
        return false;
    }

    void push(const std::string &str, int prio) {
        Node *current = new (std::nothrow) Node(str, prio);      
        if (current == nullptr) {
            std::cout << "ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ\n";
            return;
        }
        Node *f = head;
        if (head == nullptr) {
            head = current;
            last = head;
        } else {
            if (prio > head->priority) {
                current->next = head;
                head = current;
            } else {
                while (f->next != nullptr && prio <= f->next->priority) {
                    f = f->next;
                }
                current->next = f->next;
                f->next = current;       

                if (current -> next == nullptr) last = current;
            }
        }
    }

    void pop() {
        if (head == nullptr) std::cout << "очередь пуста\n";
        else {
            Node *current = head->next;
            delete(head);
            head = current;
            if (head == nullptr) last = nullptr;
        }
    }

    void clear() {
        while (head != nullptr){
            Node *f = head->next;
            delete head;
            head = f;
        }
        last = nullptr;
    }

    bool strCmp(const std::string &str1, const std::string &str2){
        if (str1.size() != str2.size()) return false;

        return std::equal(str1.begin(), str1.end(), str2.begin(), [](unsigned char a, unsigned char b) {
            return std::tolower(a) == std::tolower(b);
        });
    }

    void del(const std::string &str){
        int cnt = 0;
        while (head != nullptr && strCmp(str, head->inf)) {
            Node *f = head->next;
            delete head;
            head = f;
            ++cnt;
        }

        if (head == nullptr) {
            last = nullptr;
            return;
        }
        
        Node *current = head->next;
        Node *prev = head;
        while (current != nullptr){
            if (strCmp(current->inf, str)) {
                prev->next = current->next;
                if (current == last) last = prev;
                delete current;
                current = prev->next;
                ++cnt;
            } else {
                prev = current;
                current = current->next;
            }
        }
        std::cout << "удалено " << cnt << " элементов\n";
    }

    QueuePrio(const QueuePrio&) = delete;
    QueuePrio& operator=(const QueuePrio&) = delete;
};


class Queue {
private:
    Node *head{nullptr};
    Node *last{nullptr};
public:
    Queue() = default;

    ~Queue() {
        clear();
    }

    void review() const {
        if (head == nullptr) std::cout << "очередь пуста\n";
        else {
            std::cout << "очередь:\n";
            Node *f = head;
            while (f != nullptr) {
                std::cout << f->inf <<"\n";
                f = f->next;
            }
        }
    }

    void push(const std::string &str) {
        Node *current = new (std::nothrow) Node(str);
        if (!current) {
            std::cout << "ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ\n";
            return;
        }

        if (head == nullptr) {
            head = current;
            last = head;
        } else {
            last->next = current;
            last = current;
        }
    }

    void pop() {
        if (head == nullptr) std::cout << "очередь пуста\n";
        else {
            Node *current = head->next;
            delete(head);
            head = current;
            if (head == nullptr) last = nullptr;
        }
    }

    void clear() {
        while (head != nullptr){
            Node *f = head->next;
            delete head;
            head = f;
        }
        last = nullptr;
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};


class Stack {
private:
    Node *head{nullptr};
    int sizeS{0};
public:
    Stack() = default;

    ~Stack() {
        clear();
    }
    
    int size(){
        return sizeS;
    }
    
    bool empty() {
        if (head == nullptr) return 1;
        else return false;
    }

    void review() const {
        if (head == nullptr) std::cout << "стек пустой\n";
        else {
            Node *f = head;
            std::cout << "стек:\n";
            while (f != nullptr) {
                std::cout << f->inf << "\n";
                f = f->next;
            }
        }
    }


    void push(const std::string &str) {
        Node *current = new (std::nothrow) Node(str);
        if (current == nullptr) {
            std::cout << "ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ\n";
            return;
        }
        if (head == nullptr) {
            head = current;
        } else {
            current->next = head;
            head = current;
        }
        ++sizeS;
    }

    std::string pop() {
        std::string str;
        if (head == nullptr) {
            std::cout << "стек пуст\n";
            return "";
        } else {
            str = head->inf;
            Node *current = head->next;
            delete head;
            head = current;
            --sizeS;
            return str;
        }
    }

    void clear() {
        while (head != nullptr){
            Node *f = head->next;
            delete head;
            head = f;
        }
    }

    void reverse() {
        std::vector<std::string> v;
        v.reserve(size());
        int sz = size();
        while(!empty()) v.push_back(pop());
        for (int i = 0; i < sz; ++i) {
             push(v[i]);
        }

        
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
};

void menuList() {
    List list;
    int cmd = -1;
    std::cout << "СПИСОК\n1. добавить\n2. удалить\n3. просмотр\n4. очистить\n5. меню\n0. назад\n";
    while (cmd != 0) {
        std::cout << "пункт: ";
        if (!(std::cin >> cmd)) break;
        if (cmd == 1) {
            std::string s;
            std::cout << "данные: ";
            std::cin >> s;
            list.add(s);
        } else if (cmd == 2) {
            std::string s;
            std::cout << "элемент для удаления: ";
            std::cin >> s;
            list.del(s);
        } else if (cmd == 3) {
            list.review();
        } else if (cmd == 4) {
            list.clear();
        } else if (cmd == 5) {
            std::cout << "СПИСОК\n1. добавить\n2. удалить\n3. просмотр\n4. очистить\n5. меню\n0. назад\n";
        } else if (cmd == 0) {
            break;
        } else {
            std::cout << "неверный пункт\n";
        }
    }
}

void menuQueuePrio() {
    QueuePrio qp;
    int cmd = -1;
    std::cout << "ОЧЕРЕДЬ С ПРИОРИТЕТОМ\n1. добавить\n2. извлечь\n3. просмотр\n4. очистить\n5. удаление по строке\n6. меню\n0. назад\n";
    while (cmd != 0) {
        std::cout << "пункт: ";
        if (!(std::cin >> cmd)) break;
        if (cmd == 1) {
            std::string s;
            int prio;
            std::cout << "данные: ";
            std::cin >> s;
            std::cout << "приоритет: ";
            std::cin >> prio;
            while (qp.containsPriority(prio)) {
                std::cout << "ПРИОРИТЕТ ЗАНЯТ\nприоритет: ";
                std::cin >> prio;
            }
            qp.push(s, prio);
        } else if (cmd == 2) {
            qp.pop();
        } else if (cmd == 3) {
            qp.review();
        } else if (cmd == 4) {
            qp.clear();
        } else if (cmd == 5) {
            std::string str;
            std::cout << "введите строку для поиска и удаления совпадений:\n";
            std::cin >> str;
            qp.del(str);
        } else if (cmd == 6) {
            std::cout << "ОЧЕРЕДЬ С ПРИОРИТЕТОМ\n1. добавить\n2. извлечь\n3. просмотр\n4. очистить\n5. меню\n0. назад\n";
        } else if (cmd == 0) {
            break;
        } else {
            std::cout << "неверный пункт\n";
        }
    }
}

void menuQueue() {
    Queue q;
    int cmd = -1;
    std::cout << "ОЧЕРЕДЬ\n1. добавить\n2. извлечь\n3. просмотр\n4. очистить\n5. меню\n0. назад\n";
    while (cmd != 0) {
        std::cout << "пункт: ";
        if (!(std::cin >> cmd)) break;
        if (cmd == 1) {
            std::string s;
            std::cout << "данные: ";
            std::cin >> s;
            q.push(s);
        } else if (cmd == 2) {
            q.pop();
        } else if (cmd == 3) {
            q.review();
        } else if (cmd == 4) {
            q.clear();
        } else if (cmd == 5) {
            std::cout << "ОЧЕРЕДЬ\n1. добавить\n2. извлечь\n3. просмотр\n4. очистить\n5. меню\n0. назад\n";
        } else if (cmd == 0) {
            break;
        } else {
            std::cout << "неверный пункт\n";
        }
    }
}

void menuStack() {
    Stack st;
    int cmd = -1;
    std::cout << "СТЕК\n1. добавить\n2. извлечь\n3. просмотр\n4. очистить\n5. переворот\n6. меню\n0. назад\n";
    while (cmd != 0) {
        std::cout << "пункт: ";
        if (!(std::cin >> cmd)) break;
        if (cmd == 1) {
            std::string s;
            std::cout << "данные: ";
            std::cin >> s;
            st.push(s);
        } else if (cmd == 2) {
            st.pop();
        } else if (cmd == 3) {
            st.review();
        } else if (cmd == 4) {
            st.clear();
        } else if (cmd == 5) {
            st.reverse();
        } else if (cmd == 6) {
            std::cout << "СТЕК\n1. добавить\n2. извлечь\n3. просмотр\n4. очистить\n5. меню\n0. назад\n";
        } else if (cmd == 0) {
            break;
        } else {
            std::cout << "неверный пункт\n";
        }
    }
}

int main() {
    int choice = -1;
    std::cout << "МЕНЮ\n1. список\n2. очередь с приоритетом\n3. очередь\n4. стек\n5. меню\n0. выход\n";
    while (choice != 0) {
        std::cout << "пункт: ";
        if (!(std::cin >> choice)) break;
        if (choice == 1) {
            menuList();
        } else if (choice == 2) {
            menuQueuePrio();
        } else if (choice == 3) {
            menuQueue();
        } else if (choice == 4) {
            menuStack();
        } else if (choice == 5) {
            std::cout << "МЕНЮ\n1. список\n2. очередь с приоритетом\n3. очередь\n4. стек\n5. меню\n0. выход\n";
        } else if (choice == 0) {
            break;
        } else {
            std::cout << "неверный пункт\n";
        }
    }
    return 0;
}
