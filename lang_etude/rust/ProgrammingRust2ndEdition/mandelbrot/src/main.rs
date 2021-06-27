use num::Complex;
/// Try to determine if `c` is in the Mandelbrot set, using at most `limit`
/// iterations to decide.
///
/// If `c` is not a member, return `Some(i)`, where `i` is the number of
/// iterations it took for `c` to Leave the circle of radius 2 centered on the
/// origin.  If `c` seems to be a member (more precisely, if we reached the
/// iteration limit without being able to prove that `c` is not a member),
/// return `None`.
// This function's return value is an Option<usize>. Rust's standard library
// defines the Option type as follows:
//  enum Option<T> {
//      None,
//      Some(T),
//  }
fn escape_time(c: Complex<f64>, limit: usize) -> Option<usize> {
    let mut z = Complex { re: 0.0, im: 0.0 };
    for i in 0..limit {
        // z.norm_sqr() method call returns the square of z's distance from the
        // origin.
        if z.norm_sqr() > 4.0 {
            return Some(i);
        }
        z = z * z + c;
    }
    None
}

use std::str::FromStr;
/// Parse the string `s` as a coordinate pair, like `"400x600"` or `"1.0,0.5"`.
///
/// Specifically, `s` should have the form <left><sep><right>, where <sep> is
/// the character given by the `separator` argument, and <left> and <right> are
/// both strings that can be parsed by `T::from_str`. `separator` must be an
/// ASCII character.
///
/// If `s` has the proper form, return `Some<(x,y)>`. If it doesn't parse
/// correctly, return `None`.
// The definition of parse_pair is a generic function:
// You can read the clause <T: FromStr> aloud as, "For any type T that
// implements the FromStr trait..." This effectively let us define an entire
// family of functions at once: parse_pari<i32> is a function that parses pair
// of i32 values, parse_pair::<f64> parses pair of floating-point values, and so
// on.
//
// Our return type is Option<(T,T)>: either None or a value Some((v1,v2)), where
// (v1, v2) is a tuple of two values, both of type T.
// The parse_pair function doesn't use an explicit return statement, so its
// return value is the value of the last (and the only) expression in its body:
fn parse_pair<T: FromStr>(s: &str, separator: char) -> Option<(T, T)> {
    // The String type's find method searches the string for a character that
    // matches `separator`. If `find` returns `None`, meaning that the separator
    // character doesn't occur in the string, the entire match expression
    // evaluates to None, indicating that the parse failed.
    // Otherwise, we take index to be the separator's position in the string.
    match s.find(separator) {
        None => None,
        Some(index) => {
            // This begins to show off the power of the match expression.
            // The argument to the match is this tuple expression:
            // The expressions &s[..index] and &s[index+1..] are slices of the
            // string, preceding and following the separator. The type parameter
            // T's associated from_str function takes each of these and tries to
            // parse them as a value of type T, producing a tuple of results.
            match (T::from_str(&s[..index]), (T::from_str(&s[index+1..]))) {
                (Ok(l), Ok(r)) => Some((l,r)),
                // The wildcard pattern _ matches anything and ignores its
                // value.
                _ => None
            }
        }
    }
}
#[test]
fn test_parse_pair() {
    assert_eq!(parse_pair::<i32>("",        ','), None);
    assert_eq!(parse_pair::<i32>("10,",     ','), None);
    assert_eq!(parse_pair::<i32>(",10",     ','), None);
    // When you use a generic function, Rust will often be able to infer type
    // parameters for you, and you won't need to write them out.
    assert_eq!(parse_pair("10,20",   ','), Some((10,20)));
    assert_eq!(parse_pair::<i32>("10,20xy", ','), None);
    assert_eq!(parse_pair::<f64>("0.5x",    'x'), None);
    assert_eq!(parse_pair("0.5x1.5", 'x'), Some((0.5,1.5)));
}

