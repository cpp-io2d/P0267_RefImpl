#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D properly decodes PNG images")
{
    auto reference = "image_500x375.png";
    auto img = image_surface{reference, image_file_format::png, format::argb32};
    CHECK(  CompareImageColor( img, 0, 0, {66, 70, 81}, 0.01f ) == true);
}

TEST_CASE("IO2D properly encodes PNG images", "[!hide][!mayfail]") // cairo fails to properly read the duplicate for some reason 
{
    auto reference = "image_500x375.png";            
    auto duplicate = "duplicate.png";     
    auto ref_img = image_surface{reference, image_file_format::png, format::argb32};
    ref_img.save(duplicate, image_file_format::png);
    auto dup_img = image_surface{duplicate, image_file_format::png, format::argb32};
    CHECK( CompareWithPNGImage(dup_img, reference, 0.1f ) == true );
}

TEST_CASE("IO2D properly decodes JPG images")
{
    auto reference = "image_500x375.jpg";
    auto img = image_surface{reference, image_file_format::jpeg, format::argb32};
    CHECK(  CompareImageColor( img, 0, 0, {67, 69, 81}, 0.01f ) == true);
}
