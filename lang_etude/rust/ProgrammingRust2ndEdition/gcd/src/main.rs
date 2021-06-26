
// The fn keyword introduces a function. Here, we're defining a function named
// gcd, which takes two parameters a and b, each of which is of type u64,
// an unsigned 64-bit integer. The -> token precedes the return type: our
// function returns a u64 value. Four-space indentation is standard Rust style.
//
// By default, once a variable is initialized, its value cant't be changed, but
// placing the mut keyword before the parameters a and b allows our function
// body to assign to them. In practice, most variables dont't get assigned to;
// the mut keyword on those that do can be a helpful hint when reading code.
fn gcd(mut a: u64, mut b: u64) -> u64 {
    // The function's body starts with a call to the assert! macro, verifying
    // that neither argument is zero. The ! character marks this as a macro
    // invocation, not a function call. Like the assert macro in C and C++,
    // Rust's assert! checks that its arguemtn is true, and if it is not,
    // terminates the program with a helpful message including the source
    // location of the failing check; this kind of abrupt termination is called
    // a panic. Unlike C and C++, in which assertions can be skipped, Rust
    // always checks assertions regardless of how the program was compiled.
    // There is also a debug_assert! macro, whose assertions are skipped when
    // the program is compiled for speed.
    assert!(a != 0 && b != 0);
    // a = bq + r
    // gcd(a,b) == gcd(b,r)
    while b != 0 {
        // A let statement declares a local variable, like r in our function. We
        // don't neet to write out r's type, as long as Rust can infer it from
        // how the variable is used. In our function, the only type that works
        // for r is u64, matching a and b. Rust only infers types withing
        // function bodies: you must write out the types of function parameters
        // and return values, as we did before. If we wanted to spell out r's
        // type, we could write:
        //   let r: u64 = a % b;
        let r = a % b;
        a = b;
        b = r;
    }
    // Rust has a return statement, but the gcd function doesn't need one. If a
    // function body ends with an expression that is not followed by a
    // semicolon, that's the function's return value. In fact, any block
    // surrounded by curly braces can function as an expression. For example,
    // this is an expression that prints a message and then yields x.cos() as
    // its value:
    // {
    //      println!("evaluating cos x");
    //      x.cos()
    // }
    a
}

// Here we define a function named test_gcd, which calls gcd and checks that it
// return correct values. The #[test] atop the definition marks test_gcd as a
// test function, to be skipped in normal compilations, but included and called
// automatically if we run our program with the cargo test command. We can have
// test functions scattered throughout our source tree, placed next to the code
// they exercise, and cargo test will automatically gather them up and run them
// all.
//
// The #[test] marker is an example of an attribute. Attributes are an
// open-ended system for marking functions and other declarations with extra
// information like attributes in C++ and C#, or annotations in Java. They're
// used to control compiler warnings and code style checks, include code
// conditionally (like #ifdef in C and C++), tell Rust how to interact with code
// written in other languages, and so on.
#[test]
fn test_gcd() {
    assert_eq!(gcd(14, 15), 1);
    assert_eq!(gcd(2*3*5*11*17, 3*7*11*13*19), 3*11);
}

