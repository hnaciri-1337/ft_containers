/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:32:51 by hnaciri-          #+#    #+#             */
/*   Updated: 2023/01/08 15:09:24 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RED_BLACK_HPP
# define RED_BLACK_HPP

#include "includes.hpp"

namespace	ft
{
	struct Trunk
	{
		Trunk *prev;
		std::string str;
	
		Trunk(Trunk *prev, std::string str)
		{
			this->prev = prev;
			this->str = str;
		}
	};
	template	< class key, class val, class Alloc>
	struct	Node
	{
		ft::pair<const key, val>			*value;
		Node<key, val, Alloc>*				parent;
		Node<key, val, Alloc>*				left;
		Node<key, val, Alloc>*				right;
		Alloc								a;
		bool								black;
		Node& operator= (const Node& pr)
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
		Node(const Node &pr)
		{
			a = pr.a;
			value = a.allocate(1);
			a.construct(value, *(pr.value));
			parent = pr.parent;
			left = pr.left;
			right = pr.right;
			black = pr.black;
		}
		Node(key _key, val _value, Alloc all) : value (all.allocate (1)), parent(nullptr), left(nullptr), right(nullptr), a(all), black(false) {a.construct(value, ft::make_pair (_key, _value));}
		Node(ft::pair <key, val> &src, Alloc all) : value (all.allocate(1)), parent(nullptr), left(nullptr), right(nullptr), a(all), black(false) {a.construct(value, src);}
		Node() : parent(nullptr), left(nullptr), right(nullptr)
		{
			value = a.allocate(1);
			a.construct(value, ft::pair<key, val>());
		}
		~Node() {a.destroy (value);a.deallocate (value, 1);}
	};

	template	<class key, class val, class Compare, class Alloc>
	class redblack_tree
	{
	private:
		Node<key, val, Alloc>											*_root;
		size_t															_size;
		Compare															c;
		Alloc															a;
		typename Alloc::template rebind<Node<key, val, Alloc> >::other	allocator;
		void showTrunks(Trunk *p)
		{
			if (p == nullptr) {
				return;
			}
		
			showTrunks(p->prev);
			std::cout << p->str;
		}
		void printTree(Node<key, val, Alloc>* root, Trunk *prev, bool isLeft)
		{
			if (root == nullptr) {
				return;
			}
		
			std::string prev_str = "    ";
			Trunk *trunk = new Trunk(prev, prev_str);
		
			printTree(root->right, trunk, true);
		
			if (!prev) {
				trunk->str = "———";
			}
			else if (isLeft)
			{
				trunk->str = ".———";
				prev_str = "   |";
			}
			else {
				trunk->str = "`———";
				prev->str = prev_str;
			}
		
			showTrunks(trunk);
			if (root->black)
				std::cout << " \033[32m" << root->value->first << "\033[0m" << std::endl;
			else
				std::cout << " \033[31m" << root->value->first << "\033[0m" << std::endl;
			if (prev)
				prev->str = prev_str;
			trunk->str = "   |";
			printTree(root->left, trunk, false);
			free (trunk);
		}
		void	left_rotation (Node<key, val, Alloc> *node)
		{
			Node<key, val, Alloc> *temp = node->right;
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
		void	right_rotation (Node<key, val, Alloc> *node)
		{
			Node<key, val, Alloc> *temp = node->left;
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
		void	left_right_rotate (Node<key, val, Alloc> *node)
		{
			left_rotation (node->left);
			right_rotation (node);
		}
		void	right_left_rotate (Node<key, val, Alloc> *node)
		{
			right_rotation (node->right);
			left_rotation (node);
		}
		void	rotate (Node<key, val, Alloc> *node)
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
		void	fix_tree (Node<key, val, Alloc> *node)
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
		void	check_color (Node<key, val, Alloc>	*node)
		{
			if (node == _root || node == nullptr)
				return ;
			if (!node->black && !node->parent->black)
				fix_tree (node);
			check_color (node->parent);
		}
		size_t	height(Node<key, val, Alloc> *root, size_t debth, size_t _height)
		{
			if (root == nullptr)
			{
				_height = std::max (_height, debth);
				return (_height);
			}
			return (std::max (height (root->right, debth + 1, _height), height (root->left, debth + 1, _height)));
		}
		size_t	black_nodes(Node<key, val, Alloc> *root)
		{
			if (root == nullptr)
				return (1);
			return (black_nodes (root->left) + black_nodes (root->right) + (root->black == true));
		}
		void	insert (Node<key, val, Alloc> *root, Node<key, val, Alloc>	*_new)
		{
			if (c(_new->value->first, root->value->first))
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
		void	double_black(Node<key, val, Alloc> *node)
		{
			if (node == nullptr)
				return ;
		}
		bool	is_leaf (Node<key, val, Alloc> *node)
		{
			return (node->left == nullptr && node->right == nullptr);
		}
		void	delete_leaf (Node<key, val, Alloc> *node)
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
		void	delete_tree(Node<key, val, Alloc> *node)
		{
			if (node == nullptr)
				return ;
			delete_tree (node->left);
			delete_tree (node->right);
			allocator.destroy (node);
			allocator.deallocate (node, 1);
		}
		void	delete_black(Node<key, val, Alloc> *node)
		{
			if (is_leaf(node))
			{
				delete_leaf(node);
				return ;
			}
			if (node->right != nullptr && node->left != nullptr)
			{
				Node<key, val, Alloc>	*succ = successor(node);
				a.destroy (node->value);
				a.deallocate (node->value, 1);
				node->value = a.allocate(1);
				a.construct(node->value, *(succ->value));
				(succ->black) ? delete_black (succ) : delete_red (succ);
				return ;
			}
			Node<key, val, Alloc>	*child = (node->right != nullptr) ? successor(node) : predecessor(node);
			a.destroy (node->value);
			a.deallocate (node->value, 1);
			node->value = a.allocate(1);
			a.construct(node->value, *(child->value));
			(child->black) ? delete_black (child) : delete_red (child);
		}
		void	delete_red(Node<key, val, Alloc> *node)
		{
			if (is_leaf(node))
			{
				delete_leaf(node);
				return ;
			}
			if (node->right != nullptr && node->left != nullptr)
			{
				Node<key, val, Alloc>	*succ = successor(node);
				a.destroy (node->value);
				a.deallocate (node->value, 1);
				node->value = a.allocate(1);
				a.construct(node->value, *(succ->value));
				(succ->black) ? delete_black (succ) : delete_red (succ);
				return ;
			}
			Node<key, val, Alloc>	*child = (node->right != nullptr) ? successor(node) : predecessor(node);
			a.destroy (node->value);
			a.deallocate (node->value, 1);
			node->value = a.allocate(1);
			a.construct(node->value, *(child->value));
			(child->black) ? delete_black (child) : delete_red (child);
		}		
	public:
		redblack_tree() : _root(nullptr), _size(0) {}
		~redblack_tree() { clear(); }
		Node<key, val, Alloc>	*get_min() const
		{
			if (_root == nullptr)
				return (nullptr);
			Node<key, val, Alloc>	*temp = _root;
			while (temp->left)
				temp = temp->left;
			return (temp);
		}
		Node<key, val, Alloc>	*get_max() const
		{
			if (_root == nullptr)
				return (nullptr);
			Node<key, val, Alloc>	*temp = _root;
			while (temp->right)
				temp = temp->right;
			return (temp);
		}
		Node<key, val, Alloc>	*predecessor(Node<key, val, Alloc>* node)
		{
			Node<key, val, Alloc>	*cur = node->left;
			Node<key, val, Alloc>	*predecessor;
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
				if (c(node->value->first, cur->value->first))
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
		Node<key, val, Alloc>	*successor(Node<key, val, Alloc>* node)
		{
			Node<key, val, Alloc>	*cur = node->right;
			Node<key, val, Alloc>	*successor;
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
				if (c(cur->value->first, node->value->first))
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
		Node<key, val, Alloc>	*get_root()
		{
			return (_root);
		}
		bool	insert (const ft::pair <key, val> &_data)
		{
			ft::pair <key, val>	c(_data);
			if (find_node (_data.first) != nullptr)
				return (false);
			Node<key, val, Alloc>	*_new = allocator.allocate(1);
			allocator.construct (_new, Node<key, val, Alloc> (c, a));
			if (!_root)
				_root = _new;
			else
				insert (_root, _new);
			check_color (_new);
			_size++;
			_root->black = true;
			return (true);
		}
		bool	insert (const ft::pair <key, val> &_data) const
		{
			ft::pair <key, val>	c(_data);
			if (find_node (_data.first) != nullptr)
				return (false);
			Node<key, val, Alloc>	*_new = allocator.allocate(1);
			allocator.construct (_new, Node<key, val, Alloc> (c, a));
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
		Node<key, val, Alloc>	*find_node (const key &_key) const
		{
			Node<key, val, Alloc>	*temp = _root;
			while(temp)  
			{
				if (temp->value->first == _key)
					break ;
				if (c(_key, temp->value->first))
					temp = temp->left;   
				else
					temp = temp->right;
			}
			return (temp);
		}
		Node<key, val, Alloc>	*lower_bound(const key &k) const
		{
			Node<key, val, Alloc>	*temp = _root;
			Node<key, val, Alloc>	*_ans = nullptr;

			while (temp)
			{
				if (temp->value->first == k)
				{
					_ans = temp;
					break ;
				}
				if (c(k, temp->value->first))
				{
					_ans = temp;
					temp = temp->left;
				}
				else
					temp = temp->right;
			}
			return (_ans);
		}
		Node<key, val, Alloc>	*lower_bound(const key &k)
		{
			Node<key, val, Alloc>	*temp = _root;
			Node<key, val, Alloc>	*_ans = nullptr;

			while (temp)
			{
				if (temp->value->first == k)
				{
					_ans = temp;
					break ;
				}
				if (c(k, temp->value->first))
				{
					_ans = temp;
					temp = temp->left;
				}
				else
					temp = temp->right;
			}
			return (_ans);
		}
		Node<key, val, Alloc>	*upper_bound(const key &k) const
		{
			Node<key, val, Alloc>	*temp = _root;
			Node<key, val, Alloc>	*_ans = nullptr;

			while (temp)
			{
				if (c(k, temp->value->first))
				{
					_ans = temp;
					temp = temp->left;
				}
				else
					temp = temp->right;
			}
			return (_ans);
		}
		Node<key, val, Alloc>	*upper_bound(const key &k)
		{
			Node<key, val, Alloc>	*temp = _root;
			Node<key, val, Alloc>	*_ans = nullptr;

			while (temp)
			{
				if (c(k, temp->value->first))
				{
					_ans = temp;
					temp = temp->left;
				}
				else
					temp = temp->right;
			}
			return (_ans);
		}	
		size_t					erase(const key &k)
		{
			Node<key, val, Alloc>	*node = find_node(k);
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
		void	print (Node<key, val, Alloc> *_root)
		{
			if (!_root)
				return ;
			print (_root->left);
			std::cout << _root->value->first << " ";
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
