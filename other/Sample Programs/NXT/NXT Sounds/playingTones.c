
task main()
{
	// First argument is the frequency or tone of the sound in Hertz (Hz)
  // The second is the duration in 10 ms, i.e.
  // 20 means 200 ms and 200 means 2000 ms or 2 seconds.
	playTone(400, 20);

	// Wait while the sound is playing in the background.
	// The bSoundActive variable will be "true" until the
	// NXT is done playing the tone.
	while(bSoundActive)
		sleep(1);

	// Play a sound at 600 Hz for 200 ms.
	playTone(600, 20);
	while(bSoundActive)
		sleep(1);

	return;
}
