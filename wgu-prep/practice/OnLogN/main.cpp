// O(n log n) - Linearithmic Time: Common in efficient sorting algorithms like Merge Sort and QuickSort.  
// It grows slightly worse than linear time but is significanly better than quadratic time for large datasets.
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
#include <vector>

// ---------- Merge Sort (O(n log n)) ----------
static void merge_sort_impl(std::vector<int>& a,
                            std::vector<int>& tmp,
                            size_t l, size_t r) {
    if (r - l <= 1) return;
    size_t m = l + (r - l) / 2;
    merge_sort_impl(a, tmp, l, m);
    merge_sort_impl(a, tmp, m, r);

    // merge [l, m) and [m, r) into tmp
    size_t i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else              tmp[k++] = a[j++];
    }
    while (i < m) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    // copy back
    for (size_t t = l; t < r; ++t) a[t] = tmp[t];
}

static void merge_sort(std::vector<int>& a) {
    std::vector<int> tmp(a.size());
    merge_sort_impl(a, tmp, 0, a.size());
}

// ---------- Data generation ----------
enum class Pattern { Random, Sorted, Reversed, Duplicates };

static std::vector<int> make_data(size_t n, Pattern p) {
   std::vector<int> v(n);
   std::mt19937 rng(std::random_device{}());
   std::uniform_int_distribution<int> dist(0, 1'000'000);

   switch (p) {
      case Pattern::Random:
         for (auto& x : v) x = dist(rng);
         break;
      case Pattern::Sorted:
         for (size_t i = 0; i < n; ++i) v[i] = static_cast<int>(i);
         break;
      case Pattern::Reversed:
         for (size_t i = 0; i < n; ++i) v[i] = static_cast<int>(n - 1 - i);
         break;
      case Pattern::Duplicates: {
         std::uniform_int_distribution<int> small(0, 9); // many duplicates
         for (auto& x : v) x = small(rng);
         break;
      }
   }
   return v;
}

// ---------- Utility ----------
static bool is_sorted_non_decreasing(const std::vector<int>& v) {
   return std::is_sorted(v.begin(), v.end());
}

static double now_sec() {
   using clock = std::chrono::steady_clock;
   static auto epoch = clock::now();
   return std::chrono::duration<double>(clock::now() - epoch).count();
}

struct Args {
   size_t n = 200'000;           // default 200k
   int    trials = 3;
   std::string algo = "merge";   // "merge" or "std"
   Pattern pattern = Pattern::Random;
};

static void usage(const char* exe) {
   std::cout << "Usage: " << exe
            << " [--n N] [--trials T] [--algo merge|std] "
               "[--pattern random|sorted|reversed|duplicates]\n"
               "Examples:\n"
               "  " << exe << " --n 200000 --algo merge --trials 3\n"
               "  " << exe << " --n 200000 --algo std --pattern reversed\n";
}

static Args parse_args(int argc, char** argv) {
   Args a;
   for (int i = 1; i < argc; ++i) {
      std::string_view s = argv[i];
      auto next = [&](int& i) -> std::string_view {
         if (i + 1 >= argc) { usage(argv[0]); std::exit(2); }
         return argv[++i];
      };
      if (s == "--help" || s == "-h") { usage(argv[0]); std::exit(0); }
      else if (s == "--n")      { a.n = static_cast<size_t>(std::stoull(std::string(next(i)))); }
      else if (s == "--trials") { a.trials = std::stoi(std::string(next(i))); }
      else if (s == "--algo")   { a.algo = std::string(next(i)); }
      else if (s == "--pattern") {
         auto p = std::string(next(i));
         if      (p == "random")     a.pattern = Pattern::Random;
         else if (p == "sorted")     a.pattern = Pattern::Sorted;
         else if (p == "reversed")   a.pattern = Pattern::Reversed;
         else if (p == "duplicates") a.pattern = Pattern::Duplicates;
         else { std::cerr << "Unknown pattern: " << p << "\n"; usage(argv[0]); std::exit(2); }
      }
      else {
         std::cerr << "Unknown arg: " << s << "\n";
         usage(argv[0]); std::exit(2);
      }
   }
   return a;
}

int main(int argc, char** argv) {
   Args args = parse_args(argc, argv);

   std::cout << "Algorithm: " << args.algo
            << " | n=" << args.n
            << " | trials=" << args.trials << "\n";

   for (int t = 1; t <= args.trials; ++t) {
      auto data = make_data(args.n, args.pattern);

      // choose algorithm
      auto start = now_sec();
      if (args.algo == "merge") {
         merge_sort(data);
      } else if (args.algo == "std") {
         std::sort(data.begin(), data.end()); // introsort (avg/worst O(n log n))
      } else {
         std::cerr << "Unknown algo: " << args.algo << "\n";
         return 2;
      }
      auto dt = now_sec() - start;

      bool ok = is_sorted_non_decreasing(data);
      double nlogn = static_cast<double>(args.n) * std::log2(static_cast<double>(args.n));
      double norm = dt / nlogn; // seconds / (n log2 n) — should be ~constant across n

      std::cout << "Trial " << t
               << ": time=" << dt << " s | "
               << "OK=" << (ok ? "yes" : "NO") << " | "
               << "time/(n log2 n)=" << norm << "\n";
   }

   return 0;
}