/// Parse a pair of floating-point numbers separated by a comma as a complex
/// number.
fn parse_complex(s: &str) -> Option<Complex<f64>> {
    match parse_pair::<f64>(s, ',') {
        Some((re, im)) => Some(Complex {re, im}),
        None => None
    }
}
#[test]
fn test_parse_complex() {
    // We can use a shorthand notation to build the Complex value. It's common
    // to initialize a struct's fields with variables of the same name, so
    // rather than forcing you to write Complex { re: re, im: im }, Rust lets
    // you simply write Complex { re, im }. This is modeled on similar notations
    // in JavaScript and Haskell.
    let re = 1.25;
    let im = -0.0625;
    assert_eq!(parse_complex("1.25,-0.0625"),
                Some(Complex {re, im}));
    assert_eq!(parse_complex("1.1000,0"),
                Some(Complex {re: 1.1, im: 0.0}));
    assert_eq!(parse_complex(",-0.0625"), None);
}

/// Given the row and column of a pixel in the output image, return the
/// corresponding point on the complex plane.
///
/// `bounds` is a pair giving the width and height of the image in pixels.
/// `pixel` is a (column, row) pair indicating a particular pixel in that
/// image.
/// The `upper_left` and `lower_right` parameters are points on the complex
/// plane designating the area our image covers.
fn pixel_to_point(bounds: (usize, usize),
                  pixel: (usize, usize),
                  upper_left: Complex<f64>,
                  lower_right: Complex<f64>) -> Complex<f64>
{
    //   pixel.0
    // This refers to the first element of the tuple pixel.
    //   pixel.0 as f64
    // This is Rust's syntax for a type conversion: this converts pixel.0 to
    // an f64 value. Unlike C and C++, Rust generally refuses to convert between
    // numeric types implicitly; you must write out the conversions you need.
    let (pw, ph) = (bounds.0 as f64, bounds.1 as f64);
    let (px, py) = (pixel.0 as f64, pixel.1 as f64);
    //
    //                px
    //        ___________________
    //        |                 |
    //     py |       .         |
    //        |                 |
    //        |_________________|
    //                         pw \ ph
    //
    let (ulx, uly) = (upper_left.re, upper_left.im);
    let (lrx, lry) = (lower_right.re, lower_right.im);
    //    (ulx, uly)
    //        ________________________________
    //        |                              |
    //        |                              |
    //        |                              |
    //        |         .                    |
    //        |                              |
    //        |                              |
    //        |______________________________|
    //                                   (lrx, lry)

    Complex { re: ulx + px/pw*(lrx-ulx), im: uly - py/ph*(uly-lry) }
}

#[test]
fn test_pixel_to_point() {
//fn pixel_to_point(bounds: (usize, usize),
//                  pixel: (usize, usize),
//                  upper_left: Complex<f64>,
//                  lower_right: Complex<f64>)

    let mut b = (300, 500);
    let mut p = (100, 200);
    let mut ul = Complex { re: 0.0, im: 500.0};
    let mut lr = Complex { re: 300.0, im: 0.0};
    assert_eq!(pixel_to_point(b,p,ul,lr), Complex { re: 100.0, im: 300.0 });

    p = (0, 0);
    assert_eq!(pixel_to_point(b,p,ul,lr), Complex { re: 0.0, im: 500.0 });
    p = (300, 500);
    assert_eq!(pixel_to_point(b,p,ul,lr), Complex { re: 300.0, im: 0.0 });
    p = (0, 500);
    assert_eq!(pixel_to_point(b,p,ul,lr), Complex { re: 0.0, im: 0.0 });
    p = (300, 0);
    assert_eq!(pixel_to_point(b,p,ul,lr), Complex { re: 300.0, im: 500.0 });

    b = (100, 200);
    p = (25, 175);
    ul = Complex { re: -1.0, im: 1.0 };
    lr = Complex { re: 1.0, im: -1.0 };
    assert_eq!(pixel_to_point(b,p,ul,lr), Complex { re: -0.5, im: -0.75 });

    b = (0, 200);
    assert_eq!(pixel_to_point(b,p,ul,lr), Complex { re: f64::INFINITY, im: -0.75 });

}

