package gui;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
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
 * Description: Creates a graphical user interface for the user to create smellOvision files
 */

public class CreateFile extends JFrame {

	private JPanel contentPane;
	private JTextField textField;
	private String filePath;
	private String timeInSeconds;
	private static String argsCopy[];


	/**
	 * Create the frame.
	 */
	public CreateFile(String argsCopy[]) {
		this.argsCopy = argsCopy;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel lblPleaseEnterThe = new JLabel("Select a video file you would like to transform");
		lblPleaseEnterThe.setBounds(65, 24, 321, 70);
		contentPane.add(lblPleaseEnterThe);
		
		textField = new JTextField();
		textField.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				timeInSeconds = textField.getText();
			}
		});
		textField.setBounds(320, 168, 109, 26);
		contentPane.add(textField);
		textField.setColumns(10);
		
		JButton btnCreateFile = new JButton("Create File");
		btnCreateFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				//Some code to create a smell file.
				try {
					if(timeInSeconds == null) {
						JFrame frame = new JFrame();
						JOptionPane.showMessageDialog(frame,"You must press enter after inserting a number into the seconds field");
						throw new IOException();
					}
					copyFile_Java7(filePath, filePath + "." + timeInSeconds + ".smellOvision");
					try {
						JFrame frame1 = new JFrame();
						JOptionPane.showMessageDialog(frame1,"The new file has been saved to the same directory\n "
															 + "your source file came from. Another file manager window\n"
															 + "will open, please select the file you have just created.");
						OpenFile frame = new OpenFile(argsCopy);
						frame.setVisible(true);
					} catch (Exception err) {
						err.printStackTrace();
					}
				} catch (IOException e1) {
					System.out.println("time left blank");
				}
			}
		});
		btnCreateFile.setBounds(89, 214, 117, 29);
		contentPane.add(btnCreateFile);
		
		JButton btnNewButton = new JButton("Open File");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				fileChose();
			}
		});
		btnNewButton.setBounds(155, 78, 117, 37);
		contentPane.add(btnNewButton);
		
		JLabel label = new JLabel("Enter time in seconds smell should be released:");
		label.setBounds(17, 146, 321, 70);
		contentPane.add(label);
	}
	
	public void fileChose() {
		JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File(System.getProperty("user.home")));
        FileNameExtensionFilter filter = new FileNameExtensionFilter("MPEG4 File", "mp4", "Megap4");
        fileChooser.setFileFilter(filter);
        int result = fileChooser.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            filePath = selectedFile.getAbsolutePath();
            System.out.println("Selected file: " + selectedFile.getAbsolutePath());
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
