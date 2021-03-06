#ifndef TRACKPROCESSOR_H_INCLUDED
#define TRACKPROCESSOR_H_INCLUDED

#include "TrackBase.h"

class TrackProcessor : public TrackBase
{
public:
    enum SoloState
    {
        thisTrack,
        otherTrack,
        noTracks,
    };

    TrackProcessor (File& file, int64 startSample = 0);
    TrackProcessor (MemoryInputStream* input, int64 startSample = 0);
    TrackProcessor (const TrackProcessor& processor);

    void prepareToPlay (double sampleRate, int maxExpectedBlockSize) override;
    void processBlock (AudioBuffer<float> &buffer, MidiBuffer &midiMessages) override;
    void releaseResources() override;
    
    int64 getLengthSamples() const override { return transportSource.getTotalLength(); }
    AudioFormatReader* getReader() const { return reader; }
    AudioFormatManager& getFormatManager() { return formatManager; }

    File getFile() const { return file; }
    void setFile (File& newFile);

    void setupTransportSource (InputStream* inputStream);

private:
    File file;

    AudioFormatManager formatManager;
    AudioFormatReader* reader;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;

    JUCE_LEAK_DETECTOR (TrackProcessor)
};

#endif // !TRACKPROCESSOR_H_INCLUDED
