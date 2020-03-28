#include <iostream>

#include "JsonObjectSegmenter.h"

#include "StringHelper.h"
#include "JsonUtilities.h"
#include "JsonObject.h"
#include "JsonValue.h"
#include "JsonParser.h"

using namespace std;

void TestObjectSegmenter(std::string value);
void TestJsonParser(std::string value);
void TestArrayParser();
void TestShare();

int main()
{
    JsonObject *person = Create::A.JsonObject()
        //.WithName("Person")
        .WithJsonObjectType(JsonObjectType_Object)
        .Build();

    JsonValue* firstName = Create::A.JsonValue()
        .WithName("Vorname")
        .WithValue("Sepp")
        .WithParent(person)
        .Build();

    JsonValue* lastName = Create::A.JsonValue()
        .WithName("Alter")
        .WithValue(33)
        .WithParent(person)
        .Build();

    JsonObject *address = Create::A.JsonObject()
        .WithName("Addresse")
        .WithValues( [](Create::JsonValueListBuider builder){
            return builder
                .WithValue("Strasse", "Seppgasse 24")
                .WithValue("TuerNr", 12)
                .WithValue("Postleitzahl", 1337)
                .WithValue("Ort", "Badgerhausen")
                .Build();
        })
        .WithJsonObjectType(JsonObjectType_Object)
        .WithParent(person)
        .Build();

    std::string personString = person->ToJsonString();

    cout << personString << endl;

    auto intTest = Create::A.JsonValue()
        .WithValue(1337)
        .Build();

    auto stringTest = Create::A.JsonValue()
        .WithValue("1337")
        .Build();

    cout << intTest->ToJsonString() << " - " << stringTest->ToJsonString() << endl;

    std::string eineErkenntnis = "   Ich mag kekse.   ";
    std::string nochEineErkenntnis = "Ich mag kekse.";

    stringhelper::Trim(eineErkenntnis);
    stringhelper::Trim(nochEineErkenntnis);

    cout << "|" << eineErkenntnis << "| - |" << nochEineErkenntnis << "|" << endl;

    std::string conclusio = "    Kekse sind geil!     ";
    std::string conclusioCopy = stringhelper::TrimCopy(conclusio);

    cout << "|" << conclusio << "| - |" << conclusioCopy << "|" << endl;
    cout << "StartsWith: " << stringhelper::StartsWith("ebene", "eb") << " - " << "EndsWith: " << stringhelper::EndsWith("ebene", "ne") << endl;


    cout << endl << "TestObjectSegmenter(personString)" << endl;
    TestObjectSegmenter(personString);

    cout << endl << "TestJsonParser(personString)" << endl;
    TestJsonParser(personString);

    cout << endl << "TestArrayParser()" << endl;
    TestArrayParser();

    cout << endl << "TestShare()" << endl;
    TestShare();

    delete person;
    delete intTest;
    delete stringTest;

    return 0;
}

void TestObjectSegmenter(std::string value)
{
    std::vector<std::string> segments;

    JsonObjectSegmenter segmenter;
    segmenter.SegmentJsonString(segments, value, JsonElementType_Object);
    segmenter.PrintSegments(&cout, segments);

    std::vector<std::string> firstNameSegments;
    segmenter.SegmentJsonString(firstNameSegments, segments[0], JsonElementType_KeyValuePair);
    segmenter.PrintSegments(&cout, firstNameSegments);

    std::vector<std::string> alterSegments;
    segmenter.SegmentJsonString(alterSegments, segments[1], JsonElementType_KeyValuePair);
    segmenter.PrintSegments(&cout, alterSegments);
}

void TestJsonParser(std::string value)
{
    JsonParser parser;
    JsonNode* root = parser.ParseJsonString(value);

    std::string result = root->ToJsonString();

    cout << result << endl;

    delete root;
}

void TestArrayParser()
{
    JsonParser parser;
    JsonNode* root = parser.ParseJsonString("[123,\"456\",{\"name\":\"BADGERS\"}]");

    std::string result = root->ToJsonString();

    cout << result << endl;

    delete root;
}

void TestShare()
{
    JsonParser parser;
    JsonNode* root = parser.ParseJsonString("[{\"Name\" : \"Microsoft\", \"Kuerzel\":\"MSFT\", \"entries\" : [{\"Datum\":\"27.03.2020\"},{\"Datum\":\"28.03.2020\"}] }]");

    std::string result = root->ToJsonString();

    cout << result << endl;

    delete root;
}
