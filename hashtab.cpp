
#include "D:\source\repos\algorithms_and_data_structures\laboratory2\List.h"
#include <iostream>
using namespace std;
// hash functions//////////////////////////////////////////////////////////////////////////////////////////////////
int HashFunctionMultiplication(int k, int ts)
{
    int N = ts; double A = 0.618033;
    int h = floor(N * fmod(k * A, 1));
    return h;
}
int HashFunctionDivision(int k, int ts)
{
    return (k % ts);
}
int HashFunctionRowKeys(const char* ch, int ts)
{
    int a = 29; int M = ts;
    int result = 0;
    int size = sizeof(ch);
    for (int i = 0; i < size; i++) {
        result += (static_cast<int>(ch[i]) * pow(a, i));
    }
    result = result % M;
    return result;
}
int HashFunctionRowKeys(string ch, int ts)
{
    int a = 26; int M = ts;
    int result = 0;
    int size = ch.length();
    for (int i = 0; i < size; i++) {
        result += (static_cast<int>(ch[i]) * pow(a, i));
    }
    result = result % M;
    return result;
}
struct hashTableEntryInt {
    int e_key;
    int e_data;
    hashTableEntryInt& operator=(const hashTableEntryInt& other) {
        this->e_data = other.e_data;
        this->e_key = other.e_key;
        return *this;
    }
    bool operator ==(const hashTableEntryInt& one) {
        if ((this->e_key == one.e_key && this->e_data == one.e_data)) { return true; }// || (this == NULL && one == NULL)
        return false;
    }
    friend ostream& operator<<(ostream& os, const hashTableEntryInt& dt);
};
ostream& operator<<(ostream& os, const hashTableEntryInt& dt)
{
    os << "key: " << dt.e_key << " " << "value: " << dt.e_data;
    return os;
}
struct hashTableEntryString {
    string e_key = "empty";
    int e_data;
    hashTableEntryString() {
         e_key = "empty";
         e_data = 0;
    }
    hashTableEntryString& operator=(const hashTableEntryString& other) {
        this->e_data = other.e_data;
        this->e_key = other.e_key;
        return *this;
    }
    bool operator ==(const hashTableEntryString& one) {
        
        if ((this->e_key == one.e_key && this->e_data == one.e_data)) { return true; }// || (this == NULL && one == NULL)
        return false;
    }
    friend ostream& operator<<(ostream& os, const hashTableEntryString& dt);
};
ostream& operator<<(ostream& os, const hashTableEntryString& dt)
{
    os << "key: " << dt.e_key << " " << "value: " << dt.e_data;
    return os;
}
class HashTable_open_hashing {
private:
    int T_S;
    List<hashTableEntryString>* lists;
public:
    HashTable_open_hashing(int size = 3) {
        T_S = size;
        lists = new List<hashTableEntryString>[T_S];
        for (int i = 0; i < T_S; i++) {
            //lists[i] = NULL;
        }
    }
    int getTs() {
        return T_S;
    }
    void insert_table_row(string k, hashTableEntryString d) {
        if (lists[HashFunctionRowKeys(k, T_S)].amount() == 0) {
            //++count;
        }
        lists[HashFunctionRowKeys(k, T_S)].createnode(d);
    }
    void delete_table_row(string k) {
        node<hashTableEntryString>* temp = new node<hashTableEntryString>;
        if (lists[HashFunctionRowKeys(k, T_S)].amount() != 0) {
            temp = lists[HashFunctionRowKeys(k, T_S)].get_head();
            int c = 0;
            while (temp != NULL)
            {
                ++c;
                if (temp->data.e_key == k) {
                    lists[HashFunctionRowKeys(k, T_S)].delete_from_n_possition(c);
                    break;
                }
                temp = temp->next;
            }
        }
    }
    hashTableEntryString find_row(string k) {
        node<hashTableEntryString>* temp = new node<hashTableEntryString>;
        int t = HashFunctionRowKeys(k, T_S);
       // if ( t < T_S) { return; }
        if (lists[t].amount() != 0) {
            temp = lists[t].get_head();
            if (temp->data.e_key != "empty"){
                while (temp != NULL)
                {
                    if (temp->data.e_key == k) {
                        return temp->data;
                        break;
                    }
                    temp = temp->next;
                }
            }
            
        }
        return temp->data;
    }
    void print_table() {
        for (int i = 0; i < T_S; i++) {
                cout << i << ":: ";
                lists[i].display();
        }
    }
    // hash functions//////////////////////////////////////////////////////////////////////////////////////////////////
    friend int HashFunctionRowKeys(string ch, int T_S);
};
class HashTable_closed_hashing {
private:
    int T_S = 3;
    hashTableEntryInt* table;
    int count;
public:
    HashTable_closed_hashing(int size = 3) {
        T_S = size;
        table = new  hashTableEntryInt[T_S];
        for (int i = 0; i < T_S; i++) {
            table[i].e_key = -1;
        }
    }
    int getTs() {
        return T_S;
    }
    void resizeTable_division() {
        if (static_cast<double>(count) / T_S > 0.8) {
            hashTableEntryInt* tableTemp = new hashTableEntryInt[T_S];
            for (int i = 0; i < T_S; i++) {;
                    tableTemp[i].e_data = table[i].e_data;
                    tableTemp[i].e_key = table[i].e_key;
            }
            T_S = T_S * 2;
            delete table;
            count = 0;
            
            table = new  hashTableEntryInt[T_S];
            for (int i = 0; i < T_S; i++) {
                table[i].e_key = -1;
            }
            for (int i = 0; i < T_S / 2; i++) {
                //if (tableTemp[i].e_key != -1) {
                    insert_table_division(tableTemp[i].e_key, tableTemp[i]);
                //}                
            }
        }
    }
    void resizeTable_multiplication() {
        if (static_cast<double>(count) / T_S > 0.8) {
            hashTableEntryInt* tableTemp = new hashTableEntryInt[T_S];
            for (int i = 0; i < T_S; i++) {
                ;
                tableTemp[i].e_data = table[i].e_data;
                tableTemp[i].e_key = table[i].e_key;
            }
            T_S = T_S * 2;
            delete table;
            count = 0;

            table = new  hashTableEntryInt[T_S];
            for (int i = 0; i < T_S; i++) {
                table[i].e_key = -1;
            }
            for (int i = 0; i < T_S / 2; i++) {
                
                insert_table_multiplication(tableTemp[i].e_key, tableTemp[i]);
                               
            }
        }
    }
    void insert_table_division(int k, hashTableEntryInt d) {
        int formed_key = HashFunctionDivision(k, T_S);
        for (int i = formed_key; i < T_S + formed_key; i++) {
            int j = i;
            (j >= T_S) ? j = i - T_S : j = i;
            if (table[j].e_key == -1)
            {
                table[j] = d;
                ++count;
                break;
            }
        }
    }
    void insert_table_multiplication(int k, hashTableEntryInt d) {
        int formed_key = HashFunctionMultiplication(k, T_S);
        for (int i = formed_key; i < T_S + formed_key; i++) {
            int j = i;
            (j >= T_S) ? j = i - T_S : j = i;
            if (table[j].e_key == -1)
            {
                table[j] = d;
                ++count;
                break;
            }

        }
    }
    void delete_table_division(int k) {
        int formed_key = HashFunctionDivision(k, T_S);
        for (int i = formed_key; i < T_S + formed_key; i++) {
            int j = i;
            (j >= T_S) ? j = i - T_S : j = i;
            if (table[j].e_key == k) {
                table[j].e_key = -1;
                table[j].e_data = NULL;
                --count;
                break;
            }

        }
    }
    void delete_table_multiplication(int k) {
        int formed_key = HashFunctionMultiplication(k, T_S);
        for (int i = formed_key; i < T_S + formed_key; i++) {
            int j = i;
            (j >= T_S) ? j = i - T_S : j = i;
            if (table[j].e_key == k) {
                table[j].e_key = -1;
                table[j].e_data = NULL;
                --count;
                break;
            }

        }
    }
    hashTableEntryInt find_division(int k) {
        int formed_key = HashFunctionDivision(k, T_S);
        for (int i = formed_key; i < T_S + formed_key; i++) {
            int j = i;
            (j >= T_S) ? j = i - T_S : j = i;
            if (table[j].e_key == k) {
                return table[j];
                break;
            }

        }
        hashTableEntryInt h{NULL};
        return h;
    }
    hashTableEntryInt find_multiplication(int k) {
        int formed_key = HashFunctionMultiplication(k, T_S);
        for (int i = formed_key; i < T_S + formed_key; i++) {
            int j = i;
            (j >= T_S) ? j = i - T_S : j = i;
            if (table[j].e_key == k) {
                return table[j];
                break;
            }

        }
        hashTableEntryInt h{NULL};
        return h;
    }
    void print_table() {
        for (int i = 0; i < T_S; i++) {
            //if (table[i].e_key != -1) {
                cout <<  i << "::   ";
                cout << table[i] <<endl;
            //}            
        }
    }
    // hash functions//////////////////////////////////////////////////////////////////////////////////////////////////
    friend int HashFunctionMultiplication(int k, int T_S);
    friend int HashFunctionDivision(int k, int T_S);
};


