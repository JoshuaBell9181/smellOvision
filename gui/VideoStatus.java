package gui;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;


/*
 * Created By: Joshua Bell
 * Description: Creates an object to determine the status of the video
 */

public class VideoStatus {
    protected PropertyChangeSupport propertyChangeSupport;
    private String text;

    public VideoStatus () {
        propertyChangeSupport = new PropertyChangeSupport(this);
    }

    public void setText(String text) {
        String oldText = this.text;
        this.text = text;
        propertyChangeSupport.firePropertyChange("MyTextProperty",oldText, text);
    }

    public void addPropertyChangeListener(PropertyChangeListener listener) {
        propertyChangeSupport.addPropertyChangeListener(listener);
    }
}
