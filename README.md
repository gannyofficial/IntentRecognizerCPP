# Intent Recognition using C++

The project was created using Visual Studio IDE and its project files can be found under the root folder. The main source code of the project 'IntentRecognitionCPP.cpp' can be found under the folder 'IntentRecognitionCPP'.

## Microsoft Speech Service
The intent recognizer works using Microsoft Cognitive Service Speech SDK. The subscription is handled using the below code snippet. 

```
auto config = SpeechConfig::FromSubscription("SUBSCRIPTION_KEY", "REGION_IDENTIFIER");
```
The intent recognizer requires an active Microsoft Speech Service subscription for the speech processing. For the purprose of this project, a free subscription has ben registered to. The subscription key which can be found inside the main source code will be valid for 4 hours and 30 minutes of speech processing with 24 days remaining, at the time of final commit. 

## Intents
The intent recognizer handles the following sentences with multiple utterences from the speech, handling different semantic variations like below..

<details> <summary>
  What is the weather like today?
  </summary>
* What is the weather like now?
* How is the weather like today?
* How is the weather like now?
* What is the weather today?
* How is the weather today?
* What is the weather now?
* How is the weather now?
* What weather today?
* What weather now?
* How weather today?
* How weather now?
</details>

<details> <summary>
  What is the weather like in "City Name" today?
  </summary>
* What is the weather like in "City Name" today?
* What is the weather like in "City Name" now?
* How is the weather like in "City Name" today?
* How is the weather like in "City Name" now?
* What is the weather in "City Name" today?
* What is the weather in "City Name" now?
* How is the weather in "City Name" today?
* How is the weather in "City Name" now?
* What weather in "City Name" today?
* What weather in "City Name" now?
* How weather in "City Name" today?
* How weather in "City Name" now?
</details>
