#include <iostream>
#include <cassert>
struct d_NODE {
    int key;
    d_NODE* pNext;
    d_NODE* pPrev;
};

struct d_List {
    d_NODE* pHead;
    d_NODE* pTail;
    d_List(d_NODE* head = nullptr, d_NODE* tail = nullptr) : pHead(head), pTail(tail) {}
};

// --- Define function prototypes ---
d_NODE *createNode(int data);
d_List *createList(d_NODE *pNode);
bool addHead(d_List *&L, int data);
bool addTail(d_List *&L, int data);
bool removeHead(d_List *&L);
bool removeTail(d_List *&L);
void removeAll(d_List *&L);
void removeBefore(d_List *&L, int val);
bool removePos(d_List*& L, int pos);
bool addPos(d_List*& L, int data, int pos);
void removeAfter(d_List *&L, int val);
bool addBefore(d_List *&L, int data, int val);
bool addAfter(d_List *&L, int data, int val);
int countElements(d_List *L);
d_List *reverseList(d_List *L);
void removeDuplicate(d_List *&L);
bool removeElement(d_List *&L, int key);
void printList(d_List *L);

// function to create a list from an array
d_List *createListFromArray(int arr[], int n)
{
    d_List *newList = new d_List();
    newList->pHead = nullptr;
    newList->pTail = nullptr;
    for (int i = 0; i < n; ++i)
    {
        addTail(newList, arr[i]);
    }
    return newList;
}

// function to compare two lists
bool areListsEqual(d_List *list1, d_List *list2)
{
    d_NODE *current1 = list1 ? list1->pHead : nullptr;
    d_NODE *current2 = list2 ? list2->pHead : nullptr;
    while (current1 && current2)
    {
        if (current1->key != current2->key)
        {
            return false;
        }
        current1 = current1->pNext;
        current2 = current2->pNext;
    }
    return (current1 == nullptr && current2 == nullptr);
}

// function to free the memory of a list
void freeList(d_List *L)
{
    d_NODE *current = L->pHead;
    while (current){
        d_NODE *next = current->pNext;
        delete current;
        current = next;
    }
    delete L;
}

d_NODE *createNode(int data) {
    d_NODE *p = new d_NODE;
    if (!p) return nullptr;
    p->key = data;
    p->pNext = nullptr;
    p->pPrev = nullptr;
    return p;
}

d_List *createList(d_NODE *pNode) {
    d_List *L = new d_List;
    if (!L){
        return nullptr;
    }
    L->pHead = L->pTail = pNode;
    return L;
}

bool addHead(d_List *&L, int data) {
    d_NODE *p = createNode(data);
    if (!p){
        return false;
    }
    if (!L->pHead) {
        L->pHead = L->pTail = p;
    } 
    else {
        p->pNext = L->pHead;
        L->pHead->pPrev = p;
        L->pHead = p;
    }
    return true;
}

bool addTail(d_List *&L, int data) {
    d_NODE *p = createNode(data);
    if (!p) return false;
    if (!L->pTail) {
        L->pHead = L->pTail = p;
    } 
    else {
        p->pPrev = L->pTail;
        L->pTail->pNext = p;
        L->pTail = p;
    }
    return true;
}

bool removeHead(d_List *&L) {
    if (!L || !L->pHead) return false;
    d_NODE *temp = L->pHead;
    L->pHead = L->pHead->pNext;
    if (L->pHead){
        L->pHead->pPrev = nullptr;
    }
    else{
        L->pTail = nullptr;
    }
    delete temp;
    return true;
}

bool removeTail(d_List *&L) {
    if (!L || !L->pTail) return false;
    d_NODE *temp = L->pTail;
    L->pTail = L->pTail->pPrev;
    if (L->pTail){
        L->pTail->pNext = nullptr;
    }
    else{
        L->pHead = nullptr;
    }
    delete temp;
    return true;
}
void removeAll(d_List *&L) {
    while (L && L->pHead) {
        removeHead(L);
    }
}

