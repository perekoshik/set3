#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Точное значение площади
    const double S_exact = 0.25 * M_PI + 1.25 * std::asin(0.8) - 1.0;

    // Описание кругов
    const double x1 = 1.0, y1 = 1.0, r1 = 1.0;
    const double x2 = 1.5, y2 = 2.0, r2 = std::sqrt(5.0) / 2.0;
    const double x3 = 2.0, y3 = 1.5, r3 = std::sqrt(5.0) / 2.0;

    const double r1sq = r1 * r1;
    const double r2sq = r2 * r2;
    const double r3sq = r3 * r3;

    // Прямоугольники
    const double wx_min = 0.0, wx_max = 3.0;
    const double wy_min = 0.0, wy_max = 3.0;
    const double S_wide = (wx_max - wx_min) * (wy_max - wy_min); // 9

    const double tx_min = 1.0, tx_max = 2.0;
    const double ty_min = 1.0, ty_max = 2.0;
    const double S_tight = (tx_max - tx_min) * (ty_max - ty_min); // 1

    std::mt19937_64 rng(123456789);
    std::uniform_real_distribution<double> uni01(0.0, 1.0);

    std::cout << "N,S_wide,S_wide_rel_error,S_tight,S_tight_rel_error\n";

    for (int N = 100; N <= 100000; N += 500) {
        // Счётчики
        int M_wide = 0;
        int M_tight = 0;

        // Толстые точки
        for (int i = 0; i < N; ++i) {
            double x = wx_min + (wx_max - wx_min) * uni01(rng);
            double y = wy_min + (wy_max - wy_min) * uni01(rng);

            double dx1 = x - x1, dy1 = y - y1;
            double dx2 = x - x2, dy2 = y - y2;
            double dx3 = x - x3, dy3 = y - y3;

            bool inside =
                (dx1 * dx1 + dy1 * dy1 <= r1sq) &&
                (dx2 * dx2 + dy2 * dy2 <= r2sq) &&
                (dx3 * dx3 + dy3 * dy3 <= r3sq);

            if (inside) ++M_wide;
        }

        // Тонкие точки
        for (int i = 0; i < N; ++i) {
            double x = tx_min + (tx_max - tx_min) * uni01(rng);
            double y = ty_min + (ty_max - ty_min) * uni01(rng);

            double dx1 = x - x1, dy1 = y - y1;
            double dx2 = x - x2, dy2 = y - y2;
            double dx3 = x - x3, dy3 = y - y3;

            bool inside =
                (dx1 * dx1 + dy1 * dy1 <= r1sq) &&
                (dx2 * dx2 + dy2 * dy2 <= r2sq) &&
                (dx3 * dx3 + dy3 * dy3 <= r3sq);

            if (inside) ++M_tight;
        }

        // Плозади
        double S_wide_est  = (double)M_wide  / (double)N * S_wide;
        double S_tight_est = (double)M_tight / (double)N * S_tight;

        // Погрешность
        double err_wide  = std::fabs(S_wide_est  - S_exact) / S_exact;
        double err_tight = std::fabs(S_tight_est - S_exact) / S_exact;

        std::cout << N << ","
                  << S_wide_est  << "," << err_wide  << ","
                  << S_tight_est << "," << err_tight << "\n";
    }

    return 0;
}
