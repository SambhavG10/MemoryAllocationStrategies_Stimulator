#include <bits/stdc++.h>
using namespace std;
class node
{
public:
    string program;
    int size;
    int address;
    node *next;

    node(string program, int size)
    {
        this->program = program;
        this->size = size;
        this->next = NULL;
    }
};

void print(node *head)
{
    node *temp = head;
    while (temp != NULL)
    {
        cout << "[" << "P_ID:" << temp->program << "," << "Size:" << temp->size << "," << "Start:" << temp->address << "," << "End:" << temp->address + temp->size << "]" << "-->";
        temp = temp->next;
    }
    cout << "NULL";
    return;
}
void insertmemory(node *&head, node *&newnode)
{
    newnode->next = head;
    newnode->address = 0;
    head->address = newnode->size;
    head->size = head->size - newnode->size;
    head = newnode;
    print(head);
    return;
}
void insertGeneralMemory(node *&curr, node *&prev, node *&newnode, node *&head)
{
    prev->next = newnode;
    newnode->next = curr;
    newnode->address = curr->address;
    curr->address = newnode->address + newnode->size;
    curr->size = curr->size - newnode->size;
    print(head);
    return;
}
void allocation(node *&head)
{
    // enter program name and size
    cout << "program name ";
    string prgm;
    cin >> prgm;
    cout << "enter size ";
    int size;
    cin >> size;

    // creating a node to insert
    node *newnode = new node(prgm, size);
    // if first node is  free
    if (head->program == "free")
    {
        if (head->size > size)
        {
            insertmemory(head, newnode);
            return;
        }
        else if (head->size == size)
        {
            head->program = prgm;
            print(head);
            return;
        }
    }

    // if first node is  not free
    if (head->next == NULL && head->program != "free")
    {
        cout << "Can't allocate this  memory\n";
        return;
    }

    // first memory allocation

    if (head->next == NULL)
    {
        if (head->size > newnode->size)
        {
            insertmemory(head, newnode);
            return;
        }
        else if (head->size == newnode->size)
        {
            head->program = prgm;
            print(head);
            return;
        }
    }

    // general case
    node *curr = head;
    node *prev = curr;
    curr = curr->next;
    while (true)
    {
        if (curr == NULL)
        {
            cout << "Can't allocate this memory\n ";
            return;
        }
        if (curr->program == "free")
        {
            if (curr->size > size)
            {
                insertGeneralMemory(curr, prev, newnode, head);
                break;
            }
            else if (curr->size == size)
            {
                curr->program = prgm; // no need to update address just update program name
                print(head);
                return;
            }
            else
            {
                curr = curr->next;
                prev = prev->next;
            }
        }
        else
        {
            curr = curr->next;
            prev = prev->next;
        }
    }
    return;
}

void deallocation(node *&head)
{
    node *temp = head;
    node *temp2 = head;
    cout << "enter the program to deallocate ";
    string s;
    cin >> s;
    while (temp != NULL){
        if (temp->program == s){
            temp->program = "free";
            while (temp2 != NULL){
                if (temp2->program == "free")
                {
                    int TotalSize = 0;
                    node *temp1 = temp2;
                    while (temp1 != NULL && temp1->program == "free")
                    {
                        TotalSize += temp1->size;
                        temp1 = temp1->next;
                    }
                    temp2->size = TotalSize;
                    temp2->next = temp1;
                }
                temp2 = temp2->next;
            }
            print(head);
            return;
        }

        temp = temp->next;
    }
    return;
}
void compaction(node *&head){
    if (head->next == NULL)
    {
        cout << "compaction already done";
        return;
    }
    node *temp = head;
    int TotalSize = 0;
    if (temp->program == "free")
    {
        TotalSize += temp->size;
        head = temp->next;
        temp = head;
    }
    node *temp1 = temp;
    temp = temp->next;
    while (temp != NULL)
    {
        if (temp->program == "free" && temp->next == NULL)
        {
            TotalSize += temp->size;
            temp->size = TotalSize;
            temp1 = temp;
            break;
        }
        else if (temp->program == "free")
        {
            TotalSize += temp->size;
            temp1->next = temp->next;
            temp1 = temp->next;
            temp = temp1->next;
        }
        else
        {
            temp = temp->next;
            temp1 = temp1->next;
        }
    }
    node *temp3 = head;

    temp3->address = 0;
    if (temp1->program != "free")
    {
        node *endnode = new node("free", TotalSize);
        temp1->next = endnode;
        endnode->next = NULL;
    }
    node *temp4 = temp3->next;
    while (temp4 != NULL)
    {
        temp4->address = temp3->address + temp3->size;
        temp3 = temp3->next;
        temp4 = temp4->next;
    }
    print(head);
    cout << "\nCompaction done successfully\n";

    return;
}

int main()
{
    int TotalSpace;
    cout << "Enter the total memory space ";
    cin >> TotalSpace;
    // initially creating single node for free space
    node *head = new node("free", TotalSpace);
    node *tail = head;
    head->address = 0;
    print(head);

    while (1)
    {
        cout << "\nenter your choice\n";
        cout << "1) allocation \n";
        cout << "2) deallocation\n";
        cout << "3) compaction\n";
        cout << "4) exit\n";
        int choice;
        cin >> choice;
        if (choice == 1)
            allocation(head);
        else if (choice == 2)
            deallocation(head);
        else if (choice == 3)
            compaction(head);
        else
            break;
    }

    return 0;
}