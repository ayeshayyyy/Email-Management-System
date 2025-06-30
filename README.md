
# 📧 Email Management System in C++

## Overview

This is a console-based Email Management System implemented in C++ that simulates the core functionalities of an email platform. Users can create accounts, send emails, save drafts, move emails to trash or spam, and persist data across sessions using file I/O.

---

## Features

* 👤 **Account Management**

  * Create new user accounts
  * Login with email and password
  * Validates unique usernames and emails
  * Supports email domain verification (`lhr.nu.edu.pk`)

* 📥 **Inbox**

  * View received emails
  * Move emails to trash

* 📤 **Sent Mail**

  * View sent messages

* 📝 **Drafts**

  * Save unfinished emails
  * Send saved drafts later

* 🚫 **Spam**

  * Automatically detects and filters spam using predefined keywords
  * Move spam emails to trash

* 🗑️ **Trash**

  * View and manage deleted or spammed emails

* 💾 **Persistence**

  * Save and load all user data and emails to/from a file (`accounts.txt`)
  * Automatically backs up existing data before overwrite

---

## Spam Detection

Emails are flagged as spam if they contain any of the following keywords:

```
Winner, Free, Urgent, Claim, Bonus, Limited,
Exclusive, Gift, Guaranteed, Profit
```

---

## File Structure

* `email2.cpp`: Contains the complete codebase including templates for `Mail`, `MailList`, `Account`, and `AccountList`.
* `accounts.txt`: Used for saving and loading all email and account data (auto-managed by the system).

---

## How to Use

1. **Compile the Code:**

   ```bash
   g++ -o email_system EmailManagementSystem.cpp
   ```

2. **Run the Program:**

   ```bash
   ./email_system
   ```

3. **Choose from Menu:**

   * Create a new account
   * Login to an existing account
   * Use sub-menu to manage emails

---

## Requirements

* C++11 or later
* Standard C++ Libraries (`<iostream>`, `<fstream>`, `<string>`)

---

## Code Structure

* `Mail<T>`: Stores individual email information
* `MailList<T>`: Manages a linked list of emails (Inbox, Drafts, etc.)
* `Account<T>`: Holds all user details and related mailboxes
* `AccountList<T>`: Manages all registered accounts and handles file operations

---

## Notes

* Email addresses must belong to the domain `lhr.nu.edu.pk`
* Password must be at least 6 characters long
* The program uses templates and dynamic memory allocation extensively
* Improper program termination may cause data loss unless explicitly saved

---

## Future Enhancements
✅ Add a graphical user interface (GUI) using libraries like Qt or SFML

✅ Enable password encryption for security

✅ Support for attachments and multimedia content

✅ Implement search and filter functionalities for emails

✅ Add "Mark as Read/Unread" feature

✅ Improve spam detection using NLP or machine learning

✅ Add email reply and forward functionalities

✅ Implement pagination for large inboxes

✅ Add scheduled email sending and notifications

✅ Enable multiple account sessions

---

## Author

This project was built as part of a course assignment or learning module involving OOP and file handling in C++.

---

## Collaboration Guidelines
We welcome contributions from the open-source community. If you'd like to collaborate on this project, please adhere to the following guidelines:
1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Implement your changes and commit them with descriptive messages.
4. Push your branch to your fork and submit a pull request.

---

### Feel free to reach out if you have any questions or suggestions!
