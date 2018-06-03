#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D properly decodes PNG images")
{
    auto tolerance = 0.01f;
    auto reference = "image_500x375.png";
    auto img = image_surface{reference, image_file_format::png, format::argb32};
    CHECK( CompareImageColor(img, 0, 0, {66, 70, 81}, tolerance) == true );
    CHECK( CompareImageColor(img, 499, 0, {182, 196, 215}, tolerance) == true );
    CHECK( CompareImageColor(img, 499, 374, {201, 215, 235}, tolerance) == true );
    CHECK( CompareImageColor(img, 0, 374, {199, 213, 232}, tolerance) == true );
}

TEST_CASE("IO2D properly encodes PNG images", "[!mayfail]") // cairo backend fails to properly read the duplicate for some reason
{
    auto tolerance = 0.01f;
    auto reference = "image_500x375.png";            
    auto duplicate = "duplicate.png";
    auto ref_img = image_surface{reference, image_file_format::png, format::argb32};
    ref_img.save(duplicate, image_file_format::png);
    auto dup_img = image_surface{duplicate, image_file_format::png, format::argb32};    
    CHECK( CompareWithPNGImage(dup_img, reference, tolerance) == true );
}

TEST_CASE("IO2D properly decodes JPG images")
{
    auto tolerance = 0.01f;
    auto reference = "image_500x375.jpg";
    auto img = image_surface{reference, image_file_format::jpeg, format::argb32};
    CHECK( CompareImageColor(img, 0, 0, {67, 69, 81}, tolerance ) == true );
    CHECK( CompareImageColor(img, 499, 0, {181, 196, 215}, tolerance) == true );
    CHECK( CompareImageColor(img, 499, 374, {202, 215, 234}, tolerance) == true );
    CHECK( CompareImageColor(img, 0, 374, {198, 213, 232}, tolerance) == true );    
}

TEST_CASE("IO2D properly encodes JPG images")
{
    // give an implemantation a fair leeway with lossy compression, since the paper does not state anything about compression quality.    
    auto tolerance = 0.15f; 
    auto reference = "image_500x375.jpg";            
    auto duplicate = "duplicate.jpg";
    auto ref_img = image_surface{reference, image_file_format::jpeg, format::argb32};
    ref_img.save(duplicate, image_file_format::jpeg);
    auto dup_img = image_surface{duplicate, image_file_format::jpeg, format::argb32};    
    CHECK( CompareImages(dup_img, ref_img, tolerance) == true );
}

TEST_CASE("IO2D properly decodes TIFF images")
{
    auto tolerance = 0.01f;
    auto reference = "image_500x375.tiff";
    auto img = image_surface{reference, image_file_format::tiff, format::argb32};
    CHECK( CompareImageColor(img, 0, 0, {66, 70, 81}, tolerance) == true );
    CHECK( CompareImageColor(img, 499, 0, {182, 196, 215}, tolerance) == true );
    CHECK( CompareImageColor(img, 499, 374, {201, 215, 235}, tolerance) == true );
    CHECK( CompareImageColor(img, 0, 374, {199, 213, 232}, tolerance) == true );  
}

TEST_CASE("IO2D properly encodes TIFF images", "[!mayfail]") // cairo backend fails to properly read the duplicate for some reason
{
    auto tolerance = 0.01f;
    auto reference = "image_500x375.tiff";            
    auto duplicate = "duplicate.tiff";
    auto ref_img = image_surface{reference, image_file_format::tiff, format::argb32};
    ref_img.save(duplicate, image_file_format::tiff);
    auto dup_img = image_surface{duplicate, image_file_format::tiff, format::argb32};    
    CHECK( CompareImages(dup_img, ref_img, tolerance) == true );
}
