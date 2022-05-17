#include <iostream>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace ariel
{

    class OrgChart
    {

    private:
        struct Node
        {
            explicit Node(string val) : value(val) {}
            string value;
            vector<Node *> children;
        };

        Node *find_n(const string &find, Node *node)
        {

            if (node == nullptr)
            {
                return nullptr;
            }
            if (node->value == find)
            {
                return node;
            }

            for (auto &child : node->children)
            {
                Node *found = find_n(find, child);
                if (found != nullptr)
                {
                    return found;
                }
            }
            return nullptr;
        }

        void rec_copy_childs(const Node &from, Node &to)
        {
        }

        Node *root_tree = nullptr;
        map<string, Node *> map_tree;

    public:
        OrgChart() = default;

        // Shallow copy ctor (move ctor)
        OrgChart(OrgChart &&other) noexcept
        {
            std::cout << "/* message */" << '\n';
            root_tree = other.root_tree;
            other.root_tree = nullptr;
        }

        // deep copy ctor
        OrgChart(const OrgChart &other)
        {
            std::cout << "/* message */" << '\n';
            if (other.root_tree != nullptr)
            {
                root_tree = new Node(other.root_tree->value);
                rec_copy_childs(*other.root_tree, *root_tree);
            }
        }

        //------Operators-----
        OrgChart &operator=(OrgChart other)
        {
            std::cout << "/* message */" << '\n';
            if (this == &other)
            {
                return *this;
            }
            if (root_tree != nullptr)
            {
                delete this->root_tree;
            }
            root_tree = new Node(other.root_tree->value);
            rec_copy_childs(*other.root_tree, *this->root_tree);
            return *this;
        }

        // OrgChart &operator=(OrgChart &&other) noexcept
        // {
        //     std::cout << "/* message */" << '\n';
        //     *this->root_tree = other.root_tree;
        // }

        ~OrgChart(){};

        OrgChart &add_root(const string &x)
        {
            if (root_tree == nullptr)
            {
                root_tree = new Node(x);
            }
            else
            {
                root_tree->value = x;
            }

            return *this;
        }
        OrgChart &add_sub(const string &exsist, const string &insert_)
        {
            Node *found = find_n(exsist, root_tree);
            if (found == nullptr)
            {
                throw invalid_argument("not exist");
            }
            if (found->children.empty())
            {
                found->children.push_back(new Node(insert_));
            }
            else
            {
                found->children.push_back(new Node(insert_));
            }
            return *this;
        }

        class it
        {
        private:
        public:
            Node *current;
            list<Node *> inner;
            it() : current(nullptr) {}
            explicit it(Node *temp) : current(temp) {}

            void recu_in(Node *v)
            {
                if (v == nullptr)
                {
                    return;
                }
                for (auto &child : v->children)
                {
                    recu_in(child);
                }
                inner.push_back(v);
            }
            void recu_pre(Node *v)
            {
                if (v == nullptr)
                {
                    return;
                }
                inner.push_back(v);
                for (auto &child : v->children)
                {
                    recu_pre(child);
                }
            }
            void recu_post(Node *v)
            {
                if (v == nullptr)
                {
                    return;
                }
                // recu_post(v->left);
                // recu_post(v->right);
                // inner.push_back(v);
            }

            it(Node *root, char type)
            {
                if (root == nullptr)
                {
                    current = nullptr;
                    return;
                }
                switch (type)
                {
                case 'i':
                    recu_in(root);
                    current = *inner.begin();
                    break;
                case 'e':
                    recu_pre(root);
                    current = *inner.begin();
                    break;
                case 't':
                    recu_post(root);
                    current = *inner.begin();
                    break;
                }
            }

            string &operator*() const
            {
                return current->value;
            }

            string *operator->() const
            {
                return &(current->value);
            }

            it &operator++()
            {
                if (inner.size() > 1)
                {
                    inner.erase(inner.begin());
                    current = *inner.begin();
                }
                else
                {
                    current = nullptr;
                }
                return *this;
            }

            it operator++(int)
            {
                it temp(*inner.begin());
                ++*this;
                return temp;
            }

            bool operator==(const it &other) const
            {
                // TODO check if the iterators are equal
                return current == nullptr;
            }

            bool operator!=(const it &other) const
            {
                return !(*this == other);
            }
        };

        it begin()
        {
            return it(root_tree, 'i');
        }
        it end()
        {
            return it();
        }

        it begin_preorder()
        {
            return it(root_tree, 'e');
        }

        it end_preorder()
        {
            return it();
        }

        it begin_inorder()
        {
            return it(root_tree, 'i');
        }
        it end_inorder()
        {
            return it();
        }
        it begin_postorder()
        {
            return it(root_tree, 't');
        }
        it end_postorder()
        {

            return it();
        }

        friend ostream &operator<<(ostream &os, const OrgChart &tree)
        {

            for (auto &x : tree.map_tree)
            {
                os << ' ' << x.first;
            }
            return os;
        }

        it begin_reverse_order()
        {
            return it(root_tree, 'e');
        }

        it reverse_order()
        {
            return it(root_tree, 'e');
        }

        it begin_level_order()
        {
            return it(root_tree, 'e');
        }

        it end_level_order()
        {
            return it(root_tree, 'e');
        }
    };

}