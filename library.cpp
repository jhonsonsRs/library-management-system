#include <iostream>
#include <string>
#include <list>
#include <algorithm>

struct Student { //student type
    int ra;
    int cpf;
    int age;
    std::string name;
};

struct Book { //book type
    std::string name;
    std::string author;
    std::string publisher;
    int year;
};

struct Loan {
    Student student;
    Book book;
};


void RegisterStudent(std::list<Student>& students) {
    Student student; //declare the student
    std::cout << "Digite o seu primeiro nome: " << std::endl;
    std::cin >> student.name;
    std::cout << "Digite o RA: " << std::endl;
    std::cin >> student.ra;
    std::cout << "Digite o CPF: " << std::endl;
    std::cin >> student.cpf;
    std::cout << "Digite a sua idade: " << std::endl;
    std::cin >> student.age;
    students.push_back(student);
}

void DeleteStudent(std::list<Student>& students, const std::string& name) { //receiving the list and the name of the student to remove
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->name == name) { //checks if the provided name is the same as the student's name
            students.erase(it); // Remove the student
            std::cout << "Aluno \"" << name << "\" removido com sucesso!\n" << std::endl;
            return; // Exit the function after removing
        }
    }
    std::cout << "Aluno \"" << name << "\" não encontrado!\n" << std::endl;
}

void ModifyStudent(std::list<Student>& students, const std::string& name) {
    for (auto& student : students) {
        if (student.name == name) {
            std::cout << "Aluno \"" << name << "\" encontrado, preencha com os novos dados \n" << std::endl;
            std::cout << "Primeiro nome: " << std::endl;
            std::cin >> student.name;
            std::cout << "RA: " << std::endl;
            std::cin >> student.ra;
            std::cout << "CPF: " << std::endl;
            std::cin >> student.cpf;
            std::cout << "Idade: " << std::endl;
            std::cin >> student.age;
            std::cout << "Dados do aluno alterados com sucesso! \n" << std::endl;
            return;
        }
    }
    std::cout << "Aluno \"" << name << "\" não encontrado! \n" << std::endl;
}

void RegisterBook(std::list<Book>& books) {
    Book book;
    std::cout << "Digite o nome do Livro: " << std::endl;
    std::cin >> book.name;
    std::cout << "Digite o autor do Livro: " << std::endl;
    std::cin >> book.author;
    std::cout << "Digite a editora do Livro: " << std::endl;
    std::cin >> book.publisher;
    std::cout << "Digite o ano de publicação do Livro: " << std::endl;
    std::cin >> book.year;
    books.push_back(book);
}

void DeleteBook(std::list<Book>& books, const std::string& name) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->name == name) { //checks if the provided name is the same as the book's name
            books.erase(it); // Remove the book
            std::cout << "Livro " << name << " removido com sucesso!\n" << std::endl;
            return; // Exit the function after removing
        }
    }
    std::cout << "Livro " << name << " não encontrado!\n" << std::endl;
}

void ModifyBook(std::list<Book>& books, const std::string& name) {
    for (auto& book : books) { //range-based for loop, is the same as an iterator, but more simplified.
        if (book.name == name) {
            std::cout << "Livro \"" << name << "\" encontrado, preencha com os novos dados" << std::endl;
            std::cout << "Nome do livro: " << std::endl;
            std::cin >> book.name;
            std::cout << "Autor do livro: " << std::endl;
            std::cin >> book.author;
            std::cout << "Editora do livro: " << std::endl;
            std::cin >> book.publisher;
            std::cout << "Ano de publicação: " << std::endl;
            std::cin >> book.year;
            std::cout << "Dados do livro alterados com sucesso!" << std::endl;
            return;
        }
    }
    std::cout << "Livro " << name << " não encontrado\n" << std::endl;
}

void LendBook(std::list<Book>& books, std::list<Student>& students, std::list<Loan>& loans) { 
    std::string bookName;
    std::string studentName;
    std::cout << "Digite o nome do Aluno que o livro vai ser emprestado: " << std::endl;
    std::cin >> studentName;

    auto studentIt = std::find_if(students.begin(), students.end(), [&studentName](const Student& student) {
        return student.name == studentName;
    });

    if (studentIt == students.end()) {
        std::cout << "Aluno não encontrado.\n";
        return;
    }

    std::cout << "Digite o nome do livro a ser emprestado: " << std::endl;
    std::cin >> bookName;

    auto booksIt = std::find_if(books.begin(), books.end(), [&bookName](const Book& book) {
        return book.name == bookName;
    });

    if (booksIt == books.end()) {
        std::cout << "Livro não encontrado.\n";
        return;
    }
    
    loans.push_back({*studentIt, *booksIt});
    books.erase(booksIt);
    std::cout << "Livro \"" << bookName << "\" emprestado ao aluno \"" << studentName << "\" com sucesso.\n";
}

