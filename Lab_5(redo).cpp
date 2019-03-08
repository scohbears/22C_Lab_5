#include <iostream>
#include <cmath>
#include <queue>
#include <iomanip>

using namespace std;

template <typename T>
class TreeNode {
public:
	TreeNode(T x) {
		this->data = x;
		left = NULL;
		right = NULL;
	}
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
};
template <typename T>
class BinarySearchTree {
public:
	BinarySearchTree() { root = NULL; root_tree = NULL; current_root = NULL;}
	TreeNode<T>* root;
	TreeNode<T>* root_tree;
	TreeNode<T>* current_root;
    TreeNode<T>* insert(T x) {
        TreeNode<T>* cur_node = this->root;
        cout << "\n-->insert: " << x << endl;
        if (this->root == NULL) {
          this->root = new TreeNode<T>(x);
          return this->root;
        }
        while (cur_node != NULL) {
          if (x < cur_node->data) {
            if (cur_node->left == NULL) {
              cur_node->left = new TreeNode<T>(x);
              break;
            } else {
              cur_node = cur_node->left;
            }
          } else {
            if (cur_node->right == NULL) {
              cur_node->right = new TreeNode<T>(x);
              break;
            } else {
              cur_node = cur_node->right;
            }
          }
        }
        return this->root;
    }
  	void print_node(TreeNode<T>* node) {
		if (node) {
			if (node->right)
				cout << "\t\t\t->right: " << node->right->data << endl;
			else
				cout << "\t\t\t->right: null" << endl;
			cout << "\t\tNode: " << node->data << endl;
			if (node->left)
				cout << "\t\t\t->left: " << node->left->data << endl;
			else
				cout << "\t\t\t->left: null" << endl;
		}
	}
	// rr rotation for first while loop in balancing tree
	TreeNode<T>* rr_rotation_i(TreeNode<T>* parent) {
		cout << "entering rr_rotation" << endl;
		print_node(parent);
		TreeNode<T>* temp = parent->right;
		parent->right = temp->left;
		temp->left = parent;
		cout << "exiting  rr_rotation" << endl;
		root = temp;
		print_node(temp);
		return temp;
	}
	// rr rotation for second while loop in balancing tree
	TreeNode<T>* rr_rotation_j(TreeNode<T>* parent) {
		cout << "entering rr_rotation" << endl;
		print_node(parent);
		TreeNode<T>* temp = parent->right;
		parent->right = temp->left;
		temp->left = parent;
		cout << "exiting  rr_rotation" << endl;
		current_root = temp;
		print_node(temp);
		return temp;
	}
	void balancingTree (int n) {
		int m = (pow(2,floor(log2(n+1)))-1);
		int i = 0;
		int j = 0;
		TreeNode<T>* i_root;
		TreeNode<T>* j_root;
		rr_rotation_i(root);
		root_tree = root;
		i_root = root_tree;
		while(i+1 < (n-m)) {
			rr_rotation_i(root->right);
			i_root->right = root;
			i_root = root;
			current_root = root;
			i++;
		}
		while(m > 1) {
			m = m/2;
			rr_rotation_j(root_tree);
			root_tree = current_root;
			j_root = root_tree;
			while(j+1 < m) {
				rr_rotation_j(current_root->right);
				j_root->right = current_root;
				j_root = current_root;
				j++;
			}
			j = 0;
		}
		cout << "Root of tree is "<< root_tree->data << endl;
		printArray(root_tree);
	}
	void printArray(TreeNode<T>* x) {
    TreeNode<int>* cur_node = root;
    if(cur_node == NULL) {
        return;
    }
    queue<TreeNode<T>*> q;
    q.push(x);
    while(q.empty() == false) {
        int nodeCount = q.size();
        while(nodeCount > 0) {
            TreeNode<int>* node = q.front();
            cout << node->data << " ";
            q.pop();
            if(node->left != NULL) {
                q.push(node->left);
            }
            if(node->right != NULL) {
                q.push(node->right);
            }
            nodeCount--;
        }
        cout << endl;
    }
  }
};
int main() {
	int count = 0;
	int arr[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	for(int i = 0; i < (sizeof(arr)/sizeof(*arr)); i++) {
		count ++;
	}
	cout << count << " is counted! " <<endl;
	BinarySearchTree<int> bst;
	TreeNode<int>* root = bst.insert(arr[0]);
	for(int i = 1; i < (sizeof(arr)/sizeof(*arr)); i++) {
		bst.insert(arr[i]);
	}
	bst.balancingTree(count);
	return 0;
}

