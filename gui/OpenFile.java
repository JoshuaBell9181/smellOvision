package gui;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileNameExtensionFilter;

import javafx.application.Application;
import jssc.SerialPort;
import jssc.SerialPortException;

import javax.swing.JButton;
import javax.swing.JFileChooser;

import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.nio.file.CopyOption;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.awt.event.ActionEvent;



/*
 * Created By: Joshua Bell
 * Description: Creates a graphical user interface for the user to select file to play
 */

public class OpenFile extends JFrame {

	private JPanel contentPane;
	private String filePath;
	private String mp4File;
	private String timeInSeconds;

	/**
	 * Create the frame.
	 */
	public OpenFile(String args[]) {
		fileChose();
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JButton btnNewButton = new JButton("Start Video");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				//Sending serial communication
				try {
					SerialPort serialPort = new SerialPort("/dev/tty.usbmodem1421");
					System.out.println("Port opened: " + serialPort.openPort());
					System.out.println("Paramaters set: " + serialPort.setParams(9600, 8, 1, 0));
					char time[] = timeInSeconds.toCharArray();
					for(int i = 0; i < time.length; i++) {
						serialPort.writeByte((byte) time[i]);
					}
					System.out.println("FRDMk64 response: " + serialPort.readString());
					System.out.println("Port closed: " + serialPort.closePort());
				}
				catch(SerialPortException ex) {
					System.out.println(ex);
				}
				
				VideoPlayer.path = mp4File;
				Application.launch(VideoPlayer.class,args);
			}
		});
		btnNewButton.setBounds(146, 81, 166, 86);
		contentPane.add(btnNewButton);
	}
	
	public void fileChose() {
		JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File(System.getProperty("user.home")));
        FileNameExtensionFilter filter = new FileNameExtensionFilter("SMELLOVISION File", "smellOvision", "smell");
        fileChooser.setFileFilter(filter);
        int result = fileChooser.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            filePath = selectedFile.getAbsolutePath();
            System.out.println("Selected file: " + selectedFile.getAbsolutePath());
            mp4File = selectedFile.getAbsolutePath().substring(0,selectedFile.getAbsolutePath().indexOf('.') + 4);
            timeInSeconds = filePath.substring(mp4File.length()+1);
            timeInSeconds = timeInSeconds.substring(0, timeInSeconds.indexOf('.')+1);
            System.out.println("Time: " + timeInSeconds);
            try {
				copyFile_Java7(filePath, mp4File);
			} catch (IOException e) {
				System.out.println("There was an error creating the mp4 file.");
			}
        } 
	}
	
    public static void copyFile_Java7(String origin, String destination) throws IOException {
        Path FROM = Paths.get(origin);
        Path TO = Paths.get(destination);
        //overwrite the destination file if it exists, and copy
        // the file attributes, including the rwx permissions
        CopyOption[] options = new CopyOption[]{
          StandardCopyOption.REPLACE_EXISTING,
          StandardCopyOption.COPY_ATTRIBUTES
        }; 
        Files.copy(FROM, TO, options);
    }
}