// Remove a node before a given value in the list if it exists, otherwise do nothing
void removeBefore(d_List *&L, int val) {
    if (!L || !L->pHead || L->pHead->key == val) return;
    d_NODE *curr = L->pHead->pNext;
    while (curr) {
        if (curr->key == val) {
            d_NODE *toDelete = curr->pPrev;
            if (!toDelete){
                return;
            }
            if (toDelete == L->pHead) {
                L->pHead = curr;
                curr->pPrev = nullptr;
            } 
            else {
                toDelete->pPrev->pNext = curr;
                curr->pPrev = toDelete->pPrev;
            }
            delete toDelete;
            return;
        }
        curr = curr->pNext;
    }
}

void removeAfter(d_List *&L, int val) {
    if (!L || !L->pHead) return;
    d_NODE *curr = L->pHead;
    while (curr) {
        if (curr->key == val && curr->pNext) {
            d_NODE *toDelete = curr->pNext;
            curr->pNext = toDelete->pNext;
            if (toDelete->pNext){
                toDelete->pNext->pPrev = curr;
            }
            else{
                L->pTail = curr;
            }
            delete toDelete;
            return;
        }
        curr = curr->pNext;
    }
}

bool addPos(d_List*& L, int data, int pos) {
    if (!L || pos < 0) {
        return false;
    }
    int count = countElements(L);
    if (pos > count) {
        return false;
    }
    if (pos == 0) {
        return addHead(L, data);
    } else if (pos == count) {
        return addTail(L, data);
    } else {
        d_NODE* newNode = createNode(data);
        if (!newNode) {
            return false;
        }
        d_NODE* curr = L->pHead;
        for (int i = 0; i < pos; ++i) {
            curr = curr->pNext;
        }
        newNode->pNext = curr;
        newNode->pPrev = curr->pPrev;
        if (curr->pPrev) {
            curr->pPrev->pNext = newNode;
        }
        curr->pPrev = newNode;
        return true;
    }
}


bool removePos(d_List*& L, int data, int pos) {
    if (!L || pos < 0 || !L->pHead) {
        return false;
    }
    int count = countElements(L);
    if (pos >= count) {
        return false;
    }
    if (pos == 0) {
        return removeHead(L);
    } else if (pos == count - 1) {
        return removeTail(L);
    } else {
        d_NODE* curr = L->pHead;
        for (int i = 0; i < pos; ++i) {
            curr = curr->pNext;
        }
        if (curr->pPrev) {
            curr->pPrev->pNext = curr->pNext;
        }
        if (curr->pNext) {
            curr->pNext->pPrev = curr->pPrev;
        }
        delete curr;
        return true;
    }
}

// Insert an integer before a value of a given List:
bool addBefore(d_List *&L, int data, int val) {
    if (!L || !L->pHead) return false;
    d_NODE *curr = L->pHead;
    while (curr) {
        if (curr->key == val) {
            d_NODE *newNode = createNode(data);
            newNode->pNext = curr;
            newNode->pPrev = curr->pPrev;
            if (curr->pPrev)
                curr->pPrev->pNext = newNode;
            else
                L->pHead = newNode;

            curr->pPrev = newNode;
            return true;
        }
        curr = curr->pNext;
    }
    return false;
}

bool addAfter(d_List *&L, int data, int val) {
    if (!L || !L->pHead) return false;
    d_NODE *curr = L->pHead;
    while (curr) {
        if (curr->key == val) {
            d_NODE *newNode = createNode(data);
            newNode->pNext = curr->pNext;
            newNode->pPrev = curr;
            if (curr->pNext)
                curr->pNext->pPrev = newNode;
            else
                L->pTail = newNode;
            curr->pNext = newNode;
            return true;
        }
        curr = curr->pNext;
    }
    return false;
}


void printList(d_List *L) {
    d_NODE *curr = L ? L->pHead : nullptr;
    while (curr) {
        std::cout << curr->key << " ";
        curr = curr->pNext;
    }
    std::cout << std::endl;
}

int countElements(d_List* L) {
    if (!L || !L->pHead) {
        return 0;
    }
    int count = 0;
    d_NODE* curr = L->pHead;
    while (curr) {
        count++;
        curr = curr->pNext;
    }
    return count;
}

d_List* reverseList(d_List* L) {
    if (!L || !L->pHead) {
        return L;
    }
    d_NODE* curr = L->pHead;
    d_NODE* temp = nullptr;
    while (curr) {
        temp = curr->pPrev;
        curr->pPrev = curr->pNext;
        curr->pNext = temp;
        curr = curr->pPrev; 
    }
    temp = L->pHead;
    L->pHead = L->pTail;
    L->pTail = temp;
    return L;
}


