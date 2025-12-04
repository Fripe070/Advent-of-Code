fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        println!("You must provide a file path.");
        // std::process::exit(1);
    }
    let default_path = "test".to_string();
    let file_path = args.get(1).unwrap_or(&default_path);
    let text = std::fs::read_to_string(file_path).expect("Could not read file content");

    println!("Part 1: {}", part_1(text.clone()));
    println!("Part 2: {}", part_2(text.clone()));
}

fn part_1(text: String) -> i32 {
    let tanks = text.lines();

    let mut sum = 0;
    tanks.for_each(|tank| {
        let mut highest = 0;
        for (index_a, digit_a) in tank.chars().enumerate() {
            for index_b in index_a + 1..tank.len() {
                let digit_b = tank.chars().nth(index_b).unwrap();
                let joined: String = digit_a.to_string() + &digit_b.to_string();
                let parsed = joined.parse::<i32>().unwrap();
                if parsed > highest {
                    highest = parsed;
                }
            }
        }
        sum += highest;
    });
    sum
}

fn get_best(string: &str) -> usize {
    let mut max_index: usize = 0;
    let mut max: u32 = 0;
    string.char_indices().for_each(|(i, c)| {
        let parsed = c.to_digit(10).unwrap();
        if parsed > max {
            max_index = i;
            max = parsed;
            if max == 9 {
                return;
            }
        }
    });
    max_index
}

fn part_2(text: String) -> i64 {
    let tanks = text.lines();

    let mut sum = 0;
    tanks.for_each(|tank| {
        let mut start_index = 0;
        let mut highest = "".to_string();
        for index in 0..12 {
            let end_index = tank.len() - 12 + index + 1;
            let found_index = get_best(&tank[start_index..end_index]);
            highest.push(tank.chars().nth(start_index + found_index).unwrap());
            start_index += found_index + 1;
        }
        sum += highest.parse::<i64>().unwrap();
    });
    sum
}
