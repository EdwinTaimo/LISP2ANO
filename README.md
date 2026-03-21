Sistema de Check-In em C++ 

Este programa gerencia o fluxo de presenças de funcionários através de uma interface de linha de comando. Utiliza uma estrutura de dados personalizada para armazenar o ID, nome, estado de presença e o horário do registro. Funcionalidades Principail
* Gestão de Cadastro: Permite adicionar novos funcionários com validação de ID único e remover registros existentes.
* Controle de Presença: Realiza o check-in capturando automaticamente a hora do sistema via biblioteca <ctime>.
* Persistência de Dados: Exporta os logs para o arquivo presencas_hoje.txt utilizando o modo ios::app, que preserva o histórico anterior ao adicionar novas entradas.
 * Visualização: Lista todos os colaboradores, filtrando quem está presente ou ausente em tempo real. Detalhes Técnicos O código emprega std::vector para armazenamento dinâmico e std::fstream para manipulação de ficheiros externos. É uma solução eficiente para controle de ponto simples e monitoramento de equipe.  
