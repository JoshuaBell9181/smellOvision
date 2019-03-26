package gui;

import jssc.SerialPort;
import jssc.SerialPortException;

public class PauseVideo implements Runnable{
	
	static String videoStatus = null;
	VideoStatus status = new VideoStatus();
	
	public PauseVideo(VideoStatus video){
		this.status = video;
	}
	

	@Override
	public void run() {
		
		try {
				SerialPort serialPort = new SerialPort("/dev/tty.usbmodem1421");
				System.out.println("Port opened: " + serialPort.openPort());
				System.out.println("Paramaters set: " + serialPort.setParams(9600, 8, 1, 0));
				while(videoStatus == null ) {
					videoStatus = serialPort.readString();
				}
				if(videoStatus.equalsIgnoreCase("p")) {
					status.setText(videoStatus);
				}else {
					status.setText(videoStatus);
				}
				videoStatus = null;
				System.out.println("FRDMk64 response: " + status);
				System.out.println("Port closed: " + serialPort.closePort());
				getRun();
			}
			catch(SerialPortException ex) {
				System.out.println(ex);
			}
		}
	
	private void getRun() {
		run();
	}
	

}
