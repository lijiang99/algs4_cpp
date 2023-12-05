#include "union_find.h"

namespace algs4 {

	UF::UF(int N) {
		id_ = new int[N];
		for (int i = 0; i < N; ++i)
			id_[i] = i;
		count_ = size_ = N;
	}

	// 直接返回p所在分量的标识符，时间复杂度为O(1)
	int QuickFindUF::Find(int p) {
		return id_[p];
	}

	// 遍历数组，将与p处于相同分量的触点的标识符全部改为q的标识符，以实现合并分量
	void QuickFindUF::Union(int p, int q) {
		int p_id = Find(p), q_id = Find(q);
		if (p_id == q_id) return;
		for (int i = 0; i < size_; ++i) {
			if (id_[i] == p_id) id_[i] = q_id;
		}
		--count_;
	}

	// 查找p所在分量的标识符，即查找p所在树的根节点
	// id_[p]就是p的父节点，而根节点满足p == id_[p]
	int QuickUnionUF::Find(int p) {
		while (p != id_[p]) p = id_[p];
		return p;
	}

	// 自下而上查找p和q的根节点，将p的根节点连接到q的根节点，以实现合并分量
	void QuickUnionUF::Union(int p, int q) {
		int p_root = Find(p), q_root = Find(q);
		if (p_root == q_root) return;
		id_[p_root] = q_root;
		--count_;
	}

	WeightedQuickUnionUF::WeightedQuickUnionUF(int N) : QuickUnionUF(N) {
		sz_ = new int[N];
		for (int i = 0; i < N; ++i)
			sz_[i] = 1;	// 初始时每个树中只有一个节点
	}

	// 每次均将节点较少的树的根节点连接到节点较多的树的根节点
	// 从而降低树的层级，以防止出现极端情况（树退化为链表）
	void WeightedQuickUnionUF::Union(int p, int q) {
		int p_root = Find(p), q_root = Find(q);
		if (p_root == q_root) return;
		if (sz_[p_root] < sz_[q_root]) {
			id_[p_root] = q_root;
			sz_[q_root] += sz_[p_root];
		} else {
			id_[q_root] = p_root;
			sz_[p_root] += sz_[q_root];
		}
		--count_;
	}

	// 在查找的过程中，将路径中的所有节点的父节点都设置为根节点，以实现路径压缩
	int PCWeightedQuickUnionUF::Find(int p) {
		int root = p;
		while (root != id_[root])
			root = id_[root];
		while (p != root) {
			int parent = id_[p];
			id_[p] = root;
			p = parent;
		}
		return root;
	}
	
	// 递归法实现路径压缩
	/* int PCWeightedQuickUnionUF::Find(int p) { */
	/* 	return p == id_[p] ? p : id_[p] = Find(id_[p]); */
	/* } */
}
