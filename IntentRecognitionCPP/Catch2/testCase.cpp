// CATCH_CONFIG_MAIN is defined in the testMain.cpp
// This is the TEST CASE

#include <iostream>
#include <speechapi_cxx.h>
#include "catch.hpp"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;
using namespace Microsoft::CognitiveServices::Speech::Intent;

auto testIntent()
{
    auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
    auto config = SpeechConfig::FromSubscription("8f22cb7c3f0e40f2ad26080eae122317", "westeurope");
    auto intentRecognizer = IntentRecognizer::FromConfig(config, audioConfig);

    intentRecognizer->AddIntent("(What | How) [ is ] [ the ] {climate} [like] (today | now).", "GetWeather");
    intentRecognizer->AddIntent("(What | How) [ is ] [ the ] {city:climate} [ like ] in {city:name} (today | now).", "GetWeatherCity");
    intentRecognizer->AddIntent("(Tell | Say) [me] [an | a] [interesting | some] {fact}", "GetFact");

    std::cout << "Say something for the intent recognition..." << std::endl;
    auto intent = intentRecognizer->RecognizeOnceAsync().get();

    switch (intent->Reason)
    {
    case ResultReason::RecognizedSpeech:
    {
        std::cout << "RECOGNIZED VOICE... " << std::endl;
        std::cout << "Speech to Text: " << intent->Text.c_str() << std::endl;
        std::cout << "NO INTENT COULD BE RECOGNIZED FROM THE VOICE!" << std::endl;
        return "RECOGNIZED SPEECH";
        break;
    }

    case ResultReason::RecognizedIntent:
    {
        std::cout << "INTENT RECOGNIZED..." << std::endl;
        std::cout << "Speech to Text: " << intent->Text.c_str() << std::endl;
        std::cout << "Intent: " << intent->IntentId.c_str() << std::endl;

        auto entities = intent->GetEntities();

        if (entities.find("climate") != entities.end())
        {
            std::cout << "Recognized Intent: = " << entities["climate"].c_str() << std::endl;
        }
        else if (entities.find("city:climate") != entities.end())
        {
            std::cout << "Recognized Intent: = " << entities["city:climate"].c_str() << " in " << entities["city:name"].c_str() << std::endl;
        }
        else if (entities.find("fact") != entities.end())
        {
            std::cout << "Recognized Intent: = " << entities["fact"].c_str() << std::endl;
        }
        return "RECOGNIZED INTENT";
        break;
    }
    case ResultReason::NoMatch:
    {
        auto noMatch = NoMatchDetails::FromResult(intent);
        switch (noMatch->Reason)
        {
        case NoMatchReason::NotRecognized:
            std::cout << "NOMATCH: Speech was detected, but could not be recognized." << std::endl;
            break;
        case NoMatchReason::InitialSilenceTimeout:
            std::cout << "NOMATCH: SILENT AUDIO STREAM. SERVICE TIME OUT!" << std::endl;
            std::cout << "The audio stream contains only silence, and the service timed out waiting for the speech." << std::endl;
            break;
        case NoMatchReason::InitialBabbleTimeout:
            std::cout << "NOMATCH: NOISY AUDIO STREAM. SERVICE TIME OUT!" << std::endl;
            std::cout << "The audio stream contains only noise, and the service timed out waiting for the speech." << std::endl;
            break;
        case NoMatchReason::KeywordNotRecognized:
            std::cout << "NOMATCH: Keyword UNRECOGNIZED!" << std::endl;
            break;
        }
        return "UNRECOGNIZED SPEECH";
        break;
    }
    default:
        return "NO CONNECTION";
        break;
    }
}

TEST_CASE("TEST INTENT", "[intent]")
{
    auto testClear = false;
    auto feedBack = testIntent();

    if (feedBack == "RECOGNIZED INTENT")
    {
        testClear = true;
    }
    else if (feedBack == "RECOGNIZED SPEECH")
    {
        testClear = true;
    }
    else if (feedBack == "UNRECOGNIZED SPEECH")
    {
        testClear = true;
    }
    else
    {
        testClear = false;
    }

    // The test case will pass if an intent has been recognized or voice has been identified or if the voice couldnt be recognized due to silence or noise. 
    // The test case is designed to fail in the event of conenction not being established with the Cognitive Speech Service.

    if (testClear == true && feedBack == "RECOGNIZED INTENT")
    {
        REQUIRE(feedBack == "RECOGNIZED INTENT");
    }
    else if (testClear == true && feedBack == "RECOGNIZED SPEECH")
    {
        REQUIRE(feedBack == "RECOGNIZED SPEECH");
    }
    else if (testClear == true && feedBack == "UNRECOGNIZED SPEECH")
    {
        REQUIRE(feedBack == "UNRECOGNIZED SPEECH");
    }
    else
    {
        std::cout << "Connection is not established with the Cognitive Speech Service. Unable to complete the test!" << std::endl;
        REQUIRE(feedBack != "NO CONNECTION");
    }
}