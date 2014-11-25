#include <climits> // for INT_MIN
#include <cmath>
#include <iostream>
using namespace std;

/***************************************************************************
 * NODE
 **************************************************************************/
class Node
{
private:
   int mValue;
   Node* mLeft;
   Node* mRight;
   Node *mParent;
public:
   Node(int inValue) { mValue = inValue; mLeft = NULL; mRight = NULL; }
   int getValue() { return mValue; }
   Node* getLeft() { return mLeft; }
   void setLeft(Node* inLeft) { mLeft = inLeft; }
   Node* getRight() { return mRight; }
   void setRight(Node* inRight) { mRight = inRight; }
   void setValue(int value) { mValue = value; }
   void setParent(Node* pParent) { mParent = pParent; }
   Node* getParent() { return mParent; };
};

ostream& operator<<(ostream& os, Node* node)
{
   if (node != NULL)
   {
      os << node->getValue() << " ";
      os << node->getLeft();
      os << node->getRight();
   }
   return os;
}

/***************************************************************************
 * TREE
 **************************************************************************/
class Tree
{
private:
   static int cNextNodeNumber;
   int mHeight;
   Node* mRoot;
   int* array;
   int size;
   int currentValue;

   Node* buildTree(int height)
   {
      Node* root = new Node(cNextNodeNumber++);
      if (height > 0)
      {
         root->setLeft(buildTree(height - 1));
         root->getLeft()->setParent(root);
         root->setRight(buildTree(height - 1));
         root->getRight()->setParent(root);
      }
      return root;
   }

public:
   Tree(int height, int array[], int size)
   {
      mHeight = height;
      mRoot = buildTree(height);
      this->array = array;
      this->size = size;
      currentValue = 0;
   }
   Node* getRoot() { return mRoot; }

   void traversePreorder()
   {
      traverse(mRoot, -1);
   }

   void traverseInorder()
   {
      traverse(mRoot, 0);
   }

   void traversePostorder()
   {
      traverse(mRoot, 1);
   }

   void traverse(Node* node, int tType)
   {
      if (node == NULL) return;
      if (tType == -1)
      {
         visit(node);
      }
      traverse(node->getLeft(), tType);
      if (tType == 0)
      {
         visit(node);
      }
      traverse(node->getRight(), tType);
      if (tType == 1)
      {
         visit(node);
      }
   }

   void visit(Node* node)
   {
      // Check if node is a leaf
      if (node->getLeft() == NULL && node->getRight() == NULL)
      {
         // Insert next value
         node->setValue(array[currentValue++]);
      }
      else
      {
         // Compare children
         if (node->getLeft()->getValue() > node->getRight()->getValue())
         {
            node->setValue(node->getLeft()->getValue());
         }
         else
         {
            node->setValue(node->getRight()->getValue());
         }
      }
   }

   void traverseLevel1()
   {
      const int MAX = 128;
      Node* queue[MAX];
      Node* temp;
      int front = 0;
      int back = 0;
      queue[back++] = mRoot;
      while (front != back)
      {
         temp = queue[front];
         front = (front + 1) % MAX;
         if (temp != NULL)
         {
            cout << temp->getValue() << " ";
            queue[back] = temp->getLeft();
            back = (back + 1) % MAX;
            queue[back] = temp->getRight();
            back = (back + 1) % MAX;
         }
      }
   }

   void traverseLevel2()
   {
      for (int level = 0; level <= mHeight; level++)
      {
         int maxWhich = (int) pow((double) 2, (double) level);
         for (int which = 1; which <= maxWhich; which++)
         {
            visit(findNode(mRoot, level, which));
         }
      }
   }

   Node* findNode(Node* start, int level, int which)
   {
      int maxWhich = (int) pow((double) 2, (double) level);
      int halfway = maxWhich / 2;
      if (level == 0)
         return start;
      else
      {
         if (which <= halfway && which != 0)
         {
            findNode(start->getLeft(), level - 1, which % halfway);
         }
         else
         {
            findNode(start->getRight(), level - 1, which % halfway);
         }
      }
   }
};

ostream& operator<<(ostream& os, Tree& tree)
{
   os << tree.getRoot();
   return os;
}

int Tree::cNextNodeNumber = 0;

void tournamentSort(int array[], int & size)
{
   // Build the tree
   Tree tree((log(size)/log(2)), array, size);
   tree.traversePostorder();

   for (int i = 0; i < size; ++i)
   {
      array[i] = tree.getRoot()->getValue();

      // make a pointer variable to check for equality
      Node* traverse;

      for (traverse = tree.getRoot(); traverse->getRight() != NULL
              && traverse->getLeft() != NULL; )
      {
         // checks against all of the numbers in the tree
         if (traverse->getLeft()->getValue() == traverse->getValue())
         {
            traverse = traverse->getLeft();
         }
         else
         {
            traverse = traverse->getRight();
         }
      }
      traverse->setValue(-1);

      do
      {
         traverse = traverse->getParent();

         if (traverse->getRight()->getValue() <
             traverse->getLeft()->getValue())
         {
            traverse->setValue(traverse->getLeft()->getValue());
         }
         else
         {
            traverse->setValue(traverse->getRight()->getValue());
         }
      }
      while (traverse != tree.getRoot());
   }
}

// your tournamentSort function definition goes here
// DO NOT CHANGE anything below this line!
int main()
{
   int array[] = {15, 6, 2, 9, 8, 0, 3, 1, 5, 4, 7, 13, 10, 11, 12, 14};
   int size = sizeof(array) / sizeof(int);
   tournamentSort(array, size);
   for (int i = 0; i < size; i++)
   {
      cout << array[i] << " ";
   }
   cout << endl;
   return 0;
}