/// Render a rectangle of the Mandelbrot set into a buffer of pixels.
///
/// The `bounds` argument gives the width and height of the buffer `pixels`,
/// which holds one grayscale pixel per byte. The `upper_left` and `lower_right`
/// arguments specify points on the complex plane corresponding to the
/// upper-left and lower-right corners of the pixel buffer.
fn render(pixels: &mut [u8],
          bounds: (usize, usize),
          upper_left: Complex<f64>,
          lower_right: Complex<f64>) {
    for h in 0..bounds.1 {
        for w in 0..bounds.0 {
            let p = pixel_to_point(bounds, (w,h), upper_left, lower_right);
            pixels[w + h * bounds.0] =
                match escape_time(p, 255) {
                    None => 0,
                    Some(count) => 255 - count as u8
                }
        }
    }
}

use image::ColorType;
use image::png::PNGEncoder;
use std::fs::File;

/// Write the buffer `pixels`, whose dimensions are given by `bounds`, to the
/// file named `filename`.
// Fallible functions in Rust should return a Result value, which is either
// Ok(s) on success, where s is the successful value, or Err(e) on failure,
// where e is an error code. So what are write_image's success and error types?
fn write_image(filename: &str, pixels: &[u8], bounds: (usize, usize))
    -> Result<(), std::io::Error> {
    // When an error occurs, it's because either File::create wasn't able to
    // create the file or encoder.encode wasn't able to write the image to it;
    // the I/O operation returned an error code. The return type of File::create
    // is Result<std::fs::File, std::io::Error>, while that of encoder.encode is
    // Result<(), std::io::Error>, so both share the same error type,
    // std::io::Error. It makes sense for our write_image function to do the
    // same.
    //
    // So to properly handle File::create's result, we need to match on its
    // return value, like this:
    //  let output = match File::create(filename) {
    //      Ok(f) => f,
    //      Err(e) => {
    //          return Err(e);
    //      }
    //  };
    //
    // This kind of match statement is such a common pattern in Rust that the
    // language provies the ? operator as shorthand for the whole thing. So,
    // rathar than writing out this logic explicitly every time we attempt
    // something that could fail, you can use the following equivalent and much
    // more legible statement:
    let output = File::create(filename)?;

    let encoder = PNGEncoder::new(output);
    encoder.encode(&pixels,
                   bounds.0 as u32, bounds.1 as u32,
                   ColorType::Gray(8))?;

    // When all goes well, our write_image function has no useful value to
    // return;
    // So its success type is the unit type (), so called because it has only
    // one value, also written (). The unit type is akin to void in C and C++.
    Ok(())
}

use std::env;
fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 5 {
        eprintln!("Usage: {} FILE PIXELS UPPERLEFT LOWERRIGHT",
                  args[0]);
        eprintln!("Example: {} mandel.png 1000x750 -1.20,0.35 -1,0.20",
                  args[0]);
        std::process::exit(1);
    }

    let filename = &args[1];
    // bounds.0 is width
    // bounds.1 is height of the output image.
    let bounds = parse_pair::<usize>(&args[2], 'x')
        .expect("error parsing image dimensions");
    let ul = parse_complex(&args[3])
        .expect("error parsing upper left corner point");
    let lr = parse_complex(&args[4])
        .expect("error parsing lower right corner point");

    let mut pixels = vec![0; bounds.0 * bounds.1];

    let threads = 8;
    let rows_per_band = bounds.1 / threads + 1;
    {
        let bands: Vec<&mut [u8]> =
            pixels.chunks_mut(rows_per_band * bounds.0).collect();
        crossbeam::scope(|spawner| {
            for (i, band) in bands.into_iter().enumerate() {
                let top = rows_per_band * i;
                let height = band.len() / bounds.0;
                let band_bounds = (bounds.0, height);
                let band_p_ul = (0, top);
                let band_p_lr = (bounds.0, top + height);
                let band_ul = pixel_to_point(bounds, band_p_ul, ul, lr);
                let band_lr = pixel_to_point(bounds, band_p_lr, ul, lr);
                spawner.spawn(move |_| {
                    render(band, band_bounds, band_ul, band_lr);
                });
            }
        }).unwrap();
    }

    write_image(&filename, &pixels, bounds)
        .expect("error writing PNG file");
}
