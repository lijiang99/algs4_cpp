#ifndef ALGS4_UNION_FIND_H_
#define ALGS4_UNION_FIND_H_

namespace algs4 {

	class UF {
		public:
			UF(int N);
			virtual ~UF() { delete[] id_; }

			// p所在的分量的标识符
			virtual int Find(int p) = 0;
			// 在p和q之间添加一条连接
			virtual void Union(int p, int q) = 0;
			// 若p和q在同一分量则返回true
			bool Connected(int p, int q) { return Find(p) == Find(q); }
			// 连通分量的数量
			int count() const { return count_; }

		protected:
			int *id_;	// 分量id
			int count_;	// 分量数量
			int size_;	// 数组大小
	};

	class QuickFindUF : public UF {
		public:
			QuickFindUF(int N) : UF(N) {}

			int Find(int p) override;
			void Union(int p, int q) override;
	};

	class QuickUnionUF : public UF {
		public:
			QuickUnionUF(int N) : UF(N) {}

			int Find(int p) override;
			void Union(int p, int q) override; 
	};

	class WeightedQuickUnionUF : public QuickUnionUF {
		public:
			WeightedQuickUnionUF(int N);
			~WeightedQuickUnionUF() { delete[] sz_; }

			// 此时无需重写Find，直接使用QuickFindUF::Find即可
			void Union(int p, int q) override;

		protected:
			int *sz_;	// 分量中触点的数量（树中的节点数量）
	};

	class PCWeightedQuickUnionUF : public WeightedQuickUnionUF {
		public:
			PCWeightedQuickUnionUF(int N) : WeightedQuickUnionUF(N) {}

			int Find(int p) override;
			// 此时无需重写Union，直接使用WeightedQuickUnionUF::Union即可
	};
}

#endif
