package gui;

import java.awt.EventQueue;

import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import java.awt.event.ActionListener;
import java.io.File;
import java.awt.event.ActionEvent;

public class MainWindow {

	private JFrame frame;
	private static String argsCopy[];

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainWindow window = new MainWindow();
					window.frame.setVisible(true);
					argsCopy = args;
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public MainWindow() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		
		JMenu mnFile = new JMenu("File");
		menuBar.add(mnFile);
		
		JMenuItem mntmCreateNew = new JMenuItem("Create New...");
		mntmCreateNew.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					CreateFile frame = new CreateFile(argsCopy);
					frame.setVisible(true);
				} catch (Exception err) {
					err.printStackTrace();
				}
			}
		});
		mnFile.add(mntmCreateNew);
		
		JMenuItem mntmOpen = new JMenuItem("Open");
		mntmOpen.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					OpenFile frame = new OpenFile(argsCopy);
					frame.setVisible(true);
				} catch (Exception err) {
					err.printStackTrace();
				}
			}
		});
		mnFile.add(mntmOpen);
		
		JMenu mnEdit = new JMenu("Edit");
		menuBar.add(mnEdit);
		
		JMenuItem mntmHelp = new JMenuItem("Help");
		mnEdit.add(mntmHelp);
	}

}