void ReturnBook(std::list<Loan>& loans, std::list<Book>& books, const std::string& name) {
    for (auto it = loans.begin(); it != loans.end(); ++it) { //traverse the list
        if (it->book.name == name) {
            books.push_back(it->book);
            loans.erase(it);
            std::cout << "O livro " << name << " foi devolvido com sucesso!\n" << std::endl;
            return;
        }
    }
    std::cout << "O livro " << name << " não foi encontrado na lista de empréstimos\n" << std::endl;
}

void ViewLoans(const std::list<Loan>& loans) {
    if (loans.empty()) {  // Checks if the list is empty
        std::cout << "Nenhum livro emprestado encontrado. \n" << std::endl;
    } else {
        std::cout << "Lista dos livros emprestados: " << std::endl;
        for (const Loan& loan : loans) {
            std::cout << "Nome: " << loan.book.name << ", Autor: " << loan.book.author << ", Editora: " << loan.book.publisher << ", Ano de publicação: \n" << loan.book.year << std::endl;
        }
    }
}

void ViewBooks(const std::list<Book>& books) {
     if (books.empty()) {  // Checks if the list is empty
        std::cout << "Nenhum livro encontrado. \n" << std::endl;
    } else {
        std::cout << "Lista dos livros:" << std::endl;
        for (const Book& book : books) {
            std::cout << "Nome: " << book.name << ", Autor: " << book.author << ", Editora: " << book.publisher << ", Ano de publicação: \n" << book.year << std::endl;
        }
    }
}

void ViewStudents(const std::list<Student>& students) {
     if (students.empty()) {  // Checks if the list is empty
        std::cout << "Nenhum aluno encontrado. \n" << std::endl;
    } else {
        std::cout << "Lista de Alunos:" << std::endl;
        for (const Student& student : students) {
            std::cout << "Nome: " << student.name << ", Idade: " << student.age << ", RA: " << student.ra << ", CPF: \n" << student.cpf << std::endl;
        }
    }
}

int main() {
    std::list<Student> students;
    std::list<Book> books;
    std::list<Loan> loans;
    std::string nameToRemove;
    std::string nameToModify;
    std::string bookNameToRemove;
    std::string bookNameToModify;
    std::string bookNameToLend;
    std::string bookNameToReturn;
    std::string studentNameToLend;
    int option;
    do {
    std::cout << "Bem-vindo a biblioteca" << std::endl;
    std::cout << "1: Cadastrar aluno" << std::endl;
    std::cout << "2: Deletar aluno" << std::endl;
    std::cout << "3: Alterar aluno" << std::endl;
    std::cout << "4: Visualizar alunos" << std::endl;
    std::cout << "5: Cadastrar um livro" << std::endl;
    std::cout << "6: Deletar livro" << std::endl;
    std::cout << "7: Alterar livro" << std::endl;
    std::cout << "8: Visualizar livros" << std::endl;
    std::cout << "9: Emprestar livro para aluno" << std::endl;
    std::cout << "10: Fazer devolução de livro" << std::endl;
    std::cout << "11: Visualizar empréstimos" << std::endl;
    std::cout << "12: SAIR" << std::endl;
    std::cin >> option;
    switch(option) {
        case 1:
        RegisterStudent(students);
        break;
        case 2:
        std::cout << "Digite o nome do aluno a ser removido: " << std::endl;
        std::cin >> nameToRemove;
        DeleteStudent(students, nameToRemove);
        break;
        case 3:
        std::cout << "Digite o nome do aluno para ser alterado" << std::endl;
        std::cin >> nameToModify;
        ModifyStudent(students, nameToModify);
        break;
        case 4:
        ViewStudents(students);
        break;
        case 5:
        RegisterBook(books);
        break;
        case 6:
        std::cout << "Digite o nome do livro a ser removido: " << std::endl;
        std::cin >> bookNameToRemove;
        DeleteBook(books, bookNameToRemove);
        break;
        case 7:
        std::cout << "Digite o nome do livro a ser alterado: " << std::endl;
        std::cin >> bookNameToModify;
        ModifyBook(books, bookNameToModify);
        break;
        case 8:
        ViewBooks(books);
        break;
        case 9:
        LendBook(books, students, loans);
        break;
        case 10:
        std::cout << "Digite o nome do livro a ser devolvido: " << std::endl;
        std::cin >> bookNameToReturn;
        ReturnBook(loans, books, bookNameToReturn);
        break;
        case 11:
        ViewLoans(loans);
        break;
        case 12:
        break;
        default:
        std::cout << "Opção inválida, digite novamente" << std::endl;
        break;
    }
    }while(option!=12);
    
    return 0;
}