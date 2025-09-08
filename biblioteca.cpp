 #include <iostream>
#include <string>
#include <list>
#include <algorithm>

struct Aluno{ //tipo de aluno
    int ra;
    int cpf;
    int idade;
    std::string nome;
};

struct Livro{ //tipo do livro
    std::string nome;
    std::string autor;
    std::string editora;
    int ano;
};

struct Emprestar{
    Aluno aluno;
    Livro livro;
};


void CadastrarAluno(std::list<Aluno>& alunos){
    Aluno aluno; //declarar o aluno
    std::cout << "Digite o seu primeiro nome: " << std::endl;
    std::cin >> aluno.nome;
    std::cout << "Digite o RA: " << std::endl;
    std::cin >> aluno.ra;
    std::cout << "Digite o CPF: " << std::endl;
    std::cin >> aluno.cpf;
    std::cout << "Digite a sua idade: " << std::endl;
    std::cin >> aluno.idade;
    alunos.push_back(aluno);
}

void DeletarAluno(std::list<Aluno>& alunos, const std::string& nome){ //recebendo a lista e o nome do aluno que deseja remover
    for (auto it = alunos.begin(); it != alunos.end(); ++it) {
        if (it->nome == nome) { //vê se o nome fornecido é o mesmo nome do aluno
            alunos.erase(it); // Remove o aluno
            std::cout << "Aluno \"" << nome << "\" removido com sucesso!\n" << std::endl;
            return; // Sai da função após remover
        }
    }
    std::cout << "Aluno \"" << nome << "\" não encontrado!\n" << std::endl;
}

void AlterarAluno(std::list<Aluno>& alunos, const std::string& nome){
    for (auto& aluno : alunos) {
        if (aluno.nome == nome) {
            std::cout << "Aluno \"" << nome << "\" encontrado, preencha com os novos dados \n" << std::endl;
            std::cout << "Primeiro nome: " << std::endl;
            std::cin >> aluno.nome;
            std::cout << "RA: " << std::endl;
            std::cin >> aluno.ra;
            std::cout << "CPF: " << std::endl;
            std::cin >> aluno.cpf;
            std::cout << "Idade: " << std::endl;
            std::cin >> aluno.idade;
            std::cout << "Dados do aluno alterados com sucesso! \n" << std::endl;
            return;
        }
    }
    std::cout << "Aluno \"" << nome << "\" não encontrado! \n" << std::endl;
}

void CadastrarLivro(std::list<Livro>& livros){
    Livro livro;
    std::cout << "Digite o nome do Livro: " << std::endl;
    std::cin >> livro.nome;
    std::cout << "Digite o autor do Livro: " << std::endl;
    std::cin >> livro.autor;
    std::cout << "Digite a editora do Livro: " << std::endl;
    std::cin >> livro.editora;
    std::cout << "Digite o ano de publicação do Livro: " << std::endl;
    std::cin >> livro.ano;
    livros.push_back(livro);
}

void DeletarLivro(std::list<Livro>& livros, const std::string& nome){
    for (auto it = livros.begin(); it != livros.end(); ++it) {
        if (it->nome == nome) { //vê se o nome fornecido é o mesmo nome do aluno
            livros.erase(it); // Remove o aluno
            std::cout << "Livro " << nome << " removido com sucesso!\n" << std::endl;
            return; // Sai da função após remover
        }
    }
    std::cout << "Livro " << nome << " não encontrado!\n" << std::endl;
}

void AlterarLivro(std::list<Livro>& livros, const std::string& nome){
    for (auto& livro : livros) { //range-based for loop, é a mesma coisa que um iterator, porém mais simplificada.
        if (livro.nome == nome) {
            std::cout << "Livro \"" << nome << "\" encontrado, preencha com os novos dados" << std::endl;
            std::cout << "Nome do livro: " << std::endl;
            std::cin >> livro.nome;
            std::cout << "Autor do livro: " << std::endl;
            std::cin >> livro.autor;
            std::cout << "Editora do livro: " << std::endl;
            std::cin >> livro.editora;
            std::cout << "Ano de publicação: " << std::endl;
            std::cin >> livro.ano;
            std::cout << "Dados do livro alterados com sucesso!" << std::endl;
            return;
        }
    }
    std::cout << "Livro " << nome << " não encontrado\n" << std::endl;
}

