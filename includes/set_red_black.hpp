# ifndef SET_RED_BLACK_HPP
# define SET_RED_BLACK_HPP

#include "pair.hpp"

namespace	ft
{
	template	< class T, class Alloc>
	struct	set_Node
	{
		T									*value;
		set_Node<T, Alloc>*					parent;
		set_Node<T, Alloc>*					left;
		set_Node<T, Alloc>*					right;
		Alloc								a;
		bool								black;
		set_Node& operator= (const set_Node& pr)
		{
			a = pr.a;
			a.destroy (value);
			a.deallocate (value, 1);
			value = a.allocate(1);
			a.construct(value, *(pr.value));
			parent = pr.parent;
			left = pr.left;
			right = pr.right;
			black = pr.black;
			return (*this);
		}
		set_Node(const set_Node &pr)
		{
			a = pr.a;
			value = a.allocate(1);
			a.construct(value, *(pr.value));
			parent = pr.parent;
			left = pr.left;
			right = pr.right;
			black = pr.black;
		}
		set_Node(T &src, Alloc all) : value (all.allocate(1)), parent(nullptr), left(nullptr), right(nullptr), a(all), black(false) {a.construct(value, src);}
		set_Node() : parent(nullptr), left(nullptr), right(nullptr)
		{
			value = a.allocate(1);
			a.construct(value, T());
		}
		~set_Node() {a.destroy (value);a.deallocate (value, 1);}
	};

