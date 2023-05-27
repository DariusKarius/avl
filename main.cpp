#include <iostream>
#include <ctime>
using namespace std;
#include "avl.h"
#include "prueba.h"
#include <chrono>
#include <sstream>
#include <iomanip>

time_t convertToUnixTimestamp(const std::string& date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");

    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return std::chrono::system_clock::to_time_t(tp);
}
int main() {

    /*
    AVLTree<int> avl;
    avl.insert(2000);
    avl.insert(1700);
    avl.insert(3600);
    avl.insert(800);
    avl.insert(1900);
    avl.insert(4000);
    avl.insert(3500);
    avl.insert(350);
    avl.displayPretty();
    cout << endl;
    cout << avl.getInOrder() << endl;
    cout << avl.search_by_range(1900,2001);


    AVLTree2<int,int> avl;
    avl.insert(1, 400);
    avl.insert(2, 300);
    avl.insert(3, 150);
    avl.insert(4, 50);
    avl.insert(5, 250);
    avl.insert(6, 500);
    avl.displayPretty();
    cout << endl;
    cout << avl.getInOrder() << endl;
    cout << avl.search_by_range(300,499);


     */
    AVLTree2<int, string> av2;
    av2.insert(6,"17-12-2003");
    av2.insert(7,"23-05-2022");
    av2.insert(8,"02-02-2002");
    av2.displayPretty();
    cout << av2.search_by_range("01-01-2002","01-01-2004");
