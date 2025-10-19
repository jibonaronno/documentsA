### Demo Streaming class backfeed.py

This backfeed.py class reads a text file and send the data to the main window.
In k2_rythm.py at
```python
    @Slot()
    def on_btnstream_clicked(self):
        self.streamer = Backfeed('log4.txt')
        self.streamer.setCallback(self.getStreamData)
        self.streamer.Start(100)
```
see that ```self.getStreamData``` is registered to the callback, hence ```getStreamData``` eventually calls to ```self.LungSensorData(line)``` which is the main graph displaying and other dicision makin function.