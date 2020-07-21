#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include <pagmo/utils/hv_algos/hv_algorithm.hpp>
#include <pagmo/utils/hv_algos/hv_bf_approx.hpp>
#include <pagmo/utils/hv_algos/hv_bf_fpras.hpp>
#include <pagmo/utils/hv_algos/hv_hv2d.hpp>
#include <pagmo/utils/hv_algos/hv_hv3d.hpp>
#include <pagmo/utils/hv_algos/hv_hvwfg.hpp>
#include <pagmo/utils/hypervolume.hpp>


using namespace std;
using namespace pagmo;

int main() {
  int n = 1000; // the number of test cases
  int d = 3; // the dimension of eash point
  double max_v = 10.0; // each point is inside of [0, max_v]^d
  vector<double> r_point; // the reference point
  vector<vector<vector<double>>> set_points; // the set of test cases
  vector<double> hv; // the result of hypervolume calculation
  string output_file = "./test_cases_wfg_3d.csv";

  r_point.resize(d);
  for (int i = 0; i < d; ++i) {
    r_point[i] = max_v;
  }
  set_points.resize(n);
  for (int i = 0; i < n; ++i) {
    set_points[i].resize(i + 1);
    for (int j = 0; j < i + 1; ++j) {
      set_points[i][j].resize(d);
    }
  }
  hv.resize(n);
  
  // Generate points
  std::random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<double> gen(0.0, 10.0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i + 1; ++j) {
      for (int k = 0; k < d; ++k) {
        set_points[i][j][k] = gen(mt);
      }
    }
  }
  
  // Calc hypervolumes
  for (int i = 0; i < n; ++i) {
    cout << "i:" << i << endl;
    //hv2d calculator = hv2d(true);
    hvwfg calculator = hvwfg(d+1);
    hv[i] = calculator.compute(set_points[i], r_point);
  }

  // Save results to the file
  ofstream ofs(output_file);
  for (int i = 0; i < n; ++i) {
    ofs << "[";
    for (int j = 0; j < i + 1; ++j) {
      ofs << "[";
      for (int k = 0; k < d - 1; ++k) {
        ofs << set_points[i][j][k] << ",";
      }
      ofs << set_points[i][j][d-1] << "]";
      if (j < i) ofs << ",";
    }
    ofs << "] ";

    ofs << "[";
    for (int j = 0; j < d; ++j) {
      ofs << r_point[j];
      if (j < d - 1) ofs << ",";
    }
    ofs << "] ";

    ofs << hv[i] << endl;
  }

  return 0;
}

