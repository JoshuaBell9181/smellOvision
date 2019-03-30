package gui;

import java.io.File;  

import javafx.application.Application;
import javafx.beans.binding.Bindings;
import javafx.beans.property.DoubleProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Group;  
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.media.Media;  
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaPlayer.Status;
import javafx.scene.media.MediaView;  
import javafx.stage.Stage;
import jssc.SerialPort;
import jssc.SerialPortException;  
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;



/*
 * Created By: Joshua Bell
 * Description: Creates a video player frame which can display .MP4 files
 */

public class VideoPlayer extends Application
{  
  
	static String path = "";
	
    @Override  
    public void start(Stage primaryStage) throws Exception {  
        // TODO Auto-generated method stub  
        //Initialising path of the media file, replace this with your file path   
        //path = "/Users/joshbell/Desktop/battleship_animation.mp4";  
          
        //Instantiating Media class  
        Media media = new Media(new File(path).toURI().toString());  
          
        //Instantiating MediaPlayer class   
        MediaPlayer mediaPlayer = new MediaPlayer(media);  
          
        //Instantiating MediaView class   
        MediaView mediaView = new MediaView(mediaPlayer);  
        
        //Fit the video to the screen
        DoubleProperty mvw = mediaView.fitWidthProperty();
        DoubleProperty mvh = mediaView.fitHeightProperty();
        mvw.bind(Bindings.selectDouble(mediaView.sceneProperty(), "width"));
        mvh.bind(Bindings.selectDouble(mediaView.sceneProperty(), "height"));
          
        //by setting this property to true, the Video will be played   
        mediaPlayer.setAutoPlay(true);  
        
        VideoStatus status = new VideoStatus();
        VideoStatusListener listener = new VideoStatusListener(mediaPlayer);
        status.addPropertyChangeListener(listener);
        
        PauseVideo pauser = new PauseVideo(status);
        
        
        Thread object = new Thread(pauser);
        object.start();
          
        //setting group and scene   
        Group root = new Group();  
        root.getChildren().add(mediaView);
        Scene scene = new Scene(root,800,500);  
        primaryStage.setScene(scene);  
        primaryStage.setTitle("Playing video");  
        primaryStage.show();  
         
    }

    
      
}  
