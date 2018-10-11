
task main()
{
  // Play a sound file.
  playSoundFile("Woops.rso");

  // Wait while the sound is playing in the background.
  // The bSoundActive variable will be "true" until the
  // NXT is done playing the sound file.
  while(bSoundActive)
    sleep(1);
}
