use std::str;
use std::time::Duration;

use souvlaki::MediaControls;
use souvlaki::PlatformConfig;
use souvlaki::MediaControlEvent;
use souvlaki::MediaMetadata;

use raw_window_handle;

fn macro_finder() {

    let ports = serialport::available_ports().expect("No ports found!");

    for port in ports {
        println!("{}", port.port_name);
        let mut test_port = serialport::new(port.port_name, 9600).open().expect("Failed to open port");
        let command = "serial";
        let timeout = Duration::new(1, 0);
        test_port.set_timeout(timeout).expect("write failed");
        test_port.write(command.as_bytes()).expect("write failed");

        for i in 0..10 {
            println!("{:?}",i);
            // let mut serial_buf: Vec<u32> = vec![0; 32];
            // let result = test_port.read_to_string(serial_buf.as_mut_slice());
            // let result_str = str::from_utf8(&serial_buf).unwrap();

            let mut buffer = String::new();

            let result_str = test_port.read_to_string(&mut buffer);
            println!("{:?}", result_str.to_string().as_str().trim());
            // let result_str = "serial";
            // if result_str.contains(command){
            //     let connect_status = true;
            // } else {
            //     let connect_status = false;
            // }
            
        }
        
        
        
    }
}



// fn media_ctrl() {
//     #[cfg(not(target_os = "windows"))]
//     let hwnd = None;
//     #[cfg(target_os = "windows")]
//     let hwnd = {
//         use raw_window_handle::Win32WindowHandle;
//         let handle: Win32WindowHandle = unimplemented!();
//         Some(handle.hwnd)
//     };
//     let config = PlatformConfig {
//         dbus_name: "my_player",
//         display_name: "My Player",
//         hwnd,
//     };

//     let mut controls = MediaControls::new(config).unwrap();
//     controls.set_playback(souvlaki::MediaPlayback::Playing{progress: None});
// }

fn main() {
    // media_ctrl();
    macro_finder();
}
