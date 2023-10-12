use std::str;
use std::time::Duration;
use std::io::{BufRead, BufReader, Read};

use serde_json;

// use souvlaki::MediaControls;
// use souvlaki::PlatformConfig;
// use souvlaki::MediaControlEvent;
// use souvlaki::MediaMetadata;

// use egui;

// use raw_window_handle;

fn read_json(in_str: &str) -> (String, i32, i32, i32, i32) {
    // takes an input string in json format and reads
    let out: serde_json::Value = serde_json::from_str(in_str).expect("Check JSON Format!");
    let keys: String = out["keys"].to_string();
    let rot_sw:i32 = out["rot_sw"].to_string().parse::<i32>().unwrap();
    let slide_0: i32 = out["slide_0"].to_string().parse::<i32>().unwrap();
    let slide_1: i32 = out["slide_1"].to_string().parse::<i32>().unwrap();
    let rot_count: i32 = out["rot_count"].to_string().parse::<i32>().unwrap();
    return (keys, rot_sw, slide_0, slide_1, rot_count)
}

fn json_to_cmd(input: (String, i32, i32, i32, i32)) {
    // takes the json and uses the information to execute functions
    if input.0.contains("A"){
        println!("A pressed");
        // call some function here and for other keys 
    }
    if input.0.contains("B"){
        println!("A pressed");
    }
    if input.0.contains("C"){
        println!("A pressed");
    }
    if input.0.contains("D"){
        println!("A pressed");
    }


}

fn main() {
    let port = serialport::new("COM8", 115_200)
        .timeout(Duration::from_millis(6000))
        .open()
        .expect("Device not found!!");

    let mut port = BufReader::new(port);
    let mut line_buffer = String::new();


    loop {
        line_buffer.clear();
        port.read_line(&mut line_buffer).expect("Read failed!");
        print!("{}", line_buffer);
        let out = read_json(&line_buffer); 

    }
}