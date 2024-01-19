#include <iostream>
#include <string>
using namespace std;
template <class T>
class treeNode
{
public:
    treeNode<T> *left;
    treeNode<T> *right;
    T val;
    int height;
    int freq;
    int lcount;
    int rcount;
    treeNode(T val)
    {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
        this->freq = 1;
        this->lcount = 0;
        this->rcount = 0;
    }
};

template <class T>
class AVL
{
    treeNode<T> *root = NULL;

public:
    void insert(T val)
    {
        treeNode<T> *node = new treeNode(val);
        insert_node(&root, node);
    }
    int count_left_right_nodes(treeNode<T> *node)
    {
        if (node)
            return node->lcount + node->rcount + node->freq;
        return 0;
    }
    void _delete(T val)
    {
        treeNode<T> *node = new treeNode(val);
        deleteNode(&root, node);
        delete node;
    }
    int count_occurence(T val)
    {
        treeNode<T> *node = new treeNode(val);
        int count = 0;

        treeNode<T> *temp = find(root, node);
        delete node;
        if (!temp)
            return T();

        return temp->freq;
    }

    treeNode<T> *minValueNode(treeNode<T> *node)
    {
        treeNode<T> *temp = node;

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }
    treeNode<T> *maxValueNode(treeNode<T> *node)
    {
        treeNode<T> *temp = node;

        while (temp->right != NULL)
            temp = temp->right;

        return temp;
    }
    bool leaf(treeNode<T> *root)
    {
        if (root == NULL)
        {
            return false;
        }
        if (root->left == NULL && root->right == NULL)
            return true;
        return false;
    }
    void deleteNode(treeNode<T> **root, treeNode<T> *node)
    {

        if (*root == NULL)
            return;
        else
        {
            int cmpr = AVL::cmprtr(*root, node);
            if (cmpr == 1)
            {
                deleteNode(&((*root)->left), node);
            }
            else if (cmpr == -1)
            {
                deleteNode(&((*root)->right), node);
            }
            else
            {

                if (((*root)->left == NULL) ||
                    ((*root)->right == NULL))
                {
                    treeNode<T> *temp;
                    if ((*root)->left)
                    {
                        temp = (*root)->left;
                        (*root)->left = NULL;
                    }
                    else
                    {
                        temp = (*root)->right;
                        (*root)->right = NULL;
                    };

                    if (temp == NULL)
                    {
                        temp = *root;
                        *root = NULL;
                    }
                    else
                        *root = temp;
                    temp = NULL;
                    delete temp;
                }
                else
                {
                    treeNode<T> *temp = minValueNode((*root)->right);
                    (*root)->val = temp->val;
                    (*root)->freq = temp->freq;

                    deleteNode(&((*root)->right), temp);
                }
            }
        }

        if ((*root) == NULL)
            return;
        (*root)->lcount = count_left_right_nodes((*root)->left);
        (*root)->rcount = count_left_right_nodes((*root)->right);
        (*root)->height = 1 + max(height((*root)->left), height((*root)->right));
        int balance_factor = getbalanceFactor(*root);
        if (balance_factor > 1)
        {
            if (AVL::cmprtr(node, (*root)->left)==-1)
                right(root);
            else if (AVL::cmprtr(node, (*root)->right)==1)
            {
                left(&((*root)->left));
                right(root);
            }
        }
        if (balance_factor < -1)
        {   
            if (AVL::cmprtr(node, (*root)->right)==1)
                left(root);
            else if (AVL::cmprtr(node, (*root)->right)==-1)
            {
                right(&((*root)->right));
                left(root);
            }
        }
        
    }
    int height(treeNode<T> *node)
    {
        if (node != nullptr)
            return node->height;
        return 0;
    }
    T closest_lower(T val)
    {
        treeNode<T> *node = new treeNode(val);
        treeNode<T> *v = get_lower_bound(root, node);
        delete node;
        if (v)
            return v->val;
        return maxValueNode(root)->val;
    }
    T lower_bound(T val)
    {
        treeNode<T> *node = new treeNode(val);
        treeNode<T> *v = get_lower_bound(root, node);
        delete node;
        if (v)
            return v->val;
        return T();
    }
    treeNode<T> *get_lower_bound(treeNode<T> *root, treeNode<T> *node)
    {
        if (root == NULL)
            return NULL;
        int cmpr = AVL::cmprtr(root, node);
        if (cmpr == 0)
        {
            return root;
        }
        if (cmpr == -1)
        {
            return get_lower_bound(root->right, node);
        }
        treeNode<T> *temp = get_lower_bound(root->left, node);
        if (temp && AVL::cmprtr(temp, node) > -1)
            return temp;
        return root;
    }
    T closest_next(T val)
    {
        treeNode<T> *node = new treeNode(val);
        treeNode<T> *v = get_closest_next(root, node);
        delete node;
        if (v)
            return v->val;
        return minValueNode(root)->val;
    }
    treeNode<T> *closest_next(T val, treeNode<T> *root)
    {
        treeNode<T> *node = new treeNode(val);
        treeNode<T> *v = get_closest_next(root, node);
        delete node;
        if (v)
            return v;
        return minValueNode(root);
    }
    treeNode<T> *get_closest_next(treeNode<T> *root, treeNode<T> *node)
    {
        if (root == NULL)
            return NULL;
        int cmpr = AVL::cmprtr(root, node);
        if (cmpr == 0)
        {
            return root;
        }
        if (cmpr == -1)
        {
            return get_closest_next(root->right, node);
        }
        treeNode<T> *temp = get_closest_next(root->left, node);
        if (temp && AVL::cmprtr(temp, node) > -1)
            return temp;
        return root;
    }
    T closest_element(T val)
    {

        T v1 = smallest_prev(val);
        T v2 = closest_next(val);
        T diff_u = abs(val - v1);
        T diff_l = abs(val - v2);

        if (diff_l > diff_u)
        {
            return v1;
        }
        return v2;
    }
    T upper_bound(T val)
    {
        treeNode<T> *node = new treeNode(val);
        treeNode<T> *v = get_upper_bound(root, node);
        delete node;
        if (v)
            return v->val;
        return 0;
    }
    treeNode<T> *get_upper_bound(treeNode<T> *root, treeNode<T> *node)
    {
        if (root == NULL)
            return NULL;
        int cmpr = AVL::cmprtr(root, node);

        if (cmpr < 1)
        {
            return get_upper_bound(root->right, node);
        }
        treeNode<T> *temp = get_upper_bound(root->left, node);
        if (temp && AVL::cmprtr(temp, node) > -1)
            return temp;
        return root;
    }
    T smallest_prev(T val)
    {
        treeNode<T> *node = new treeNode(val);
        treeNode<T> *v = get_smallest_prev(root, node);
        delete node;
        if (v)
            return v->val;
        return minValueNode(root)->val;
    }
    treeNode<T> *smallest_prev(T val, treeNode<T> *root)
    {
        treeNode<T> *node = new treeNode(val);
        treeNode<T> *v = get_smallest_prev(root, node);
        delete node;
        if (v)
            return v;
        return minValueNode(root);
    }
    treeNode<T> *common_Ancestor(treeNode<T> *root, T left, T right)
    {
        if (root == NULL)
            return NULL;
        T val = root->val;
        // Your code here
        int left_cmpr = AVL::cmprtr(val, left);
        int right_cmpr = AVL::cmprtr(val, right);
        if (left_cmpr == 0 || right_cmpr == 0)
        {
            return root;
        }
        if (left_cmpr == 1 && right_cmpr == -1 || left_cmpr == -1 && right_cmpr == 1)
        {
            return root;
        }
        else if (left_cmpr == -1 && right_cmpr == -1)
        {
            return common_Ancestor(root->right, left, right);
        }
        else if (left_cmpr == 1 && right_cmpr == 1)
        {
            return common_Ancestor(root->left, left, right);
        }

        return NULL;
    }
    treeNode<T> *get_smallest_prev(treeNode<T> *root, treeNode<T> *node)
    {
        if (root == NULL)
            return NULL;
        int cmpr = AVL::cmprtr(root, node);
        if (cmpr == 0)
        {
            return root;
        }
        if (cmpr == 1)
        {
            return get_smallest_prev(root->left, node);
        }
        treeNode<T> *temp = get_smallest_prev(root->right, node);

        if (temp && AVL::cmprtr(temp, node) < 1)
            return temp;
        return root;
    }
    int getbalanceFactor(treeNode<T> *node)
    {
        if (node)
            return height(node->left) - height(node->right);
        return 0;
    }
    T Kth_largest(int k)
    {
        treeNode<T> *temp = NULL;
        KLargestElement(root, 0, k, &temp);
        if (temp)
            return temp->val;
        return 0;
    }
    void KLargestElement(treeNode<T> *root, int smaller_nodes, int k, treeNode<T> **temp)
    {
        if (root == NULL)
            return;
        if (root->lcount + smaller_nodes < k)
        {
            if (root->lcount + root->freq + smaller_nodes >= k)
            {
                *temp = root;
                return;
            }
            else
            {
                KLargestElement(root->right, smaller_nodes + root->lcount + root->freq, k, temp);
            }
        }
        else
        {
            KLargestElement(root->left, smaller_nodes, k, temp);
        }
    }
    void findElementIndex(treeNode<T> *root, int smaller_nodes, treeNode<T> *node, int *kindex)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            int cmpr = AVL::cmprtr(root, node);
            if (cmpr == 1)
            {
                findElementIndex(root->left, smaller_nodes, node, kindex);
            }
            else if (cmpr == -1)
            {
                findElementIndex(root->right, smaller_nodes + root->lcount + root->freq, node, kindex);
            }
            else
            {
                *kindex = smaller_nodes + root->lcount;
            }
        }
    }
    bool search(T val)
    {
        treeNode<T> *node = new treeNode(val);
        if (find(root, node))
        {
            delete node;
            return true;
        }

        delete node;
        return false;
    }
    void inorder()
    {
        inorder(root);
    }
    void inorder(treeNode<T> *root)
    {
        if (root == NULL)
            return;
        inorder(root->left);

        for (int i = 0; i < root->freq; i++)
            cout << root->val << " ";
        inorder(root->right);
    }
    void preorder()
    {
        preorder(root);
    }
    void preorder(treeNode<T> *root)
    {
        if (root == NULL)
            return;
        for (int i = 0; i < root->freq; i++)
            cout << root->val << " ";
        inorder(root->left);
        inorder(root->right);
    }
    void postorder()
    {
        postorder(root);
    }
    void postorder(treeNode<T> *root)
    {
        if (root == NULL)
            return;

        inorder(root->left);
        inorder(root->right);
        for (int i = 0; i < root->freq; i++)
            cout << root->val << " ";
    }
    treeNode<T> *find(treeNode<T> *root, treeNode<T> *node)
    {
        if (root == NULL)
        {
            return NULL;
        }
        int cmpr = AVL::cmprtr(root, node);
        if (cmpr == 1)
        {
            return find(root->left, node);
        }
        else if (cmpr == -1)
        {
            return find(root->right, node);
        }
        return root;
    }

    void right(treeNode<T> **y)
    {
        treeNode<T> *prev_root = *y;
        treeNode<T> *x = (*y)->left;

        treeNode<T> *temp = x->right;

        x->right = *y;
        (*y)->left = temp;

        (*y)->height = max(height((*y)->left),
                           height((*y)->right)) +
                       1;
        x->height = max(height(x->left),
                        height(x->right)) +
                    1;

        (*y)->lcount = count_left_right_nodes((*y)->left);
        (*y)->rcount = count_left_right_nodes((*y)->right);
        if (temp)
        {
            temp->lcount = count_left_right_nodes(temp->left);
            temp->rcount = count_left_right_nodes(temp->right);
        }
        x->lcount = count_left_right_nodes(x->left);
        x->rcount = count_left_right_nodes(x->right);
        *y = x;
    }
    void left(treeNode<T> **y)
    {

        treeNode<T> *x = (*y)->right;
        treeNode<T> *temp = x->left;

        x->left = (*y);
        (*y)->right = temp;

        (*y)->height = max(height((*y)->left),
                           height((*y)->right)) +
                       1;
        x->height = max(height(x->left),
                        height(x->right)) +
                    1;
        (*y)->lcount = count_left_right_nodes((*y)->left);
        (*y)->rcount = count_left_right_nodes((*y)->right);
        if (temp)
        {
            temp->lcount = count_left_right_nodes(temp->left);
            temp->rcount = count_left_right_nodes(temp->right);
        }
        x->lcount = count_left_right_nodes(x->left);
        x->rcount = count_left_right_nodes(x->right);
        *y = x;
    }

    void insert_node(treeNode<T> **root, treeNode<T> *node)
    {
        if (*root == NULL)
        {
            *root = node;
        }
        else
        {
            int cmpr = AVL::cmprtr(*root, node);
            if (cmpr == 1)
            {
                insert_node(&((*root)->left), node);
            }
            else if (cmpr == -1)
            {
                insert_node(&((*root)->right), node);
            }
            else
            {
                (*root)->freq = (*root)->freq + 1;
            }
        }
        (*root)->lcount = count_left_right_nodes((*root)->left);
        (*root)->rcount = count_left_right_nodes((*root)->right);
        (*root)->height = 1 + max(height((*root)->left), height((*root)->right));

        int balance_factor = getbalanceFactor(*root);
        if (balance_factor > 1)
        {
            if (AVL::cmprtr(node, (*root)->left)==-1)
                right(root);
            else if (AVL::cmprtr(node, (*root)->right)==1)
            {
                left(&((*root)->left));
                right(root);
            }
        }
        if (balance_factor < -1)
        {   
            if (AVL::cmprtr(node, (*root)->right)==1)
                left(root);
            else if (AVL::cmprtr(node, (*root)->right)==-1)
            {
                right(&((*root)->right));
                left(root);
            }
        }
    }
    static int cmprtr(treeNode<T> *n1, treeNode<T> *n2)
    {
        if (n1->val < n2->val)
            return -1;
        else if (n1->val > n2->val)
            return 1;
        return 0;
    }
    static long cmprtr(T n1, T n2)
    {
        if (n1 < n2)
            return -1;
        else if (n1 > n2)
            return 1;
        return 0;
    }
    /* void printBT(const std::string &prefix, treeNode<T> *node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──");

            // print the value of the node
            std::cout << node->val << "-" << node->lcount<<"-"<<node->rcount << std::endl;

            // enter the next tree level - left and right branch
            printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
            printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    } */
    int count_range(T left, T right)
    {
        if (AVL::cmprtr(left, right) == 1)
            return 0;
        treeNode<T> *anc = common_Ancestor(root, left, right);
        if (anc)
        {
            treeNode<T> *rright = smallest_prev(right, anc);
            treeNode<T> *lleft = closest_next(left, anc);
            int l = 0;
            int r = 0;
            findElementIndex(anc, 0, rright, &r);
            findElementIndex(anc, 0, lleft, &l);
            return r - l + rright->freq;
        }
        return 0;
    }
    /* void printBT()
    {
        printBT("", root, false);
    } */
};

