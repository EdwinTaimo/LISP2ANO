#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

struct Funcionario {
    int id;
    string nome;
    int estado; // 0: Ausente, 1: Presente
    string horaCheckin;
};

// Função simples para obter a hora atual
string obterHoraAtual() {
    time_t t = time(0);
    struct tm *agora = localtime(&t);
    char buffer[10];
    strftime(buffer, 10, "%H:%M:%S", agora);
    return string(buffer);
}

int main() {
    vector<Funcionario> lista;
    int opcao;

    do {
        cout << "\n--- SISTEMA CHECK-IN ---" << endl;
        cout << "1. Adicionar Funcionario" << endl;
        cout << "2. Remover Funcionario" << endl;
        cout << "3. Listar e Ver Estados" << endl;
        cout << "4. Marcar Presenca (Check-In)" << endl;
        cout << "5. Gerar/Atualizar Ficheiro Final" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                int novoId;
                cout << "ID do funcionario: "; cin >> novoId;

                // Validação de ID Único
                bool jaExiste = false;
                for (const auto& f : lista) {
                    if (f.id == novoId) {
                        jaExiste = true;
                        break;
                    }
                }

                if (jaExiste) {
                    cout << "Erro: Este ID ja esta registado!" << endl;
                } else {
                    Funcionario f;
                    f.id = novoId;
                    cin.ignore();
                    cout << "Nome: "; getline(cin, f.nome);
                    f.estado = 0;
                    f.horaCheckin = "--:--";
                    lista.push_back(f);
                    cout << "Funcionario adicionado com sucesso." << endl;
                }
                break;
            }

            case 2: {
                int idRemover;
                cout << "ID a remover: "; cin >> idRemover;
                bool removido = false;
                for (auto it = lista.begin(); it != lista.end(); ++it) {
                    if (it->id == idRemover) {
                        lista.erase(it);
                        cout << "Funcionario removido." << endl;
                        removido = true;
                        break;
                    }
                }
                if (!removido) cout << "ID nao encontrado." << endl;
                break;
            }

            case 3: {
                cout << "\nLISTA GERAL:" << endl;
                for (const auto& f : lista) {
                    string status = (f.estado == 1) ? "[PRESENTE]" : "[AUSENTE]";
                    cout << "ID: " << f.id << " | " << f.nome << " | " << status;
                    if (f.estado == 1) cout << " as " << f.horaCheckin;
                    cout << endl;
                }
                break;
            }

            case 4: {
                int idCheck;
                cout << "Insira o ID para Check-In: "; cin >> idCheck;
                bool encontrado = false;
                for (auto& f : lista) {
                    if (f.id == idCheck) {
                        f.estado = 1;
                        f.horaCheckin = obterHoraAtual();
                        cout << "Check-In feito: " << f.nome << " as " << f.horaCheckin << endl;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) cout << "Funcionario nao encontrado." << endl;
                break;
            }

            case 5: {
                // ios::app faz com que o texto seja adicionado ao fim do ficheiro sem apagar o anterior
                ofstream ficheiro("presencas_hoje.txt", ios::app); 
                
                if (ficheiro.is_open()) {
                    ficheiro << "\n--- REGISTO GERADO AS " << obterHoraAtual() << " ---" << endl;
                    for (const auto& f : lista) {
                        string status = (f.estado == 1) ? "Presente" : "Ausente";
                        ficheiro << "ID: " << f.id << " | Nome: " << f.nome 
                                 << " | Estado: " << status << " | Hora: " << f.horaCheckin << endl;
                    }
                    ficheiro.close();
                    cout << "Ficheiro 'presencas_hoje.txt' atualizado!" << endl;
                }
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}