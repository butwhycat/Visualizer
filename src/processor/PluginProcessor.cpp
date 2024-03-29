#include "PluginProcessor.h"
#include "../editor/PluginEditor.h"

VisualizerProcessor::VisualizerProcessor()
	: AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::mono(), true)
#endif
		.withOutput("Output", AudioChannelSet::mono(), true)
#endif
	) {
}

VisualizerProcessor::~VisualizerProcessor() = default;

const String VisualizerProcessor::getName() const {
	return JucePlugin_Name;
}

bool VisualizerProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool VisualizerProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool VisualizerProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double VisualizerProcessor::getTailLengthSeconds() const {
	return 0.0;
}

int VisualizerProcessor::getNumPrograms() {
	return 1;
	// NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int VisualizerProcessor::getCurrentProgram() {
	return 0;
}

void VisualizerProcessor::setCurrentProgram(int index) {
	ignoreUnused(index);
}

const String VisualizerProcessor::getProgramName(int index) {
	ignoreUnused(index);
	return {};
}

void VisualizerProcessor::changeProgramName(int index, const String& newName) {
	ignoreUnused(index, newName);
}

void VisualizerProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
	// Use this method as the place to do any pre-playback
	// initialisation that you need...
	ignoreUnused(sampleRate, samplesPerBlock);
}

void VisualizerProcessor::releaseResources() {
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

bool VisualizerProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
	ignoreUnused (layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
	    && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}

void VisualizerProcessor::processBlock(AudioBuffer<float>& buffer,
                                       MidiBuffer& midiMessages) {
	ignoreUnused(midiMessages);

	ScopedNoDenormals noDenormals;
	const auto totalNumInputChannels = getTotalNumInputChannels();
	const auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.
	for (int channel = 0; channel < totalNumInputChannels; ++channel) {
		auto* channelData = buffer.getWritePointer(channel);
		ignoreUnused(channelData);
		// ..do something to the data...
	}
}

bool VisualizerProcessor::hasEditor() const {
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VisualizerProcessor::createEditor() {
	return new VisualizerEditor(*this);
}

void VisualizerProcessor::getStateInformation(MemoryBlock& destData) {
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
	ignoreUnused(destData);
}

void VisualizerProcessor::setStateInformation(const void* data, int sizeInBytes) {
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
	ignoreUnused(data, sizeInBytes);
}

// This creates new instances of the plugin...
AudioProcessor*JUCE_CALLTYPE createPluginFilter() {
	return new VisualizerProcessor();
}
