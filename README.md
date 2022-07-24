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
</details>

<details> <summary>
  Tell me an interesting fact.
  </summary>
  
* Say me an interesting fact.
* Tell me a interesting fact.
* Say me a interesting fact.
* Tell me some fact.
* Say me some fact.
* Tell some fact.
* Say some fact
* Tell a fact.
* Say a fact.
</details>
  
## Intent Recognizer - Sample Output
The sample output of few speech utterences can be seen below..

**What is the weather today**</br>

![image](https://user-images.githubusercontent.com/77659842/180663450-a0aa5b11-d049-46f3-81f5-b2c180fb8cd2.png)

**What is the weather in Paris today**</br>

![image](https://user-images.githubusercontent.com/77659842/180663278-57a14f0a-9e13-4587-b1d2-c54d2a27b218.png)

**What is the weather in Munich today**</br>

![image](https://user-images.githubusercontent.com/77659842/180663373-b6ac1550-a38c-4973-a7f3-026a39411f77.png)

**Tell me an interesting fact.** </br>

![image](https://user-images.githubusercontent.com/77659842/180663490-2c5b7041-7152-4c00-8efc-5a31be45eb4f.png)


## Catch2 Test
The catch2 test case files are located in the folder 'IntentRecognitionCPP/Catch2'. It contains 'catch.hpp' header, 'testMain.cpp' and 'testCase.cpp' test files.  

**TEST CASE: Voice & Intent Recognized** </br>

![image](https://user-images.githubusercontent.com/77659842/180663894-ec4a93a4-b875-4a0a-973e-9b25ff1f5a65.png)

**TEST CASE: Voice Recognized But No Intent Identified** </br>

![image](https://user-images.githubusercontent.com/77659842/180663918-3ed874b8-6322-48bf-9edc-2bb5791cab72.png)

**TEST CASE: Voice Not Recognized** </br>

![image](https://user-images.githubusercontent.com/77659842/180663973-4cff6d2c-5ee5-41c4-9378-b90a7677cf39.png)









