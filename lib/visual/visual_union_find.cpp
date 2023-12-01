#include "union_find.h"
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <mgl2/mgl.h>

void plot_union_find(std::shared_ptr<algs4::UF> uf, const std::vector<std::pair<int,int>> &conns,
		int width, int height, double y_max, const char *save_path) {
	mglData y1(conns.size()), y2(conns.size());
	for (int i = 0, total = 0; i < conns.size(); ++i) {
		total += uf->cost();
		y1.a[i] = uf->cost();
		y2.a[i] = (total * 1.0) / i;
		uf->reset_cost();

		if (uf->Connected(conns[i].first, conns[i].second)) continue;
		uf->Union(conns[i].first, conns[i].second);
	}

	mglGraph gr(0, width, height);
	gr.SetRanges(0, 900, 0, y_max);
	double x_val[] = {0, 900};
	gr.SetTicksVal('x', mglData(2, x_val), "0\n900");
	gr.SetFontSize(2);
	gr.Plot(y1, "h. ");
	gr.Plot(y2, "r. ");
	gr.Axis("!");
	gr.WriteSVG(save_path);
}

int main(int argc, char* argv[]) {
	int N;
	std::cin >> N;

	std::pair<int,int> conn;
	std::vector<std::pair<int,int>> conns;
	conns.reserve(900);
	while (std::cin >> conn.first >> conn.second) conns.emplace_back(conn);

	plot_union_find(std::make_shared<algs4::QuickFindUF>(N), conns, 500, 860, 1300, "quick-find.svg");
	plot_union_find(std::make_shared<algs4::QuickUnionUF>(N), conns, 500, 90, 100, "quick-union.svg");
	plot_union_find(std::make_shared<algs4::WeightedQuickUnionUF>(N), conns, 500, 30, 20, "weighted-quick-union.svg");

	return 0;
}
