#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Message
{
private:
    string m_message;
    vector<string> m_words;
    vector<int> m_enumeration;
    string m_key;
    vector<int> m_key_enumeration;

private:
    // ������� ������ �� �������
    void fillWords() 
    {
        string word = "";
        for (int i = 0; i <= m_message.length(); i++) 
        {
            if (m_message[i] == ' ' || i == m_message.length()) 
            {
                m_words.push_back(word);
                word = "";
            }
            else 
            {
                word += m_message[i];
            }
        }
    }

    // ������� ������ � ������� ��������
    void createDependent() 
    {
        fillWords();

        int a = 1;
        int b = 1;
        int hlp = a;
        for (int i = 0; i < m_words.size(); i++) 
        {
            m_enumeration.push_back(a);
            b = a;
            a += hlp;
            hlp = b;
        }
    }

    // �������� ������ �� �����
    bool isNumber(const string& str)
    {
        for (char const& c : str) 
        {
            if (isdigit(c) == 0) 
            {
                return false;
            }
        }
        return true;
    }

public:
    Message(string message) 
    {
        m_message = message;
        createDependent();
    }

    ~Message() {}

    // ���� �����
    void putKey() 
    {
        m_key_enumeration.clear();
        cout << "Enter key using 'space': ";
        getline(cin, m_key);

        string el = "";
        for (int i = 0; i <= m_key.length(); i++) 
        {
            if (m_key[i] == ' ' || i == m_key.length()) 
            {
                // ���������, ���� el �� �������� ������
                if (isNumber(el)) {
                    m_key_enumeration.push_back(stoi(el));
                    el = "";
                }
                else 
                {
                    cout << "Uncorrect element" << endl;
                    putKey();
                    break;
                }
            }
            else 
            {
                el += m_key[i];
            }
        }

        // ��������� ������ �����
        if (m_key_enumeration.size() != m_enumeration.size()) 
        {
            // ���� ���-�� ��������� ����� �� ����� ���-�� ����
            cout << "Number of key elements != number of words" << endl;
            m_key_enumeration.clear();
            putKey();
        }
        else 
        {
            // ���� � ����� ���������� �� ����� ��������
            int a = 1;
            int b = 1;
            int hlp = a;
            for (int i = 0; i < m_key_enumeration.size(); i++) 
            {
                bool mist = true;

                for (int j = 0; j < m_key_enumeration.size(); j++) 
                {
                    if (a == m_key_enumeration[j]) 
                    {
                        mist = false;
                    }
                }

                if (mist) 
                {
                    cout << "Uncorrect key" << endl;
                    putKey();
                    break;
                }

                b = a;
                a += hlp;
                hlp = b;
            }
        }
    }

    // Encode
    void Encode() 
    {
        cout << "Encode: ";
        int steps = m_enumeration.size();
        for (int i = 0; i < steps; i++) 
        {
            for (int j = 0; j < steps; j++) 
            {
                if (m_key_enumeration[i] == m_enumeration[j]) 
                {
                    swap(m_enumeration[i], m_enumeration[j]);
                    swap(m_words[i], m_words[j]);
                }
            }
        }
        cout << endl;
    }

    // Decode
    void Decode() 
    {
        cout << "Decode: ";
        int steps = m_enumeration.size();
        for (int i = 0; i < steps; i++)
        {
            for (int j = steps - 1; j > i; j--)
            {
                if (m_enumeration[j] < m_enumeration[j - 1])
                {
                    swap(m_enumeration[j], m_enumeration[j - 1]);
                    swap(m_words[j], m_words[j - 1]);
                }
            }
        }
        cout << endl;
    }

    // ������� ��������� ���������
    void showMessage() 
    {
        cout << "Message: " << m_message << endl;
    }

    // ������� ������ ����
    void showWords() 
    {
        cout << "Words: ";
        for (int i = 0; i < m_words.size(); i++) 
        {
            cout << m_words[i] << " ";
        }
        cout << endl;
    }

    // ������� ������ ����� ��������
    void showEnumeration() 
    {
        cout << "Enumeration: ";
        for (int i = 0; i < m_enumeration.size(); i++) 
        {
            cout << m_enumeration[i] << " ";
        }
        cout << endl;
    }

    // ������� ������ ����� �����
    void showKey() {
        cout << "Key: ";
        for (int i = 0; i < m_key_enumeration.size(); i++) 
        {
            cout << m_key_enumeration[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    string words;
    cout << "Enter a message: ";
    getline(cin, words);

    Message message(words);
    message.showMessage();
    message.showWords();
    message.showEnumeration();

    message.putKey();

    message.Encode();
    message.showWords();

    message.Decode();
    message.showWords();
}
