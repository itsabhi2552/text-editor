#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

class TextEditor
{
private:
    struct Node
    {
        string data;
        Node *next;
        Node(string str)
        {
            data = str;
            next = NULL;
        }
    };

    Node *copyData(Node *head)
    {
        if (head == NULL)
        {
            return NULL;
        }

        Node *copyHead = new Node(head->data);
        Node *copyTemp = copyHead;
        Node *temp = head->next;
        while (temp != NULL)
        {
            copyTemp->next = new Node(temp->data);
            copyTemp = copyTemp->next;
            temp = temp->next;
        }

        return copyHead;
    }

    vector<Node *> searchNode(Node *head, string target)
    {
        vector<Node *> arr;
        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->data == target)
            {
                arr.push_back(temp);
            }
            temp = temp->next;
        }
        return arr;
    }

    void deleteNode(Node *head, Node *target)
    {
        if (head == target)
        {
            head = head->next;
        }

        else
        {
            Node *temp = head;
            while (temp->next != target)
            {
                temp = temp->next;
            }
            temp->next = target->next;
        }
    }

    ofstream fout;
    string fileName;
    Node *head = NULL;
    stack<Node *> undo;
    stack<Node *> redo;

public:
    void createStorage()
    {
        cout << "\n<enter the name of the file>: ";
        cin >> fileName;
        fileName += ".txt";
        fout.open(fileName);
        system("cls");
        cout << "\n<storage has been created for your data with file name \"" + fileName + "\">" << endl;
    }

    void insertData()
    {
        string temp;
        undo.push(copyData(head));
        cout << "\n<enter the data you want to insert (to end use \">\" symbol)>:\n\n data: < ";
        while (true)
        {
            cin >> temp;
            if (temp == ">")
            {
                break;
            }
            else
            {
                if (head == NULL)
                {
                    head = new Node(temp);
                }
                else
                {
                    Node *tempNode = head;
                    while (tempNode->next != NULL)
                    {
                        tempNode = tempNode->next;
                    }
                    tempNode->next = new Node(temp);
                }
            }
        }
        system("cls");
        cout << "\n<data has been inserted in your file  \"" + fileName + "\">" << endl;
    }

    void updateData()
    {
        string temp;
        vector<Node *> arr;
        undo.push(copyData(head));
        cout << "\n<enter the data you want to update>: ";
        cin >> temp;
        arr = searchNode(head, temp);
        if (arr.size() == 0)
        {
            system("cls");
            cout << "\n<no data with name \"" + temp + "\" that you want to update is found>\n";
        }
        else if (arr.size() == 1)
        {
            string str;
            cout << "\n<enter the data that you want to update with>: ";
            cin >> str;
            arr[0]->data = str;
            system("cls");
            cout << "\n<data with name \"" + temp + "\" is updated with \"" + str + "\" >\n";
        }
        else
        {
            string str;
            int indx;
            cout << "\n<there are " + to_string(arr.size()) + " places where the data with name \"" + temp + "\" is found>\n";
            cout << "\n<which one you want to update>: ";
            cin >> indx;
            cout << "\n<enter the data that you want to update with>: ";
            cin >> str;
            arr[indx - 1]->data = str;
            system("cls");
            cout << "\n<data with name \"" + temp + "\" is updated with \"" + str + "\" >\n";
        }
    }

    void appendData()
    {
        string temp;
        undo.push(copyData(head));
        cout << "\n<enter the data you want to append (to end use \">\" symbol)>:\n\n data: < ";
        while (true)
        {
            cin >> temp;
            if (temp == ">")
            {
                break;
            }
            else if (head == NULL)
            {
                head = new Node(temp);
            }
            else
            {
                Node *tempNode = head;
                while (tempNode->next != NULL)
                {
                    tempNode = tempNode->next;
                }
                tempNode->next = new Node(temp);
            }
        }
        system("cls");
        cout << "\n<data has been appended in your file  \"" + fileName + "\">" << endl;
    }

    void searchData()
    {
        vector<Node *> arr;
        string temp;
        cout << "\n<enter the data you want to search>: ";
        cin >> temp;
        arr = searchNode(head, temp);
        system("cls");
        if (arr.size() == 0)
        {
            cout << "\n<no data with name \"" + temp + "\" is found>\n";
        }
        else if (arr.size() == 1)
        {
            cout << "\n<there is only one place where the data with name \"" + temp + "\" is found>\n";
        }
        else
        {
            cout << "\n<there are " + to_string(arr.size()) + " places where the data with name \"" + temp + "\" is found>\n";
        }
    }

    void deleteData()
    {
        vector<Node *> arr;
        string temp;
        undo.push(copyData(head));
        cout << "\n<enter the data you want to delete>: ";
        cin >> temp;
        arr = searchNode(head, temp);
        if (arr.size() == 0)
        {
            system("cls");
            cout << "\n<no data with name \"" + temp + "\" that you want to delete is found>\n";
        }
        else if (arr.size() == 1)
        {
            system("cls");
            deleteNode(head, arr[0]);
            cout << "\n<data with name \"" + temp + "\" is deleted>\n";
        }
        else
        {
            int indx;
            cout << "\n<there are " + to_string(arr.size()) + " places where the data with name \"" + temp + "\" is found>\n";
            cout << "\n<which one you want to delete>: ";
            cin >> indx;
            system("cls");
            deleteNode(head, arr[indx - 1]);
            cout << "\n<data with name \"" + temp + "\" is deleted>\n";
        }
    }

    void displayData()
    {
        Node *temp = head;
        system("cls");
        cout << "data: < ";
        while (temp != NULL)
        {
            cout << temp->data << ' ';
            temp = temp->next;
        }
        cout << ">\n";
    }

    void undoOperation()
    {
        if (!undo.empty())
        {
            redo.push(head);
            head = undo.top();
            undo.pop();
            system("cls");
            cout << "\n<undo operation is done>\n";
        }
        else
        {
            system("cls");
            cout << "\n<there is nothing to undo>\n";
        }
    }

    void redoOperation()
    {
        if (!redo.empty())
        {
            undo.push(head);
            head = redo.top();
            redo.pop();
            system("cls");
            cout << "\n<redo operation is done>\n";
        }
        else
        {
            system("cls");
            cout << "\n<there is nothing to redo>\n";
        }
    }

    void saveData()
    {
        Node *temp = head;
        string tempStr = "";
        while (temp != NULL)
        {
            tempStr += temp->data + ' ';
            temp = temp->next;
        }
        fout << tempStr;
        fout.close();
        system("cls");
        cout << "\n <data is saved in permanent storage with file name \"" + fileName + "\"" << endl;
    }
};

