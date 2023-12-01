#include <iostream>
#include <vector>
#include <limits>

struct TreeNode {
    int rating;
    std::vector<TreeNode*> children;

    // Конструктор для узла дерева с заданным рейтингом
    TreeNode(int val) : rating(val), children() {}
};

// Функция для поиска сенсаций и максимальной разницы в рейтингах
void findSensations(TreeNode* root, int& maxDifference, int& minRating, std::vector<int>& sensations, std::vector<std::pair<int, int>>& maxDifferenceParticipants) {
    if (!root) return;

    // Если у узла нет детей (спортсмен выиграл), проверяем его рейтинг
    if (root->children.empty()) {
        // Если его рейтинг ниже минимального рейтинга, обновляем минимальный рейтинг и добавляем его в список сенсаций
        if (root->rating < minRating) {
            minRating = root->rating;
            sensations.push_back(root->rating);
        }
        return;
    }

    // Проходим по всем детям текущего узла и запускаем функцию рекурсивно
    for (auto child : root->children) {
        findSensations(child, maxDifference, minRating, sensations, maxDifferenceParticipants);
    }

    // Находим минимальный рейтинг среди детей текущего узла
    int minChildRating = std::numeric_limits<int>::max();
    for (auto child : root->children) {
        if (child->rating < minChildRating) {
            minChildRating = child->rating;
        }
    }

    // Проверяем, является ли текущий узел сенсационным (победил среди детей и имеет низший рейтинг)
    if (root->rating == minRating && root->rating < minChildRating) {
        sensations.push_back(root->rating);
    }

    // Проверяем разницу рейтингов между текущим узлом и его детьми для поиска максимальной разницы
    for (auto child : root->children) {
        // Проверяем, имеет ли дочерний узел больший рейтинг, чем минимальный рейтинг в узлах текущего уровня
        if (child->rating > minRating) {
            // Рассчитываем разницу между рейтингом текущего дочернего узла и минимальным рейтингом
            int difference = child->rating - minRating;

            // Если разница больше текущей максимальной разницы, обновляем максимальную разницу
            if (difference > maxDifference) {
                maxDifference = difference;

                // Очищаем вектор, содержащий пары участников с максимальной разницей
                maxDifferenceParticipants.clear();

                // Добавляем новую пару участников с максимальной разницей в вектор
                maxDifferenceParticipants.emplace_back(minRating, child->rating);
            }
            // Если разница равна текущей максимальной разнице, добавляем пару участников в вектор
            else if (difference == maxDifference) {
                maxDifferenceParticipants.emplace_back(minRating, child->rating);
            }
        }
    }

}

int main() {
    system("chcp 1251");

    // Создание узлов дерева
    TreeNode* root = new TreeNode(10);
    TreeNode* node1 = new TreeNode(8);
    TreeNode* node2 = new TreeNode(11);
    TreeNode* node3 = new TreeNode(7);
    TreeNode* node4 = new TreeNode(9);
    TreeNode* node5 = new TreeNode(12);

    // Связывание узлов в дереве
    root->children.push_back(node1);
    root->children.push_back(node2);
    node1->children.push_back(node3);
    node1->children.push_back(node4);
    node2->children.push_back(node5);

    int maxDifference = std::numeric_limits<int>::min();
    int minRating = std::numeric_limits<int>::max(); // Изменение начального значения minRating
    std::vector<int> sensations;
    std::vector<std::pair<int, int>> maxDifferenceParticipants;

    // Вызов функции для поиска сенсаций и максимальной разницы рейтингов
    findSensations(root, maxDifference, minRating, sensations, maxDifferenceParticipants);

    // Вывод результатов
    std::cout << "Сенсационные результаты (игрок с низшим рейтингом, которые выиграли): ";
    for (int rating : sensations) {
        std::cout << rating << " ";
    }
    std::cout << "\nСамая большая разница рейтингов: " << maxDifference << std::endl;
    std::cout << "Сенсационные результаты (игроки с максимальной разницей): ";
    for (const auto& pair : maxDifferenceParticipants) {
        std::cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    std::cout << std::endl;

    // Освобождение памяти, выделенной под узлы
    delete root;
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;

    return 0;
}