// This use declaration brings the standard library trait FromStr into scope. A
// trait is a collection of methods that types can implement. Any type that
// implements the FromStr trait has a from_str method that tries to parse a
// value of that type from a string. The u64 type implements FromStr, and we'll
// call u64::from_str to parse our comand-line arguments. Although we never use
// the name FromStr elsewhere in the program, a trait must be in scope in order
// to use its methods. We'll cover traits in detail in Chapter 11.
use std::str::FromStr;
// This use declalation brings in the std::env module, which provides several
// useful functions and types for interacting with the execution environment,
// including the args function, which gives us access to the program's
// command-line arguments.
use std::env;
// Our main function doesn't return a value, so we can simply omit the -> and
// return type that would normally follow the parameter list.
fn main() {
    // We declare a mutable local variable numbers and initialize it to an empty
    // vector. Vec is Rust's growable vector type, analogous to C++'s
    // std::vector, a Python list, or a JavaScript array. Even though vectors
    // are designed to be grown and shrunk dynamically, we must still mark the
    // variable mut for Rust to let us push numbers onto the end of it.
    //
    // The type of numbers is Vec<u64>, a vector of u64 values, but as before,
    // we don't need to write that out. Rust will infer it for us, in part
    // because what we push onto the vector are u64 values, but also because we
    // pass the vector's elements to gcd, which accepts only u64 values.
    let mut numbers = Vec::new();

    // Here we use a for loop to process our command-line arguments, setting the
    // variable arg to each argument in turn and evaluating the loop body.
    //
    // The std::env module's args function returns an iterator, a value that
    // produces each argument on demand, and indicates when we're done.
    // Iterators are ubiquitous in Rust; the standard library includes other
    // iterators that produce the elements of a vector, the lines of a file,
    // messages recieved on a communications channel, and almost anything else
    // that make sense to loop over. Rust's iterators are very efficient: the
    // compiler is usually able to translate then into the same code as a
    // handwritten loop. We'll show how this works and give examples in Chapter
    // 15.
    //
    // Beyond their use with for loops, iterators include a broad selection of
    // methods you can use directly. For example, the first value produced by
    // the iterator returned by args is always the name of the program being
    // run. We want to skip that, so we call the iterator's skip method to
    // produce a new iterator that omits that first value.
    for arg in env::args().skip(1) {
        // Here we call u64::from_str to attempt to parse our command-line
        // argument arg as an unsigned 64-bit integer. Rather than a method
        // we're invoking on some u64 value we have at hand, u64::from_str is a
        // function associated with the u64 type, akin to a static method in C++
        // or Java. The from_str function doesn't return a u64 directly, but
        // rather a Result value that indicates whether the parse succeeded or
        // failed. A Result value is one of two variants:
        //   - A value written Ok(v), indicating that the parse succeeded and
        //   v is the value produced
        //   - A value written Err(e), indicating that the parse failed and e is
        //   an error value explaining why
        //
        //   We use Result's expect method to check the success of our parse. If
        //   the result is an Err(e), expect prints a message that includes a
        //   description of e and exits the program immediately. However, if the
        //   result is Ok(v), expect simply returns v itself, which we are
        //   finally able to push onto the end of our vector of numbers.
        numbers.push(u64::from_str(&arg)
                     .expect("error parsing argument"));
    }

    // There's no greatest common divisor of an empty set of numbers, so we
    // check that our vector has at least one element and exit the program with
    // an error if it doesn't. We use the eprintln! macro to write our error
    // message to the standard error output stream.
    if numbers.len() == 0 {
        eprintln!("Usage: gcd NUMBER ...");
        std::process::exit(1);
    }

    // This loop uses d as its running value, updating it to stay the greatest
    // common divisor of all the numbers we've processed so far. As before, we
    // must mark d as mutable so that we can assign to it in the loop.
    //
    // When we iterate, we want to tell Rust that ownership of the vector should
    // remain with numbers; we are merely borrowing its elements for the loop.
    // The & operator in &numbers[1..] borrows a reference to the vector's
    // elements from the second onward. The for loop iterates over the
    // referenced elements, letting m borrow each element in succession. The *
    // operator in *m dereferences m, yielding the value it refers to; this is
    // the next u64 we want to pass to gcd.
    // Finally, since numbers owns the vector, Rust automatically frees it when
    // numbers goes out of scope at the end of main.
    let mut d = numbers[0];
    for m in &numbers[1..] {
        d = gcd(d, *m);
    }

    // Having iterated over the elements of numbers, the program prints the
    // result to the standard output stream. The println! macro takes a template
    // string, substitutes formatted versions of the remaining argument for the
    // {...} forms as they appear in the template string, and writes the result
    // to the standard output stream.
    println!("The greatest common divisor of {:?} is {}",
             numbers, d);
}
