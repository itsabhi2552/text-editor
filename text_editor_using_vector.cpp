#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

class TextEditor
{
private:
    ofstream fout;
    string fileName;
    vector<string> data;
    map<string, vector<int>> memo;
    stack<vector<string>> dataUndo;
    stack<vector<string>> dataRedo;
    stack<map<string, vector<int>>> memoUndo;
    stack<map<string, vector<int>>> memoRedo;

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
                data.push_back(temp);
                memo[temp].push_back(data.size() - 1);
            }
        }
        dataUndo.push(data);
        memoUndo.push(memo);
        system("cls");
        cout << "\n<data has been inserted in your file  \"" + fileName + "\">" << endl;
    }

    void updateData()
    {
        string temp;
        cout << "\n<enter the data you want to update>: ";
        cin >> temp;
        dataUndo.push(data);
        memoUndo.push(memo);
        if (memo[temp].size() == 0)
        {
            system("cls");
            cout << "\n<no data with name \"" + temp + "\" that you want to update is found>\n";
        }
        else if (memo[temp].size() == 1)
        {
            string str;
            int indx = memo[temp][0];
            cout << "\n<enter the data that you want to update with>: ";
            cin >> str;
            data[indx] = str;
            memo[temp].pop_back();
            memo[str].push_back(indx);
            system("cls");
            cout << "\n<data with name \"" + temp + "\" is updated with \"" + str + "\" >\n";
        }
        else
        {
            string str;
            int indx;
            cout << "\n<there are " + to_string(memo[temp].size()) + " places where the data with name \"" + temp + "\" is found>\n";
            cout << "\n<which one you want to update>: ";
            cin >> indx;
            cout << "\n<enter the data that you want to update with>: ";
            cin >> str;
            indx = memo[temp][indx - 1];
            data[indx] = str;
            memo[temp].erase(memo[temp].begin() + indx - 1);
            memo[str].push_back(indx);
            system("cls");
            cout << "\n<data with name \"" + temp + "\" is updated with \"" + str + "\" >\n";
        }
    }

    void appendData()
    {
        string temp;
        cout << "\n<enter the data you want to append (to end use \">\" symbol)>:\n\n data: < ";
        dataUndo.push(data);
        memoUndo.push(memo);
        while (true)
        {
            cin >> temp;
            if (temp == ">")
            {
                break;
            }
            else
            {
                data.push_back(temp);
                memo[temp].push_back(data.size() - 1);
            }
        }
        system("cls");
        cout << "\n<data has been appended in your file  \"" + fileName + "\">" << endl;
    }

    void searchData()
    {
        string temp;
        cout << "\n<enter the data you want to search>: ";
        cin >> temp;
        system("cls");
        if (memo[temp].size() == 0)
        {
            cout << "\n<no data with name \"" + temp + "\" is found>\n";
        }
        else if (memo[temp].size() == 1)
        {
            cout << "\n<there is only one place where the data with name \"" + temp + "\" is found>\n";
        }
        else
        {
            cout << "\n<there are " + to_string(memo[temp].size()) + " places where the data with name \"" + temp + "\" is found>\n";
        }
    }

    void deleteData()
    {
        string temp;
        cout << "\n<enter the data you want to delete>: ";
        cin >> temp;
        dataUndo.push(data);
        memoUndo.push(memo);
        if (memo[temp].size() == 0)
        {
            system("cls");
            cout << "\n<no data with name \"" + temp + "\" that you want to delete is found>\n";
        }
        else if (memo[temp].size() == 1)
        {
            system("cls");
            data.erase(data.begin() + memo[temp][0]);
            memo[temp].pop_back();
            cout << "\n<data with name \"" + temp + "\" is deleted>\n";
        }
        else
        {
            int indx;
            cout << "\n<there are " + to_string(memo[temp].size()) + " places where the data with name \"" + temp + "\" is found>\n";
            cout << "\n<which one you want to delete>: ";
            cin >> indx;
            system("cls");
            data.erase(data.begin() + memo[temp][indx - 1]);
            memo[temp].erase(memo[temp].begin() + indx - 1);
            cout << "\n<data with name \"" + temp + "\" is deleted>\n";
        }
    }

    void displayData()
    {
        system("cls");
        cout << "data: < ";
        for (int i = 0; i < data.size(); i++)
        {
            cout << data[i] << " ";
        }
        cout << ">\n";
    }

    void undoOperation()
    {
        if (!dataUndo.empty())
        {
            dataRedo.push(data);
            memoRedo.push(memo);
            data = dataUndo.top();
            memo = memoUndo.top();
            dataUndo.pop();
            memoUndo.pop();
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
        if (!dataRedo.empty())
        {
            dataUndo.push(data);
            memoUndo.push(memo);
            data = dataRedo.top();
            memo = memoRedo.top();
            dataRedo.pop();
            memoRedo.pop();
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
        string temp;
        for (int i = 0; i < data.size(); i++)
        {
            temp += data[i] + " ";
        }
        fout << temp;
        fout.close();
        system("cls");
        cout << "\n <data is saved in permanent storage with file name \"" + fileName + "\"\n";
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