	template	<class T, class Compare, class Alloc>
	class set_redblack_tree
	{
	private:
		set_Node<T, Alloc>												*_root;
		size_t															_size;
		Compare															c;
		Alloc															a;
		typename Alloc::template rebind<set_Node<T, Alloc> >::other		allocator;
		void	left_rotation (set_Node<T, Alloc> *node)
		{
			set_Node<T, Alloc> *temp = node->right;
			node->right = temp->left;
			if (node->right != nullptr)
				node->right->parent = node;
			if (node->parent == nullptr)
			{
				_root = temp;
				temp->parent = nullptr;
			}
			else
			{
				temp->parent = node->parent;
				if (node->parent->left == node)
					temp->parent->left = temp;
				else
					temp->parent->right = temp;
			}
			temp->left = node;
			node->parent = temp;
		}
		void	right_rotation (set_Node<T, Alloc> *node)
		{
			set_Node<T, Alloc> *temp = node->left;
			node->left = temp->right;
			if (node->left != nullptr)
				node->left->parent = node;
			if (node->parent == nullptr)
			{
				_root = temp;
				temp->parent = nullptr;
			}
			else
			{
				temp->parent = node->parent;
				if (node->parent->right == node)
					temp->parent->right = temp;
				else
					temp->parent->left = temp;
			}
			temp->right = node;
			node->parent = temp;
		}
		void	left_right_rotate (set_Node<T, Alloc> *node)
		{
			left_rotation (node->left);
			right_rotation (node);
		}
		void	right_left_rotate (set_Node<T, Alloc> *node)
		{
			right_rotation (node->right);
			left_rotation (node);
		}
		void	rotate (set_Node<T, Alloc> *node)
		{
			if (node->parent->left == node)
			{
				if (node->parent->parent->left == node->parent)
				{
					right_rotation (node->parent->parent);
					node->black = false;
					node->parent->black = true;
					if (node->parent->right != nullptr)
						node->parent->right->black = false;
					return ;
				}
				right_left_rotate (node->parent->parent);
				node->black = true;
				node->right->black = false;
				node->left->black = false;
				return ;
			}
			if (node->parent->parent->right == node->parent)
			{
				left_rotation (node->parent->parent);
				node->black = false;
				node->parent->black = true;
				if (node->parent->left != nullptr)
					node->parent->left->black = false;
				return ;
			}
			left_right_rotate (node->parent->parent);
			node->black = true;
			node->right->black = false;
			node->left->black = false;
			return ;
		}
		void	fix_tree (set_Node<T, Alloc> *node)
		{
			if (node->parent->parent->left == node->parent)
			{
				// aunt : node->parent->parent->right
				if (node->parent->parent->right == nullptr || node->parent->parent->right->black == true)
					return rotate (node);
				if (node->parent->parent->right != nullptr)
					node->parent->parent->right->black = true;
				node->parent->black = true;
				node->parent->parent->black = false;
				return ;
			}
			// aunt : node->parent->parent->left
			if (node->parent->parent->left == nullptr || node->parent->parent->left->black == true)
					return rotate (node);
			if (node->parent->parent->left != nullptr)
				node->parent->parent->left->black = true;
			node->parent->black = true;
			node->parent->parent->black = false;
			return ;
		}
		void	check_color (set_Node<T, Alloc>	*node)
		{
			if (node == _root || node == nullptr)
				return ;
			if (!node->black && !node->parent->black)
				fix_tree (node);
			check_color (node->parent);
		}
		size_t	height(set_Node<T, Alloc> *root, size_t debth, size_t _height)
		{
			if (root == nullptr)
			{
				_height = std::max (_height, debth);
				return (_height);
			}
			return (std::max (height (root->right, debth + 1, _height), height (root->left, debth + 1, _height)));
		}
		size_t	black_nodes(set_Node<T, Alloc> *root)
		{
			if (root == nullptr)
				return (1);
			return (black_nodes (root->left) + black_nodes (root->right) + (root->black == true));
		}
		void	insert (set_Node<T, Alloc> *root, set_Node<T, Alloc>	*_new)
		{
			if (c(*_new->value, *root->value))
			{
				if (root->left)
					insert (root->left, _new);
				else
				{
					root->left = _new;
					root->left->parent = root;
				}
			}
			else
			{
				if (root->right)
					insert (root->right, _new);
				else
				{
					root->right = _new;
					root->right->parent = root;
				}
			}
		}
		bool	pure_black(set_Node<T, Alloc> *node)
		{
			if (node->black == false || (node->right != nullptr && node->right->black == false) || (node->left != nullptr && node->left->black == false))
				return (false);
			return (true);
		}
		void	double_black(set_Node<T, Alloc> *node)
		{
			if (node == nullptr || node == _root)
				return ;
			set_Node<T, Alloc>	*sibling = (node->parent->left == node) ? node->parent->right : node->parent->left;
			bool					isleft = (node->parent->left == node) ? true : false;
			if (sibling == nullptr)
				return ;
			if (pure_black(sibling))
			{
				sibling->black = false;
				if (node->parent->black == false)
					node->parent->black = true;
				else
					double_black (node->parent);
				return ;					
			}
			if (sibling->black == false)
			{
				bool	t = sibling->black;
				sibling->black = node->parent->black;
				node->parent->black = t;
				(node->parent->left == node) ? left_rotation(node->parent) : right_rotation(node->parent);
				double_black (node);
				return ;
			}
			if (sibling->black == true && ((isleft == true && (sibling->right == nullptr || sibling->right->black == true)) || (isleft == false && (sibling->left == nullptr || sibling->left->black == true))))
			{
				sibling->black = false;
				(sibling->left != nullptr && sibling->left->black == false) ? sibling->left->black = true : sibling->right->black = true;
				(isleft == true) ? right_rotation(sibling) : left_rotation(sibling);
				double_black (node);
				return ;
			}
			if (sibling->black == true && ((isleft == false && (sibling->left != nullptr && sibling->left->black == false)) || (isleft == true && (sibling->right != nullptr && sibling->right->black == false))))
			{
				set_Node<T, Alloc>	*sibling_child = (sibling->left != nullptr && sibling->left->black == false) ? sibling->left : sibling->right;
				if (sibling->left != nullptr && sibling->right != nullptr)
					sibling_child = (isleft == true) ? sibling->right : sibling->left;
				bool	t = node->parent->black;
				node->parent->black = sibling->black;
				sibling->black = t;
				(isleft == true) ? left_rotation (node->parent) : right_rotation (node->parent);
				sibling_child->black = true;
				return ;
			}
		}
		bool	is_leaf (set_Node<T, Alloc> *node)
		{
			return (node->left == nullptr && node->right == nullptr);
		}
		void	delete_red_leaf (set_Node<T, Alloc> *node)
		{
			if (node != _root)
			{
				if (node->parent->left == node)
					node->parent->left = nullptr;
				else
					node->parent->right = nullptr;
			}
			else
				_root = nullptr;
			allocator.destroy (node);
			allocator.deallocate (node, 1);
		}
		void	delete_black_leaf (set_Node<T, Alloc> *node)
		{
			double_black (node);
			if (node != _root)
			{
				if (node->parent->left == node)
					node->parent->left = nullptr;
				else
					node->parent->right = nullptr;
			}
			else
				_root = nullptr;
			allocator.destroy (node);
			allocator.deallocate (node, 1);
		}
		void	delete_tree(set_Node<T, Alloc> *node)
		{
			if (node == nullptr)
				return ;
			delete_tree (node->left);
			delete_tree (node->right);
			allocator.destroy (node);
			allocator.deallocate (node, 1);
		}
		void	swap_node(set_Node<T, Alloc> **_node, set_Node<T, Alloc> **_child)
		{
			set_Node<T, Alloc> *node = *_node;
			set_Node<T, Alloc> *child = *_child;

			Alloc						a = node->a;
			node->a = child->a;
			child->a = a;
			bool						black = node->black;
			node->black = child->black;
			child->black = black;
			if (child->parent == node)
			{
				set_Node<T, Alloc>		*left = child->left;
				set_Node<T, Alloc>		*right = child->right;
				if (node->left == child)
				{
					child->left = node, child->right = node->right;
					if (child->right != nullptr)
						child->right->parent = child;
				}
				else
				{
					child->right = node, child->left = node->left;
					if (child->left != nullptr)
						child->left->parent = child;
				}
				child->parent = node->parent;
				if (child->parent == nullptr)
					_root = child;
				else
					(child->parent->left == node) ? child->parent->left = child : child->parent->right = child;
				node->parent = child;
				node->left = left;
				node->right = right;
				if (node->left != nullptr)
					node->left->parent = node;
				if (node->right != nullptr)
					node->right->parent = node;
			}
			else
			{
				set_Node<T, Alloc>		*left = node->left;
				set_Node<T, Alloc>		*right = node->right;
				set_Node<T, Alloc>		*parent = node->parent;
				node->left = child->left;
				if (node->left != nullptr) node->left->parent = node;
				child->left = left;
				if (child->left != nullptr) child->left->parent = child;
				node->right = child->right;
				if (node->right != nullptr) node->right->parent = node;
				child->right = right;
				if (child->right != nullptr) child->right->parent = child;
				
				if (node->parent == nullptr)
					_root = child;
				else
					(node->parent->left == node) ? node->parent->left = child : node->parent->right = child;
				(child->parent->left == child) ? child->parent->left = node : child->parent->right = node;
				node->parent = child->parent;
				child->parent = parent;
			}
		}
		void	delete_black(set_Node<T, Alloc> *node)
		{
			if (is_leaf(node))
			{
				delete_black_leaf(node);
				return ;
			}
			if (node->right != nullptr && node->left != nullptr)
			{
				set_Node<T, Alloc>	*child = predecessor(node);
				swap_node(&node, &child);
				(node->black) ? delete_black (node) : delete_red (node);
				return ;
			}
			set_Node<T, Alloc>	*child = (node->right != nullptr) ? successor(node) : predecessor(node);
			swap_node(&node, &child);
			(node->black) ? delete_black (node) : delete_red (node);
		}
		void	delete_red(set_Node<T, Alloc> *node)
		{
			if (is_leaf(node))
			{
				delete_red_leaf(node);
				return ;
			}
			if (node->right != nullptr && node->left != nullptr)
			{
				set_Node<T, Alloc>	*child = predecessor(node);
				swap_node(&node, &child);
				(node->black) ? delete_black (node) : delete_red (node);
				return ;
			}
			set_Node<T, Alloc>	*child = (node->right != nullptr) ? successor(node) : predecessor(node);
			swap_node(&node, &child);
			(node->black) ? delete_black (node) : delete_red (node);
		}	
	public:
		set_redblack_tree() : _root(nullptr), _size(0) {}
		~set_redblack_tree() { clear(); }
		set_Node<T, Alloc>	*get_min() const
		{
			if (_root == nullptr)
				return (nullptr);
			set_Node<T, Alloc>	*temp = _root;
			while (temp->left)
				temp = temp->left;
			return (temp);
		}
		set_Node<T, Alloc>	*get_max() const
		{
			if (_root == nullptr)
				return (nullptr);
			set_Node<T, Alloc>	*temp = _root;
			while (temp->right)
				temp = temp->right;
			return (temp);
		}
		set_Node<T, Alloc>	*predecessor(set_Node<T, Alloc>* node)
		{
			set_Node<T, Alloc>	*cur = node->left;
			set_Node<T, Alloc>	*predecessor;
			if (cur)
			{
				while(cur->right != NULL)
					cur = cur->right;
				return (cur);
			}
			cur = node;
			while (cur->parent)
				cur = cur->parent;
			predecessor = nullptr;
			while (cur)
			{
				if (c(*node->value, *cur->value))
					cur = cur->left;
				else if (node->value > cur->value)
				{
					predecessor = cur;
					cur = cur->right;
				} 
				else
					break;
			}
			return (predecessor);
		}
		set_Node<T, Alloc>	*successor(set_Node<T, Alloc>* node)
		{
			set_Node<T, Alloc>	*cur = node->right;
			set_Node<T, Alloc>	*successor;
			if (cur)
			{
				while(cur->left != NULL)
					cur = cur->left;
				return (cur);
			}
			cur = node;
			while (cur->parent)
				cur = cur->parent;
			successor = nullptr;
			while (cur)
			{
				if (c(*cur->value, *node->value))
					cur = cur->right;
				else if (node->value < cur->value)
				{
					successor = cur;
					cur = cur->left;
				} 
				else
					break;
			}
			return (successor);
		}
		set_Node<T, Alloc>	*const*get_root() const
		{
			return (&_root);
		}
		void				set_size(size_t __size)
		{
			_size = __size;
		}
		void				set_root(set_Node<T, Alloc>	*rt)
		{
			_root = rt;
		}
		bool	insert (const T &_data)
		{
			T	c(_data);
			if (find_node (_data) != nullptr)
				return (false);
			set_Node<T, Alloc>	*_new = allocator.allocate(1);
			allocator.construct (_new, set_Node<T, Alloc> (c, a));
			if (!_root)
				_root = _new;
			else
				insert (_root, _new);
			check_color (_new);
			_size++;
			_root->black = true;
			return (true);
		}
		bool	insert (const T &_data) const
		{
			T	c(_data);
			if (find_node (_data) != nullptr)
				return (false);
			set_Node<T, Alloc>	*_new = allocator.allocate(1);
			allocator.construct (_new, set_Node<T, Alloc> (c, a));
			if (!_root)
				_root = _new;
			else
				insert (_root, _new);
			check_color (_new);
			_size++;
			_root->black = true;
			return (true);
		}
		size_t			height(void)
		{		
			return (height (_root, 0, 0));
		}
		size_t			black_nodes()
		{
			return (black_nodes(_root));
		}
		set_Node<T, Alloc>	*find_node (const T &_key) const
		{
			set_Node<T, Alloc>	*temp = _root;
			while(temp)  
			{
				if (*temp->value == _key)
					break ;
				if (c(_key, *temp->value))
					temp = temp->left;   
				else
					temp = temp->right;
			}
			return (temp);
		}
		set_Node<T, Alloc>	*lower_bound(const T &k) const
		{
			set_Node<T, Alloc>	*temp = _root;
			set_Node<T, Alloc>	*_ans = nullptr;

			while (temp)
			{
				if (*temp->value == k)
				{
					_ans = temp;
					break ;
				}
				if (c(k, *temp->value))
				{
					_ans = temp;
					temp = temp->left;
				}
				else
					temp = temp->right;
			}
			return (_ans);
		}
		set_Node<T, Alloc>	*lower_bound(const T &k)
		{
			set_Node<T, Alloc>	*temp = _root;
			set_Node<T, Alloc>	*_ans = nullptr;

			while (temp)
			{
				if (*temp->value == k)
				{
					_ans = temp;
					break ;
				}
				if (c(k, *temp->value))
				{
					_ans = temp;
					temp = temp->left;
				}
				else
					temp = temp->right;
			}
			return (_ans);
		}
		set_Node<T, Alloc>	*upper_bound(const T &k) const
		{
			set_Node<T, Alloc>	*temp = _root;
			set_Node<T, Alloc>	*_ans = nullptr;

			while (temp)
			{
				if (c(k, *temp->value))
				{
					_ans = temp;
					temp = temp->left;
				}
				else
					temp = temp->right;
			}
			return (_ans);
		}
		set_Node<T, Alloc>	*upper_bound(const T &k)
		{
			set_Node<T, Alloc>	*temp = _root;
			set_Node<T, Alloc>	*_ans = nullptr;

			while (temp)
			{
				if (c(k, *temp->value))
				{
					_ans = temp;
					temp = temp->left;
				}
				else
					temp = temp->right;
			}
			return (_ans);
		}	
		size_t					erase(const T &k)
		{
			set_Node<T, Alloc>	*node = find_node(k);
			if (node == nullptr)
				return (0);
			if (node->black)
				delete_black(node);
			else
				delete_red(node);
			_size--;
			return (1);
		}
		void	clear ()
		{
			delete_tree (_root);
			_size = 0;
			_root = nullptr;
		}
		void	print (set_Node<T, Alloc> *_root)
		{
			if (!_root)
				return ;
			print (_root->left);
			std::cout << *_root->value << " ";
			print (_root->right);
		}
		size_t	size () const
		{
			return (_size);
		}
	};
}
# endif

/*
				I - RED BLACK TREE HAS 6 CONDITION :
		1 - Every node is red or black
		2 - Root is always black
		3 - New insetion are always red
		4 - Every path from root to leaf has the same number of black nodes
		5 - No path have to consesives red nodes
		6 - Nulls are black
				II - BALENCING
		1 - If we have black aunt we rotate
			a. If we have imbalence the grand parent left child, left sub tree we do right rotaion
			b. If we have imbalence the grand parent right child, right sub tree we do left rotaion
			c. If we have imbalence the grand parent left child, right sub tree we do left-right rotaion
			a. If we have imbalence the grand parent right child, left sub tree we do right-left rotaion
		2 - If we have red aunt we color flip
			a. Just changing the colors
*/
