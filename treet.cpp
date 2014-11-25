#include <cmath>
#include <iostream>
using namespace std;
class Node
{
private:
   int mValue;
   Node* mLeft;
   Node* mRight;
public:
   Node(int inValue) { mValue = inValue; mLeft = NULL; mRight = NULL; }
   int getValue() { return mValue; }
   Node* getLeft() { return mLeft; }
   void setLeft(Node* inLeft) { mLeft = inLeft; }
   Node* getRight() { return mRight; }
   void setRight(Node* inRight) { mRight = inRight; }
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
class Tree
{
private:
   static int cNextNodeNumber;
   int mHeight;
   Node* mRoot;
   Node* buildTree(int height)
   {
      Node* root = new Node(cNextNodeNumber++);
      if (height > 0)
      {
         root->setLeft(buildTree(height - 1));
         root->setRight(buildTree(height - 1));
      }
      return root;
   }
public:
   Tree(int height)
   {
      mHeight = height;
      mRoot = buildTree(height);
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
      cout << node->getValue() << " ";
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
main()
{
   Tree tree(3);
   cout << tree << endl;
   tree.traversePreorder();
   cout << endl;
   tree.traverseInorder();
   cout << endl;
   tree.traversePostorder();
   cout << endl;
   tree.traverseLevel1();
   cout << endl;
   tree.traverseLevel2();
   cout << endl;
}
