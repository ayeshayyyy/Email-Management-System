#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string spamWords[] = {"Winner", "Free", "Urgent", "Claim", "Bonus", "Limited",
                            "Exclusive", "Gift", "Guaranteed", "Profit"};

const int spamCount = sizeof(spamWords) / sizeof(spamWords[0]);
template <typename T>
struct Mail
{
    T senderAddress;
    T receiverAddress;
    T subject;
    T content;
    bool isSpam;
    Mail<T> *next;
    Mail(T sender, T receiver, T sub, T cont, bool spamStatus)
    {
        senderAddress = sender;
        receiverAddress = receiver;
        subject = sub;
        content = cont;
        isSpam = spamStatus;
        next = nullptr;
    }
};

template <typename T>
struct Node
{
    T data;
    Node<T> *next;

    Node(T d)
    {
        data = d;
        next = nullptr;
    }
};

template <typename T>
class MailList
{
public:
    Mail<T> *head;

    MailList() { head = nullptr; }

    ~MailList()
    {
        while (head)
        {
            Mail<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addMail(T sender, T receiver, T sub, T cont, bool isSpam)
    {
        Mail<T> *newMail = new Mail<T>(sender, receiver, sub, cont, isSpam);
        if (!head)
        {
            head = newMail;
        }
        else
        {
            Mail<T> *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newMail;
        }
    }

    Mail<T> *removeEmail(int index)
    {
        if (!head)
            return nullptr;

        Mail<T> *temp = head;
        Mail<T> *prev = nullptr;
        for (int i = 1; temp && i < index; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        if (!temp)
            return nullptr;
        if (prev)
        {
            prev->next = temp->next;
        }
        else
        {
            head = temp->next;
        }

        temp->next = nullptr;
        return temp;
    }

    void addToTrash(T sender, T receiver, T sub, T cont, bool isSpam)
    {
        Mail<T> *newMail = new Mail<T>(sender, receiver, sub, cont, isSpam);
        if (!head)
        {
            head = newMail;
        }
        else
        {
            Mail<T> *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newMail;
        }
    }

    void displayTrash()
    {
        if (!head)
        {
            cout << "Trash is empty." << endl;
            return;
        }

        cout << "\nTrash:\n";
        Mail<T> *temp = head;
        int index = 1;
        while (temp)
        {
            cout << index << "- " << temp->subject << " from " << temp->senderAddress << endl;
            temp = temp->next;
            index++;
        }

        cout << "Select an email to view details (enter number): ";
        int choice;
        cin >> choice;

        temp = head;
        for (int i = 1; temp && i < choice; i++)
        {
            temp = temp->next;
        }

        if (!temp)
        {
            cout << "Invalid choice!\n";
        }
        else
        {
            cout << endl;
            cout << "--- Email Details ---" << endl;
            cout << "From: " << temp->senderAddress << endl;
            cout << "To: " << temp->receiverAddress << endl;
            cout << "Subject: " << temp->subject << endl;
            cout << "Content: " << temp->content << endl;
        }
    }

    void displaySentMails(T senderEmail)
    {
        if (!head)
        {
            cout << "No sent mails available." << endl;
            return;
        }
        cout << endl;
        cout << "Sent Mails:" << endl;

        int count = 0;
        Mail<T> *temp = head;
        while (temp)
        {
            if (temp->senderAddress == senderEmail)
            {
                count++;
            }
            temp = temp->next;
        }

        if (count == 0)
        {
            cout << "No sent mails available." << endl;
            return;
        }
        Mail<T> **sentMails = new Mail<T> *[count];

        temp = head;
        int index = 0;

        while (temp)
        {
            if (temp->senderAddress == senderEmail)
            {
                cout << (index + 1) << "- " << temp->subject << " to " << temp->receiverAddress << endl;
                sentMails[index] = temp;
                index++;
            }
            temp = temp->next;
        }

        cout << "Select an email to view details (enter number): ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > count)
        {
            cout << "Invalid choice!\n";
        }
        else
        {
            Mail<T> *selectedMail = sentMails[choice - 1];
            cout << endl;
            cout << "--- Email Details ---" << endl;
            cout << "Sender: " << selectedMail->senderAddress << endl;
            cout << "Recipient: " << selectedMail->receiverAddress << endl;
            cout << "Subject: " << selectedMail->subject << endl;
            cout << "Content: " << selectedMail->content << endl;
        }
        delete[] sentMails;
    }

    void displayDrafts(T senderEmail)
    {
        if (!head)
        {
            cout << "No drafts available.\n";
            return;
        }

        cout << "\nDrafts:\n";

        int count = 0;
        Mail<T> *temp = head;
        while (temp)
        {
            if (temp->senderAddress == senderEmail)
            {
                count++;
            }
            temp = temp->next;
        }
        if (count == 0)
        {
            cout << "No drafts available." << endl;
            return;
        }
        Mail<T> **draftMails = new Mail<T> *[count];

        temp = head;
        int index = 0;

        while (temp)
        {
            if (temp->senderAddress == senderEmail)
            {
                cout << (index + 1) << "- " << temp->subject << " to " << temp->receiverAddress << endl;
                draftMails[index] = temp;
                index++;
            }
            temp = temp->next;
        }

        cout << "Select a draft to view details (enter number): ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > count)
        {
            cout << "Invalid choice!" << endl;
        }
        else
        {
            Mail<T> *selectedMail = draftMails[choice - 1];
            cout << endl;
            cout << "--- Email Details ---" << endl;
            cout << "Sender: " << selectedMail->senderAddress << endl;
            cout << "Recipient: " << selectedMail->receiverAddress << endl;
            cout << "Subject: " << selectedMail->subject << endl;
            cout << "Content: " << selectedMail->content << endl;
        }
        delete[] draftMails;
    }

    void displaySpamEmails(T receiverEmail)
    {
        if (!head)
        {
            cout << "No Spam Emails available." << endl;
            return;
        }

        cout << "Spam Emails:" << endl;

        int count = 0;
        Mail<T> *temp = head;
        while (temp)
        {
            if (temp->receiverAddress == receiverEmail && temp->isSpam)
            {
                count++;
            }
            temp = temp->next;
        }

        if (count == 0)
        {
            cout << "No Spam Emails available." << endl;
            return;
        }

        Mail<T> **spamMails = new Mail<T> *[count];

        temp = head;
        int index = 0;
        while (temp)
        {
            if (temp->receiverAddress == receiverEmail && temp->isSpam)
            {
                cout << (index + 1) << "- " << temp->subject << " from " << temp->senderAddress << endl;
                spamMails[index] = temp;
                index++;
            }
            temp = temp->next;
        }

        cout << "Select a Spam Email to view details (enter number): ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > count)
        {
            cout << "Invalid choice!" << endl;
        }
        else
        {
            Mail<T> *selectedMail = spamMails[choice - 1];
            cout << "\n--- Spam Email Details ---" << endl;
            cout << "Sender: " << selectedMail->senderAddress << endl;
            cout << "Recipient: " << selectedMail->receiverAddress << endl;
            cout << "Subject: " << selectedMail->subject << endl;
            cout << "Content: " << selectedMail->content << endl;
        }

        delete[] spamMails;
    }

    void displayInbox()
    {
        if (!head)
        {
            cout << "Inbox is empty." << endl;
            return;
        }

        cout << "\nInbox:" << endl;
        Mail<T> *temp = head;
        int index = 1;
        while (temp)
        {
            cout << index << "- From: " << temp->senderAddress << ", Subject: " << temp->subject << endl;
            temp = temp->next;
            index++;
        }

        cout << "Select an email to view details (enter number): ";
        int choice;
        cin >> choice;

        temp = head;
        int i = 1;
        while (temp && i < choice)
        {
            temp = temp->next;
            i++;
        }

        if (!temp)
        {
            cout << "Invalid choice!" << endl;
        }
        else
        {
            cout << "\n--- Inbox Details ---" << endl;
            cout << "From: " << temp->senderAddress << endl;
            cout << "To: " << temp->receiverAddress << endl;
            cout << "Subject: " << temp->subject << endl;
            cout << "Content: " << temp->content << endl;
        }
    }
};

template <typename T>
class Account
{
public:
    MailList<T> drafts;
    MailList<T> sentMails;
    T username;
    T email;
    T password;
    MailList<T> inbox;
    MailList<T> sent;
    MailList<T> spam;
    Account<T> *next;
    MailList<T> trash;

    Account()
    {
        username = " ";
        email = " ";
        password = " ";
        next = nullptr;
    }

    Account(T user, T mail, T pass)
    {
        username = user;
        email = mail;
        password = pass;
        next = nullptr;
    }

    void moveEmailToTrash(int index)
    {
        Mail<T> *emailToMove = inbox.removeEmail(index);
        if (emailToMove)
        {
            trash.addToTrash(emailToMove->senderAddress, emailToMove->receiverAddress,
                             emailToMove->subject, emailToMove->content,
                             emailToMove->isSpam);
            delete emailToMove;
            cout << "Email moved to Trash successfully!" << endl;
        }
        else
        {
            cout << "Invalid email index!" << endl;
        }
    }

    void spamToTrash(int index)
    {
        Mail<T> *spamToMove = spam.removeEmail(index);
        if (spamToMove)
        {
            trash.addToTrash(spamToMove->senderAddress, spamToMove->receiverAddress,
                             spamToMove->subject, spamToMove->content,
                             spamToMove->isSpam);
            delete spamToMove;
            cout << "Email moved to Trash successfully!" << endl;
        }
        else
        {
            cout << "Invalid email index!" << endl;
        }
    }

    void DraftToSent(int index)
    {
        Mail<T> *DraftToSend = drafts.removeEmail(index);
        if (DraftToSend)
        {
            sent.addMail(DraftToSend->senderAddress, DraftToSend->receiverAddress,
                         DraftToSend->subject, DraftToSend->content,
                         DraftToSend->isSpam);
            delete DraftToSend;
            cout << "Draft moved to sent successfully!" << endl;
        }
        else
        {
            cout << "Invalid draft index!" << endl;
        }
    }
};

template <typename T>
class AccountList
{
public:
    Account<T> *head;

    AccountList()
    {
        head = nullptr;
    }

    ~AccountList()
    {
        while (head)
        {
            Account<T> *temp = head;
            head = head->next;

            // Clean up inbox
            while (temp->inbox.head)
            {
                Mail<T> *mailTemp = temp->inbox.head;
                temp->inbox.head = temp->inbox.head->next;
                delete mailTemp;
            }

            // Clean up sent
            while (temp->sent.head)
            {
                Mail<T> *mailTemp = temp->sent.head;
                temp->sent.head = temp->sent.head->next;
                delete mailTemp;
            }

            // Clean up spam
            while (temp->spam.head)
            {
                Mail<T> *mailTemp = temp->spam.head;
                temp->spam.head = temp->spam.head->next;
                delete mailTemp;
            }

            // Clean up trash
            while (temp->trash.head)
            {
                Mail<T> *mailTemp = temp->trash.head;
                temp->trash.head = temp->trash.head->next;
                delete mailTemp;
            }

            // Clean up drafts
            while (temp->drafts.head)
            {
                Mail<T> *mailTemp = temp->drafts.head;
                temp->drafts.head = temp->drafts.head->next;
                delete mailTemp;
            }

            delete temp;
        }
    }

    bool isUniqueUsername(const T &username)
    {
        Account<T> *temp = head;
        while (temp)
        {
            if (temp->username == username)
                return false;
            temp = temp->next;
        }
        return true;
    }

    bool isUniqueEmail(const T &email)
    {
        Account<T> *temp = head;
        while (temp)
        {
            if (temp->email == email)
                return false;
            temp = temp->next;
        }
        return true;
    }

    void saveToFile(const string &filename)
    {
        // Create backup of existing file
        ifstream existingFile(filename);
        if (existingFile.good())
        {
            existingFile.close();
            string backupName = filename + ".bak";
            if (rename(filename.c_str(), backupName.c_str()) != 0)
            {
                cout << "Warning: Could not create backup file." << endl;
            }
        }

        ofstream file(filename);
        if (!file)
        {
            cout << "Error: Could not open file for saving." << endl;
            return;
        }

        try
        {
            Account<T> *acc = head;
            while (acc != nullptr)
            {
                file << acc->username << " " << acc->email << " " << acc->password << endl;

                Mail<T> *temp = acc->inbox.head;
                while (temp)
                {
                    file << "INBOX " << temp->senderAddress << " " << temp->receiverAddress << " "
                         << "\"" << temp->subject << "\" " << "\"" << temp->content << "\"" << endl;
                    temp = temp->next;
                }

                temp = acc->sent.head;
                while (temp)
                {
                    file << "SENT " << temp->senderAddress << " " << temp->receiverAddress << " "
                         << "\"" << temp->subject << "\" " << "\"" << temp->content << "\"" << endl;
                    temp = temp->next;
                }

                temp = acc->trash.head;
                while (temp)
                {
                    file << "TRASH " << temp->senderAddress << " " << temp->receiverAddress << " "
                         << "\"" << temp->subject << "\" " << "\"" << temp->content << "\"" << endl;
                    temp = temp->next;
                }

                file << "END" << endl;
                acc = acc->next;
            }

            file.close();
            cout << "Accounts and emails saved successfully." << endl;
        }
        catch (...)
        {
            cout << "Error occurred while saving data." << endl;
            file.close();
            // Restore backup if exists
            string backupName = filename + ".bak";
            ifstream backupFile(backupName);
            if (backupFile.good())
            {
                backupFile.close();
                remove(filename.c_str());
                rename(backupName.c_str(), filename.c_str());
                cout << "Previous version restored from backup." << endl;
            }
        }
    }

    void loadFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "No previous data found." << endl;
            return;
        }

        string username, email, password, type;
        string sender, receiver, subject, content;

        while (file >> username >> email >> password)
        {
            Account<T> *newAccount = new Account<T>(username, email, password);
            newAccount->next = head;
            head = newAccount;

            while (file >> type)
            {
                if (type == "END")
                    break;

                file >> sender >> receiver;
                file.ignore();
                getline(file, subject, '"');
                getline(file, subject, '"');

                file.ignore();
                getline(file, content, '"');
                getline(file, content, '"');

                Node<char> *subjectHead = nullptr;
                Node<char> *contentHead = nullptr;

                for (int i = 0; subject[i] != '\0'; i++)
                {
                    insertChar(subjectHead, subject[i]);
                }

                for (int i = 0; content[i] != '\0'; i++)
                {
                    insertChar(contentHead, content[i]);
                }

                bool isSpam = containsSpamWord(subjectHead) || containsSpamWord(contentHead);

                while (subjectHead)
                {
                    Node<char> *temp = subjectHead;
                    subjectHead = subjectHead->next;
                    delete temp;
                }
                while (contentHead)
                {
                    Node<char> *temp = contentHead;
                    contentHead = contentHead->next;
                    delete temp;
                }

                Mail<T> *newMail = new Mail<T>(sender, receiver, subject, content, isSpam);
                if (type == "INBOX")
                {
                    newMail->next = newAccount->inbox.head;
                    newAccount->inbox.head = newMail;
                }
                else if (type == "SENT")
                {
                    newMail->next = newAccount->sent.head;
                    newAccount->sent.head = newMail;
                }
                else if (type == "TRASH")
                {
                    newMail->next = newAccount->trash.head;
                    newAccount->trash.head = newMail;
                }
            }
        }

        file.close();
        cout << "Accounts and emails loaded successfully." << endl;
    }

    template <typename U>
    void insertChar(Node<U> *&head, U ch)
    {
        Node<U> *newNode = new Node<U>(ch);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node<U> *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    template <typename U>
    int getLength(Node<U> *head)
    {
        int len = 0;
        while (head)
        {
            len++;
            head = head->next;
        }
        return len;
    }

    template <typename U>
    bool isValidEmail(Node<U> *eHead)
    {
        const char *domain = "lhr.nu.edu.pk";
        Node<U> *dHead = nullptr;
        for (int i = 0; domain[i] != '\0'; i++)
        {
            insertChar(dHead, domain[i]);
        }

        int eLen = getLength(eHead);
        int dLen = getLength(dHead);

        if (eLen <= dLen)
        {
            return false;
        }

        int shift = eLen - dLen;
        while (shift--)
        {
            eHead = eHead->next;
        }
        while (dHead)
        {
            if (eHead->data != dHead->data)
            {
                return false;
            }
            eHead = eHead->next;
            dHead = dHead->next;
        }

        return true;
    }

    template <typename U>
    bool matchSpamWord(Node<U> *start, const string &spamWord)
    {
        for (char c : spamWord)
        {
            if (!start || start->data != c)
            {
                return false;
            }
            start = start->next;
        }
        return true;
    }

    template <typename U>
    bool containsSpamWord(Node<U> *head)
    {
        while (head)
        {
            for (int i = 0; i < spamCount; i++)
            {
                if (matchSpamWord(head, spamWords[i]))
                {
                    return true;
                }
            }
            head = head->next;
        }
        return false;
    }

    void createAccount(const T &username, const T &email, const T &password)
    {
        int passLength = 0;
        while (password[passLength] != '\0')
        {
            passLength++;
        }

        Node<char> *emailHead = nullptr;
        for (int i = 0; email[i] != '\0'; i++)
        {
            insertChar(emailHead, email[i]);
        }

        if (!isUniqueUsername(username) || !isUniqueEmail(email) || !isValidEmail(emailHead) || passLength < 6)
        {
            while (emailHead)
            {
                Node<char> *temp = emailHead;
                emailHead = emailHead->next;
                delete temp;
            }
            cout << "Error: Invalid input or user already exists." << endl;
            return;
        }

        Account<T> *newAccount = new Account<T>(username, email, password);

        if (!head)
        {
            head = newAccount;
        }
        else
        {
            Account<T> *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newAccount;
        }

        while (emailHead)
        {
            Node<char> *temp = emailHead;
            emailHead = emailHead->next;
            delete temp;
        }

        cout << "Account successfully created!" << endl;
    }

    Account<T> *login(const T &email, const T &password)
    {
        Account<T> *temp = head;
        while (temp)
        {
            if (temp->email == email && temp->password == password)
            {
                cout << "Login successful!" << endl;
                return temp;
            }
            temp = temp->next;
        }
        cout << "Login failed: Invalid credentials." << endl;
        return nullptr;
    }

    Account<T> *getUser(const T &email)
    {
        Account<T> *temp = head;
        while (temp)
        {
            if (temp->email == email)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void sendEmail(Account<T> *sender, const T &receiverEmail, const T &subject, const T &content)
    {
        Account<T> *receiver = head;
        while (receiver)
        {
            if (receiver->email == receiverEmail)
            {
                Node<char> *subjectHead = nullptr;
                Node<char> *contentHead = nullptr;

                for (int i = 0; subject[i] != '\0'; i++)
                {
                    insertChar(subjectHead, subject[i]);
                }

                for (int i = 0; content[i] != '\0'; i++)
                {
                    insertChar(contentHead, content[i]);
                }

                bool isSpam = containsSpamWord(subjectHead) || containsSpamWord(contentHead);

                while (subjectHead)
                {
                    Node<char> *temp = subjectHead;
                    subjectHead = subjectHead->next;
                    delete temp;
                }
                while (contentHead)
                {
                    Node<char> *temp = contentHead;
                    contentHead = contentHead->next;
                    delete temp;
                }

                if (isSpam)
                {
                    receiver->spam.addMail(sender->email, receiver->email, subject, content, true);
                    cout << "Email sent but moved to spam!" << endl;
                }
                else
                {
                    receiver->inbox.addMail(sender->email, receiver->email, subject, content, false);
                    cout << "Email sent successfully!" << endl;
                }
                sender->sent.addMail(sender->email, receiver->email, subject, content, false);
                return;
            }
            receiver = receiver->next;
        }
        cout << "Error: Recipient not found." << endl;
    }
};

template <typename T>
void createNewMail(Account<T> *sender, AccountList<T> &users)
{
    T receiverEmail, subject, content;
    cout << "Enter recipient's email: ";
    getline(cin, receiverEmail);

    Account<T> *receiver = users.getUser(receiverEmail);
    if (!receiver)
    {
        cout << "No user exists with this email." << endl;
        return;
    }

    cout << "Enter subject: ";
    getline(cin, subject);
    cout << "Enter content: ";
    getline(cin, content);

    int choice;
    cout << "1. Send Mail." << endl;
    cout << "2. Save as Draft." << endl;
    cout << "Choose an option: " << endl;

    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        users.sendEmail(sender, receiverEmail, subject, content);
    }
    else if (choice == 2)
    {
        sender->drafts.addMail(sender->email, receiverEmail, subject, content, false);
        cout << "Email saved as draft!" << endl;
    }
}

int main()
{
    AccountList<string> users;
    Account<string> *loggedInUser = nullptr;
    int choice, subChoice;
    string username, email, password, receiverEmail, subject, content;
    users.loadFromFile("accounts.txt");
    while (true)
    {
        cout << "Main Menu: ";
        cout << "\n1- Create New Account\n2- Login Account\n3- Exit System" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter email: ";
            getline(cin, email);
            cout << "Enter password: ";
            getline(cin, password);

            users.createAccount(username, email, password);
            loggedInUser = users.getUser(email);
            if (loggedInUser)
            {
                while (true)
                {
                    if (!loggedInUser)
                    {
                        break;
                    }

                    cout << "\nSub Menu:" << endl;
                    cout << "1- Create New Mail\n2- Sent\n3- Inbox\n4- Draft\n5- Spam\n6- Trash\n7- Logout" << endl;
                    cout << "Choose an option or (-1 to go back): ";
                    cin >> subChoice;
                    cin.ignore();

                    if (subChoice == -1)
                        break;

                    switch (subChoice)
                    {
                    case 1:
                        createNewMail(loggedInUser, users);
                        break;
                    case 2:
                        loggedInUser->sent.displaySentMails(loggedInUser->email);
                        break;
                    case 3:
                        int inboxChoice;
                        loggedInUser->inbox.displayInbox();
                        cout << "\n1- Move an email to Trash\n2- Back (-1 to go back)\nChoose an option: ";
                        cin >> inboxChoice;
                        cin.ignore();

                        if (inboxChoice == -1)
                            break;
                        if (inboxChoice == 1)
                        {
                            int emailIndex;
                            cout << "Enter the email index to move to Trash (-1 to go back): ";
                            cin >> emailIndex;
                            cin.ignore();
                            if (emailIndex == -1)
                                break;
                            loggedInUser->moveEmailToTrash(emailIndex);
                        }
                        break;
                    case 4:
                        int userChoice;
                        loggedInUser->drafts.displayDrafts(loggedInUser->email);
                        cout << "\n1- Send an email from drafts\n2- Back (-1 to go back)\nChoose an option: ";
                        cin >> userChoice;
                        cin.ignore();

                        if (userChoice == -1)
                            break;
                        if (userChoice == 1)
                        {
                            int draftIndex;
                            cout << "Enter the email index to move from Draft to Sent (-1 to go back): ";
                            cin >> draftIndex;
                            cin.ignore();
                            if (draftIndex == -1)
                                break;
                            loggedInUser->DraftToSent(draftIndex);
                        }
                        break;
                    case 5:
                        int spamChoice;
                        loggedInUser->spam.displaySpamEmails(loggedInUser->email);
                        cout << "\n1- Move an email from Spam to Trash\n2- Back (-1 to go back)\nChoose an option: ";
                        cin >> spamChoice;
                        cin.ignore();

                        if (spamChoice == -1)
                            break;
                        if (spamChoice == 1)
                        {
                            int spamIndex;
                            cout << "Enter the email index to move from Spam to Trash (-1 to go back): ";
                            cin >> spamIndex;
                            cin.ignore();
                            if (spamIndex == -1)
                                break;
                            loggedInUser->spamToTrash(spamIndex);
                        }
                        break;
                    case 6:
                        loggedInUser->trash.displayTrash();
                        break;
                    case 7:
                        if (!loggedInUser)
                        {
                            cout << "You are not logged in." << endl;
                            break;
                        }
                        loggedInUser = nullptr;
                        cout << "Logged out successfully." << endl;
                        break;
                    }
                    if (subChoice == 8)
                        break;
                }
            }
            break;

        case 2:
            if (loggedInUser)
            {
                cout << "Already logged in as " << loggedInUser->username << ".\n";
                break;
            }
            cout << "Enter email: ";
            getline(cin, email);
            cout << "Enter password: ";
            getline(cin, password);
            loggedInUser = users.login(email, password);
            if (loggedInUser)
            {
                while (true)
                {
                    if (!loggedInUser)
                    {
                        break;
                    }
                    cout << "\nSub Menu:" << endl;
                    cout << "1- Create New Mail\n2- Sent\n3- Inbox\n4- Draft\n5- Spam\n6- Trash\n7- Logout" << endl;
                    cout << "Choose an option or (-1 to go back): ";
                    cin >> subChoice;
                    cin.ignore();

                    if (subChoice == -1)
                        break;

                    switch (subChoice)
                    {
                    case 1:
                        createNewMail(loggedInUser, users);
                        break;
                    case 2:
                        loggedInUser->sent.displaySentMails(loggedInUser->email);
                        break;
                    case 3:
                        int inboxChoice;
                        loggedInUser->inbox.displayInbox();
                        cout << "\n1- Move an email to Trash\n2- Back (-1 to go back)\nChoose an option: ";
                        cin >> inboxChoice;
                        cin.ignore();

                        if (inboxChoice == -1)
                            break;
                        if (inboxChoice == 1)
                        {
                            int emailIndex;
                            cout << "Enter the email index to move to Trash (-1 to go back): ";
                            cin >> emailIndex;
                            cin.ignore();
                            if (emailIndex == -1)
                                break;
                            loggedInUser->moveEmailToTrash(emailIndex);
                        }
                        break;
                    case 4:
                        int userChoice;
                        loggedInUser->drafts.displayDrafts(loggedInUser->email);
                        cout << "\n1- Send an email from drafts\n2- Back (-1 to go back)\nChoose an option: ";
                        cin >> userChoice;
                        cin.ignore();

                        if (userChoice == -1)
                            break;
                        if (userChoice == 1)
                        {
                            int draftIndex;
                            cout << "Enter the email index to move from Draft to Sent (-1 to go back): ";
                            cin >> draftIndex;
                            cin.ignore();
                            if (draftIndex == -1)
                                break;
                            loggedInUser->DraftToSent(draftIndex);
                        }
                        break;
                    case 5:
                        int spamChoice;
                        loggedInUser->spam.displaySpamEmails(loggedInUser->email);
                        cout << "\n1- Move an email from Spam to Trash\n2- Back (-1 to go back)\nChoose an option: ";
                        cin >> spamChoice;
                        cin.ignore();

                        if (spamChoice == -1)
                            break;
                        if (spamChoice == 1)
                        {
                            int spamIndex;
                            cout << "Enter the email index to move from Spam to Trash (-1 to go back): ";
                            cin >> spamIndex;
                            cin.ignore();
                            if (spamIndex == -1)
                                break;
                            loggedInUser->spamToTrash(spamIndex);
                        }
                        break;
                    case 6:
                        loggedInUser->trash.displayTrash();
                        break;
                    case 7:
                        if (!loggedInUser)
                        {
                            cout << "You are not logged in." << endl;
                            break;
                        }
                        loggedInUser = nullptr;
                        cout << "Logged out successfully." << endl;
                        break;
                    }
                    if (subChoice == 8)
                        break;
                }
            }
            else
            {
                cout << "Invalid email or password.\n";
            }
            break;

        case 3:
            cout << "Exiting system...";
            users.saveToFile("accounts.txt");
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}