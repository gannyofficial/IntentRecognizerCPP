#include <iostream>
#include <speechapi_cxx.h>

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;
using namespace Microsoft::CognitiveServices::Speech::Intent;

auto IntentRecognitionWithMicrophone()
{
    auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
    auto config = SpeechConfig::FromSubscription("8f22cb7c3f0e40f2ad26080eae122317", "westeurope");
    
    // Connection is established with Azure Cognitive Speech Service using the above subscription key and region identifier.
    
    auto intentRecognizer = IntentRecognizer::FromConfig(config, audioConfig);

    intentRecognizer->AddIntent("(What | How) [ is ] [ the ] {climate} [like] (today | now).", "GetWeather");
    intentRecognizer->AddIntent("(What | How) [ is ] [ the ] {city:climate} [ like ] in {city:name} (today | now).", "GetWeatherCity");
    intentRecognizer->AddIntent("(Tell | Say) [me] [an | a] [interesting | some] {fact}", "GetFact");

    // More intents can be added here. Intents within () are mandatory elements in the speech. Intents within [] are optional. 

    std::cout << "Say something for the intent recognition..." << std::endl;
    auto intent = intentRecognizer->RecognizeOnceAsync().get();

        switch (intent->Reason)
        {
        case ResultReason::RecognizedSpeech:
        {
            std::cout << "RECOGNIZED VOICE... " << std::endl;
            std::cout << "Speech to Text: " << intent->Text.c_str() << std::endl;
            std::cout << "NO INTENT COULD BE RECOGNIZED FROM THE VOICE!" << std::endl;
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

            // For every newly added intent, it has to be handled here for further processing. 

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
            break;
        }

       case ResultReason::Canceled:
        {
            auto cancellation = CancellationDetails::FromResult(intent);

            if (!cancellation->ErrorDetails.empty())
            {
                std::cout << "CANCELED: Error Details=" << cancellation->ErrorDetails.c_str() << std::endl;
                std::cout << "CANCELED: Check the speech resource key and region values if it is active." << std::endl;
            }
        }
        break;
        }
}

int main()
{
    try
    {
        IntentRecognitionWithMicrophone();
    }
    catch (std::exception e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