void choice(int opt, TextEditor &obj)
{

    if (opt == 1)
    {
        obj.createStorage();
    }
    else if (opt == 2)
    {
        obj.insertData();
    }
    else if (opt == 3)
    {
        obj.updateData();
    }
    else if (opt == 4)
    {
        obj.appendData();
    }
    else if (opt == 5)
    {
        obj.searchData();
    }
    else if (opt == 6)
    {
        obj.deleteData();
    }
    else if (opt == 7)
    {
        obj.displayData();
    }
    else if (opt == 8)
    {
        obj.undoOperation();
    }
    else if (opt == 9)
    {
        obj.redoOperation();
    }
    else if (opt == 10)
    {
        obj.saveData();
    }
    else
    {
        exit(0);
    }
}

void createMenu()
{
    cout << "\npress 1: create storage for your data" << endl;
    cout << "press 2: insert data" << endl;
    cout << "press 3: update data" << endl;
    cout << "press 4: append data" << endl;
    cout << "press 5: search data" << endl;
    cout << "press 6: delete data" << endl;
    cout << "press 7: display data on console" << endl;
    cout << "press 8: undo operation" << endl;
    cout << "press 9: redo operation" << endl;
    cout << "press 10: save data in permanent storage" << endl;
    cout << "\n<enter your choice>: ";
}

int main()
{
    system("cls");
    TextEditor obj;
    while (true)
    {
        int opt;
        createMenu();
        cin >> opt;
        choice(opt, obj);
    }
    return 0;
}