void Emprestar(std::list<Livro>& livros, std::list<Aluno>& alunos, std::list<Emprestar>& emprestimos){ 
    std::string nomeLivro;
    std::string nomeAluno;
    std::cout << "Digite o nome do Aluno que o livro vai ser emprestado: " << std::endl;
    std::cin >> nomeAluno;

    auto alunoIt = std::find_if(alunos.begin(), alunos.end(), [&nomeAluno](const Aluno& aluno) {
        return aluno.nome == nomeAluno;
    });

    if (alunoIt == alunos.end()) {
        std::cout << "Aluno não encontrado.\n";
        return;
    }

    std::cout << "Digite o nome do livro a ser emprestado: " << std::endl;
    std::cin >> nomeLivro;

    auto livrosIt = std::find_if(livros.begin(), livros.end(), [&nomeLivro](const Livro& livro) {
        return livro.nome == nomeLivro;
    });

    if (livrosIt == livros.end()) {
        std::cout << "Livro não encontrado.\n";
        return;
    }
    
    emprestimos.push_back({*alunoIt, *livrosIt});
    livros.erase(livrosIt);
    std::cout << "Livro \"" << nomeLivro << "\" emprestado ao aluno \"" << nomeAluno << "\" com sucesso.\n";
}

void Devolucao(std::list<Emprestar>& emprestimos, std::list<Livro>& livros, const std::string& nome){
    for (auto it = emprestimos.begin(); it != emprestimos.end(); ++it) { //percorre a lista
        if (it->nome == nome) {
            livros.push_back(*it);
            emprestimos.erase(it);
            std::cout << "O livro " << nome << " foi devolvido com sucesso!\n" << std::endl;
            return;
        }
    }
    std::cout << "O livro " << nome << " não foi encontrado na lista de empréstimos\n" << std::endl;
}

void VisualizarEmprestimos(const std::list<Livro>& emprestimo){
    if (emprestimo.empty()) {  // Verifica se a lista ta vazia
        std::cout << "Nenhum livro emprestado encontrado. \n" << std::endl;
    } else {
        std::cout << "Lista dos livros emprestados: " << std::endl;
        for (const Livro& livro : emprestimo) {
            std::cout << "Nome: " << livro.nome << ", Autor: " << livro.autor << ", Editora: " << livro.editora << ", Ano de publicação: \n" << livro.ano << std::endl;
        }
    }
}

void VisualizarLivros(const std::list<Livro>& livros){
     if (livros.empty()) {  // Verifica se a lista ta vazia
        std::cout << "Nenhum livro encontrado. \n" << std::endl;
    } else {
        std::cout << "Lista dos livros:" << std::endl;
        for (const Livro& livro : livros) {
            std::cout << "Nome: " << livro.nome << ", Autor: " << livro.autor << ", Editora: " << livro.editora << ", Ano de publicação: \n" << livro.ano << std::endl;
        }
    }
}

void VisualizarAluno(const std::list<Aluno>& alunos){
     if (alunos.empty()) {  // Verifica se a lista ta vazia
        std::cout << "Nenhum aluno encontrado. \n" << std::endl;
    } else {
        std::cout << "Lista de Alunos:" << std::endl;
        for (const Aluno& aluno : alunos) {
            std::cout << "Nome: " << aluno.nome << ", Idade: " << aluno.idade << ", RA: " << aluno.ra << ", CPF: \n" << aluno.cpf << std::endl;
        }
    }
}

int main(){
    std::list<Aluno> alunos;
    std::list<Livro> livros;
    std::list<Emprestar> emprestimos;
    std::string nomeRemover;
    std::string nomeAlterar;
    std::string nomeLivroRemover;
    std::string nomeLivroAlterar;
    std::string nomeLivroEmprestar;
    std::string nomeLivroDevolver;
    std::string nomeAlunoEmprestar;
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
    switch(option){
        case 1:
        CadastrarAluno(alunos);
        break;
        case 2:
        std::cout << "Digite o nome do aluno a ser removido: " << std::endl;
        std::cin >> nomeRemover;
        DeletarAluno(alunos, nomeRemover);
        break;
        case 3:
        std::cout << "Digite o nome do aluno para ser alterado" << std::endl;
        std::cin >> nomeAlterar;
        AlterarAluno(alunos, nomeAlterar);
        break;
        case 4:
        VisualizarAluno(alunos);
        break;
        case 5:
        CadastrarLivro(livros);
        break;
        case 6:
        std::cout << "Digite o nome do livro a ser removido: " << std::endl;
        std::cin >> nomeLivroRemover;
        DeletarLivro(livros, nomeLivroRemover);
        break;
        case 7:
        std::cout << "Digite o nome do livro a ser alterado: " << std::endl;
        std::cin >> nomeLivroAlterar;
        AlterarLivro(livros, nomeLivroAlterar);
        break;
        case 8:
        VisualizarLivros(livros);
        break;
        case 9:
        Emprestar(livros, alunos, emprestimos);
        break;
        case 10:
        std::cout << "Digite o nome do livro a ser devolvido: " << std::endl;
        std::cin >> nomeLivroDevolver;
        Devolucao(emprestimo, livros, nomeLivroDevolver);
        break;
        case 11:
        VisualizarEmprestimos(emprestimo);
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