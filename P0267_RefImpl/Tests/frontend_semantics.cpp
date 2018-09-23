#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static path_builder Build()
{
    path_builder pb{};
    pb.new_figure({42.f, 7.f});
    pb.rel_line({50.f, 60.f});
    pb.rel_matrix(matrix_2d::create_scale({5.f, 7.f}));
    pb.rel_line({100.f, 30.f});
    pb.matrix(matrix_2d::create_scale({7.f, 5.f}));
    pb.line({30.f, 40.f});
    pb.revert_matrix();
    pb.rel_quadratic_curve({10.f, 10.f}, {20.f, 20.f});
    pb.quadratic_curve({50.f, 50.f}, {70.f, 70.f});
    pb.close_figure();
    return pb;
}

TEST_CASE("path_builder is properly comparable with another path_builder")
{
    auto pb1 = Build();
    auto pb2 = Build();        
    CHECK( pb1 == pb2 );
    
    pb2.pop_back();
    CHECK( pb1 != pb2 );
}
