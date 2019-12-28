use math::round;
use std::env::args;
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;
use std::io::Result;

/// Main entry point
fn main() -> Result<()> {
    let args: Vec<String> = args().collect();
    let filename = &args[1];

    println!("Using puzzle input '{}'", filename);
    let f = File::open(filename)?;
    let reader = BufReader::new(f);

    let mut total_fuel = 0.0;
    for line in reader.lines() {
        total_fuel += calculate_fuel_required(
            line.expect("Unable read line from file")
                .parse::<f64>()
                .unwrap(),
        );
    }
    println!("Total fuel required: {}", total_fuel);
    Ok(())
}

/// Calculates the fuel required for a module of mass.
///
/// # Arguments
///
/// * `mass` - A float holding the mass of a module
fn calculate_fuel_required(mass: f64) -> f64 {
    return round::floor(mass / 3., 0) - 2.0;
}
