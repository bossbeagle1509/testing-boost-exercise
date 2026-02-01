#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <Eigen/Dense>
#include <fstream>
#include <string>

#include "matrixIO.hpp"

BOOST_AUTO_TEST_SUITE(MatrixIOTests)

BOOST_AUTO_TEST_CASE(SimpleOpenDataTest)
{
  const std::string filename = "test_matrix.csv";
  const int size = 3;

  // Create a 3x3 matrix file
  std::ofstream file(filename);
  BOOST_REQUIRE(file.is_open());
  file << "1,2,3\n";
  file << "4,5,6\n";
  file << "7,8,9\n";
  file.close();

  // Read the matrix
  Eigen::MatrixXd m = matrixIO::openData(filename, size);

  // Check dimensions
  BOOST_REQUIRE_EQUAL(m.rows(), size);
  BOOST_REQUIRE_EQUAL(m.cols(), size);

  // Check values
  double expected[3][3] = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      BOOST_CHECK_CLOSE(m(i, j), expected[i][j], 1e-4);
    }
  }

  // Cleanup
  std::remove(filename.c_str());
}

BOOST_AUTO_TEST_SUITE_END()