#include<iostream>

class SingleNode {
public:
    int data;
    SingleNode *nextPtr;
    SingleNode();
    ~SingleNode();
};

SingleNode::SingleNode()
{
    this->data = 0;
    this->nextPtr = nullptr;
}

SingleNode::~SingleNode()
{
    std::cout << "Node :" << this->data << " is being destroyed" << std::endl;
    nextPtr == nullptr;
}

class SinglyLinkedList {
private:
      //data members
      static SinglyLinkedList* objPtr;
      SingleNode *headPtr;
      SingleNode *tailPtr;

      //member function
      SinglyLinkedList();
      SinglyLinkedList(const SinglyLinkedList &obj)=default;
      SinglyLinkedList* operator=(const SinglyLinkedList &obj){};
    public:
        static SinglyLinkedList* getObj();
        SingleNode* createNode();
        int insertNode(int data);
        int deleteNode(int data);
        void printLinkedList();
        void destroyNodes();
        ~SinglyLinkedList();
        
};

SinglyLinkedList* SinglyLinkedList::objPtr = nullptr;

SinglyLinkedList::SinglyLinkedList()
{
    this->headPtr == nullptr;
    this->tailPtr == nullptr;
}

SinglyLinkedList::~SinglyLinkedList()
{
    destroyNodes();
    this->headPtr = nullptr;
    this->tailPtr = nullptr;
}

void SinglyLinkedList::destroyNodes()
{
    //This is to avoid memory leak
    SingleNode *currNode = this->headPtr;
    SingleNode *tmpNode = nullptr;
    while(currNode != nullptr)
    {
        tmpNode = currNode;
        currNode = currNode->nextPtr;
        delete tmpNode;
    }

}
SinglyLinkedList* SinglyLinkedList::getObj()
{
     
    if(objPtr == nullptr)
    {
        objPtr = new SinglyLinkedList();
    }

    return (objPtr);
}

SingleNode* SinglyLinkedList::createNode()
{
    return(new SingleNode());
}

int SinglyLinkedList::insertNode(int data)
{
    SingleNode *node = createNode();
    if(node)
    {
        node->data = data;
    }    

    if(headPtr == nullptr)
    {
        headPtr = node;
        tailPtr = node;
    }
    else
    {
        tailPtr->nextPtr = node;
        tailPtr = node;
    }
}


int SinglyLinkedList::deleteNode(int data)
{
    SingleNode* currNode = headPtr;
    SingleNode* prevNode = nullptr;
    while(currNode != nullptr)
    {
        if(currNode->data == data)
        {
            if(currNode == headPtr)
            {
                if(headPtr == tailPtr)
                {
                    headPtr = currNode->nextPtr;
                    tailPtr = headPtr;
                }
                else
                {
                    headPtr = currNode->nextPtr;
                }
            }
            else
            {
                prevNode->nextPtr = currNode->nextPtr ;
                if(currNode == tailPtr)
                {
                    tailPtr = prevNode;
                }
            }
            delete currNode;
            break;   
        }
        prevNode = currNode;
        currNode = currNode->nextPtr;
    }
}

void SinglyLinkedList::printLinkedList()
{
    SingleNode *currNode = headPtr;
    int nodeCounter = 0;
    while(currNode)
    {
        nodeCounter++;
        std::cout << "Node: " << nodeCounter << "Data :" << currNode->data << std::endl;
        currNode = currNode->nextPtr;
    }
}

void createSingleLinkedList();
int main()
{
    int choice;

    std::cout << "Pls select your option: " << std::endl;
    std::cout << "1:Create Singly Linked List " << std::endl;
    std::cout << "0:Exit " << std::endl;
    std::cin >> choice ;
    switch(choice) {
    case 1:
          createSingleLinkedList();
          break;
    case 0:
          break;
    default:
          break;      
    }
    return 0;
}


void createSingleLinkedList()
{
    SinglyLinkedList *obj = SinglyLinkedList::getObj();

    if(!obj)
    {
        std::cout << "failed to create singly linked list obj" << std::endl;
    }
    int choice;
    int data;
    bool continueLoop = true;
    while(continueLoop)
    {
    std::cout << "Pls select your option: " << std::endl;
    std::cout << "1:Insert element " << std::endl;
    std::cout << "2:Delete element " << std::endl;
    std::cout << "3:Print Linked List " << std::endl;
    std::cout << "0:Exit " << std::endl;
    std::cin >> choice ;
    switch(choice) {
    case 1:
          std::cout <<"Enter Data" <<std::endl;
          std::cin >> data;
          obj->insertNode(data) ;
          break;
    case 2:
          std::cout <<"Enter Data" <<std::endl;
          std::cin >> data;
          obj->deleteNode(data) ;
          break;
    case 3:
          obj->printLinkedList();
          break;
    case 0:
        continueLoop = false;
         break;
    default:
          continueLoop = false;
          break;      
    }
    }
    delete(obj) ;
}