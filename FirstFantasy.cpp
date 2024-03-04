// FirstFantasy.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "SystemOutput.h"
#include "Character/Character.h"
#include "Utils.h"
#include "Combat/Combat.h"

int main()
{
    SystemOutput::getInstance()->printToConsole("Hello world!", SystemOutput::outputLevel::INFO);
    Utils::set_rand_seed(time(NULL));

    Character bob = Character();
    Character steve = Character();

    steve.set_name("steve");

    vector<Character*> allies = vector<Character*>();
    allies.push_back(&bob);

    vector<Character*> enemies = vector<Character*>();
    enemies.push_back(&steve);

    Combat combat = Combat(allies, enemies);
    combat.print_participants();

    while (!combat.take_turn()){}
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