void removeDuplicate(d_List*& L) {
    if (!L || !L->pHead) return;
    d_NODE* curr = L->pHead;
    while (curr) {
        d_NODE* runner = curr->pNext;
        while (runner) {
            if (runner->key == curr->key) {
                d_NODE* dup = runner;
                runner = runner->pNext;
                if (dup->pPrev){
                    dup->pPrev->pNext = dup->pNext;
                }
                if (dup->pNext){
                    dup->pNext->pPrev = dup->pPrev;
                }
                if (dup == L->pHead){
                    L->pHead = dup->pNext;
                }
                if (dup == L->pTail){
                    L->pTail = dup->pPrev;
                }
                delete dup;
            } 
            else {
                runner = runner->pNext;
            }
        }
        curr = curr->pNext;
    }
}

bool removeElement(d_List*& L, int key) {
    if (!L || !L->pHead) return false;
    bool removed = false;
    d_NODE* curr = L->pHead;
    while (curr) {
        if (curr->key == key) {
            d_NODE* tmp = curr;
            curr = curr->pNext;
            if (tmp->pPrev){
                tmp->pPrev->pNext = tmp->pNext;
            }
            else{
                L->pHead = tmp->pNext;
            }
            if (tmp->pNext){
                tmp->pNext->pPrev = tmp->pPrev;
            }
            else{
                L->pTail = tmp->pPrev;
            }
            delete tmp;
            removed = true;
        } else {
            curr = curr->pNext;
        }
    }
    return removed;
}

// --- Function main to test the above functions ---

