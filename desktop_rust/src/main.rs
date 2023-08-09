use std::str;
use std::time::Duration;


fn macro_finder() {

    let ports = serialport::available_ports().expect("No ports found!");

    for port in ports {
        println!("{}", port.port_name);
        let mut test_port = serialport::new(port.port_name, 9600).open().expect("Failed to open port");
        let command = "serial_num";

        let timeout = Duration::new(1, 0);
        test_port.set_timeout(timeout).expect("write failed");
        test_port.write(command.as_bytes()).expect("write failed");
        let mut serial_buf: Vec<u8> = vec![0; 8];
        let result = test_port.read(serial_buf.as_mut_slice());
        let result_str = str::from_utf8(&serial_buf);
        println!("{:?}", result_str.expect("REASON").trim());
    }
}

fn main() {
   macro_finder();
}

