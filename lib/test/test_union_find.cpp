#include "union_find.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cerr << "usage: " << argv[0] << " data_file_path [0, 1, 2, 3]\n";
		std::cerr << "0: QuickFindUF\n1: QuickUnionUF\n2: WeightedQuickUnionUF\n"
			<< "3: PCWeightedQuickUnionUF" << std::endl;
		return -1;
	}

	std::ifstream input(argv[1]);
	int option = std::atoi(argv[2]);
	int N, p, q;
	std::shared_ptr<algs4::UF> uf;

	input >> N;
	switch(option) {
		case 0:
			std::cout << "QuickFindUF\n";
			uf = std::make_shared<algs4::QuickFindUF>(N);
			break;
		case 1:
			std::cout << "QuickUnionUF\n";
			uf = std::make_shared<algs4::QuickUnionUF>(N);
			break;
		case 2:
			std::cout << "WeightedQuickUnionUF\n";
			uf = std::make_shared<algs4::WeightedQuickUnionUF>(N);
			break;
		case 3:
			std::cout << "PCWeightedQuickUnionUF\n";
			uf = std::make_shared<algs4::PCWeightedQuickUnionUF>(N);
			break;
		default:
			break;
	}

	auto start = std::chrono::high_resolution_clock::now();
	while (input >> p >> q) {
		if (uf->Connected(p, q)) continue;
		uf->Union(p, q);
		std::cout << p << ' ' << q << '\n';
	}
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << uf->count() << " components, elapsed time: "
		<< elapsed.count() << "s" << std::endl;

	return 0;
}
