fn gcd(mut a: u64, mut b: u64) -> u64 {
    assert!(a != 0 && b != 0);
    while b != 0 {
        let r = a % b;
        a = b;
        b = r;
    }
    a
}

// We start with a use declaration to make some of the actix-web crate's
// definitions easier to get at. When we write use actix_web::{...}, each of the
// names listed inside the curly brackets becomes directly usable in our code;
// instead of having to spell out the full name actix_web::HttpResponse each
// time we use it, we can simply refer to it as HttpResponse.
use actix_web::{web, App, HttpResponse, HttpServer};

fn main() {
    // Create a server that responds to requests for a single path, "/";
    //
    // The argument we pass to HttpServer::new is the Rust closure expression ||
    // { App::new() ... }. A closure is a value that can be called as if it were
    // a function. This closure takes no arguments, but if it did, their names
    // would be appear between the || vertical bars. The {...} is the body of
    // the closure. When we start our server, Actix starts a pool of threads to
    // handle incoming requests. Each thread calls our closure to get a fresh
    // copy of the App value that tels it how to route and handle requests.
    let server = HttpServer::new(|| {
        // This closure calls App::new to create a new, empty App and then calls
        // its route method to add a single route for the path "/". The handler
        // provided for that route, web::get().to(get_index), treaants HTTP GET
        // request by calling the function get_index. The route method returns
        // the same App it was invoked on, now enhanced with the new route.
        // Since there's no semicolon at the end of the closure's body, the App
        // is the closure's return value, ready for the HttpServer thread to
        // use.
        App::new()
            .route("/", web::get().to(get_index))
            .route("/gcd", web::post().to(post_gcd))
    });

    println!("Serving on http://localhost:3000...");
    server
        .bind("127.0.0.1:3000").expect("error binding server to address.")
        .run().expect("error running server");
}

fn get_index() -> HttpResponse {
    HttpResponse::Ok()
        .content_type("text/html")
        // Since the response text contains a lot of double quotes, we write it
        // using the Rust "raw string" syntax: the letter r, zero or more hash
        // marks, a double quote folowed by the same number of hash marks. Any
        // character may occur within a raw string witout being escaped,
        // including double quotes; in fact, no escape sequences like \" are
        // recognized. We can always ensure the string ends where we intend by
        // using more hash marks around the quotes than ever appear in the text.
        .body(
            r#"
                <title>GCD Calculator</title>
                <form action"/gcd" method="post">
                <input type"text" name="a"/>
                <input type"text" name="b"/>
                <button type="submit">Compute GCD</button>
                </form>
            "#,
        )
}

use serde::Deserialize;
// Placing a #[derive(Deserialize)] attribute above a type definition tells the
// serde crate to examine the type when the program is compiled and
// automatically generate code to parse a value of this type from data in the
// format that HTML forms use for POST requests. In fact, that attribute is
// sufficient to let you parse a GcdParameters value from almost any sort of
// structured data: JSON, YAML, TOML, or any one of a number of other textual
// and binary formats.
#[derive(Deserialize)]
struct GcdParameters {
    a: u64,
    b: u64,
}

// For a function to serve as an Actix request handler, its arguments must all
// have types Actix knows how to extract from an HTTP request. Our post_gcd
// function takes one argument, form, whose type is web::Form<GcdParameters>.
// Actix knows how to extract a value of any type web::Form<T> from an HTTP
// request if, and only if, T can be deserialized from HTML from POST data.
// Since we've placed the #[derive(Deserialize)] attribute on our GcdParameters
// type definition, Actix can deserialize it from form data, so request handlers
// can expect a web::Form<GcdParameters> value as a parameter.
fn post_gcd(form: web::Form<GcdParameters>) -> HttpResponse {
    if form.a == 0 || form.b == 0 {
        return HttpResponse::BadRequest()
            .content_type("text/html")
            .body("Computing the GCD with zero is boring.")
    }

    let response =
        format!("The greatest common divisor of the numbers {} and {} \
                is <b>{}</b>\n",
                form.a, form.b, gcd(form.a, form.b));

    HttpResponse::Ok()
        .content_type("text/html")
        .body(response)
}

