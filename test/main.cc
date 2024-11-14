#include <iostream>
#include <cassert>
#include <rubytree.hh>

void testInsertion() {
    RubyTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);

    assert(tree.search(10) != nullptr);
    assert(tree.search(20) != nullptr);
    assert(tree.search(30) != nullptr);
    assert(tree.search(15) != nullptr);
    assert(tree.search(25) != nullptr);
    assert(tree.search(5) != nullptr);
    assert(tree.search(1) != nullptr);

    std::cout << "Test: Insertion successful." << std::endl;
}

void testDeletion() {
    RubyTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);

    tree.remove(20);
    assert(tree.search(20) == nullptr);

    tree.remove(5);
    assert(tree.search(5) == nullptr);

    std::cout << "Test: Deletion successful." << std::endl;
}

void testSearch() {
    RubyTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    assert(tree.search(10) != nullptr);
    assert(tree.search(5) != nullptr);
    assert(tree.search(20) != nullptr);
    assert(tree.search(99) == nullptr);

    std::cout << "Test: Search successful." << std::endl;
}

int main() {
    testInsertion();
    testDeletion();
    testSearch();

    std::cout << "All tests successful!" << std::endl;

    RubyTree<int> tree;

    // Insert elements
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);


    // Search for elements
    int searchValue = 15;
    auto searchResult = tree.search(searchValue);
    if (searchResult) {
        std::cout << "Element " << searchValue << " found." << std::endl;
    } else {
        std::cout << "Element " << searchValue << " not found." << std::endl;
    }

    return 0;
}
