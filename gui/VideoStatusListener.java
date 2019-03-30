package gui;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaPlayer.Status;


/*
 * Created By: Joshua Bell
 * Description: Creates a listener object to determine if pause/play detected
 */

public class VideoStatusListener implements PropertyChangeListener {

	MediaPlayer mediaPlayer;
	
	public VideoStatusListener(MediaPlayer mediaPlayer) {
		this.mediaPlayer = mediaPlayer;
	}
	
	@Override
	public void propertyChange(PropertyChangeEvent event) {
		if (event.getPropertyName().equals("MyTextProperty")) {
			
			Status currentStatus = mediaPlayer.getStatus();
			
			if(currentStatus == Status.PLAYING) {
				mediaPlayer.pause();
			} else if(currentStatus == Status.PAUSED || currentStatus == Status.STOPPED) {
				System.out.println("Player will start at:" + mediaPlayer.getCurrentTime());
				mediaPlayer.play();
			}
        }
	}

}