int main(int argc, char const *argv[])
{
    AVL<int> tree;

	while (true)
	{   int q;
		cout << "\n1.Insert\n2.Delete\n3.Search\n4.Count Occurence\n5.Lower Bound\n6.Upper Bound\n7.Closest Element\n8.Kth Largest\n9.Count Range\n10.Inorder\n11.Preorder\n12.Post order\n";
		cin >> q;
		if (q == 1)
		{   int k;
			cout<<"Enter-\n";
            cin>>k;
            tree.insert(k);
		}
		else if (q == 2)
		{   int k;
			cout<<"Enter-\n";
            cin>>k;
            tree._delete(k);
			
		}else if (q == 3)
		{   int k;
			cout<<"Enter-\n";
            cin>>k;
            cout<<tree.search(k);
			
		}else if (q == 4)
		{   int k;
			cout<<"Enter-\n";
            cin>>k;
            cout<<tree.count_occurence(k);
			
		}else if (q == 5)
		{   int k;
			cout<<"Enter-\n";
            cin>>k;
            cout<<tree.lower_bound(k);
			
		}else if (q == 6)
		{   int k;
			cout<<"Enter-\n";
            cin>>k;
            cout<<tree.upper_bound(k);
			
		}else if (q == 7)
		{   int k;
			cout<<"Enter-\n";
            cin>>k;
            cout<<tree.closest_element(k);
			
		}else if (q == 8)
		{   int k;
			cout<<"Enter-\n";
            cin>>k;
            cout<<tree.Kth_largest(k);
			
		}else if (q == 9)
		{   int k1,k2;
			cout<<"Enter range-\n";
            cin>>k1>>k2;
            cout<<tree.count_range(k1,k2);
			
		}else if (q == 10)
		{
			tree.inorder();
		}else if (q == 11)
		{
			tree.preorder();
		}else if (q == 12)
		{
			tree.postorder();
		}
		else
		{
			cout << "Wrong choice\n";
		}
	}

    /* code */
    return 0;
}
