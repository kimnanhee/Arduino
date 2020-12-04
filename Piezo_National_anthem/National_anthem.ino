int piezo = 5;

int tones[] = {0, 261, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 783, 880, 987, 1046}; // NULL,도,레,레,미, ..., 도
int times[] = {500,1000, 1500, 3000}; // 8분읍표, 4분음표, 점4분음표, 점2분음표

int arr_eum[] = {5,8,7,6, 8,5,3,5, 8,9,10,11,10,9,0,   12,11,10,9, 8,7,6,5,3, 5,8,9,9,10,8,0};
int arr_time[] = {1,2,0,1, 1,1,1,1, 1,0,0,2,0,3,1,   2,0,1,1, 1,0,0,1,1, 1,1,0,0,1,3};
int numTones = 31;

void setup()
{

}

void loop()
{
  int i;
  for(i=0; i<numTones; i++)
  {
    if(tones[arr_eum[i]]==0) noTone(piezo); // 쉼표
    else tone(piezo, tones[arr_eum[i]]); // 음표
    delay(times[arr_time[i]]/3);
    
    noTone(piezo);
    delay(50);
  }
  delay(5000);
}