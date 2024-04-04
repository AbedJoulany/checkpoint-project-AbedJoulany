# Phone Book12

This is a simple command-line phone book application written in C. It allows users to manage their contacts by inserting, deleting, editing, searching, sorting, and listing contacts.

## How to Use

1. **Insert**: Add a new contact to the phone book.
2. **Delete**: Remove a contact from the phone book.
3. **Edit**: Modify an existing contact's information.
4. **Search**: Find contacts by first name, last name, telephone number, or cellphone number.
5. **Show All**: Display a list of all contacts.
6. **Sort**: Arrange contacts alphabetically by first name, last name, telephone number, or cellphone number.
7. **Help**: Get information about the program and its usage.
8. **Exit**: Close the program.

## Usage

Compile the code and run the executable file. Follow the on-screen instructions to navigate through the menu options.

## Features

- User-friendly interface.
- Supports up to 50 contacts.
- Data is stored in memory during program execution.
- Contacts are saved and loaded from a file named `phonebookFile`.
- Contacts can be sorted alphabetically by different attributes.
- Easy navigation through the menu system.

## Development Environment

- Language: C
- Compiler: gcc
- IDE: CLion

## File Structure

- `phonebook.c`: Source code file containing the phone book application logic.
- `phonebookFile`: Text file used for storing contact information.
- Header files: `termios.h`, `stdio.h`, `string.h`, `stdlib.h`, `unistd.h`, `stdbool.h`.

## Note

Ensure that the `phonebookFile` is present in the specified location before running the program.