int main()
{
    int fpm = 0, thpm = 0, choise = 0;
    HashTable_open_hashing hash_table_s_i;
    HashTable_closed_hashing hash_table_i_i_c;
    hashTableEntryInt hte_i_i;
    hashTableEntryString hte_s_i;
    string str_key, str_value; int ind, key, value;
    while (fpm != 3) {
        cout << "choose the action" << endl;
        cout << "1 - HashTable_open_hashing" << endl;
        cout << "2 - HashTable_closed_hashing" << endl;
        cout << "3 - exit the menu" << endl;
        cin >> fpm;
        switch (fpm)
        {
        case 1:
            cout << "HashTable_open_hashing<string, int> hash_table" << endl;
            while (thpm != 5) {
                cout << "choose the action" << endl;
                cout << "1 - insert key-value" << endl;
                cout << "2 - delete by key" << endl;
                cout << "3 - find by key" << endl;
                cout << "4 - print table" << endl;
                cout << "5 - exit the menu" << endl;
                cin >> thpm;
                switch (thpm)
                {
                case 1:
                    cout << "enter key string: not empty and not deleted " << endl;
                    cin >> str_key;
                    cout << "enter value int: " << endl;
                    cin >> value;
                    hte_s_i.e_key = str_key; hte_s_i.e_data = value;
                    hash_table_s_i.insert_table_row(hte_s_i.e_key, hte_s_i);
                    break;
                case 2:
                    cout << "enter key string: " << endl;
                    cin >> str_key;
                    hash_table_s_i.delete_table_row(str_key);
                    break;
                case 3:
                    cout << "enter key string: " << endl;
                    cin >> str_key;
                    cout << hash_table_s_i.find_row(str_key) << endl;
                    break;
                case 4:
                    hash_table_s_i.print_table();
                    break;
                }
            }
            break;
        case 2:
            cout << "HashTable_closed_hashing<int, int> hash_table" << endl;
            cout << "Division-1 or multiplication-2 method of hashing: " << endl;
            cin >> choise;
            while (thpm != 5) {
                cout << "choose the action" << endl;
                cout << "1 - insert key-value" << endl;
                cout << "2 - delete by key" << endl;
                cout << "3 - find by key" << endl;
                cout << "4 - print table" << endl;
                cout << "5 - exit the menu" << endl;
                cin >> thpm;
                switch (thpm)
                {
                case 1:
                    cout << "enter key int: not -1" << endl;
                    cin >> key;
                    cout << "enter value int: " << endl;
                    cin >> value;
                    hte_i_i.e_key = key; hte_i_i.e_data = value;
                    if (choise == 1) {
                        hash_table_i_i_c.resizeTable_division();
                        hash_table_i_i_c.insert_table_division(hte_i_i.e_key, hte_i_i);
                    }
                    else if (choise == 2) {
                        hash_table_i_i_c.resizeTable_multiplication();
                        hash_table_i_i_c.insert_table_multiplication(hte_i_i.e_key, hte_i_i);
                    }
                    break;
                case 2:
                    cout << "enter key int: " << endl;
                    cin >> key;
                    if (choise == 1) {
                        hash_table_i_i_c.delete_table_division(key);
                        hash_table_i_i_c.resizeTable_division();
                    }
                    else if (choise == 2) {
                        hash_table_i_i_c.delete_table_multiplication(key);
                        hash_table_i_i_c.resizeTable_multiplication();
                    }
                    break;
                case 3:
                    cout << "enter key int: " << endl;
                    cin >> key;
                    if (choise == 1) {
                        cout << hash_table_i_i_c.find_division(key) << endl;
                    }
                    else if (choise == 2) {
                        cout << hash_table_i_i_c.find_multiplication(key) << endl;
                    }
                    break;
                case 4:
                    hash_table_i_i_c.print_table();
                    break;
                }
            }
            break;
        }
    }
}