int main()
{
    std::cout << "--- Begin running test cases ---" << std::endl;

    // Test case 1: createNode /////////////////////////////////////////////////
    std::cout << "Test createNode: ";
    d_NODE *node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->pNext == nullptr);
    std::cout << "Passed" << std::endl;
    delete node1;

    // Test case 2: createList //////////////////////////////////////////////////
    std::cout << "Test createList: ";
    d_NODE *head2 = createNode(20);
    d_List *list2 = createList(head2);
    assert(list2 != nullptr && list2->pHead == head2 && list2->pTail == head2);
    std::cout << "Passed" << std::endl;
    freeList(list2);

    // Test case 3: addHead //////////////////////////////////////////////////////
    std::cout << "Test addHead: ";
    d_List *list3 = new d_List();
    assert(addHead(list3, 30));
    assert(list3->pHead != nullptr && list3->pHead->key == 30 && list3->pTail->key == 30);
    assert(addHead(list3, 40));
    assert(list3->pHead->key == 40 && list3->pHead->pNext->key == 30 && list3->pTail->key == 30);
    std::cout << "Passed" << std::endl;
    freeList(list3);

    // Test case 4: addTail /////////////////////////////////////////////////////////
    std::cout << "Test addTail: ";
    d_List *list4 = new d_List();
    assert(addTail(list4, 50));
    assert(list4->pHead != nullptr && list4->pHead->key == 50 && list4->pTail->key == 50);
    assert(addTail(list4, 60));
    assert(list4->pHead->key == 50 && list4->pTail->key == 60 && list4->pHead->pNext->key == 60);
    std::cout << "Passed" << std::endl;
    freeList(list4);

    // Test case 5: removeHead //////////////////////////////////////////////////////////////////
    std::cout << "Test removeHead: ";
    int arr1[3] = {70, 80, 90};
    d_List *list5 = createListFromArray(arr1, 3);
    assert(removeHead(list5) && list5->pHead->key == 80);
    assert(removeHead(list5) && list5->pHead->key == 90);
    assert(removeHead(list5) && list5->pHead == nullptr && list5->pTail == nullptr);
    assert(!removeHead(list5)); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(list5);

    // Test case 6: removeTail ///////////////////////////////////////////////////////////////////
    std::cout << "Test removeTail: ";
    int arr2[3] = {100, 110, 120};
    d_List *list6 = createListFromArray(arr2, 3);
    removeTail(list6);
    assert(list6->pTail->key == 110 && list6->pTail->pNext == nullptr);
    removeTail(list6);
    assert(list6->pTail->key == 100 && list6->pTail->pNext == nullptr && list6->pHead == list6->pTail);
    removeTail(list6);
    assert(list6->pHead == nullptr && list6->pTail == nullptr);
    d_List *emptyList6 = new d_List();
    removeTail(emptyList6); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(emptyList6);
    freeList(list6);

    // Test case 7: removeAll /////////////////////////////////////////////////////////////////////
    std::cout << "Test removeAll: ";
    int arr3[3] = {130, 140, 150};
    d_List *list7 = createListFromArray(arr3, 3);
    removeAll(list7);
    assert(list7->pHead == nullptr && list7->pTail == nullptr);
    d_List *emptyList7 = new d_List();
    removeAll(emptyList7); // Remove from empty list
    assert(emptyList7->pHead == nullptr && emptyList7->pTail == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(emptyList7);
    freeList(list7);

    // Test case 8: removeBefore //////////////////////////////////////////////////////////////////////
    std::cout << "Test removeBefore: ";
    int arr4[5] = {160, 170, 180, 190, 200};
    d_List *list8 = createListFromArray(arr4, 5);

    // testcase 1
    removeBefore(list8, 180);
    int expectedArr8[4] = {160, 180, 190, 200};
    d_List *expectedList8 = createListFromArray(expectedArr8, 4);
    assert(areListsEqual(list8, expectedList8));

    // testcase 2
    removeBefore(list8, 200);
    int expectedArr8_2[3] = {160, 180, 200};
    d_List *expectedList8_2 = createListFromArray(expectedArr8_2, 3);
    assert(areListsEqual(list8, expectedList8_2));

    // testcase 3
    removeBefore(list8, 170); // Don't have any element before
    int expectedArr8_2_2[3] = {160, 180, 200};
    d_List *expectedList8_2_2 = createListFromArray(expectedArr8_2_2, 3);
    assert(areListsEqual(list8, expectedList8_2_2));

    // free memory
    freeList(expectedList8);
    freeList(expectedList8_2);
    freeList(expectedList8_2_2);
    freeList(list8);
    std::cout << "Passed" << std::endl;

    // Test case 9: remove after ////////////////////////////////////////////////////////////
    std::cout << "Test removeAfter: ";
    int arr5[4] = {220, 230, 240, 250};
    d_List *list9 = createListFromArray(arr5, 4);
    // testcase 1
    removeAfter(list9, 220);
    int expectedArr9[3] = {220, 240, 250};
    d_List *expectedList9 = createListFromArray(expectedArr9, 3);
    assert(areListsEqual(list9, expectedList9));
    // testcase 2
    removeAfter(list9, 250); // Don't have any element after
    int expectedArr9_2[3] = {220, 240, 250};
    d_List *expectedList9_2 = createListFromArray(expectedArr9_2, 3);
    assert(areListsEqual(list9, expectedList9_2));
    // testcase 3
    removeAfter(list9, 240);
    int expectedArr9_3[2] = {220, 240};
    d_List *expectedList9_3 = createListFromArray(expectedArr9_3, 2);
    assert(areListsEqual(list9, expectedList9_3));
    // testcase 4
    int arr9_single[1] = {260};
    d_List *list9_single = createListFromArray(arr9_single, 1);
    removeAfter(list9_single, 260);
    int expectedArr9_single[1] = {260};
    d_List *expectedList9_single = createListFromArray(expectedArr9_single, 1);
    assert(areListsEqual(list9_single, expectedList9_single));
    // testcase 5
    d_List *emptyList9 = new d_List();
    removeAfter(emptyList9, 270);
    assert(areListsEqual(emptyList9, new d_List()));
    // free memory
    freeList(expectedList9);
    freeList(expectedList9_2);
    freeList(expectedList9_3);
    freeList(expectedList9_single);
    freeList(list9);
    freeList(list9_single);
    freeList(emptyList9);
    std::cout << "Passed" << std::endl;

    // // // Test case 10: addPos /////////////////////////////////////////////////////////
    std::cout << "Test addPos: ";
    d_List *list10 = new d_List();
    assert(addPos(list10, 280, 0));
    assert(list10->pHead != nullptr && list10->pHead->key == 280 && list10->pTail->key == 280);
    assert(addPos(list10, 290, 1));
    assert(list10->pHead->key == 280 && list10->pTail->key == 290 && list10->pHead->pNext->key == 290);
    assert(addPos(list10, 300, 1));
    assert(list10->pHead->key == 280 && list10->pTail->key == 290 && list10->pHead->pNext->key == 300);
    assert(list10->pHead->pNext->pNext->key == 290);
    assert(addPos(list10, 310, 3));
    assert(list10->pHead->key == 280 && list10->pTail->key == 310 && list10->pHead->pNext->key == 300);
    assert(list10->pHead->pNext->pNext->key == 290 && list10->pHead->pNext->pNext->pNext->key == 310);
    assert(!addPos(list10, 320, 5));  // Positions out of range
    assert(!addPos(list10, 330, -1)); // Negative position
    // free memory
    freeList(list10);
    std::cout << "Passed" << std::endl;

    // Test case 11: RemovePos /////////////////////////////////////////////////////////
    std::cout << "Test RemovePos: ";
    int arr11[5] = {340, 350, 360, 370, 380};
    d_List *list11 = createListFromArray(arr11, 5);
    assert(list11->pHead->key == 340 && list11->pTail->key == 380);
    // testcase 1
    removePos(list11, 340, 0);
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 370 && list11->pHead->pNext->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext->pNext == nullptr);
    // testcase 2
    removePos(list11, 370, 2);
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext == nullptr);
    // testcase 3
    removePos(list11, 350, 5); // Positions out of range
    assert(list11->pHead->key == 350 && list11->pTail->key == 380);
    assert(list11->pHead->pNext->key == 360 && list11->pHead->pNext->pNext->key == 380);
    assert(list11->pHead->pNext->pNext->pNext == nullptr);
    // free memory
    freeList(list11);
    std::cout << "Passed" << std::endl;

    // Test case 12: addBefore /////////////////////////////////////////////////////////
    std::cout << "Test addBefore: ";
    int arr12[4] = {390, 400, 410, 420};
    d_List *list12 = createListFromArray(arr12, 4);
    assert(list12->pHead->key == 390 && list12->pTail->key == 420);
    // testcase 1
    addBefore(list12, 380, 400);
    int arr12_1[5] = {390, 380, 400, 410, 420};
    d_List *expectedList12_1 = createListFromArray(arr12_1, 5);
    assert(areListsEqual(list12, expectedList12_1));
    // testcase 2
    addBefore(list12, 370, 390);
    int arr12_2[6] = {370, 390, 380, 400, 410, 420};
    d_List *expectedList12_2 = createListFromArray(arr12_2, 6);
    assert(areListsEqual(list12, expectedList12_2));
    // testcase 3
    addBefore(list12, 360, 350); // Don't have any element before
    int arr12_3[6] = {370, 390, 380, 400, 410, 420};
    d_List *expectedList12_3 = createListFromArray(arr12_3, 6);
    assert(areListsEqual(list12, expectedList12_3));
    // free memory
    freeList(list12);
    freeList(expectedList12_1);
    freeList(expectedList12_2);
    freeList(expectedList12_3);
    std::cout << "Passed" << std::endl;

    // Test case 13: addAfter /////////////////////////////////////////////////////////
    std::cout << "Test addAfter: ";
    int arr13[4] = {430, 440, 450, 460};
    d_List *list13 = createListFromArray(arr13, 4);
    assert(list13->pHead->key == 430 && list13->pTail->key == 460);
    // testcase 1
    addAfter(list13, 470, 440);
    int arr13_1[5] = {430, 440, 470, 450, 460};
    d_List *expectedList13_1 = createListFromArray(arr13_1, 5);
    assert(areListsEqual(list13, expectedList13_1));
    // testcase 2
    addAfter(list13, 480, 460);
    int arr13_2[6] = {430, 440, 470, 450, 460, 480};
    d_List *expectedList13_2 = createListFromArray(arr13_2, 6);
    assert(areListsEqual(list13, expectedList13_2));
    // testcase 3
    addAfter(list13, 490, 200); // Don't have any element after
    int arr13_3[6] = {430, 440, 470, 450, 460, 480};
    d_List *expectedList13_3 = createListFromArray(arr13_3, 6);
    assert(areListsEqual(list13, expectedList13_3));
    // free memory
    freeList(expectedList13_1);
    freeList(expectedList13_2);
    freeList(expectedList13_3);
    freeList(list13);
    std::cout << "Passed" << std::endl;

    // Test case 14: printList /////////////////////////////////////////////////////////
    std::cout << "Test printList: "; // Don't need to assert anything
    std::cout << "Passed" << std::endl;

    // Test case 15: countElements /////////////////////////////////////////////////////////
    std::cout << "Test countElements: ";
    // Test case 1
    int arr15[5] = {500, 510, 520, 530, 540};
    d_List *list15 = createListFromArray(arr15, 5);
    assert(countElements(list15) == 5);
    // Test case 2
    int arr15_2[3] = {550, 560, 570};
    d_List *list15_2 = createListFromArray(arr15_2, 3);
    assert(countElements(list15_2) == 3);
    // Test case 3
    int arr15_3[1] = {580};
    d_List *list15_3 = createListFromArray(arr15_3, 1);
    assert(countElements(list15_3) == 1);
    // Test case 4
    d_List *emptyList15 = new d_List();
    assert(countElements(emptyList15) == 0);
    // free memory
    freeList(list15);
    freeList(list15_2);
    freeList(list15_3);
    freeList(emptyList15);
    std::cout << "Passed" << std::endl;

    // Test case 16: reverseList /////////////////////////////////////////////////////////
    std::cout << "Test reverseList: ";
    // Test case 1
    int arr16[5] = {590, 600, 610, 620, 630};
    d_List *list16 = createListFromArray(arr16, 5);
    d_List *reversedList16 = reverseList(list16);
    int expectedArr16[5] = {630, 620, 610, 600, 590};
    d_List *expectedList16 = createListFromArray(expectedArr16, 5);
    assert(areListsEqual(reversedList16, expectedList16));
    // Test case 2
    int arr16_2[3] = {640, 650, 660};
    d_List *list16_2 = createListFromArray(arr16_2, 3);
    d_List *reversedList16_2 = reverseList(list16_2);
    int expectedArr16_2[3] = {660, 650, 640};
    d_List *expectedList16_2 = createListFromArray(expectedArr16_2, 3);
    assert(areListsEqual(reversedList16_2, expectedList16_2));
    // Test case 3
    int arr16_3[1] = {670};
    d_List *list16_3 = createListFromArray(arr16_3, 1);
    d_List *reversedList16_3 = reverseList(list16_3);
    int expectedArr16_3[1] = {670};
    d_List *expectedList16_3 = createListFromArray(expectedArr16_3, 1);
    assert(areListsEqual(reversedList16_3, expectedList16_3));
    // Test case 4
    d_List *emptyList16 = new d_List();
    d_List *reversedList16_4 = reverseList(emptyList16);
    assert(reversedList16_4->pHead == nullptr && reversedList16_4->pTail == nullptr);
    // free memory
    freeList(expectedList16);
    freeList(expectedList16_2);
    freeList(expectedList16_3);
    freeList(reversedList16);
    freeList(reversedList16_2);
    freeList(reversedList16_3);
    freeList(reversedList16_4);
    freeList(list16);
    freeList(list16_2);
    freeList(list16_3);
    freeList(emptyList16);
    std::cout << "Passed" << std::endl;

    // Test case 17: removeDuplicate /////////////////////////////////////////////////////////
    std::cout << "Test removeDuplicate: ";
    // Test case 1
    int arr17[6] = {680, 690, 690, 700, 710, 710};
    d_List *list17 = createListFromArray(arr17, 6);
    removeDuplicate(list17);
    int expectedArr17[4] = {680, 690, 700, 710};
    d_List *expectedList17 = createListFromArray(expectedArr17, 4);
    assert(areListsEqual(list17, expectedList17));
    // Test case 2
    int arr17_2[5] = {720, 730, 740, 740, 740};
    d_List *list17_2 = createListFromArray(arr17_2, 5);
    removeDuplicate(list17_2);
    int expectedArr17_2[3] = {720, 730, 740};
    d_List *expectedList17_2 = createListFromArray(expectedArr17_2, 3);
    assert(areListsEqual(list17_2, expectedList17_2));
    // Test case 3
    int arr17_3[4] = {750, 760, 760, 770};
    d_List *list17_3 = createListFromArray(arr17_3, 4);
    removeDuplicate(list17_3);
    int expectedArr17_3[3] = {750, 760, 770};
    d_List *expectedList17_3 = createListFromArray(expectedArr17_3, 3);
    assert(areListsEqual(list17_3, expectedList17_3));
    // Test case 4
    int arr17_4[2] = {780, 780};
    d_List *list17_4 = createListFromArray(arr17_4, 2);
    removeDuplicate(list17_4);
    int expectedArr17_4[1] = {780};
    d_List *expectedList17_4 = createListFromArray(expectedArr17_4, 1);
    assert(areListsEqual(list17_4, expectedList17_4));
    // Test case 5
    int arr17_5[1] = {790};
    d_List *list17_5 = createListFromArray(arr17_5, 1);
    removeDuplicate(list17_5);
    int expectedArr17_5[1] = {790};
    d_List *expectedList17_5 = createListFromArray(expectedArr17_5, 1);
    assert(areListsEqual(list17_5, expectedList17_5));
    // Test case 6
    d_List *emptyList17 = new d_List();
    removeDuplicate(emptyList17);
    assert(emptyList17->pHead == nullptr && emptyList17->pTail == nullptr);
    // free memory
    freeList(expectedList17);
    freeList(expectedList17_2);
    freeList(expectedList17_3);
    freeList(expectedList17_4);
    freeList(expectedList17_5);
    freeList(list17);
    freeList(list17_2);
    freeList(list17_3);
    freeList(list17_4);
    freeList(list17_5);
    freeList(emptyList17);
    std::cout << "Passed" << std::endl;

    // Test case 18: removeElement /////////////////////////////////////////////////////////
    std::cout << "Test removeElement: ";
    // Test case 1
    int arr18[5] = {800, 810, 820, 830, 840};
    d_List *list18 = createListFromArray(arr18, 5);
    assert(removeElement(list18, 820));
    int expectedArr18[4] = {800, 810, 830, 840};
    d_List *expectedList18 = createListFromArray(expectedArr18, 4);
    assert(areListsEqual(list18, expectedList18));
    // Test case 2
    int arr18_2[3] = {850, 860, 870};
    d_List *list18_2 = createListFromArray(arr18_2, 3);
    assert(removeElement(list18_2, 850));
    int expectedArr18_2[2] = {860, 870};
    d_List *expectedList18_2 = createListFromArray(expectedArr18_2, 2);
    assert(areListsEqual(list18_2, expectedList18_2));
    // Test case 3
    int arr18_3[4] = {880, 890, 900, 910};
    d_List *list18_3 = createListFromArray(arr18_3, 4);
    assert(removeElement(list18_3, 910));
    int expectedArr18_3[3] = {880, 890, 900};
    d_List *expectedList18_3 = createListFromArray(expectedArr18_3, 3);
    assert(areListsEqual(list18_3, expectedList18_3));
    // Test case 4
    int arr18_4[2] = {920, 930};
    d_List *list18_4 = createListFromArray(arr18_4, 2);
    assert(removeElement(list18_4, 920));
    int expectedArr18_4[1] = {930};
    d_List *expectedList18_4 = createListFromArray(expectedArr18_4, 1);
    assert(areListsEqual(list18_4, expectedList18_4));
    // Test case 5
    int arr18_5[1] = {940};
    d_List *list18_5 = createListFromArray(arr18_5, 1);
    assert(removeElement(list18_5, 940));
    int expectedArr18_5[0] = {};
    d_List *expectedList18_5 = createListFromArray(expectedArr18_5, 0);
    assert(areListsEqual(list18_5, expectedList18_5));
    // Test case 6
    d_List *emptyList18 = new d_List();
    assert(!removeElement(emptyList18, 950)); // Remove from empty list
    assert(emptyList18->pHead == nullptr && emptyList18->pTail == nullptr);
    // free memory
    freeList(expectedList18);
    freeList(expectedList18_2);
    freeList(expectedList18_3);
    freeList(expectedList18_4);
    freeList(expectedList18_5);
    freeList(list18);
    freeList(list18_2);
    freeList(list18_3);
    freeList(list18_4);
    freeList(list18_5);
    freeList(emptyList18);
    std::cout << "Passed" << std::endl;
    std::cout << "--- End running test cases ---" << std::endl;
    return 0;
}